#include <iostream>
#include <filesystem>
#include <string>
#include "text_converter.h"
#include "parquet_converter.h"

namespace fs = std::filesystem;

// 自定义 ends_with 函数
bool ends_with(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length()) return false;
    return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
}

// 创建与输入路径相对应的输出路径
fs::path get_output_path(const fs::path& input_dir, const fs::path& output_dir, const fs::path& input_file) {
    // 获取相对于输入目录的相对路径
    auto relative_path = fs::relative(input_file, input_dir);
    // 替换文件扩展名为.jsonl
    auto output_path = output_dir / relative_path;
    output_path.replace_extension(".jsonl");

    // 确保输出目录存在
    fs::create_directories(output_path.parent_path());

    return output_path;
}

int main() {
    const std::string input_dir = "input-dataset";
    const std::string output_dir = "output";

    if (!fs::exists(output_dir)) {
        fs::create_directory(output_dir);
    }

    TextConverter text_converter;
    ParquetConverter parquet_converter;

    // 递归遍历输入目录
    for (const auto& entry : fs::recursive_directory_iterator(input_dir)) {
        if (!entry.is_regular_file()) continue;

        const auto& file_path = entry.path();
        auto output_path = get_output_path(input_dir, output_dir, file_path);

        if (ends_with(file_path.string(), ".txt")) {
            std::cout << "正在转换文本文件: " << file_path << std::endl;
            text_converter.convert(file_path.string(), output_path.string());
        }
        else if (ends_with(file_path.string(), ".parquet")) {
            std::cout << "正在转换 Parquet 文件: " << file_path << std::endl;
            parquet_converter.convert(file_path.string(), output_path.string());
        }
        else {
            std::cout << "无法识别的文件格式: " << file_path << std::endl;
        }
    }

    std::cout << "转换完成。" << std::endl;
    return 0;
}