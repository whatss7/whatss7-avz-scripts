#include "../walib.h"

int crate_pos = 2;

void NextCratePos(int wave, int time) {
    AConnect(ATime(wave, time), [](){
        crate_pos = (crate_pos - 1) % 3 + 2;
    });
}

void AScript() {
    Init({AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ASQUASH, AFLOWER_POT, AUMBRELLA_LEAF});

    const int i_len = 1250, a_len = 601;
    // Ia-PP | PP | Ia-PP | PP | N | PP | PP

    C(1, -599, AFLOWER_POT, 3, 3);
    for (int w: { 1, 2, 4, 6, 7, 9, 10, 12, 14, 16, 17, 19 }) {
        PP(w, a_len - 200);
        if (w == 9 || w == 19) {
            PP(w, a_len + i_len - 200);
            PP(w, a_len + i_len + a_len - 200);
            N(w, a_len + i_len + a_len * 2 - 200, crate_pos, 9);
            NextCratePos(w, a_len + i_len + a_len * 2 - 200 + 1);
        }
    }
    for (int w: { 3, 8, 11, 13, 18 }) {
        ManualI(w, 1, 3, 3, a_len);
        if (w == 13) A(w, 650, 3, 8);
        else TempC(w, 650 - SDT, ASQUASH, crate_pos, 8, 651);
        PP(w, i_len - 200, 8.5);
    }
    for (int w: { 5, 15 }) {
        ZomboniN(w, a_len - 200, crate_pos, 9);
        NextCratePos(w, a_len - 200 + 1);
    }
}