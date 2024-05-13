#include "../walib.h"

void AScript() {
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ALILY_PAD, APUFF_SHROOM,
        ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, AWALL_NUT
    });
    const int i_len = 1543, a_len = 681;
    waStopGigaBanCols = {8, 9};
    // I-PPDD | PPDD | I-PPDD | NDD | PPDD
    for (int w: {1, 2, 5, 7, 10, 12, 15, 17}) {
        PP(w, a_len - 200, 8.5);
        DD(w, a_len - 200 + 110, 7.4125);
    }
    for (int w: {3, 6, 8, 11, 13, 16, 18}) {
        ManualI(w, 1, 1, 6, 681);
        PP(w, i_len - 200, 8.5);
        DD(w, i_len - 200 + 220, 7.4125);
    }
    for (int w: {4, 9, 14, 19}) {
        N(w, a_len - 200, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
        DD(w, a_len - 200 + 110, 7.4125);
        if (w == 9 || w == 19) {
            PP(w, a_len + a_len - 200);
            DD(w, a_len + a_len - 200 + 110);
            ManualI(w, a_len + a_len + 1, 1, 6);
            PPExceptOne(w, a_len + a_len + i_len - 200, 8.5, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT});
            MaidDance(w, a_len + a_len + i_len - 200, w + 1, w == 9 ? a_len - 200 : -200);
            PPLast(w, 4300);
        }
    }
    for (int w: {20}) {
        P(w, 225, 4, 7.5875);
        PP(w, 309, 9, {2, 2, 5, 5});
        PP(w, 409, 9, {2, 2, 5, 5});
        PPExceptOne(w, 815);
        BlockLast(w, 820, 4300);
        UntilOneLeft(w, 820, nullptr,
            [=](){
                ACard(APUFF_SHROOM, GetLastZombie()->Row() + 1, 8);
                AConnect(ANowDelayTime(751), [](){ ACard(APUFF_SHROOM, GetLastZombie()->Row() + 1, 7); });
            },
            [=](){
                ARemovePlant(GetLastZombie()->Row() + 1, 8);
                ARemovePlant(GetLastZombie()->Row() + 1, 7);
            }
        );
        PPLast(w, 4300);
    }
}