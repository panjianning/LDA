# LDA
[![License](https://img.shields.io/pypi/l/Django.svg)](LICENSE)
[![Language](https://img.shields.io/badge/language-c%2B%2B-orange.svg)](src)

使用Collapsed Gibbs sampling训练的Latent Dirichlet Allocation模型。

数学推导在[LDA.pdf](https://github.com/PanJianning/LDA/edit/master/LDA.pdf)

## 动机
写这个项目是为了学习近似推断方法，Gibbs sampling和Variational Bayes。 原本是想参考sklearn的LDA实现，先实现online variational bayes版本的，但考虑到
Collapsed Gibbs sampling实现上更为简单，并发现百度的Familia项目可供参考，于是就有了此项目。Familia是加载百度自己训练好的模型，然后对新数据进行inference。而本项目可以基于自己的数据训练LDA模型。另外，对Familia做了精简，不再依赖glogs, protobuf等库。

## 编译
需支持C++14

只在Windows 10上进行了测试， Makefile也是针对Windows系统写的，生产main.exe。
```shell
make main
```
## 测试数据
测试数据是自己从维基百科获取的一些文章，主题包括不同领域的人物，乐队，公司等。

数据使用了GB2313编码存储

运行下面命令
```python
python tools/jieba_cut.py
```
可生成模型需要的输入文档和词汇表

## 结果
3626个词，47篇文档，15个主题，进行1000次迭代

下面为得到的15个主题的前15个主题词
```
[Topic 00] 等 公司 集团 超过 成立 全球 约 及 清华 阿里巴巴 至 管理 人民币 亿元 首席
[Topic 01] 中国 大陆 腾讯 网易 知乎 广州 创立 大话西游 开发 突破 QQ 万 平台 业务 超
[Topic 02] 纽约 杂志 版 出版 发行 起 连线 为 客 欧洲 对 年代 Time 广告 政治
[Topic 03] Google 用户 Twitter 其他 Facebook 互联网 服务 同时 注册 可以 截至 搜索 亿 使用 网站
[Topic 04] 的 在 和 是 美国 与 于 并 也 英语 被 获得 上 中 有
[Topic 05] 专辑 了 乐队 单曲 公告牌 冠军 唱片 发行 排行榜 单曲榜 百强 他们 这 音乐 位
[Topic 06] 电影 普里 及 迪卡 最佳 达蒙 奥 男演员 系列 出演 最高 克鲁斯 惊悚片 山达基 人员
[Topic 07] 及 计算机 计算机科学 人工智能 领域 工作 万维网 因 斯坦福大学 贡献 图灵奖 分析 科学家 伯纳斯 李
[Topic 08] NBA 球员 赛季 联盟 价值 篮球 效力 哈登 入选 最有 运动员 次 后卫 职业 火箭
[Topic 09] 作品 等 奥威尔 其 福克纳 小说 不 广泛 作家 过 皆 冯 表现 威廉 自己
[Topic 10] 专辑 她 张 单曲 发行 泰勒 全球 超过 斯威夫特 音乐 发布 取得 林肯公园 佩里 艾薇儿
[Topic 11] 总统 俄罗斯 普京 人民日报 从 担任 至 选举 参议员 机关报 报名 奥巴马 任 晋冀鲁豫 r
[Topic 12] 他 了 爱因斯坦 理论 图灵 篇 现代 密码 英国 牛顿 机器 研究 相对论 发展 政府
[Topic 13] 年 大学 学校 学院 为 卡内基 校园 中山大学 国立 位于 清华大学 世界 名 拥有 斯坦福
[Topic 14] 年 月 了 日 他 为 成为 曾 生于 新 影响 称为 公司 进入 赢得
```
## 参考
[Finding scientific topics](http://psiexp.ss.uci.edu/research/papers/sciencetopics.pdf)
