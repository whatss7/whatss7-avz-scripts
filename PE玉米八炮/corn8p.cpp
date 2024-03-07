// #define WALIB_DEBUG
#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    // I-PP | PP | I-PP | PP (11.5, 6, 11.5, 6)
    const int ice_len = 1200;
    WAInit({ AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ACOFFEE_BEAN, ALILY_PAD,
             ACHERRY_BOMB, AUMBRELLA_LEAF, APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM });
    aIceFiller.Start({{3, 6}, {4, 6}});

    // 此段用于测试在极端情况下必须在有多个红眼的路进行收尾的情况。
    // AConnect(ATime(9, 1), [](){
    //     for (auto &&zombie: aAliveZombieFilter) {
    //         if (zombie.AtWave() == 8 && zombie.Type() == AHY_32) {
    //             zombie.Row() = 0;
    //             zombie.Ordinate() = 50;
    //         }
    //     }
    // });

    for (int w: {3, 5, 7, 9, 11, 13, 15, 17, 19}) {
        // 对w11炸不到的红眼，应当都是慢速红眼，不构成威胁（大概
        I(w, 50, 601);
        PP(w, ice_len - 200);
        if (w == 9 || w == 19) {
            if (AGetZombieTypeList()[AHY_32]) {
                N(w, ice_len - 200, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
            }
            PPForEnd(w, ice_len + 601 - 200);
            PPExceptOne(w, ice_len + 601 * 3 - 200);
            WAStopGiga(w, ice_len + 601 * 3 - 200 + 4, { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AUMBRELLA_LEAF }, 4300);
            PPLast(w, 4300);
            WAMaidDance(w, 3003, w + 1, 318);
        }
    }

    for (int w: {1, 2, 4, 6, 8, 10, 12, 14, 16, 18}) {
        PP(w);
        if (w == 10) {
            SmartA();
            TempC(w, 300, AUMBRELLA_LEAF, {{3, 8}, {4, 8}}, 400);
        }
    }

    for (int w: {20}) {
        PP(w);
        P(w, 225, 4, 7.5875);
        TempC(w, 300, AUMBRELLA_LEAF, {{3, 8}, {4, 8}}, 400);
        I(w, 400);
        ForEnd(w, (PCP + 601) * 2 - CFT, [w](){
            P(w, (PCP + 601) * 2, 2, 9);
            A(w, (PCP + 601) * 2, 5, 9);
            N(w, (PCP + 601) * 2, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
        });
        // 巨人2432cs锤七列炮，留点容错
        PPExceptOne(w, 2300);
        WAStopGiga(w, 2300, { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AUMBRELLA_LEAF }, 5999);
        PPLast(w, 5999);
    }
}