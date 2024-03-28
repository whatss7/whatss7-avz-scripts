#include "../walib.h"

void AScript() {
    // I-PP | PP | I-PP | PP (11.5, 6, 11.5, 6)
    const int i_len = 1250, short_i_len = 1150;
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ACOFFEE_BEAN, ALILY_PAD,
        ACHERRY_BOMB, AUMBRELLA_LEAF, APUMPKIN, APUFF_SHROOM, ASUN_SHROOM
    });
    aIceFiller.Start({{3, 6}, {4, 6}});
    AutoFixNuts();

    // 此段用于测试在极端情况下必须在有多个红眼的路进行收尾的情况。
    // AConnect(ATime(9, 1), [](){
    //     for (auto &&zombie: aAliveZombieFilter) {
    //         if (zombie.AtWave() == 8 && zombie.Type() == AHY_32) {
    //             zombie.Row() = 0;
    //             zombie.Ordinate() = 50;
    //         }
    //     }
    // });

    for (int w: {1, 2, 4, 6, 8, 10, 12, 14, 16, 18}) {
        PP(w);
        if (w == 10) {
            SmartA();
            TempC(w, 300, AUMBRELLA_LEAF, {{3, 8}, {4, 8}}, 400);
        }
    }

    for (int w: {3, 5, 7, 11, 13, 15, 17}) {
        // 对w11炸不到的红眼，应当都是慢速红眼，不构成威胁（大概
        I(w, 1, 601);
        PP(w, i_len - 200);
    }

    // w9/w19特化，100冰，1150生效炮，谨防小丑炸核
    for (int w: {9, 19}) {
        I(w, 100);
        PP(w, short_i_len - 200);
        N(w, short_i_len - 200, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
        PPForEnd(w, short_i_len + 601 - 200);
        PPExceptOne(w, short_i_len + 601 + i_len - 200);
        waStopGigaBanCols = { 9 };
        // 玉米停滞效果还行，三垫勉强够用
        StopGiga(w, short_i_len + 601 + i_len - 200 + 5, { APUFF_SHROOM, ASUN_SHROOM, AUMBRELLA_LEAF }, 4300);
        PPLast(w, 4300);
        MaidDance(w, short_i_len + 601 + i_len - 200, w + 1, 318);
    }

    for (int w: {20}) {
        P(w, PCP, 2, 9);
        A(w, PCP, 5, 9);
        P(w, 225, 4, 7.5875);
        TempC(w, 300, AUMBRELLA_LEAF, {{3, 8}, {4, 8}}, 400);
        I(w, 601 + 1);
        N(w, 601 + i_len - 200, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
        PP(w, 601 + i_len - 200);
        PPExceptOne(w, 601 + i_len + PCP);
        StopGiga(w, 601 + i_len + PCP + 5, { APUFF_SHROOM, ASUN_SHROOM, AUMBRELLA_LEAF }, 5999);
        PPLast(w, 5999);
    }
}