#include "../whatss7-avz2-lib/walib.h"

void AScript(){
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, ADOOM_SHROOM, APUMPKIN});
    WAAutoManageCob();
    aIceFiller.Start({{1, 1}, {5, 1}});
    aPlantFixer.Start(APUMPKIN);
    aPlantFixer.SetHp(4000 / 3 * 2);
    // ch5: I-PP|I-PP|PP (15, 15, 6)

    // w1-w9: N|PP|PP|I-PP|I-PP|PP|I-PP|I-PP|PP
    // w10-w19: PP|I-PP|I-PP|PP|I-PP|I-PP|PP|I-PP|I-PP|PP
    // w20: PP

    // w1: N
    for (int w: {1}) {
        N(w, PCP, 3, 9);
    }

    // w2, w3, w6, w9, w10, w13, w16, w19, w20: PP
    for (int w: {2, 3, 6, 9, 10, 13, 16, 19, 20}) {
        PP(w);
    }

    // w4, w5, w7, w8, w11, w12, w14, w15, w17, w18: I-PP
    for (int w: {4, 5, 7, 8, 11, 12, 14, 15, 17, 18}) {
        I(w, 100);
        PP(w, 1500 - 200, 8.5);
    }
}