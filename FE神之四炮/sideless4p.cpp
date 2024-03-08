#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ACHERRY_BOMB, ABLOVER, APUMPKIN});
    WACheck(true, false);
    WAAutoManageCob();
    WAStartBlover();
    WAFixNuts();
    // I-PP | I-PP | N | PP
    const int i_len = 1750, a_len = 875;
    // w1 / w10 PP 601cs
    for (int w: {1, 10}) {
        PP(w);
        if (w == 10) SmartA();
    }
    // I-PP #1
    for (int w: { 5, 9, 11, 15, 19 }) {
        ManualI(w, 1, 3, 7, w == 11 ? 601 : a_len);
        PP(w, i_len - 200, 8.5);
        if (w == 9 || w == 19) {
            ManualI(w, i_len + 1, 3, 7);
            PP(w, i_len * 2 - 200, 8);
            N(w, i_len * 2 + a_len - 200, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
        }
    }
    // I-PP #2
    for (int w: { 2, 6, 12, 16 }) {
        ManualI(w, 1, 3, 7, w == 2 ? 601 : i_len);
        PP(w, i_len - 200, 8.5);
    }
    // N
    for (int w: { 3, 7, 13, 17 }) {
        N(w, a_len - 200, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
    }
    // PP
    for (int w: { 4, 8, 14, 18 }) {
        PP(w, a_len - 200, 8.5);
    }
    for (int w: {20}) {
        PP(w);
        ManualI(w, 601 + 1, 2, 1);
        PP(w, 601 + i_len - 200, 8.5);
        ManualI(w, 601 + i_len + 1, 2, 1);
        PP(w, 601 + i_len * 2 - 200, 8);
    }
}