#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    // 因为潜水有啃核威胁，所以特别加上
    WAInit({ADOOM_SHROOM, AM_DOOM_SHROOM, AICE_SHROOM, ALILY_PAD, ACOFFEE_BEAN, ACHERRY_BOMB, APUMPKIN},
           std::vector<AZombieType>({ACG_3, AGL_7, AWW_8, AQS_11, ABC_12, AHT_14, AXC_15, AKG_17, ABJ_20, ABY_23, AHY_32}));
    WAAutoManageCob();
    aIceFiller.Start({{2, 7}});

    // S6: I-N|PP|PP|PP|PP (12, 6, 6, 6, 6)
    // w1-w9: PP|PP|PP|PP|I-N|PP|PP|PP|PPN'
    // w10-w19: PP|PP|PP|PP|I-N|PP|PP|PP|PP|I-N'
    // w20: PPDD

    // 加速波 PP
    for (int w: WaveList(1, 20)) {
        if (w == 5 || w == 14 || w == 19) continue;
        // PP
        PP(w);
        if (w == 9) N(w, 400, {{3, 8}, {4, 8}, {3, 9}, {4, 9}}, 601, 1);
        if (w == 10) SmartA();
        if (w == 20) PP(w, 400);
    } 
    // 冰波 I-N
    for (int w: {5, 14, 19}) {
        I(w, 100);
        N(w, 1200 - 200, {{3, 8}, {4, 8}, {3, 9}, {4, 9}}, 601, 1);
    }
}