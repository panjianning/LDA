// Copyright (c) 2017, Baidu.com, Inc. All Rights Reserved
// This file is modified from Baidu's Familia Project

#ifndef LDA_DOCUMENT_H
#define LDA_DOCUMENT_H

#include <algorithm>
#include <string>
#include <vector>

namespace LDA {

struct Topic {
    int tid;
    double prob;
    bool operator<(const Topic& t) const {
        return prob > t.prob;
    }
};

struct Token {
    int topic;
    int id;
};

class LDADoc {
public:
    LDADoc() = default;
   
    explicit LDADoc(int num_topics) {
        init(num_topics);
    }
  
    void init(int num_topics);
  
    void add_token(const Token& token);
  
    void set_topic(int index, int new_topic);

    inline Token& token(size_t index) {
        return _tokens[index];
    }

    inline void set_alpha(float alpha) {
        _alpha = alpha;
    }

    inline size_t size() const {
        return _tokens.size();
    }

    inline size_t topic_sum(int topic_id) const {
        return _topic_sum[topic_id];
    }

protected:
    float _alpha;
    int _num_topics;
    std::vector<Token> _tokens;
    std::vector<int> _topic_sum;
};

}

#endif