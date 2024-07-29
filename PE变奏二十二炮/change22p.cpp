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
        DD(w, 359 + 107, 7.8125);
        MultiTempC(w, 600, {ASCAREDY_SHROOM, AFLOWER_POT}, 9, {5, 6}, 610);
    }
    for (int w: {10}) {
        P(w, 318, 2, 9);
        P(w, 394, 2, 8.55);
        A(w, 394 + 110, 1, 9);
        P(w, 275, 5, 9);
        D(w, 275 + 124, 5, 8);
        MultiTempC(w, 510, {APUFF_SHROOM, ASUN_SHROOM}, 9, {5, 6}, 601);
    }
    for (int w: {3, 5, 7, 9, 11, 13, 15, 17, 19}) {
        I(w, 100);
        PP(w, 440, 7.4, {1, 5});
        PP(w, i_len - 200);
        D(w, i_len - 200 + 220, 1, 7.975);
        D(w, i_len - 200 + 220, 5, 8.65);
        if (w == 9 || w == 19) {
            P(w, i_len + 318, 2, 9);
            D(w, i_len + 318 + 220, 1, 9);
            B(w, i_len + 20 + 220, 5, 9);
            PPExceptOne(w, i_len + 318 + 220, 9);
            StopGiga(w, i_len + 318 + 220, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT}, 4300);
            MaidDance(w, i_len + 318 + 220, w + 1, 318 - 460);
            PPLast(w, 4300);
        }
    }
    for (int w: {2, 4, 6, 8, 12, 14, 16, 18}) {
        PS(w, 318, 2, 9);
        D(w, 318 + 110, 1, 9);
        B(w, 20 + 225, 5, 9);
        D(w, 20 + 225 + 124, 5, 8.1);
        MultiTempC(w, 510, {APUFF_SHROOM, ASUN_SHROOM}, 9, {5, 6}, 601);
    }
    for (int w: {20}) {
        P(w, 225, 4, 7.5875);
        PP(w, 309, 9, {2, 2, 5, 5});
        // 左移一组炮炸蹦极
        PP(w, 409, 8.5, {2, 5});
        PP(w, 409, 9, {2, 5});
        PPExceptOne(w, 814);
        BlockLast(w, 820, 3800);
        PPLast(w, 3800);
    }
}