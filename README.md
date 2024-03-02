# whatss7-avz-scripts

## 说明

使用 [AvZ 2](https://github.com/vector-wlc/AsmVsZombies) 编写的键控脚本。请注意 AvZ 2 与 AvZ 1 区别很大，下列脚本不适用于 AvZ 1 用户。

以下说明“无伤”的，指玉米加农炮、忧郁菇等输出植物无伤，南瓜头和垫材等可能受伤；或者即使受伤，也有能力通过换炮等方式解决。

- 标题后跟有“挂机”的，指已经测试无操作挂机100f无伤。
  - “挂机\*”表示挂机测试时采用均匀填充的极限出怪。
  - “挂机\*\*”表示特定情况下可挂机，具体查看阵型对应说明。
- 标题后跟有“半挂机”的，指具备挂机能力，但是因为一些缺陷，测试无法达到100f。
- 标题后跟有“不稳定”的，指虽然已经手打2f无伤，但是存在明显缺陷。
- 标题后跟有“未完成”的，指此脚本还未写完。

[键控考级阵脚本汇总](./level.md)

## 目录

- [whatss7-avz-scripts](#whatss7-avz-scripts)
  - [说明](#说明)
  - [目录](#目录)
  - [已完成的阵型](#已完成的阵型)
    - [PE 经典十二炮 P6 挂机](#pe-经典十二炮-p6-挂机)
    - [PE 经典八炮](#pe-经典八炮)
      - [P4-c 挂机](#p4-c-挂机)
      - [对ch6](#对ch6)
      - [ch5](#ch5)
      - [P5 挂机\*\*](#p5-挂机)
      - [P6 不稳定](#p6-不稳定)
      - [ch4](#ch4)
      - [P4](#p4)
      - [S6 不稳定](#s6-不稳定)
      - [S4](#s4)
    - [PE 经典十炮](#pe-经典十炮)
      - [P6 挂机\*\*](#p6-挂机)
      - [S6 挂机\*\*](#s6-挂机)
    - [PE 经典四炮](#pe-经典四炮)
      - [ch4](#ch4-1)
      - [邻C6u 不稳定](#邻c6u-不稳定)
    - [RE 天台十炮 P5 挂机](#re-天台十炮-p5-挂机)
    - [DE 双冰六炮 ch5](#de-双冰六炮-ch5)
    - [PE 单紫卡十二炮](#pe-单紫卡十二炮)
      - [S6 半挂机](#s6-半挂机)
    - [NE 核代十炮·改 P6 半挂机](#ne-核代十炮改-p6-半挂机)
    - [ME 田八炮 对C8u 不稳定](#me-田八炮-对c8u-不稳定)
    - [RE 神之七炮 ch5u](#re-神之七炮-ch5u)
    - [PE 空炸十八炮 P6 挂机](#pe-空炸十八炮-p6-挂机)
    - [PE 玉米八炮 对ch6](#pe-玉米八炮-对ch6)
    - [PE 万四炮 ch4-N 原创 不稳定](#pe-万四炮-ch4-n-原创-不稳定)
    - [PE 全金属四炮 ch4-N 不稳定](#pe-全金属四炮-ch4-n-不稳定)
    - [DE 连拦十四炮 对ch6 不稳定](#de-连拦十四炮-对ch6-不稳定)
  - [计划完成的阵型](#计划完成的阵型)
    - [FE 新磁铁四炮 对C6u 未完成](#fe-新磁铁四炮-对c6u-未完成)


## 已完成的阵型

### PE 经典十二炮 P6 挂机

[P6: PP | PP | PP | PP | PP | PP  (6, 6, 6, 6, 6, 6)](jd12p.cpp)

键控入门脚本。

### PE 经典八炮

#### P4-c 挂机

[P4: ccccPP | ccccPP | ccccPP | ccccPP  (875, 875, 875, 875)](PE经典八炮/jd8p-P4c.cpp)

使用垫材在9列垫舞王。若使用9秒波长，冰道盖过9列无法放置垫材，而在8列放置垫材或干脆不放置垫材都可能漏炸伴舞。

#### 对ch6

[对ch6: I-PP | PP | I-PP | PP  (12, 6, 12, 6)](PE经典八炮/jd8p-ch6.cpp)

12秒冰波可以守7列，在7列存冰。如果零冰开的话存冰比较极限，收尾必须手动拖满。

没有核弹首代是因为w9如果是加速波，收尾很难处理撑杆。

#### ch5

[ch5: I-PP | IPP-PP | PP  (15, 15, 6)](PE经典八炮/jd8p-ch5.cpp)

在底线存冰，第一个冰波矿工冰杀，第二个冰波矿工热过渡处理，加速波矿工直接炸掉。

#### P5 挂机\*\*

[P5u-N: ccccPP | ccccPP | ccccPP | ccccPP | N  (7.5, 7.5, 7.5, 7.5, 7.5)](PE经典八炮/jd8p-P5u.cpp)

**\*\*: 本阵型挂机测试仅进行了50f。**

使用垫材在9列垫舞王。垫材冷却751cs因此无法使用7秒波长。

是真没想到，自然出怪下P4和P5也能在w10刷新延迟，因此w10额外点一个核。

#### P6 不稳定

[P6-2N: PP | PP | PP | N | PP | N' (6, 6, 6, 6, 6, 6)](PE经典八炮/jd8p-P6.cpp)

两个核波相邻的话咖啡豆冷却不够，分开的话w19核弹冷却不够，所以加入铲种炮，阳光消耗较大。

核坑位比较极限，需要拖收尾，而因为经典八炮本身存在不低的io，所以都是脆皮的情况下不一定拖得满收尾。

#### ch4

[ch4: IPP-PP | IPP-PP (18, 18)](PE经典八炮/jd8p-ch4.cpp)

**因为纯ch4无法零冰开，所以使用了单独的有存冰存档，请将 `PE经典八炮/game1_11.dat` 复制到存档文件夹后，从DE入口进入。**

多出来的四炮用于热过渡守7列存冰和底线。因为小鬼有概率冲到底线所以还是给底线套了南瓜。因为存冰需要恢复，所以又是一个需要拖满的脚本。

#### P4

[P4: PP | PP | PP | PP (9, 9, 9, 9)](PE经典八炮/jd8p-P4.cpp)

不使用垫材的版本。如果出现刷新延迟，而9秒后还未刷新，则再开一炮。对意外刷新也做了处理。

基本能挂机，但如果出现连续三次不足18s的刷新延迟，因为冰核都被用完也是有可能出问题的。

#### S6 不稳定

[S6: I-N | PP | PP | PP | PP (12, 6, 6, 6, 6)](PE经典八炮/jd8p-S6.cpp)

w1-w9只点一冰的话，w9后炮要等18秒才能转好，所以额外点一核帮忙收尾并且解决2路撑杆越过存冰啃炮的问题。但是带撑杆的中速关这样做会直接刷新（甚至如果快速关没有撑杆，两炮下去直接刷新），导致w10无炮可用。倒是可以用地刺在冰波w5扎爆2路冰车然后w9再垫一下撑杆。

同时，和P6-2N一样，一轮点了4次核，核坑位也要拖收尾解决，但快速关不一定能拖。不过因为这个节奏中有3个冰波，拖收尾压力没有P6-2N那么大，可以少拖18s。

南瓜需要手动补，不想算南瓜什么时候能补了（或者干脆可以炮炸珊瑚使得南瓜无伤）。

#### S4

[S4: IPP-PP | ccccPP | ccccPP (1800, 875, 875)](PE经典八炮/jd8p-S4.cpp)

热过渡解决冰车，然后垫材垫舞王。~~P4和ch4生下的孩子，懒得写挂机部分了~~

### PE 经典十炮

#### P6 挂机\*\*

[P6: PP | PP | PP | PP | PP | N  (6, 6, 6, 6, 6, 6)](PE经典十炮/jd10p-P6N.cpp)

**\*\*: 本阵型挂机测试仅进行了50f。**

在键控难以拖收尾的情况下，炮炸珊瑚和炮炸蹦极都容易导致炮转不过来，所以使用叶子保护伞保护高坚果，冰消珊瑚。掉阳光较多，偷了花。

#### S6 挂机\*\*

**\*\*: 本阵型挂机测试仅进行了50f。**

[S6: I-PP | PP | PP | PP | PP  (12, 6, 6, 6, 6)](PE经典十炮/jd10p-S6.cpp)

开始时考虑的是在7列存冰+偷花，但撑杆就啃炮了；于是手动规划了冰的种植，改为1列偷花。

### PE 经典四炮

#### ch4

[ch4: I-PP | I-PP (18, 18)](./PE经典四炮/jd4p.cpp)

非常朴素的ch4。需要手工收尾拖满。

#### 邻C6u 不稳定

[邻C6u: I-PP | I-PP | N | PP (18, 18, 9, 9)](./PE经典四炮/jd4p-C6u.cpp)

基本骨架写出来了，收尾还没写...

### RE 天台十炮 P5 挂机

[P5: PP | PP | PP | PP | PP (7, 7, 7, 7, 7)](./RE天台十炮/tt10p.cpp)

底线炮有概率被小鬼啃，所以啃得多了之后换一下炮。

### DE 双冰六炮 ch5

[ch5: I-PP | I-PP | PP (15, 15, 6)](./DE双冰六炮/2i6p.cpp)

收尾难顶，除此之外好像没什么问题。

### PE 单紫卡十二炮

#### S6 半挂机

[S6: I-PP | PP | PPDD | PP | PP (12, 6, 6, 6, 6)](./PE单紫卡十二炮/dzk12p.cpp)

不管小鬼，而且红眼留到第二波再炸时，小鬼可能进家，这时有两种解决方法：一种是拦截，直接拦下第二波炸出来的小鬼，这样可以解决一个加速波；另一种是点冰，让小鬼在地刺上减速，这样可以解决两个加速波。综合起来就是这样的轨道，再加点首尾特化处理蹦极就能挂机了...吗？

w10的刷新延迟通过多点一核解决（如果是均匀出怪，一个樱桃都应该能解决），但是谁能想到非旗帜波两炮也能不刷新...而且这个还没有什么好的解决办法，w9要拖收尾必须要带垫材四件套导致不能带樱桃，而且即使带了樱桃，冰波冰道也盖过了9列。

就算凹出了没有刷新延迟的出怪，以上处理下小鬼甚至还是能进家，所以只能半挂机了。或者之后再试试ch6的阵解，不过这样就得找位置存冰了。

### NE 核代十炮·改 P6 半挂机

[P6: PP | PP | PP | PP | PP | N (6, 6, 6, 6, 6, 6)](./NE核代十炮·改/nen10p.cpp)

没想到NE有这么多细节。

前院炸2-9和4-9时，1路部分僵尸走得慢的僵尸会被漏掉，不确定是不是要炸1-9。漏个跳跳气球什么的都好说，漏个读报什么的就当场啃炮。以及，小鬼也有概率啃底线炮。

墓碑出的僵尸用樱桃炸掉，但是如果放樱桃的位置刚好是核坑位的话...

抛开这些不谈的话，倒是基本能挂机，打个2f的展示视频也不难。所以，键控一级啦！

### ME 田八炮 对C8u 不稳定

[对C6u: I-PP | PP | PP | I-PP | PP | PP (1253, 746, 746, 1253, 746, 746)](./ME田八炮/tian8p.cpp)

之前弄了半天都有哪里不对，后来发现是我写的 `PP` 函数算错了屋顶时机...

因为要炮炸空降，所以前场改为点核，但这样经常漏炸各种东西；以及还是有红眼砸率，但好像我也就只能这样了。

### RE 神之七炮 ch5u

[ch5u: I-PP | IP-PP | PP (12.5, 15.5, 7)](./RE神之七炮/sideless7p.cpp)

算是首个完全没有借助演示视频等帮助写出来的阵。

全程ch5的话，存冰顶不住。为了3-3的炮不瞬间融化，不能连续打加速波，所以也不太能首代。要想双存冰位顶住的话，收尾必须不能点冰。所以主要的心思都花在处理收尾上，通过安排切入的位置找到方便收尾的排布。

挂机当且仅当全难度极限出怪，且w9和w19边路存在至少一个巨人。因为收尾时可能的情况较多，所以没有写全出怪挂机。

### PE 空炸十八炮 P6 挂机

[P6: PPD | PPD | PPD | PPD | PPD | PPD (6, 6, 6, 6, 6, 6)](./PE空炸十八炮/ab18p.cpp)

为什么这阵能是键控二级阵呢...

自然出怪是真的猛，3炮+1核都能刷新延迟（虽然是因为快速关大量僵尸还没入场）

### PE 玉米八炮 对ch6

[对ch6: I-PP | PP | I-PP | PP (12, 6, 12, 6)](./PE玉米八炮/corn8p.cpp)

朴素的ch6。全难度极限出怪下挂机，其他的得考虑怎么收尾。南瓜头应该可以留到简单关修，懒得写了.jpg

### PE 万四炮 ch4-N 原创 不稳定

[ch4-N: I-PP | I-PP | N | PP (18, 18, 12, 6)](./PE万四炮/wan4p.cpp)

第一个原创造型（水）阵。ch4-N总给我一种怪感觉，就觉得为什么不C6u呢，不是更省冰吗...不过用起来确实是好用。

### PE 全金属四炮 ch4-N 不稳定

[ch4-N: I-PP | I-PP | N | PP (18, 18, 12, 6)](./PE万四炮/wan4p.cpp)

存冰位置也太...不过基本就是复制之前的ch4-N了。

### DE 连拦十四炮 对ch6 不稳定

[对ch6: IP-P/PD | P/Bd | IP-P/PD | P/Bd](./DE连拦十四炮/bd14p.cpp)

冲击三级，先练习一下预备知识连拦，但是这也并不简单。

不稳定在于：下半场尾炸加速小鬼时，有可能突然冒出来一个减速小鬼；上半场有砸率，需要引入垫材。

## 计划完成的阵型

### FE 新磁铁四炮 对C6u 未完成

[对C6u: ICC-PA | N | IaC-PA' | PP (19, 6, 19, 6)](./FE新磁铁四炮/xct4p.cpp)

感觉键控窝瓜超出我现在的能力范围了，这个阵以后再说吧。
