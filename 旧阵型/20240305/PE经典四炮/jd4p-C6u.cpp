#include <avz.h>
#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, ADOOM_SHROOM, ALILY_PAD, APUMPKIN});
    WAAutoManageCob();
    WAStartBlover();
    WAFixNuts();
    aIceFiller.Start({{3, 5}, {1, 4}, {6, 4}});

    // C6u: I-PP|I-PP|N|PP (18, 18, 9, 9)
    // w1-w9: PP|I-PP|N|PP|I-PP|I-PP|N|PP|I-PP
    // w10-w19: PP|I-PP|I-PP|N|PP|I-PP|I-PP|N|PP|I-PP
    const int ice_len = 1800;
    const int a_len = 900;

    for (int w: {1, 4, 8, 14, 18}) {
        PP(w, a_len - 200, 8.4875);
    }
    for (int w: {2, 5, 6, 9, 11, 12, 15, 16, 19}) {
        if (w == 6 || w == 12 || w == 16) {
            I(w, 1, 1800);
        } else if (w == 11) {
            I(w, 1, 601);
        } else {
            I(w, 1, 900);
        }
        PP(w, ice_len - 200, 8.425);
        if (w == 9 || w == 19) {
            PP(w, ice_len * 2 - 200, 8.425);
            N(w, ice_len * 2 + a_len - 200, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
        }
    }
    for (int w: {3, 7, 13, 17}) {
        N(w, a_len - 200, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
    }
    for (int w: {10}) {
        PP(w);
        SmartA();
    }
    for (int w: {20}) {
        PP(w);
        I(w, 601);
        PP(w, 600 + ice_len - 200, 8.425);
        N(w, 4300, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
    }
}