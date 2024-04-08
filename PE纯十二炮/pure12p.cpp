#include "../walib.h"

void AScript() {
    Init({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ALILY_PAD, APUMPKIN});
    C(1, -599, {ALILY_PAD, APUMPKIN}, 3, 9);
    C(1, -599 + 3001, {ALILY_PAD, APUMPKIN}, 4, 9);
    aIceFiller.Start({{3, 9}, {4, 9}});
    for (int w: {1, 3, 5, 7, 9, 11, 13, 15, 17, 19}) {
        I(w, 100, 601);
        PP(w, 949);
        PP(w, 949 + 380, 2.3);
        if (w == 9 || w == 19) {
            PP(w, 1149 + PCP);
        }
    }
    for (int w: {2, 4, 6, 8, 10, 12, 14, 16, 18}) {
        PP(w);
    }
}