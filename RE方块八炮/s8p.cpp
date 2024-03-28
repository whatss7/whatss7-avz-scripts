#include "../walib.h"

// 1: 14炮激活，14炮拦截；2：44炮激活，14炮拦截
int status = 1;
const int i_len = 2000;

void UseCob(int w) {
    AConnect(ATime(w, 1), [w](){
        if (status == 1) {
            RoofP(w, i_len - 200, 1, 2, 8.75);
            RoofP(w, i_len - 200, 4, 4, 8.75);
            RoofP(w, i_len - 200 + 223, 1, 2, 6.9);
            RoofP(w, i_len - 200 + 223, 4, 4, 6.9);
        } else {
            RoofP(w, i_len - 200, 4, 2, 8.75);
            RoofP(w, i_len - 200, 4, 4, 8.75);
            RoofP(w, i_len - 200 + 223, 1, 2, 6.9);
            RoofP(w, i_len - 200 + 223, 4, 4, 6.9);
        }
        status = 3 - status;
    });
}

void AScript() {
    Init({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, AFLOWER_POT, ACHERRY_BOMB, AJALAPENO});
    aIceFiller.Start({{1, 3}, {3, 3}, {5, 3}});
    for (int w: WaveList(1, 8) + WaveList(11, 18)) {
        I3(w, 12, i_len);
        UseCob(w);
    }
    for (int w: { 9 }) {
        I3(w, 12, i_len);
        AConnect(ATime(w, 1), [w](){
            // PSN
            if (status == 1) {
                RoofP(w, i_len - 200, 1, 2, 8.75);
                RoofP(w, i_len - 200, 4, 4, 8.75);
                RoofP(w, i_len - 200, 1, 2, 8.75);
                RoofP(w, i_len - 200, 4, 4, 8.75);
                N(w, i_len - 200 + 220, 2, 6);
            } else {
                RoofP(w, i_len - 200, 4, 2, 8.75);
                RoofP(w, i_len - 200, 4, 4, 8.75);
                RoofP(w, i_len - 200, 1, 2, 8.75);
                RoofP(w, i_len - 200, 4, 4, 8.75);
                N(w, i_len - 200 + 220, 2, 6);
            }
            status = 3 - status;
        });
    }
    for (int w: { 19 }) {
        I3(w, 12, i_len);
        AConnect(ATime(w, 1), [w](){
            // PSN
            if (status == 1) {
                RoofP(w, i_len - 200, 1, 2, 8.75);
                RoofP(w, i_len - 200, 4, 4, 8.75);
                RoofP(w, i_len - 200, 1, 2, 8.75);
                RoofP(w, i_len - 200, 4, 4, 8.75);
                N(w, i_len - 200 + 270, 3, 6);
            } else {
                RoofP(w, i_len - 200, 4, 2, 8.75);
                RoofP(w, i_len - 200, 4, 4, 8.75);
                RoofP(w, i_len - 200, 1, 2, 8.75);
                RoofP(w, i_len - 200, 4, 4, 8.75);
                N(w, i_len - 200 + 270, 3, 6);
            }
            status = 3 - status;
        });
    }
}
