// Copyright (c) 2017, Baidu.com, Inc. All Rights Reserved
// This file is modified from Baidu's Familia Project

#include "lda/vocab.h"
#include "lda/utils.h"
#include "lda/log.h"

#include <fstream>
#include <vector>

namespace LDA {

int Vocab::get_word_id(const std::string& word) const {
    auto it = _word2id.find(word);
    return it == _word2id.end()? OOV : it->second;
}

void Vocab::load(const std::string& vocab_file) {
    _word2id.clear();
    _id2word.clear();

    std::ifstream fin(vocab_file, std::ios::in);
    if (!fin.is_open()) {
        Log::Warning("Failed to open vocab_file!");
        return;
    }
    
    Log::Info("Loading vocab from: %s", vocab_file.c_str());

    std::string word;
    int id = 0;
    while (getline(fin, word)) {
        if (_word2id.find(word) != _word2id.end()) {
            Log::Warning("Duplicate word [%s] in vocab file",word.c_str());
            continue;
        }
        _word2id[word] = id;
        _id2word.push_back(word);
        id++;
    }
    fin.close();
    Log::Info("Load vocabulary success! #vocabulary size = %d", size());
}

}
