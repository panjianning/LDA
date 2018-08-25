// Copyright (c) 2017, Baidu.com, Inc. All Rights Reserved
// This file is modified from Baidu's Familia Project

#include "lda/sampler.h"
#include "lda/log.h"

namespace LDA {

void GibbsSampler::sample_doc(LDADoc& doc) {
    int new_topic = -1;
    Token new_token;
    for (size_t i = 0; i < doc.size(); ++i) {
        Token& token = doc.token(i);
        new_topic = sample_token(doc, token);
        doc.set_topic(i, new_topic);
        new_token = {new_topic, token.id};
        _model->add_token(new_token);
    }
}

int GibbsSampler::sample_token(LDADoc& doc, Token& token) {
    int num_topics = _model->num_topics();
    std::vector<float> accum_prob(num_topics, 0.0);
    float prob = 0.0, sum = 0.0;
    float a = 0.0; // count_topic_k_in_this_doc
    float b = 0.0; // count_token_is_topic_k
    float c = 0.0; //count_topic_k
    _model->remove_token(token);

    for (int t = 0; t < num_topics; ++t) {
        a = doc.topic_sum(t) + _model->alpha();
        b = _model->get_count_by(token.id, t) + _model->beta();
        c = _model->get_count_by(t) + _model->beta_sum();
    
        prob = a * b / c;
        sum += prob;
        accum_prob[t] = (t == 0 ? prob : accum_prob[t - 1] + prob);
    }

    double dart = rand() * sum;
    return std::lower_bound(accum_prob.begin(), accum_prob.end(), dart) - accum_prob.begin();

}

}
