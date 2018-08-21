# Copyright (c) 2018, Jianning Pan. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import jieba
import os
import re

# remove non-chinese and non-letter character
def clean(text):
    reg_chinese = re.compile(r'[^\u4e00-\u9fa5a-zA-Z]+')
    text = re.sub(reg_chinese, ' ', text)
    return text

def tokenize(input_dir, output_docs_path="docs.auto.txt", 
             output_vocab_path="vocab.auto.txt"):
    vocab = set()
    file_list = os.listdir(input_dir)
    all_docs = []
    for file in file_list:
        path = os.path.join(input_dir, file)
        with open(path, 'rt') as f:
            lines = f.readlines()
            content = ' '.join(lines)
            content = clean(content)
            doc = list(jieba.cut(content))
            all_docs.append(' '.join(doc))
        for word in doc:
            if word not in vocab:
                vocab.add(word)

    with open(output_docs_path,'wt') as f:
        for doc in all_docs:
            f.write(doc+'\n')

    with open(output_vocab_path, 'wt') as f:
        for word in vocab:
            f.write(word+'\n')

if __name__ == '__main__':
    tokenize(r"C:\Home\代码\LDA\raw_docs")