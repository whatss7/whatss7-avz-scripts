#include "../walib.h"

void AScript() {
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, APUMPKIN, ACHERRY_BOMB,
        APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT
    });
    const int i_len = 1149;
    StartIceFiller({{4, 9}});
    AutoFixNuts();

    // 临时存冰
    C(1, -599, AICE_SHROOM, 1, 9);
    C(2, 100 - ADT - CBT, ACOFFEE_BEAN, 1, 9);
    C(10, -745, AICE_SHROOM, 2, 9);
    C(10, 445, AM_ICE_SHROOM, 1, 9);
    C(10, 230 - ADT - CBT, ACOFFEE_BEAN, 2, 9);
    C(12, 100 - ADT - CBT, ACOFFEE_BEAN, 1, 9);

    for (int w: {2, 4, 6, 8, 10, 12, 14, 16, 18}) {
        if (w != 2 && w != 10 && w != 12) I(w, 100);
        if (w == 10) PP(w, 440, 8.275, {1, 5});
        else PP(w, 440, 7.4, {1, 5});
        PP(w, i_len - 200);
        DD(w, i_len - 200 + 212, 7.975);
        if (w == 19) {
            PP(w, i_len + 318, 9, {2, 5});
            DD(w, i_len + 318 + 215, 9);
            PPExceptOne(w, i_len + 318 + 215, 9);
            StopGiga(w, i_len + 318 + 215, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT}, 4300);
            MaidDance(w, i_len + 318 + 215, w + 1, 318 - 460);
            PPLast(w, 4300);
        }
    }
    for (int w: {1, 3, 5, 7, 11, 13, 15, 17}) {
        PP(w, 282, 9, {2, 2, 5, 5});
        if (w == 1 || w == 11) A(w, 225 + 1, 2, 9);
        DD(w, 282 + 110, 9);
    }
    for (int w: {9, 19}) {
        PP(w, 282);
        PP(w, 282 + 95, 9);
        DD(w, 282 + 205, 9);
        PPExceptOne(w, 601 + 440, 9, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT});
        MaidDance(w, 492, w + 1, 318 - 460);
        PPLast(w, 4300);
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