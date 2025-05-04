#include "text_converter.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

void TextConverter::convert(const std::string& input_path, const std::string& output_path) {
    std::ifstream ifs(input_path);
    if (!ifs) {
        std::cerr << "无法打开输入文件: " << input_path << std::endl;
        return;
    }
    std::ofstream ofs(output_path);
    if (!ofs) {
        std::cerr << "无法打开输出文件: " << output_path << std::endl;
        return;
    }
    std::string line;
    while (std::getline(ifs, line)) {
        nlohmann::json j;
        j["text"] = line;
        ofs << j.dump() << "\n";
    }
}