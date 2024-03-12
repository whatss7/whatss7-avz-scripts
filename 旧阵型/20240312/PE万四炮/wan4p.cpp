#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ACOFFEE_BEAN, ALILY_PAD, ATALL_NUT, APUMPKIN, ACHERRY_BOMB, APUFF_SHROOM, ASUN_SHROOM});
    // ch4-N: I-PP | I-PP | I-N | PP
    const int i1_len = 1750, i2_len = 1200;
    aIceFiller.Start({{1, 1}, {6, 2}, {4, 4}});
    C(1, -599, ALILY_PAD, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
    C(1, 152, ALILY_PAD, 4, 4);
    C(3, 0, {ALILY_PAD, ATALL_NUT}, 3, 7);
    WAFixNuts(1, -598);
    for (int w: {1}) {
        N(w, 341, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
    }
    for (int w: {3, 7, 13, 17}) {
        I3(w, 11, 601);
        PP(w, i1_len - 200, 8.45);
    }
    for (int w: {4, 8, 14, 18}) {
        I3(w, 11, i1_len);
        PP(w, i1_len - 200, 8.45);
    }
    for (int w: {5, 9, 11, 15, 19}) {
        I3(w, 11, w == 11 ? 601 : i1_len);
        N(w, i2_len - 200, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
        if (w == 9 || w == 19) {
            PP(w, i2_len + 601 - 200, 8.45);
            PP(w, i2_len + 601 + i1_len - 200, 8.45);
        }
    }
    for (int w: {2, 6, 10, 12, 16}) {
        PP(w, 341);
    }
    for (int w: {20}) {
        P(w, 225, 4, 7.5875);
        I(w, 400);
        AConnect(ATime(w, 400), [](){ aIceFiller.Stop(); });
        PP(w, i1_len - 200 + 100, 8.45);
        P(w, i1_len - 200 + 100, 5, 8.45);
        N(w, i1_len - 200, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
    }
}