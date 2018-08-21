// Copyright (c) 2018, Jianning Pan. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "trainer.h"
#include <memory>

namespace LDA {

Trainer::Trainer(TopicModel* model, SamplerType type) 
    :Trainer(std::shared_ptr<TopicModel>(model), type) {
}

Trainer::Trainer(std::shared_ptr<TopicModel> model, SamplerType type) {
    _model = model;
    if (type == SamplerType::GibbsSampling) {
        Log::Info("Use GibbsSampling");
        _sampler = std::unique_ptr<Sampler>(new GibbsSampler(_model));
    } else if (type == SamplerType::MetropolisHastings) {
        Log::Info("Use MetropolisHastings");
        // not implemented
        // _sampler = std::unique_ptr<Sampler>(new MHSampler(_model));
    }
}

void Trainer::init_docs(std::vector<std::vector<std::string> >& raw_docs) {
    for(auto& raw_doc : raw_docs) {
        LDADoc doc(_model->num_topics());
        doc.set_alpha(_model->alpha());
        for (const auto& token : raw_doc) {
            int id = _model->term_id(token);
            if (id != OOV) {
                int init_topic = rand_k(_model->num_topics());
                doc.add_token({init_topic, id});
                _model->insert_word_topic(id, init_topic);
            } else {
                // Log::Debug("'%s' not in vocabulary, ignored.", token.c_str());
            }
        }
        _docs.emplace_back(doc);
    }
    Log::Info("Number of docs: %d", _docs.size());
    Log::Info("Init docs done");
}

void Trainer::train(std::vector<std::vector<std::string> >& raw_docs, int max_iter) {
    fix_random_seed();
    init_docs(raw_docs);
    Log::Info("Training...");
    int iter = 1;
    while(iter <= max_iter) {
        for (auto& doc : _docs) {
            _sampler->sample_doc(doc);
        }
        iter++;
    }
    Log::Info("Model trained.");
    _model->init_topic_word_dist();
}


}