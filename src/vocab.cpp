// Copyright (c) 2017, Baidu.com, Inc. All Rights Reserved
// This file is modified from Baidu's Familia Project

#include "lda/vocab.h"
#include "lda/utils.h"
#include "lda/log.h"

#include <fstream>
#include <vector>

namespace LDA {

int Vocab::get_id(const std::string& word) const {
    auto it = _term2id.find(word);
    return it == _term2id.end()? OOV : it->second;
}

void Vocab::load(const std::string& vocab_file) {
    _term2id.clear();
    std::ifstream fin(vocab_file, std::ios::in);
    if (!fin.is_open()) {
        Log::Warning("Failed to open vocab_file!");
        return;
    }
    
    Log::Info("Loading vocab from: %s", vocab_file.c_str());

    _id2term.clear();

    std::string term;
    int id = 0;
    while (getline(fin, term)) {
        if (_term2id.find(term) != _term2id.end()) {
            Log::Warning("Duplicate word [%s] in vocab file",term.c_str());
            continue;
        }
        _term2id[term] = id;
        _id2term.push_back(term);
        id++;
    }
    fin.close();
    Log::Info("Load vocabulary success! #vocabulary size = %d", size());
}

}