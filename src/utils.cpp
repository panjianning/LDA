// Copyright (c) 2017, Baidu.com, Inc. All Rights Reserved
// This file is modified from Baidu's Familia Project

#include "lda/utils.h"
#include "lda/log.h"
#include <fstream>


namespace LDA {

// 简单版本的split函数, 按照分隔符进行分割
void split(std::vector<std::string>& result, const std::string& text, char separator) {

    size_t start = 0;
    size_t end = 0;
    if (text.empty()) {
        return;
    }
    while ((end = text.find(separator, start)) != std::string::npos) {
        std::string substr = text.substr(start, end - start);
        result.push_back(std::move(substr));
        start = end + 1;
    }
    // NOTE: 如果输入没有分割字符，则返回原输入
    result.push_back(text.substr(start));

}

void load_docs(const std::string& docs_path, std::vector<std::vector<std::string> >& container) {
    std::fstream fin(docs_path, std::ios::in);
    if (!fin.is_open()) {
        Log::Fatal("Failed to read the docs, can't open %s", docs_path.c_str());
    }
    std::string line;
    while(getline(fin,line)) {
        std::vector<std::string> result;
        split(result, line, ' ');
        container.push_back(result);
    }
    fin.close();
}

}