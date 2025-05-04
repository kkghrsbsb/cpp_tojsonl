#include "parquet_converter.h"
#include <arrow/api.h>
#include <arrow/io/api.h>
#include <arrow/table.h>
#include <arrow/type.h>
#include <arrow/array.h>
#include <parquet/arrow/reader.h>
#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>

void ParquetConverter::convert(const std::string& input_path, const std::string& output_path) {
    std::shared_ptr<arrow::io::ReadableFile> infile;
    auto status = arrow::io::ReadableFile::Open(input_path);
    if (!status.ok()) {
        std::cerr << "无法打开 Parquet 文件: " << input_path << "，错误信息: " << status.status().ToString() << std::endl;
        return;
    }
    infile = status.ValueOrDie();

    auto result_reader = parquet::arrow::OpenFile(infile, arrow::default_memory_pool());
    if (!result_reader.ok()) {
        std::cerr << "无法创建 Parquet 读取器: " << result_reader.status().ToString() << std::endl;
        return;
    }
    std::unique_ptr<parquet::arrow::FileReader> reader = std::move(result_reader).ValueOrDie();

    std::shared_ptr<arrow::Table> table;
    auto st = reader->ReadTable(&table);
    if (!st.ok()) {
        std::cerr << "读取表失败: " << st.ToString() << std::endl;
        return;
    }

    std::shared_ptr<arrow::ChunkedArray> selected_col;
    std::string selected_col_name;
    for (int i = 0; i < table->num_columns(); ++i) {
        auto col = table->column(i);
        if (col->type()->id() == arrow::Type::STRING) {
            selected_col = col;
            selected_col_name = table->field(i)->name();
            break;
        }
    }

    if (!selected_col) {
        std::cerr << "未找到任何字符串类型的列，文件: " << input_path << std::endl;
        return;
    }

    std::ofstream ofs(output_path);
    if (!ofs.is_open()) {
        std::cerr << "无法打开输出文件: " << output_path << std::endl;
        return;
    }

    for (int c = 0; c < selected_col->num_chunks(); ++c) {
        auto chunk = std::dynamic_pointer_cast<arrow::StringArray>(selected_col->chunk(c));
        if (!chunk) {
            std::cerr << "chunk 不是 StringArray 类型，跳过该块。" << std::endl;
            continue;
        }

        for (int64_t i = 0; i < chunk->length(); ++i) {
            if (chunk->IsNull(i)) continue;
            std::string val = chunk->GetString(i);
            nlohmann::json j;
            j["text"] = val;
            ofs << j.dump() << "\n";
        }
    }

    std::cout << "Parquet 转换完成: " << input_path << " -> " << output_path << std::endl;
}