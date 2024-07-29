#include "../walib.h"

void AScript() {
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ATALL_NUT, APUMPKIN,
        ACHERRY_BOMB, APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT
    });
    const int i_len = 1149;
    StartIceFiller({{3, 9}, {4, 9}});
    AutoFixNuts();
    for (int w: {1}) {
        PP(w, 359);
        DD(w, 359 + 110, 7.8125);
    }
    for (int w: {10}) {
        PP(w, 318, 9, {2, 5, 5});
        P(w, 401, 2, 9);
        D(w, 318 + 110, 5, 9);
        A(w, 401 + 111, 1, 9);
    }
    for (int w: {3, 5, 7, 9, 11, 13, 15, 17, 19}) {
        I(w, 100);
        PP(w, 440, 7.4, {1, 5});
        PP(w, i_len - 200);
        DD(w, i_len - 200 + 215, 7.975);
        if (w == 9 || w == 19) {
            PP(w, i_len + 318, 9, {2, 5});
            DD(w, i_len + 318 + 215, 9);
            PPExceptOne(w, i_len + 318 + 215, 9);
            StopGiga(w, i_len + 318 + 215, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT}, 4300);
            MaidDance(w, i_len + 318 + 215, w + 1, 318 - 460);
            PPLast(w, 4300);
        }
    }
    for (int w: {2, 4, 6, 8, 12, 14, 16, 18}) {
        PP(w, 318, 9, {2, 2, 5, 5});
        DD(w, 318 + 107, 9);
    }
    for (int w: {20}) {
        P(w, 225, 4, 7.5875);
        PP(w, 309, 9, {2, 2, 5, 5});
        PP(w, 409, 9, {2, 2, 5, 5});
        PPExceptOne(w, 814);
        BlockLast(w, 820, 3800);
        PPLast(w, 3800);
    }
}