#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ACOFFEE_BEAN, ALILY_PAD, 
            ATALL_NUT, ACHERRY_BOMB, AUMBRELLA_LEAF, APUFF_SHROOM, ASUN_SHROOM});
    // ch4-N: I-PP | I-PP | I-N | PP
    const int i1_len = 1800, i2_len = 1200;
    aIceFiller.Start({{3, 1}, {4, 1}});
    WAFixNuts(1, -598);
    // w1-w5: N | PP | I-PP | I-PP | I-N | ...
    // 需要布好的睡莲：3-7高坚果，4-7高坚果，第一个核，3-1存冰位荷叶，4-1存冰位荷叶，3-4叶子保护伞
    // 3-7高坚果在w4 419cs前种下 -> 4-7要在(w4 -2582) = (w3 -782) = (w2 -181) = (w1 420)前种下
    // 第一个核(w1 -599) -> 4-7 (w1 152) -> 3-1 (w2 302) -> 4-1 (w3 452) -> 3-4 (w3 1203) -> 3-7 (w4 154)
    // 第三个冰波中，上半场需要提前樱桃来把2路矿工和3路海豚收掉
    // 冰波优先用掉4-8，非冰波尽量不用4-8
    C(1, -599, {ALILY_PAD, ADOOM_SHROOM}, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
    C(1, 152, {ALILY_PAD, ATALL_NUT}, 4, 7);
    C(2, 302, ALILY_PAD, 3, 1);
    C(3, 452, ALILY_PAD, 4, 1);
    C(3, 1203, {ALILY_PAD, AUMBRELLA_LEAF}, 3, 4);
    C(4, 154, {ALILY_PAD, ATALL_NUT}, 3, 7);
    for (int w: {1}) {
        C(w, PCP - ADT - CBT, ACOFFEE_BEAN, {{3, 8}, {3, 9}, {4, 8}, {4, 9}});
    }
    for (int w: {2, 6, 10, 12, 16}) {
        PP(w);
    }
    for (int w: {3, 7, 13, 17}) {
        I(w, 1);
        PP(w);
    }
}