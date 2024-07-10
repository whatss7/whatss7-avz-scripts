# whatss7-avz-scripts

## 说明

使用 [AvZ 2](https://github.com/vector-wlc/AsmVsZombies) 编写的键控脚本。请注意 AvZ 2 与 AvZ 1 区别很大，下列脚本不适用于 AvZ 1 用户。

极限阵脚本使用 [AvZ修改器库](https://github.com/qrmd0/AvZLib/tree/main/Reisen/mod) 锁定阳光，因此运行此代码库中的脚本时，也请安装此扩展。

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
    - [PE 双冰十六炮·改 ch6](#pe-双冰十六炮改-ch6)
    - [NE 土豆四炮 邻C7u 不稳定](#ne-土豆四炮-邻c7u-不稳定)
    - [DE 前置八炮 ch5](#de-前置八炮-ch5)
    - [FE 新磁铁四炮 对C6u 不稳定](#fe-新磁铁四炮-对c6u-不稳定)
    - [PE 无冰瓜二十炮 P6-2I 挂机\*](#pe-无冰瓜二十炮-p6-2i-挂机)
    - [PE 玉米八炮 对ch6](#pe-玉米八炮-对ch6)
    - [RE 中开六炮 C6i-N 不稳定](#re-中开六炮-c6i-n-不稳定)
    - [NE 舞夜惊魂 P6](#ne-舞夜惊魂-p6)
    - [NE 新舞夜惊魂 P6](#ne-新舞夜惊魂-p6)
    - [RE 方块八炮 ch4\*](#re-方块八炮-ch4)
    - [ME 纯十五炮 C7u](#me-纯十五炮-c7u)
    - [PE 纯十二炮 ch6](#pe-纯十二炮-ch6)
    - [ME 十五炮 C7u](#me-十五炮-c7u)
    - [FE 弦十四炮](#fe-弦十四炮)
      - [P4](#p4)
      - [S4](#s4)
      - [间C7u](#间c7u)
    - [DE 双冰六炮 ch5](#de-双冰六炮-ch5)
    - [ME 田八炮](#me-田八炮)
      - [对C8u 挂机 不稳定](#对c8u-挂机-不稳定)
      - [C9u](#c9u)
    - [RE 椭盘十四炮 ch4](#re-椭盘十四炮-ch4)
    - [PE 空炸十八炮 / 尾炸十八炮](#pe-空炸十八炮--尾炸十八炮)
      - [P6(空炸)](#p6空炸)
      - [P6(尾炸)](#p6尾炸)
    - [NE 压碑五炮 C7u](#ne-压碑五炮-c7u)
    - [DE 花园六炮 ch4 不稳定](#de-花园六炮-ch4-不稳定)
    - [FE 纯三炮 C4u 不稳定](#fe-纯三炮-c4u-不稳定)
    - [PE 纯二十炮 P5u](#pe-纯二十炮-p5u)
    - [ME 神之六炮 C7u](#me-神之六炮-c7u)
  - [计划完成的阵型](#计划完成的阵型)
    - [PE 全金属四炮 ch4-N 手动 未完成](#pe-全金属四炮-ch4-n-手动-未完成)
    - [DE 斜八炮 ch4u 原创 未完成](#de-斜八炮-ch4u-原创-未完成)
    - [ME 核聚变六炮 P5 未完成](#me-核聚变六炮-p5-未完成)


## 已完成的阵型

### PE 双冰十六炮·改 ch6

[ch6: IPP-PP | PPDD | IPP-PP | PPDD (12.5, 6, 12.5, 6)](./PE双冰十六炮·改/2i16p.cpp)

根据 Seml 测试，PE场地，1256cs冰波小丑才会以极小概率炸超前置炮，所以以前我写的很多的11.5s冰波其实没有必要...当然如果要保水路九列另说。

### NE 土豆四炮 邻C7u 不稳定

[邻C7u: I-PP | I-PP | AA'a | N | PP (16, 19, 6, 6.9, 6)](./NE土豆四炮/potato4p.cpp)

使用智能脚本，3路出现极慢矿工时，推迟土豆雷的放置时机防止短冰波矿工啃雷。1路漏炸的跳跳会被辣椒烧掉。

唯一的问题就是窝瓜太能演了，AA'a波刷新延迟太严重了...

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

### NE 舞夜惊魂 P6

[P6: cPP | cPP | cPP | cPP | cPP | cPP (6, 6, 6, 6, 6, 6)](./NE舞夜惊魂/dance12p.cpp)

女仆秘籍覆盖不到第一帧，那么想挂机的话，就必须把伴舞往回拉，掉节操不可避了（至少拉的距离小于1px看不出来

考级指南里写的Pc一度让我以为是垫材垫撑杆，想了半天没搞懂，然后看了演示之后发现，是cP垫舞王，然后在伴舞出土前连撑杆一起炸掉。

### NE 新舞夜惊魂 P6

[P6: cPP | cPP | cPP | cPP | cPP | cPP (6, 6, 6, 6, 6, 6)](./NE新舞夜惊魂/newdance.cpp)

即使借助修改器，这个开局也比[旧舞夜惊魂](#ne-舞夜惊魂-p6)麻烦许多，步骤如下：

1. 生成若干舞王（这里生成了10只），等待其召唤伴舞
2. 干掉一个舞王的前伴舞，退出重进
3. 等待该舞王召唤伴舞，退出重进
4. 干掉其前伴舞，在舞王召唤前生成一个扶梯僵尸，给舞王一个坚果
5. 选一个新的舞王，先干掉其前伴舞，再干掉扶梯，退出重进
6. 等待该舞王召唤伴舞，退出重进
7. 干掉其前伴舞，在舞王召唤前生成一个扶梯僵尸，给舞王一个坚果
8. 如果还有没处理的舞王，回到5
9. 把上述的“前伴舞”换成“后伴舞”，重复2-8步。
10. 魅惑所有舞王（不能用魅惑菇，会重置伴舞信息），移动舞王到x=3，两个扶梯到x=42，干掉多余的伴舞。
11. 借助文件夹下的 `newdance_start.cpp`，设置两个扶梯分别为第9波、第19波生成。

这样，所有舞王都会认为两个扶梯分别是它的前伴舞和后伴舞，舞王发现自己的前后伴舞在啃食上下伴舞，于是原地不动了（伴舞处于啃食动作）。上下伴舞手没有扶梯长，因此不会啃食扶梯，而扶梯恰好处于忧郁菇的判定范围内和攻击范围外，卡出永动曾。

这个阵比起旧舞夜惊魂稳定许多，每路都有冰瓜，不必担心减速不到，而且每个收尾都可以保证拖满，于是w20我就胡乱发炮了（

### RE 方块八炮 ch4\*

[ch4\*: I-PPDD | I-PPDD (20, 20)](./RE方块八炮/s8p.cpp)

感觉写完这个阵可以去写C2八炮了，笑死

倒是没有像C2八炮一样用2032冰波，因为巨人投掷到一半减速解除了，感觉拦截时间就不是很好算了。

就算是ch4\*，用冰量也是很大的，并且屋顶难拖收尾，所以不仅收尾不能点冰，还必须有首代操作。收尾的安排方式可以见代码里的注释。

### ME 纯十五炮 C7u

[C7u: IP-PPDD | IP-PPDD | PPDD | A'NDD | PPDD (17.5, 17.5, 6.2, 6.2, 6.2)](./ME纯十五炮/pure15p.cpp)

**此阵为极限阵，不考虑阳光消耗。**

本来计划热过渡防止冰道覆盖核坑位，结果后来发现为了防止锤核导致拦截失败，本来就要用辣椒烧一下，于是热过渡就纯守3-7花盆...

另外，感觉写复杂了，也没看到有谁键控，都是手控的...所以以后说不定会再来写个守7的版本。

### PE 纯十二炮 ch6

[ch6: I-PPdd | PP | I-PPdd | PP (12.5, 6, 12.5, 6)](./PE纯十二炮/pure12p.cpp)

感觉偷的一点阳光属于杯水车薪，总之能偷一点是一点吧...

为了发经典十二炮和冰雨十二炮这两个过于简单的阵型的视频写出的阵...

### ME 十五炮 C7u

[C7u: IPP-PPDD | IPP-PPDD | BPAD | A'NDD | PPDD (1630, 1720, 601, 620, 625)](./ME十五炮/col7-15p.cpp)、

选用这些波长的原因：
- 1630: 使得这一波巨人在第一加速波不锤炮；
- 1720: 使得这一波的扶梯不会啃炮；
- 601: 樱桃380就会蹭巨人，因此必须在380之前激活；
- 620: 使得上波45路撑杆不会落地；
- 625: 使得前面的波长下可以实现复用。

猛炫1250阳光...大致算算，不出红白纯打P6回1000阳光，只出白眼还没考虑。感觉还需要优化。

经过RND验证，一次冻结锁400，二次冻结锁300（即RND中冻结数值都填0），速度锁0.37，巨人也锤不到炮。

### FE 弦十四炮

#### P4

[P4: PPDD | PPDD | PPDD | NDD (875, 875, 875, 850)](./FE弦十四炮/string14p.cpp)

P4拦截确实有点不好说，875波存在小概率蹭到红眼翻车。测试10000波共翻车10次，勉强还在个人的接受范围内。

采用869波长的话，倒是可以严谨拦截，但是w17的时候海豚会跳过模仿核啃炮。考虑到这里已经猛炫2000阳光，而换一次炮需要1350阳光，所以还是蹭红眼吧，实在不行SL，或者可以考虑使用智能脚本，真的出现会蹭到的红眼时，激活炮生效的瞬间在9列强行用坚果墙垫一下。

以及，同样的行走时间，调一下使用垫材的时间，居然可以通过相位使得红眼慢上30px这么多，确实想不到。

#### S4

[S4: I-B-PPDD | PPDD | PSD/PD (1827, 824, 824)](./FE弦十四炮/string14p-s4.cpp)

用了自制[便携速度计算器](./utils/speed.html)，写垫材腰也不酸了，腿也不疼了（不是

冰波波长1827，并没有1860，可以直接空炸，压制力更高，也不用担心P4解蹭红眼的问题了。

#### 间C7u

[间C7u: I-PPDD | PPDD | I-PPDD | NDD | PPDD (1543, 681, 1543, 681, 681)](./FE弦十四炮/string14p-c7u.cpp)

一开始想直接把S4里的分离套过来打一个邻C7u，但是这样的话，后面三连加速波只能用9炮，辣椒开冰道就不是那么划算了...而且还要面临分离炮蹭上路巨人的问题。

所以参考了一下[视频](https://www.bilibili.com/video/BV1n54y1d7Yq)，发现其实没必要打601加速波，于是就轻松愉快写出来了，甚至不用写垫材。

### DE 双冰六炮 ch5

[ch5: I-PP | I-PP | PP (15, 15, 6)](./DE双冰六炮/2i6p.cpp)

收尾有冰道点不了核，辣椒烧梯，所以在7列施用垫材拖延。

### ME 田八炮

#### 对C8u 挂机 不稳定

[对C8u: I-PP | PP | PP | I-PP | PP | PP (1253, 746, 746, 1253, 746, 746)](./ME田八炮/tian8p.cpp)

之前弄了半天都有哪里不对，后来发现是我当时写的 `PP` 函数算错了屋顶时机...

因为要炮炸空降，所以前场改为点核，但这样经常漏炸各种东西；以及还是有红眼砸率，但好像我也就只能这样了。

#### C9u

[C9u: Ia-PP | PP | IA-PP | PP | N | PP | PP (12.5, 6, 12.5, 6, 6, 6, 6)](./ME田八炮/tian8p-c9u.cpp)

稳定性++，阳光--，可以考虑3-1和3-2偷花。用窝瓜和樱桃防止冰道盖过核坑位。

### RE 椭盘十四炮 ch4

[ch4: I3PPDD-B-PP | I3PPDD-B-PP (18, 18)](./RE椭盘十四炮/ellipse14p.cpp)

最折磨的一集+最掉节操的一集...

想要两冰开必须多一次首代并且开局种花盆，而w9收尾肯定是要点樱桃+核的，这意味着w10比w1要多处理蹦极的同时还基本没有灰烬的帮助，因此只能在w1设计首代。

w1使用Nd/BND的方式保护450才点得出来的核；w2就是常规的PDD，第三个D中的一个换成A。分离炮炸不到3列跳跳，而尾炸炮要想炸到3列跳跳就炸不到1列跳跳，所以w4点一个辣椒解决跳跳。

w10也是PDD，但是上半的第二D换成炸3路的d炸掉蹦极，并且用辣椒拦截1列小鬼。但没有PDD处理冰车了，所以再点一个樱桃炸冰车，顺便炸掉跳跳。樱桃在最晚的D时也转不好，所以只能推迟使用。

w9/w19收尾必须借助1路，因此为了确保稳定把一个巨人移过去了，节操--；并且这两波小丑确实可能把樱桃给炸了，但是看了lcx的参考脚本后发现，那个版本也有炸核问题，所以懒得改了（

### PE 空炸十八炮 / 尾炸十八炮

#### P6(空炸)

[P6: PPD | PPD | PPD | PPD | PPD | PPD (6, 6, 6, 6, 6, 6)](./PE空炸十八炮/ab18p.cpp)

感觉点核还是有点太过了，改回樱桃了，不过这下不能保证自然出怪挂机了...

#### P6(尾炸)

[P6: PPd | PPd | PPd | PPd | PPd | PPd (6, 6, 6, 6, 6, 6)](./PE空炸十八炮/tb18p.cpp)

因为垫材用的太多了，专门来练一练写垫材。

### NE 压碑五炮 C7u

[C7u: I-PP | I-PP | PA | N | PP (18, 18, 6, 6, 6)](./NE压碑五炮/to5p.cpp)

普普通通的C7u。w20防止墓碑占掉核坑，临时种一个小喷。没有验证是不是零砸率，大概率不是，但是犯懒了（

### DE 花园六炮 ch4 不稳定

[ch4: I-PPd | I-PPd (17.5, 17.5)](./DE花园六炮/garden6p.cpp0)

运阵一时爽，收尾火葬场。收尾采用PS'(铲种)N/PND，A炸掉巨人更多的一侧，剩余的用冰豆维持减速，让曾的一级IO喷掉。

黄油似乎可以干扰投掷...先不管了

先留个数据吧，种下玉米投手到命中巨人耗时最少147。以后想起来翻修了再来看吧...

### FE 纯三炮 C4u 不稳定

**此阵为极限阵，不考虑阳光消耗。**

[C4u: I-B-Nd | I-B-PAA' (25, 25)](./FE纯三炮/pure3p.cpp)

少炮阵是真的难...

这个阵最大的威胁主要来自于红眼。如果巨人情况最差，则每波需要用11次垫材（1路5次，5路6路各3次，就算让樱桃也垫到一下还是需要10垫），而我们只有2张垫材，最多支持6垫。所以用了智能脚本，根据各条路的威胁（就是与理论最快的距离）判断垫哪里。但是智能脚本是这样的，锁个RND就能让脚本当场去世。（5次垫材是最优下垫时机下的结论，但因为要迁就下半场的时机，实际上上路需要6垫）

为了降低不稳定因素（主要是撑杆），小喷换成了大喷。分离炮通过调整时机和炸点保证全收跳跳、全伤当前波巨人。

就算大多数垫材都会分配给1路拖满其脚步，1路也经常会只受到3次灰烬伤害，就经常需要窝瓜解决残血巨人。但是4-7核波为了防小丑分离炮需要炸4路，2路冰车没人管了，会压掉一排大喷使得2路压力骤增，所以需要窝瓜来削减巨人血量并且干掉冰车；不巧的是4-7核波对1路的爆炸范围还很小，因此这里大概率1路也要个窝瓜，于是当场冲突去世。为了解决这个问题，4-7核波的上一波被安排为3-6核波（3-6核波不容易出现需要窝瓜的情况），这一波前禁用窝瓜，留在这一波里提前用窝瓜压一次红眼，省出窝瓜留着解决4-7核波的冰车。对于其他的几个核波，3-8核波也容易漏1路，3-7相对好一点。因此总的核坑循环就是`3-7` - `3-8` - `3-6` - `4-7`，高压波和低压波交替，使得窝瓜冷却可以缓和一点。

最后，3-6核波对每一个6路红眼都有35%的概率炸不到，问题不大因为这样的红眼都走的比较慢，但是它投出的小鬼不这么觉得。考虑到4-7核收下路快速很轻松，可以将4-7核波尾炸炸点左移，使得这些靠左的小鬼也能被收到。

就算已经用了上面的这些方法，翻车率仍然不低，但好歹能脸出视频了，就这样吧（

### PE 纯二十炮 P5u

[P5u: PPDD | PPdd | PPDD | PPdd | PPDD (657, 752, 657, 752, 657)](./PE纯二十炮/pure20p.cpp)

这个阵能和FE纯三炮一样都是三级？这不对吧（

需要垫一下跳跳防止偷家，但考级指南中的170垫不太对，有可能垫不到，实际上最晚应该是162垫延迟80铲（使用无偏垫材），这里取160垫延迟80铲。

脚本里还顺便垫了一下舞王，实际上如果用上女仆秘籍可以不用垫舞王，只垫一下1路。

小概率篮球砸炮，小概率小丑炸炮，但这是纯炮循环的代价，实际带个双冰就完事了（

### ME 神之六炮 C7u

[C7u: IP-PP | IP-PP | PA | N | PP (1719, 1719, 601, 746, 601)](./ME神之六炮/sideless6p.cpp)

冰波波长受梯子限制，第二加速波波长受篮球限制，第一加速波波长受花盆CD限制，第三加速波波长受复用限制。看起来波长很可调，但是实际上只能这样。

就算不考虑冰瓜，因为樱桃会被车压爆，仍然有可能有小鬼被丢到炮尾上，但是概率极小。

## 计划完成的阵型

### PE 全金属四炮 ch4-N 手动 未完成

[ch4-N: I-PP | I-PP | N | PP (18, 18, 12, 6)](./PE全金属四炮/metal4p.cpp)

存冰位置也太...不过基本就是复制之前的ch4-N了。

但是存冰好像转不过来，还是属于没完成。

### DE 斜八炮 ch4u 原创 未完成

一个ch4u水阵...

精准土豆+冰杀好像必然带来炮损，这里经20000只矿工测试，平均每只带来0.1264炮损，问题不大。

但是深入研究之后发现这阵好像没那么简单，垫材好像不太够用...目前bug有5路巨人逃离爆炸范围和收尾困难...

### ME 核聚变六炮 P5 未完成

知道正解是单冰C7u节奏，但是想尝试使用铲种强行运作P5节奏，但是AA'a波花盆没办法同时用在两处，大概成立不了...
