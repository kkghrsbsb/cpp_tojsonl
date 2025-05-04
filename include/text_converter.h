#pragma once

#include "converter.h"

class TextConverter : public Converter {
public:
    // 把每一行文本作为一个 JSONL 条目输出
    void convert(const std::string& input_path, const std::string& output_path) override;
};
