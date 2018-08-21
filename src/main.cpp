// Copyright (c) 2018, Jianning Pan. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "lda/vocab.h"
#include "lda/log.h"
#include "lda/document.h"
#include "lda/model.h"
#include "lda/trainer.h"
#include "utils.h"

#include <iostream>
#include <cstdio>
#include <memory>

using namespace LDA;

int main(int argc, char const *argv[]) {
    
    Log::ResetLogLevel(LogLevel::Info);

    int num_topic;
    std::cout << "num_topic: ";
    std::cin >> num_topic;
    int max_iter;
    std::cout << "max_iter: ";
    std::cin >> max_iter;

    float alpha = 0.1, beta = 0.01;
    std::shared_ptr<TopicModel> model = std::make_shared<TopicModel>(num_topic, 
        "vocab.auto.txt", alpha, beta);
    Trainer trainer(model);
    
    std::vector<std::vector<std::string> > raw_docs;
    load_docs("docs.auto.txt",raw_docs);
    trainer.train(raw_docs, max_iter);

    auto topic_word = model->topic_word();
    auto& vocab = model->vocab();
    for(int tid = 0; tid < num_topic; tid++) {
        printf("[Topic %02d] ", tid);
        int cnt = 0;
        for(auto& word_prob : topic_word[tid]) {
            std::cout << vocab.get_word(word_prob.id) << " "; // << word_prob.prob << " ";
            cnt++;
            if(cnt >= 15) break;
        }
        std::cout << "\n\n";
    }
    return 0;
}