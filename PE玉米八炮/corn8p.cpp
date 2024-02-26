#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    // I-PP | PP | I-PP | PP (11.5, 6, 11.5, 6)
    const int ice_len = 1149;
    WAInit({ AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB });
    aIceFiller.Start({{3, 6}, {4, 6}});

    for (int w: {3, 5, 7, 9, 11, 13, 15, 17, 19}) {
        I(w, 1, 601);
        PP(w, ice_len - 200);
    }

    for (int w: {1, 2, 4, 6, 8, 10, 12, 14, 16, 18}) {
        PP(w);
        if (w == 10) SmartA();
    }

    for (int w: { 20 }) {
        PP(w);
        P(w, 225, 4, 7.5875);
        I(w, 400);
    }
}