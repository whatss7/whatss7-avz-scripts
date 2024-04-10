#include "../walib.h"

void AScript() {
    const int i_len = 1250, short_i_len = 1150;
    Init({ 
        AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ALILY_PAD, ADOOM_SHROOM, 
        APUMPKIN, APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AUMBRELLA_LEAF
    });
    C(1, -599, { ASUN_SHROOM, ACOFFEE_BEAN }, 5, 1);
    C(1, -599 + 751, { ASUN_SHROOM, ACOFFEE_BEAN }, 6, 1);
    aIceFiller.Start({{1, 1}, {2, 1}});
    for (int w: {1}) {
        PP(w);
        DD(w);
    }
    for (int w: {2, 4, 6, 8, 10, 12, 14, 16, 18}) {
        PP(w);
        if (w == 10) {
            TempC(w, 300 - 751, AUMBRELLA_LEAF, 2, 2, 400);
            TempC(w, 300, AUMBRELLA_LEAF, 5, 2, 400);
        }
    }
    for (int w: {3, 5, 7, 11, 13, 15, 17}) {
        if (w == 3) {
            C(w - 1, 601 + 1 - CBT - ADT, ACOFFEE_BEAN, 1, 1);
        } else {
            I(w, 1, 601);
        }
        PP(w, i_len - 200);
        DD(w, i_len - 200 + 380, 2.3);
    }
    waStopGigaBanCols = { 9 };
    for (int w: {9, 19}) {
        I(w, 100);
        if (w == 19) {
            AConnect(ATime(w, 101), [](){
                aIceFiller.Stop();
            });
        }
        PP(w, short_i_len - 200);
        DD(w, short_i_len - 200 + 380, 2.3);
        N(w, short_i_len + PCP, {{3, 9}, {4, 9}});
        DD(w, short_i_len + PCP + 220, 8.5);
        PPExceptOne(w, short_i_len + 601 + i_len - 200, 8, { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM });
        PPLast(w, 4300);
        MaidDance(w, short_i_len + 601 + i_len - 200, w + 1, PCP);
    }
    for (int w: {20}) {
        P(w, 225, 4, 7.5875);
        PP(w, 309, 9, {2, 2, 5, 5});
        PP(w, 409, 9, {2, 2, 5, 5});
        PPExceptOne(w, 1080);
        BlockLast(w, 1085, 3655);
        PPLast(w, 3655);
        AtEnd([](){
            ARemovePlant(1, 1);
            ARemovePlant(2, 1);
            ARemovePlant(5, 1);
            ARemovePlant(6, 1);
        });
    }
}