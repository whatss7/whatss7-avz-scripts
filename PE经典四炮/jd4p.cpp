#include <avz.h>
#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, ADOOM_SHROOM, ALILY_PAD, APUFF_SHROOM, ASUN_SHROOM, APUMPKIN});    
    WAAutoManageCob();
    aPlantFixer.Start(APUMPKIN);
    aPlantFixer.SetHp(4000 / 3 * 2);
    aIceFiller.Start({{3, 5}, {1, 4}, {6, 4}});

    // ch4 I-PP|I-PP (18, 18)
    AAssumeWavelength({
        ATime(1, 601), ATime(2, 601), ATime(3, 1800), ATime(4, 1800), ATime(5, 1800),
        ATime(6, 1800), ATime(7, 1800), ATime(8, 1800),
        ATime(10, 601), ATime(11, 1800), ATime(12, 1800), ATime(13, 1800), ATime(14, 1800),
        ATime(15, 1800), ATime(16, 1800), ATime(17, 1800), ATime(18, 1800),
    });

    // w1 N
    for (int w: {1}) {
        N(w, PCAP, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
    }

    // w2 PP
    for (int w: {2}) {
        PP(w);
    }

    // 常规 I-PP
    for (int w: WaveList(3, 9) + WaveList(11, 19)) {
        I(w);
        PP(w, 1800 - 200, 8.5);
        // w9 和 w19 再点一核帮忙收尾
        if (w == 9 || w == 19) {
            N(w, 1820, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
        }
    }

    // w10 PPA 樱桃消延迟
    for (int w: {10}) {
        PP(w);
        A(w, 400, 2, 9);
    }

    // w20 I-PP 但冰杀蹦极
    for (int w: {20}) {
        I(w, 400);
        PP(w, 1800 - 200, 8.5);
    }
}