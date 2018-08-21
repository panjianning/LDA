// Copyright (c) 2018, Jianning Pan. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef LDA_TRAINER_H
#define LDA_TRAINER_H

#include <memory>

#include "lda/vocab.h"
#include "lda/document.h"
#include "lda/sampler.h"
#include "lda/model.h"
#include "lda/utils.h"
#include "lda/log.h"

namespace LDA {

enum class SamplerType {
    GibbsSampling,
    MetropolisHastings
};

class Trainer {
public:
    Trainer(TopicModel* model, SamplerType type = SamplerType::GibbsSampling);
    Trainer(std::shared_ptr<TopicModel> model, SamplerType type = SamplerType::GibbsSampling);
    ~Trainer() {
        // _sampler.reset(); //seems not have to add this line.
        Log::Debug("Deconstruct trainer");
    }
    
    inline std::shared_ptr<TopicModel> get_model() {
        return _model;
    }

    void train(std::vector<std::vector<std::string> >& raw_docs, int max_iter = 5);

private:
    void init_docs(std::vector<std::vector<std::string> >& raw_docs);

    std::shared_ptr<TopicModel> _model;
    std::unique_ptr<Sampler> _sampler;
    std::vector<LDADoc> _docs;
};

}

#endif