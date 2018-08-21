// Copyright (c) 2017, Baidu.com, Inc. All Rights Reserved
// This file is modified from Baidu's Familia Project

#include "lda/document.h"
#include "log.h"

namespace LDA {

void LDADoc::init(int num_topics) {
    _num_topics = num_topics;
    _tokens.clear();
    _topic_sum.resize(_num_topics, 0);
}

void LDADoc::add_token(const Token& token) {
    Log::CHECK(token.topic >= 0 && token.topic < _num_topics, 
        "Topic %d out of range!", token.topic);
   _tokens.push_back(token);
   _topic_sum[token.topic]++;
}
  
void LDADoc::set_topic(int index, int new_topic) {
    Log::CHECK(new_topic >= 0 && new_topic <_num_topics, 
        "Topic %d out of range!", new_topic);
    int old_topic = _tokens[index].topic;
    if (new_topic == old_topic) {
        return;
    }
    _tokens[index].topic = new_topic;
    _topic_sum[old_topic]--;
    _topic_sum[new_topic]++;
}

}