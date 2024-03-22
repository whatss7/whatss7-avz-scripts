# whatss7-avz-scripts

## 说明

使用 [AvZ 2](https://github.com/vector-wlc/AsmVsZombies) 编写的键控脚本。请注意 AvZ 2 与 AvZ 1 区别很大，下列脚本不适用于 AvZ 1 用户。

以下说明“无伤”的，指玉米加农炮、忧郁菇等输出植物无伤，南瓜头和垫材等可能受伤；或者即使受伤，也有能力通过换炮等方式解决。

- 标题后跟有“挂机”的，指已经测试无操作挂机100f无伤。
  - 与“不稳定”一起标注时，挂机仅测试2f，但理论上可挂机。
  - “挂机\*”表示特定情况下可挂机，具体查看阵型对应说明。
- 标题后跟有“手动”的，指此脚本有必要的手动操作；否则，默认至少能挂机完成一次全难度极限出怪。
- 标题后跟有“不稳定”的，指虽然已经2f无伤，但是存在明显缺陷。
- 标题后跟有“未完成”的，指此脚本还未写完。

[键控考级阵脚本汇总](./level.md)

[目录中没有的旧阵型在此处查阅](./旧阵型/README.md)

## 目录

- [whatss7-avz-scripts](#whatss7-avz-scripts)
  - [说明](#说明)
  - [目录](#目录)
  - [已完成的阵型](#已完成的阵型)
    - [PE 全金属四炮 ch4-N 手动 不稳定](#pe-全金属四炮-ch4-n-手动-不稳定)
    - [NE 土豆四炮 邻C7u](#ne-土豆四炮-邻c7u)
  - [计划完成的阵型](#计划完成的阵型)
    - [FE 新磁铁四炮 对C6u 未完成](#fe-新磁铁四炮-对c6u-未完成)


## 已完成的阵型

### PE 全金属四炮 ch4-N 手动 不稳定

[ch4-N: I-PP | I-PP | N | PP (18, 18, 12, 6)](./PE全金属四炮/metal4p.cpp)

存冰位置也太...不过基本就是复制之前的ch4-N了。

### NE 土豆四炮 邻C7u

[邻C7u: I-PP | I-PP | N | AA'a | PP (16, 19, 6, 6.9, 6)](./NE土豆四炮/potato4p.cpp)

使用智能脚本，3列出现极慢矿工时，推迟土豆雷的放置时机防止短冰波矿工啃雷。一列漏炸的跳跳会被辣椒烧掉。

唯一的问题就是窝瓜太能演了，AA'a波疯狂刷新延迟...

## 计划完成的阵型

### FE 新磁铁四炮 对C6u 未完成

[对C6u: ICC-PA | N | IaC-PA' | PP (19, 6, 19, 6)](./FE新磁铁四炮/xct4p.cpp)

感觉键控窝瓜超出我现在的能力范围了，这个阵以后再说吧。

