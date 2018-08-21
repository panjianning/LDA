// Copyright (c) 2017, Baidu.com, Inc. All Rights Reserved
// This file is modified from Baidu's Familia Project

#ifndef LDA_SAMPLER_H
#define LDA_SAMPLER_H

#include "lda/document.h"
#include "lda/model.h"
#include "lda/utils.h"
#include "lda/log.h"

#include <memory>

namespace LDA {

class Sampler {
public:
    virtual ~Sampler() {
        Log::Debug("Deconstruct sampler");
    }
    virtual void sample_doc(LDADoc& doc) = 0;
};

class GibbsSampler : public Sampler {
public:
    GibbsSampler(std::shared_ptr<TopicModel> model) : _model(model) {
    }
    void sample_doc(LDADoc& doc) override;
    
    GibbsSampler(const GibbsSampler&) = delete;
    GibbsSampler& operator=(const GibbsSampler&) = delete;
private:
    int sample_token(LDADoc& doc, Token& token);
    std::shared_ptr<TopicModel> _model;
};

}

#endif