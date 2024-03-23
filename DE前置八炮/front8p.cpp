#include "../walib.h"

void AScript() {
    Init({ AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ACOFFEE_BEAN, APUFF_SHROOM, ASUN_SHROOM });
    aIceFiller.Start({{2, 1}, {4, 1}});
    const int i_len = 1500;
    for (int w: { 4, 7, 11, 14, 17 }) {
        I(w, 1, 601);
        PP(w, i_len - 200, 8.5);
    }
    for (int w: { 2, 5, 8, 12, 15, 18 }) {
        I(w, 1, w == 2 ? 601 : i_len);
        PP(w, 465, 7.4125);
        PP(w, i_len - 200, 8.5);
    }
    for (int w: { 1, 3, 6, 9, 10, 13, 16, 19 }) {
        PP(w);
        if (w == 9 || w == 19) {
            PP(w, 601 + i_len - 200, 8.5);
            PP(w, 601 + i_len + 465, 8.5);
            PP(w, 601 + i_len + i_len - 200, 8.5);
        }
    }
    for (int w: { 20 }) {
        PP(w, 309, 9, {2, 2, 4, 4});
        PP(w, 409, 9, {2, 2, 4});
        A(w, 409, 4, 9);
        I(w, 409);
    }
}