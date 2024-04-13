#include "../walib.h"

void AScript(){
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, ADOOM_SHROOM,
        APUMPKIN, APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT
    });
    aIceFiller.Start({{1, 1}, {5, 1}});
    AutoFixNuts();

    // ch5: I-PP|I-PP|PP (15, 15, 6)
    const int i_len = 1500;

    // I-PP 第一冰波
    for (int w: {3, 6, 9, 11, 13, 16, 19}) {
        I(w, 1, 601);
        PP(w, i_len - 200, 8.6);
        if (w == 9 || w == 19) {
            PP(w, i_len + i_len - 200, 8.5);
            PP(w, i_len + i_len + 601 - 200, 8.5);
        }
    }

    // I-PP 第二冰波
    for (int w: {4, 7, 14, 17}) {
        I(w, 1, i_len);
        PP(w, i_len - 200, 8.6);
    }

    // PP
    for (int w: {1, 2, 5, 8, 10, 12, 15, 18, 20}) {
        PP(w);
        if (w == 20) {
            I(w, 601 + 1);
            PP(w, 601 + i_len - 200, 8.5);
            PP(w, 601 + i_len + i_len - 200, 8.5);
        }
    }
}