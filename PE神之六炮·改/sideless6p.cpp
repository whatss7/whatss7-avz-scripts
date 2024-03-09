#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({ AUMBRELLA_LEAF, ATALL_NUT, AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ASQUASH });
    WAAutoManageCob();
    WAFixNuts();
    const int i_len = 1800, a_len = 900;
    // I-PP
    for (int w: { 3, 6, 9, 10, 13, 16, 19, 20 }) {
        ManualI(w, 1, 1, 4, a_len);
        PP(w, i_len - 200, 8.5);
        if (w == 9 || w == 19 || w == 20) {
            PP(w, i_len + a_len - 200);
            PP(w, i_len + a_len * 2 - 200);
        }
        if (w == 10 || w == 20) {
            TempC(w, -720, ASQUASH, 2, 6, -405);
            TempC(w, -401, AUMBRELLA_LEAF, 2, 6, 400);
            TempC(w, 350, AUMBRELLA_LEAF, 5, 6, 400);
        }
    }
    // PP #1
    for (int w: { 1, 4, 7, 11, 14, 17 }) {
        PP(w, a_len - 200, 8.5);
    }
    // PP #2
    for (int w: { 2, 5, 8, 12, 15, 18 }) {
        PP(w, a_len - 200, 8.5);
    }
}