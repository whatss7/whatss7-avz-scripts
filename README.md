# whatss7-avz-scripts

## 说明

使用 [AvZ 2](https://github.com/vector-wlc/AsmVsZombies) 编写的键控脚本。请注意 AvZ 2 与 AvZ 1 区别很大，下列脚本不适用于 AvZ 1 用户。

以下说明“无伤”的，指玉米加农炮、忧郁菇等输出植物无伤，南瓜头和垫材等可能受伤。

## 已完成的阵型

### PE 经典十二炮 (P6)

[已完成，挂机50f无伤](jd12p.cpp)

P6: PP | PP | PP | PP | PP | PP  (6, 6, 6, 6, 6, 6)

键控入门脚本。

### PE 经典八炮 (P4)

[已完成，挂机50f无伤](jd8p-P4c.cpp)

P4: ccccPP | ccccPP | ccccPP | ccccPP  (875, 875, 875, 875)

使用垫材在9列垫舞王。若使用9秒波长，冰道盖过9列无法放置垫材，而在8列放置或不放置都可能漏炸伴舞。

### PE 经典十炮 (P6)

[已完成，挂机50f无伤](jd10p-P6N.cpp)

P6: PP | PP | PP | PP | PP | N  (6, 6, 6, 6, 6, 6)

在键控难以拖收尾的情况下，炮炸珊瑚和炮炸蹦极都容易导致炮转不过来，所以使用叶子保护伞保护高坚果，冰消珊瑚。掉阳光较多，偷了花。

### PE 经典十炮 (S6)

[已完成，挂机50f无伤](jd10p-S6.cpp)

S6: I-PP | PP | PP | PP | PP  (12, 6, 6, 6, 6)

开始时考虑的是在7列存冰+偷花，但撑杆就啃炮了；于是手动规划了冰的种植，改为1列偷花。

### PE 经典四炮 (ch4)

[已完成，不可挂机](jd4p.cpp)

ch4: I-PP | I-PP (18, 18)

要挂机的话，需要分有红、有白、无白三种情况写，目前确保有红的情况下，手工收尾也行，但有概率小鬼啃冰翻车。

### PE 经典八炮 (ch6)

[已完成，不可挂机](jd8p-ch6.cpp)

ch6: I-PP | PP | I-PP | PP  (12, 6, 12, 6)

12秒冰波可以守7列，在7列存冰。如果零冰开的话存冰比较极限，收尾必须手动拖满。
没有核弹首代是因为w9如果是加速波，收尾很难处理撑杆。
手工收尾在有红眼的情况下已经完成。

### PE 经典八炮 (ch5)

[已完成，不可挂机](jd8p-ch5.cpp)

ch6: I-PP | IPP-PP | PP  (15, 15, 6)

在底线存冰，第一个冰波矿工冰杀，第二个冰波矿工热过渡处理，加速波矿工直接炸掉。
手工收尾在有红眼的情况下已经完成。

### PE 经典八炮 (P5u)

[已完成，挂机50f无伤](jd8p-P5uN.cpp)

P5u-N: ccccPP | ccccPP | ccccPP | ccccPP | N  (751, 751, 751, 751, 600)

使用垫材在9列垫舞王。垫材冷却751cs因此无法使用7秒波长。

## 计划完成的阵型

### PE 二十四炮 (ch6)

[未完成](24p-ch6.cpp)

ch6: IPP-PPDD | PPSSDD | IPP-PPDD | PPSSDD (12, 6, 12, 6)

还什么都没写...

### DE 双冰六炮 (ch5)

[未完成](de-2i6p-ch5.cpp)

ch5: I-PP | I-PP | PP (15, 15, 6)

存冰恢复有问题，使用核弹首代会炸掉梯子，暂时弃坑。

