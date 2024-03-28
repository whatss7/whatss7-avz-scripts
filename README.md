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
    - [NE 土豆四炮 邻C7u](#ne-土豆四炮-邻c7u)
    - [DE 前置八炮 ch5](#de-前置八炮-ch5)
    - [FE 新磁铁四炮 对C6u 不稳定](#fe-新磁铁四炮-对c6u-不稳定)
    - [PE 无冰瓜二十炮 P6-2I 挂机\*](#pe-无冰瓜二十炮-p6-2i-挂机)
    - [PE 玉米八炮 对ch6](#pe-玉米八炮-对ch6)
    - [RE 中开六炮 C6i-N 不稳定](#re-中开六炮-c6i-n-不稳定)
    - [RE 方块八炮 ch4\*](#re-方块八炮-ch4)
  - [计划完成的阵型](#计划完成的阵型)
    - [PE 全金属四炮 ch4-N 手动 不稳定](#pe-全金属四炮-ch4-n-手动-不稳定)


## 已完成的阵型

### NE 土豆四炮 邻C7u

[邻C7u: I-PP | I-PP | AA'a | N | PP (16, 19, 6, 6.9, 6)](./NE土豆四炮/potato4p.cpp)

使用智能脚本，3路出现极慢矿工时，推迟土豆雷的放置时机防止短冰波矿工啃雷。1路漏炸的跳跳会被辣椒烧掉。

唯一的问题就是窝瓜太能演了，AA'a波疯狂刷新延迟...

### DE 前置八炮 ch5

[ch5: I-PP | IPP-PP | PP (15, 15, 6)](./DE前置八炮/front8p.cpp)

极其简单的ch5，就没什么好说的了。

### FE 新磁铁四炮 对C6u 不稳定

[对C6u: ICC-PA | PP | ICC-PA'a | N (19, 6, 19, 6)](./FE新磁铁四炮/xct4p.cpp)

双边扎冰车，阳光消耗极大，但是需要这样守六列炮。防止窝瓜演戏，2路小丑冲家爆炸，在Aa'波使用大蒜控丑。

不稳定在于，1路巨人被辣椒解除减速后身位过于靠前，导致投出小鬼啃食底线炮；1路6路巨人砸5列植物；蹦极偷盲3-1/3-2/4-1/4-2。前两个考虑使用地刺大蒜垫一下，但后面一个只能考虑低压关补了，实在没有空位再带磁力菇了。

### PE 无冰瓜二十炮 P6-2I 挂机\*

[P6: PPDD | PPDD | PPI | PPDD | PPDD | PPI (6, 6, 6, 6, 6, 6)](./PE无冰瓜二十炮/winterless20p.cpp)

**\*: 本脚本挂机测试采用随机极限出怪。**

不想适配自然出怪了，刷新延迟处理得头疼，就极限出怪挂机了。

分为有红眼和无红眼，有红眼时采用P6-2I，无红眼时使用类似经典十八炮的节奏来回复阳光。

所以，键控二级了！

### PE 玉米八炮 对ch6

[对ch6: I-PP | PP | I-PP | PP (12.5, 6, 12.5, 6)](./PE玉米八炮/corn8p.cpp)

朴素的ch6。略微延长冰波让存冰有更多时间恢复，而w9/w19略微缩短冰波防止小丑炸核。

### RE 中开六炮 C6i-N 不稳定

[C6i-N: I-PP | I-PP | I-PP | N | PP (12.5, 12.5, 12.5, 6, 6.5)](./RE中开六炮/mo6p.cpp)

屋顶收尾特有的难绷，垫材只有花盆，收尾拖不满，C6i的用冰还多...

不稳定在于，收尾边路没有巨人时旁路巨人锤炮，以及小概率小鬼啃5-1炮。由于2-8/4-8都是核坑位，还不能使用垫材拖延。

### RE 方块八炮 ch4\*

[ch4\*: I-PP | I-PP (20, 20)](./RE方块八炮/s8p.cpp)

感觉写完这个阵可以去写C2八炮了，笑死

倒是没有像C2八炮一样用2032冰波，因为巨人投掷到一半减速解除了，感觉拦截时间就不是很好算了。

就算是ch4*，用冰量也是很大的，并且屋顶难拖收尾，所以不仅收尾不能点冰，还必须有首代操作。收尾的安排方式可以见代码里的注释。

## 计划完成的阵型

### PE 全金属四炮 ch4-N 手动 不稳定

[ch4-N: I-PP | I-PP | N | PP (18, 18, 12, 6)](./PE全金属四炮/metal4p.cpp)

存冰位置也太...不过基本就是复制之前的ch4-N了。

但是存冰好像转不过来，还是属于没完成。

