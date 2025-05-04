#pragma once

#include <string>

class Converter {
public:
    virtual ~Converter() = default;
    // 将输入文件转换为 JSONL 格式
    virtual void convert(const std::string& input_path, const std::string& output_path) = 0;
};
