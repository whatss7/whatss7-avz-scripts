#include "../walib.h"


void AScript() {
    Init({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN});
    aIceFiller.Start({{2, 3}, {4, 6}});
    for (int w: WaveList(1, 20)) {
        I3(w, 11, 1800);
        RoofP(w, 410, 2, 2, 9);
        RoofP(w, 410, 7, 4, 9);
        RoofP(w, 630, 1, 2, 8.5);
        RoofP(w, 630, 6, 4, 8.5);
        // 经各130000只扶梯测试，3列炮和5列炮，11冰波1140炸(4, 7.975)全收3/4列扶梯
        // 但是分离炮有可能还要作为清丑手段
        RoofP(w, 1140, w % 2 == 1 ? 3 : 5, 4, 7.975);
        RoofP(w, 1600, 4, 2, 9);
        RoofP(w, 1600, 4, 4, 9);
    }
}