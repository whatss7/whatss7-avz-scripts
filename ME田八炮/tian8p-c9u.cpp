#include "../walib.h"

int crate_pos = 2;

void AScript() {
    Init({AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ASQUASH, AFLOWER_POT, AUMBRELLA_LEAF});

    const int i_len = 1250, a_len = 601;
    // Ia-PP | PP | Ia-PP | PP | N | PP | PP

    // w1-w9: PP|Ia-PP|PP|IA-PP|PP|N|PP|PP|I-PP(|PP|I-PP|PP)
    // w10-w19: PP|PP|Ia-PP|PP|IA-PP|PP|N|PP|PP|I-PP(|PP|I-PP|PP)

    C(1, -599, AFLOWER_POT, 3, 3);
    AtEnd([](){ ARemovePlant(3, 3, AFLOWER_POT); });
    TempC(10, 300 - 751, AUMBRELLA_LEAF, 2, 4, 400);
    TempC(10, 300, AUMBRELLA_LEAF, 4, 4, 400);
    TempC(20, 300 - 751, AUMBRELLA_LEAF, 2, 4, 400);
    TempC(20, 300, AUMBRELLA_LEAF, 4, 4, 400);
    for (int w: { 1, 3, 5, 7, 8, 10, 11, 13, 15, 17, 18 }) {
        PP(w, a_len - 200);
    }
    for (int w: { 2, 4, 9, 12, 14, 19, 20 }) {
        ManualI(w, 1, 3, 3, a_len);
        if (w == 2 || w == 12) TempC(w, 650 - SDT, ASQUASH, w == 2 ? 2 : 3, 8, 1250);
        else if (w == 4 || w == 14) A(w, 650, 3, 8);
        PP(w, i_len - 200);
        if (w == 9 || w == 19 || w == 20) {
            PP(w, i_len + a_len - 200);
            PP(w, i_len + a_len + i_len - 200);
            PP(w, i_len + a_len + i_len + a_len - 200);
        }
    }
    for (int w: { 6, 16 }) {
        ZomboniN(w, a_len - 200, w == 6 ? 2 : 3, 9);
    }
}