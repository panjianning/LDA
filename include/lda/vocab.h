// Copyright (c) 2017, Baidu.com, Inc. All Rights Reserved
// This file is modified from Baidu's Familia Project

#ifndef LDA_VOCAB_H
#define LDA_VOCAB_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace LDA {

//Out Of Vocabulary
constexpr int OOV = -1;

class Vocab {
public:
    Vocab() = default;

    void load(const std::string& vocab_file);
    
    int get_word_id(const std::string& word) const;

    inline std::string get_word(int id) const {
        return _id2word[id];
    }

    inline size_t size() const {
        return _word2id.size();
    }

    Vocab(const Vocab&) = delete;
    Vocab& operator=(const Vocab&) = delete;
private:
    std::unordered_map<std::string, int> _word2id;
    std::vector<std::string> _id2word;
};

}

#endif
