# whatss7-avz-scripts

## 说明

使用 [AvZ 2](https://github.com/vector-wlc/AsmVsZombies) 编写的键控脚本。请注意 AvZ 2 与 AvZ 1 区别很大，下列脚本不适用于 AvZ 1 用户。

## 已完成的阵型

### PE 经典十二炮 (P6)

[已完成，条件挂机](jd12p.cpp)

P6: PP | PP | PP | PP | PP | PP  (6, 6, 6, 6, 6, 6)

键控入门脚本，保证每轮都有红眼的情况下可挂机。

### PE 经典八炮 (ch6)

[已完成，不可挂机，未完全测试](jd8p-ch6.cpp)

ch6: I-PP | PP | I-PP | PP  (12, 6, 12, 6)

存冰恢复有一定问题。

### PE 经典八炮 (P4)

[已完成，不稳定挂机](jd8p-P4c.cpp)

P4: ccccPP | ccccPP | ccccPP | ccccPP  (9, 9, 9, 9)

使用垫材在8列垫舞王。为了消除不稳定性没有使用小喷菇和阳光菇，而是使用向日葵和大蒜，导致连续出舞王的情况下阳光损耗较大，但就算这样也会漏炸伴舞。缩短波长可以防止冰道盖过9列从而在9列垫舞王，以后再来翻修吧。

## 计划完成的阵型

### PE 二十四炮 (ch6)

[未完成](./24p-ch6.cpp)

ch6: IPP-PPDD | PPSSDD | IPP-PPDD | PPSSDD (12, 6, 12, 6)

还什么都没写...

### DE 双冰六炮 (ch5)

[未完成](./de-2i6p-ch5.cpp)

ch5: I-PP | I-PP | PP (15, 15, 6)

存冰恢复有问题，使用核弹首代会炸掉梯子，暂时弃坑。

### PE 经典四炮

[未完成](jd4p.cpp)

ch4: I-PP | I-PP (18, 18)

写了一半...

### PE 经典十炮 (S6)

[未完成](jd10p-S6.cpp)

S6: I-PP | PP | PP | PP | PP  (12, 6, 6, 6, 6)

小偷盯上高坚果的情况需要处理，不能冰杀只能炸掉，但炸掉炮的冷却转不过来。

