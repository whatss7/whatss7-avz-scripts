#include "../walib.h"

void AScript() {
    Init({AICE_SHROOM, ADOOM_SHROOM, AM_DOOM_SHROOM, AFLOWER_POT, AUMBRELLA_LEAF});

    const int a_len = 700;

    C(1, -599, AFLOWER_POT, 3, 3);
    for (int w: {1, 2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 16, 17, 18, 19}) {
        PP(w, a_len - 200);
        if (w == 9 || w == 19) {
            PP(w, a_len * 3 - 200);
            PP(w, a_len * 4 - 200);
            PP(w, a_len * 5 - 200);
        }
    }
    for (int w: {10}) {
        WhiteN(w, PCP, 4, 9);
        ManualI(w, 400, 3, 3);
    }
    for (int w: {20}) {
        PP(w, a_len - 200);
        ManualI(w, 400, 3, 3);
        PP(w, a_len * 2 - 200);
        PP(w, a_len * 3 - 200);
        PP(w, a_len * 4 - 200);
    }
    for (int w: {5, 15}) {
        ZomboniN(w, a_len - 200, w == 5 ? 3 : 2, 9);
    }
}