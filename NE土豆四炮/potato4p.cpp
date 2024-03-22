#include "../walib.h"

void AScript() {
    Init({
        APOTATO_MINE, AUMBRELLA_LEAF, AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, 
        ACHERRY_BOMB, AJALAPENO, ASQUASH, ATALL_NUT, ABLOVER
    });
    AutoBlover(2, 1);

    int short_len = 1615, long_len = 1900;

    C(1, -599, ATALL_NUT, 1, 2);
    for (int w: {2, 7, 12, 17}) {
        N(w, 500, {{3, 9}, {3, 8}, {2, 8}, {1, 8}});
    }
    for (int w: {3, 8, 13, 18}) {
        A(w, PCP, 2, 9);
        J(w, PCP, 5, 1);
        C(w, PCP - 182, ASQUASH, 4, 9);
    }
    for (int w: {1, 4, 9, 10, 14, 19}) {
        PP(w);
        if (w == 9 || w == 19) {
            ManualI(w, 601 + 1, 5, 1);
            PP(w, 601 + short_len - 200, 8.5);
            ManualI(w, 601 + short_len + 1, 5, 1);
            PP(w, 601 + short_len + long_len - 200, 8.5);
        }
        if (w == 10) {
            TempC(w, -500, AUMBRELLA_LEAF, 3, 3, 400);
            TempC(w, 300, AUMBRELLA_LEAF, 2, 7, 400);
        }
    }
    for (int w: {5, 15}) {
        ManualI(w, 1, 5, 1, 601);
        PP(w, short_len - 200, 8.5);
    }
    for (int w: {6, 11, 16}) {
        C(w - 1, (w == 11 ? 601 : short_len) - 648, APOTATO_MINE, 3, 3);
        ManualI(w, 1, 5, 1, w == 11 ? 601 : short_len);
        PP(w, long_len - 200, 8.5);
    }
    for (int w: {20}) {
        TempC(w, -500, AUMBRELLA_LEAF, 3, 3, 400);
        TempC(w, 300, AUMBRELLA_LEAF, 2, 7, 400);
        PP(w);
        ManualI(w, 601 + 1, 5, 1);
        PP(w, 601 + short_len - 200, 8.5);
        ManualI(w, 601 + short_len + 1, 5, 1);
        PP(w, 601 + short_len + long_len - 200, 8.5);
    }
}