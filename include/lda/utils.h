// Copyright (c) 2017, Baidu.com, Inc. All Rights Reserved
// This file is modified from Baidu's Familia Project

#ifndef LDA_UTILS_H
#define LDA_UTILS_H

#include <atomic>
#include <ctime>
#include <random>
#include <string>
#include <fstream>
#include <sstream>

namespace LDA {

// 返回一个可在多线程下工作的随机数引擎
inline std::mt19937& local_random_engine() {
    struct engine_wrapper_t {
        std::mt19937 engine;
        engine_wrapper_t() {
            static std::atomic<unsigned long> x(0);
            std::seed_seq sseq = {x++, x++, x++, x++};
            engine.seed(sseq);
        }
    };
    static engine_wrapper_t r;
    return r.engine;
}

// 固定随机种子并重置分布
inline void fix_random_seed(int seed = 2147483647) {
    auto& engine = local_random_engine();
    engine.seed(seed);
    static std::uniform_real_distribution<double> distribution(0.0, 1.0); 
    distribution.reset(); // 重置分布，使下一次从分布中生成的样本不依赖过去的生成的状态
}

// 返回min~max之间的随机浮点数, 默认返回0~1的浮点数
inline double rand(double min = 0.0, double max = 1.0) {
    auto& engine = local_random_engine();
    static std::uniform_real_distribution<double> distribution(min, max);

    return distribution(engine);
}

// 返回[0, k - 1]之间的整型浮点数
inline int rand_k(int k) {
    return static_cast<int>(rand(0.0, 1.0) * k);
}

// 简单版本的split函数, 按照分隔符进行分割
void split(std::vector<std::string>& result, const std::string& text, char separator);

void load_docs(const std::string& docs_path, std::vector<std::vector<std::string> >& container);

}

#endif