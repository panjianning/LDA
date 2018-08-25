// Copyright (c) 2017, Baidu.com, Inc. All Rights Reserved
// This file is modified from Baidu's Familia Project

#ifndef LDA_MODEL_H
#define LDA_MODEL_H

#include "lda/utils.h"
#include "lda/vocab.h"
#include "lda/document.h"
#include "lda/log.h"

#include <unordered_map>
#include <utility>

namespace LDA {

struct WordProb {
    int id;
    float prob;
    bool operator<(const WordProb& other) const {
        return prob > other.prob;
    }
};

typedef std::vector<WordProb> WordDist;
typedef std::unordered_map<int, int> TopicDist;

class TopicModel {
public:
    TopicModel() = delete;

    virtual ~TopicModel() {
        Log::Debug("Deconstruct model");
    }

    TopicModel(int num_topics, const std::string& vocab_file, float alpha=0.1, 
        float beta=0.01);

    void set_topic_word_dist();

    inline int get_count_by(int word_id, int topic) const {
        const TopicDist& dist = _word_topic.at(word_id);
        if (dist.count(topic)) {
            return dist.at(topic);
        } else {
            return 0;
        }
    }

    inline int get_count_by(int topic) const {
        return _topic_sum.at(topic);
    }

    inline void add_token(Token& token) {
        TopicDist& dist = _word_topic.at(token.id);
        if (dist.count(token.topic)) {
            dist[token.topic]++;
        } else {
            dist[token.topic] = 1;
        }
        _topic_sum[token.topic]++;
    }

    inline void remove_token(Token& token) {
        TopicDist& dist = _word_topic.at(token.id);
        dist[token.topic]--;
        _topic_sum[token.topic]--;
    }

    inline int word_id(const std::string& word) const {
        return _vocab.get_word_id(word);
    }

    inline int num_topics() const {
        return _num_topics;
    }

    inline size_t vocab_size() const {
        return _vocab.size();
    }

    inline float alpha() const {
        return _alpha;
    }

    inline float alpha_sum() const {
        return _alpha_sum;
    }

    inline float beta() const {
        return _beta;
    }

    inline float beta_sum() const {
        return _beta_sum;
    }

    inline const Vocab& vocab() const {
        return _vocab;
    }

    inline const std::vector<WordDist>& topic_word() const {
        return _topic_word;
    }

private:
    std::vector<TopicDist> _word_topic;
    std::vector<WordDist> _topic_word;
    std::vector<int> _topic_sum;
    Vocab _vocab;
    int _num_topics;
    float _alpha;
    float _alpha_sum;
    float _beta;
    float _beta_sum;
};

}

#endif
