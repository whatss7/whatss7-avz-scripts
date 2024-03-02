#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ACOFFEE_BEAN, ALILY_PAD, ATALL_NUT, APUMPKIN, ACHERRY_BOMB, AUMBRELLA_LEAF, APUFF_SHROOM});
    // ch4-N: I-PP | I-PP | I-N | PP
    const int i1_len = 1800, i2_len = 1200;
    aIceFiller.Start({{3, 1}, {4, 1}});
    WAFixNuts(1, -598);
    for (int w: {1}) {
        N(w, 341, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
        C(w, 100 + 751, {ALILY_PAD, ATALL_NUT}, 4, 7);
        C(w, 100 + 751 * 2, ALILY_PAD, 3, 1);
        C(w, 100 + 751 * 3, {ALILY_PAD, ACHERRY_BOMB}, 3, 7);
        C(w, 100 + 751 * 4, ALILY_PAD, 4, 1);
        C(w, 100 + 751 + 3001, ATALL_NUT, 3, 7);
    }
    for (int w: {3, 7, 13, 17}) {
        if (w == 3) {
            C(w - 1, 1 + 601 - ADT - CBT, ACOFFEE_BEAN, 5, 1);
        } else {
            I(w, 1, 601);
        }
        PP(w, i1_len - 200, 8.45);
    }
    for (int w: {4, 8, 14, 18}) {
        if (w == 4) {
            C(w - 1, 1 + i1_len - ADT - CBT, ACOFFEE_BEAN, 2, 1);
        } else {
            I(w, 11, i1_len);
        }
        PP(w, i1_len - 200, 8.45);
    }
    for (int w: {5, 9, 11, 15, 19}) {
        I(w, 11, w == 11 ? 601 : i1_len);
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