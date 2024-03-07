# whatss7-avz-scripts

## 说明

使用 [AvZ 2](https://github.com/vector-wlc/AsmVsZombies) 编写的键控脚本。请注意 AvZ 2 与 AvZ 1 区别很大，下列脚本不适用于 AvZ 1 用户。

以下说明“无伤”的，指玉米加农炮、忧郁菇等输出植物无伤，南瓜头和垫材等可能受伤；或者即使受伤，也有能力通过换炮等方式解决。

- 标题后跟有“挂机”的，指已经测试无操作挂机100f无伤。
  - “挂机\*”表示挂机测试时采用均匀填充的极限出怪。
  - “挂机\*\*”表示特定情况下可挂机，具体查看阵型对应说明。
  - 与“不稳定”一起标注时，挂机仅测试2f，但理论上可挂机。
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
    - [PE 空炸十八炮 P6 挂机](#pe-空炸十八炮-p6-挂机)
    - [PE 玉米八炮 对ch6](#pe-玉米八炮-对ch6)
    - [PE 万四炮 ch4-N 原创 手动 不稳定](#pe-万四炮-ch4-n-原创-手动-不稳定)
    - [PE 全金属四炮 ch4-N 手动 不稳定](#pe-全金属四炮-ch4-n-手动-不稳定)
    - [DE 连拦十四炮 对ch6](#de-连拦十四炮-对ch6)
    - [PE 二十四炮 P6-2I 挂机](#pe-二十四炮-p6-2i-挂机)
    - [NE 舞夜惊魂 P6](#ne-舞夜惊魂-p6)
  - [计划完成的阵型](#计划完成的阵型)
    - [FE 新磁铁四炮 对C6u 未完成](#fe-新磁铁四炮-对c6u-未完成)


## 已完成的阵型

### PE 空炸十八炮 P6 挂机

[P6: PPD | PPD | PPD | PPD | PPD | PPD (6, 6, 6, 6, 6, 6)](./PE空炸十八炮/ab18p.cpp)

为什么这阵能是键控二级阵呢...

自然出怪是真的猛，3炮+1核都能刷新延迟（虽然是因为快速关大量僵尸还没入场）

### PE 玉米八炮 对ch6

[对ch6: I-PP | PP | I-PP | PP (12, 6, 12, 6)](./PE玉米八炮/corn8p.cpp)

朴素的ch6。因为玉米的存在，垫红眼时会出现红眼前进的情况，在极端情况下会翻车，但是概率相对较小（不代表没有）。

### PE 万四炮 ch4-N 原创 手动 不稳定

[ch4-N: I-PP | I-PP | N | PP (18, 18, 12, 6)](./PE万四炮/wan4p.cpp)

第一个原创造型（水）阵。ch4-N总给我一种怪感觉，就觉得为什么不C6u呢，不是更省冰吗...不过用起来确实是好用。

### PE 全金属四炮 ch4-N 手动 不稳定

[ch4-N: I-PP | I-PP | N | PP (18, 18, 12, 6)](./PE全金属四炮/metal4p.cpp)

存冰位置也太...不过基本就是复制之前的ch4-N了。

### DE 连拦十四炮 对ch6

[对ch6: IP-Pcc/PD | P/Bd | IP-Pcc/PD | P/Bd](./DE连拦十四炮/bd14p.cpp)

需要连拦时，不可完美预判冰，否则部分冰波巨人炸不到，最后会投出减速小鬼啃炮。

### PE 二十四炮 P6-2I 挂机

[P6-2I: PPDD | PPI | PPSSDD | PPDD | PPI | PPSSDD (6, 6, 6, 6, 6, 6)](./PE二十四炮/pe24p.cpp)

万阵之王！完美公式！

但是有极小概率翻车：没有红眼时旗帜波有小概率刷新延迟；有红眼时 PPI 波有小概率刷新延迟；精舞有小概率未知原因延迟生效导致伴舞啃炮。

### NE 舞夜惊魂 P6

[P6: cPP | cPP | cPP | cPP | cPP | cPP (6, 6, 6, 6, 6, 6)](./NE舞夜惊魂/dance12p.cpp)

听说是写阵五分钟，开局两小时的阵。写了个开局脚本，能选择两个~~幸运~~伴舞传到指定位置，还能调节传送的位置。

由于开局的那一帧（就是点击 `Continue` 后的那一帧）无法被女仆秘籍覆盖，有概率伴舞前进1px，然后当场翻车，因此脚本也加入了把伴舞拉回1px的修改（节操--）。这应该可以通过控制点击 `Continue` 时机解决，但我不会（

考级指南里写的Pc一度让我以为是垫材垫撑杆，想了半天没搞懂，然后看了演示之后发现，是cP垫舞王，然后在伴舞出土前连撑杆一起炸掉。

不稳定在于，如果收尾的时候边路出红眼，而旁路不出红眼，边路巨人没减速到的话旧会砸炮翻车。

## 计划完成的阵型

### FE 新磁铁四炮 对C6u 未完成

[对C6u: ICC-PA | N | IaC-PA' | PP (19, 6, 19, 6)](./FE新磁铁四炮/xct4p.cpp)

感觉键控窝瓜超出我现在的能力范围了，这个阵以后再说吧。
