// Copyright (c) 2017, Baidu.com, Inc. All Rights Reserved
// This file is modified from Baidu's Familia Project

#include "lda/sampler.h"
#include "lda/log.h"

namespace LDA {

void GibbsSampler::sample_doc(LDADoc& doc) {
    int new_topic = -1;
    int old_topic = -1;
    int word_id = -1;
    for (size_t i = 0; i < doc.size(); ++i) {
        word_id = doc.token(i).id;
        old_topic = doc.token(i).topic;
        new_topic = sample_token(doc, doc.token(i));
        if (old_topic == new_topic) continue;
        doc.set_topic(i, new_topic);
        _model->update_word_topic(word_id, old_topic, new_topic);
    }
}

int GibbsSampler::sample_token(LDADoc& doc, Token& token) {
    int old_topic = token.topic;
    int num_topics = _model->num_topics();
    std::vector<float> prob(num_topics, 0.0);
    // use for sampling from Cat(prob)
    std::vector<float> accum_prob(num_topics, 0.0);
    float sum = 0.0;
    float dt_alpha = 0.0; // count_topic_k_in_this_doc
    float wt_beta = 0.0; // count_token_is_topic_k
    float t_sum_beta_sum = 0.0; //count_topic_k
    for (int t = 0; t < num_topics; ++t) {
        dt_alpha = doc.topic_sum(t) + _model->alpha();
        wt_beta = _model->word_topic(token.id, t) + _model->beta();
        // Log::Debug("%f %f",dt_alpha,wt_beta);
        t_sum_beta_sum = _model->topic_sum(t) + _model->beta_sum();
        if (t == old_topic) {
            dt_alpha -= 1;
            wt_beta -= 1;
            t_sum_beta_sum -= 1;
        }

        // Log::CHECK(dt_alpha>=0,"dt_alpha < 0!");
        // Log::CHECK(wt_beta>=0,"wt_beta < 0!");
        // Log::CHECK(t_sum_beta_sum>=0,"t_sum_beta_sum < 0!");

        prob[t] = dt_alpha * wt_beta / t_sum_beta_sum;
        sum += prob[t];
        accum_prob[t] = (t == 0 ? prob[t] : accum_prob[t - 1] + prob[t]);
    }

    double dart = rand() * sum;
    if (dart <= accum_prob[0]) {
        return 0;
    }
    for (int t = 1; t < num_topics; ++t) {
        if (dart > accum_prob[t - 1] && dart <= accum_prob[t]) {
            return t;
        }
    }
    return num_topics - 1;
}

}