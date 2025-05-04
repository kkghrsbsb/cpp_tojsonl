#pragma once

#include "converter.h"
#include <string>

class ParquetConverter : public Converter {
public:
    // 读取 parquet 文件中的 text 字段列，转为 JSONL
    void convert(const std::string& input_path, const std::string& output_path) override;
};
