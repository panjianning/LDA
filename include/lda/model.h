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

    void init_topic_word_dist();

    inline int term_id(const std::string& term) const {
        return _vocab.get_id(term);
    }

    inline TopicDist& word_topic(int term_id) {
        return _word_topic.at(term_id);
    }

    inline int word_topic(int word_id, int topic_id) const {
        const TopicDist& dist = _word_topic.at(word_id);
        if (dist.count(topic_id)) {
            return dist.at(topic_id);
        } else {
            return 0;
        }
    }

    inline void insert_word_topic(int word_id, int new_topic) {
        TopicDist& dist = _word_topic.at(word_id);
        if (dist.count(new_topic)) {
            dist[new_topic]++;
        } else {
            dist[new_topic] = 1;
        }
        _topic_sum[new_topic]++;
    }

    inline void update_word_topic(int word_id, int old_topic, int new_topic) {
        if (old_topic == new_topic) return;
        TopicDist& dist = _word_topic.at(word_id);
        dist[old_topic]--;
        _topic_sum[old_topic]--;
        insert_word_topic(word_id, new_topic);
    }

    inline uint64_t topic_sum(int topic_id) const {
        return _topic_sum.at(topic_id);
    }

    inline std::vector<uint64_t>& topic_sum() {
        return _topic_sum;
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
    std::vector<uint64_t> _topic_sum;
    Vocab _vocab;
    int _num_topics;
    float _alpha;
    float _alpha_sum;
    float _beta;
    float _beta_sum;
};

}

#endif