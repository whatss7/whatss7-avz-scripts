#include "../walib.h"

int dy_cob = 3;

void DynamicP(int w, int t, int row, int col) {
    AConnect(ATime(w, t - RCFT), [=](){
        RoofP(w, t, dy_cob, row, col);
        dy_cob = 8 - dy_cob;
    });
}

void AScript() {
    Init({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, AFLOWER_POT});
    StartIceFiller({{2, 3}, {4, 6}});
    const int i_len = 1750;
    for (int w: {1, 10}) {
        // PPDDDD, 第二个D顺手解决下波冰车
        DynamicP(w, 401, 2, 9);
        RoofP(w, 401, 6, 4, 9);
        RoofP(w, 510, 2, 2, 9);
        RoofP(w, 510, 4, 4, 9);
        RoofP(w, 635, 1, 2, 9);
        RoofP(w, 635, 4, 4, 9);
    }
    for (int w: {2, 11}) {
        // I-B-PP
        I3(w, 16, 601);
        TempC(w, 950, AFLOWER_POT, 2, 9, 1150);
        RoofP(w, 1140, 7, 4, 8.1);
        DynamicP(w, i_len - 200, 2, 9);
        RoofP(w, i_len - 200, 6, 6, 9);
    }
    for (int w: WaveList(3, 9) + WaveList(12, 19)) {
        I3(w, 11, i_len);
        RoofP(w, 410, 2, 2, 9);
        RoofP(w, 410, 4, 4, 9);
        RoofP(w, 630, 1, 2, 8.5);
        RoofP(w, 630, 4, 4, 8.5);
        TempC(w, 950, AFLOWER_POT, 2, 9, 1150);
        RoofP(w, 1140, 7, 4, 8.1);
        DynamicP(w, i_len - 200, 2, 9);
        RoofP(w, i_len - 200, 6, 4, 9);
    }
}