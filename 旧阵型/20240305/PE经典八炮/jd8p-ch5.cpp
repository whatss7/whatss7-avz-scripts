#include "../whatss7-avz2-lib/walib.h"

APlantFixer umbrellaFixer;

void AScript(){
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, ADOOM_SHROOM, ALILY_PAD, APUMPKIN, AUMBRELLA_LEAF, APUFF_SHROOM, ASUN_SHROOM});
    WAAutoManageCob();
    aIceFiller.Start({{1, 1}, {6, 1}});
    WAFixNuts();

    // 底线只有单曾无法冰杀，需要叶子保护伞防偷
    umbrellaFixer.Start(AUMBRELLA_LEAF, {{2, 1}, {5, 1}});

    // ch5: I-PP|IPP-PP|PP (15, 15, 6)
    // ch5可以冰杀矿工从而在底线存冰，但是冰波转加速波时矿工无法处理，用多出的两炮热过渡

    // w1-w9: N|PP|PP|I-PP|IPP-PP|PP|I-PP|IPP-PP|PP
    // w10-w19: PPA|I-PP|IPP-PP|PP|I-PP|IPP-PP|PP|I-PP|IPP-PP|PP
    // w20: PP

    // w1: N
    for (int w: {1}) {
        N(w, PCP, 3, 9);
    }
    // w2, w3, w6, w9, w13, w16, w19: PP
    for (int w: {2, 3, 6, 9, 10, 13, 16, 19, 20}) {
        PP(w);
        if (w == 10) SmartA();
        if (w == 20) I(w, -50);
    }

    // w4, w7, w11, w14, w17: I-PP
    for (int w: {4, 7, 11, 14, 17}) {
        I(w, 100);
        PP(w, 1500 - 200, 8.5);
    }

    // w5, w8, w12, w15, w18: IPP-PP
    for (int w: {5, 8, 12, 15, 18}) {
        I(w, 100);
        PP(w, 400, 8);
        PP(w, 1500 - 200);
    }
}