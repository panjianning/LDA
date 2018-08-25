// Copyright (c) 2017, Baidu.com, Inc. All Rights Reserved
// This file is modified from Baidu's Familia Project

#include "lda/model.h"
#include "lda/log.h"
#include "lda/utils.h"

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

namespace LDA {

TopicModel::TopicModel(int num_topics, const std::string& vocab_file, float alpha, 
        float beta) {
    _num_topics = num_topics;
    _alpha = alpha;
    _beta = beta;
    _alpha_sum = _alpha * _num_topics;
    _topic_sum = std::vector<int>(_num_topics, 0);

     _vocab.load(vocab_file);
    
    _beta_sum = _beta * _vocab.size();
    _word_topic.clear();
    _word_topic.resize(_vocab.size());

    Log::Info("Model Info: #num_topics = %d  #vocab_size = %d  #alpha = %f  #beta = %f",
        _num_topics, _vocab.size(), _alpha, _beta);
}


void TopicModel::set_topic_word_dist() {
    _topic_word.clear();
    _topic_word.resize(_num_topics);
    for(size_t word_id = 0; word_id < _vocab.size(); word_id++) {

        TopicDist& topic_dist = _word_topic.at(word_id);

        for(auto it = topic_dist.cbegin(); it != topic_dist.cend(); it++) {
            int topic_id = it->first;
            int topic_count = it->second;
            // Log::Info("%d", _topic_sum[topic_id] + _beta_sum);
            float prob = (_beta+topic_count)/(_topic_sum[topic_id]+_beta_sum);
            if(prob > 0.0) {
                _topic_word[topic_id].push_back({static_cast<int>(word_id), prob});
            }
        }
    }
    for(int tid = 0; tid < _num_topics; tid++) {
        std::sort(_topic_word[tid].begin(), _topic_word[tid].end());
    }
}

}
