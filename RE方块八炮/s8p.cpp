#include "../walib.h"

// 1: 14炮激活，14炮拦截；2：44炮激活，14炮拦截
int status = 1;
const int a_len = 750, i_len = 2000;

void UseCob_i(int w) {
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

void UseCob_a(int w) {
    AConnect(ATime(w, 1), [w](){
        if (status == 1) {
            RoofP(w, a_len - 200, 1, 2, 8.5);
            RoofP(w, a_len - 200, 4, 4, 8.5);
            RoofP(w, a_len - 200 + 110, 1, 2, 7.4);
            RoofP(w, a_len - 200 + 110, 4, 4, 7.4);
        } else {
            RoofP(w, a_len - 200, 4, 2, 8.5);
            RoofP(w, a_len - 200, 4, 4, 8.5);
            RoofP(w, a_len - 200 + 110, 1, 2, 7.4);
            RoofP(w, a_len - 200 + 110, 4, 4, 7.4);
        }
        status = 3 - status;
    });
}

void AScript() {
    Init({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, AFLOWER_POT, AJALAPENO, ASQUASH, ADOOM_SHROOM});
    StartReloadMode();
    aIceFiller.Start({{1, 3}, {3, 3}, {5, 3}});
    for (int w: {1, 10}) {
        UseCob_a(w);
    }
    for (int w: WaveList(2, 8) + WaveList(11, 18)) {
        I3(w, 12, w == 2 || w == 11? a_len : i_len);
        UseCob_i(w);
    }
    for (int w: { 9, 19 }) {
        I3(w, 12, i_len);
        AConnect(ATime(w, 1), [w](){
            // 收尾I-PSN-PS
            // PSN，N伤不到本波仅作为拦截，剩二血红，因此接PS
            // 加速波后的冰波激活炮在本波激活炮后200+745+x+1800=2745+x<3475发射，加速波波长至少是730，取750
            // 如果考虑3550PS，本波结束后745+550=1295前加速波激活炮需要转好，则PSN的PS要在3750-2180=1570前生效
            // 冰车1555碾压6普通，所以考虑1550生效
            if (status == 1) {
                RoofP(w, 1550, 1, 2, 8.875);
                RoofP(w, 1550, 4, 4, 8.875);
                RoofP(w, 1550, 1, 2, 8.875);
                RoofP(w, 1550, 4, 4, 8.875);
                N(w, 1550 + 220, 2, 6);
                RoofP(w, 3550, 4, 2, 7);
                RoofP(w, 3550, 4, 4, 7);
                RoofP(w, 3550, 1, 2, 7);
                RoofP(w, 3550, 4, 4, 7);
            } else {
                RoofP(w, 1550, 4, 2, 8.875);
                RoofP(w, 1550, 4, 4, 8.875);
                RoofP(w, 1550, 1, 2, 8.875);
                RoofP(w, 1550, 4, 4, 8.875);
                N(w, 1550 + 220, 2, 6);
                RoofP(w, 3550, 1, 2, 7);
                RoofP(w, 3550, 4, 4, 7);
                RoofP(w, 3550, 1, 2, 7);
                RoofP(w, 3550, 4, 4, 7);
            }
        });
    }
    for (int w: { 20 }) {
        I3(w, 12, i_len);
        AConnect(ATime(w, 1), [w](){
            // 核转不过来，使用I-PD-PSN
            // 此处核则需要全伤巨人
            // 使用PD时，红眼全程不投掷，因此3555cs锤五列炮
            if (status == 1) {
                RoofP(w, 1550, 1, 2, 8.75);
                RoofP(w, 1550, 4, 4, 8.75);
                RoofP(w, 1550 + 220, 1, 2, 7.4);
                RoofP(w, 1550 + 220, 4, 4, 7.4);
                RoofP(w, 3550, 4, 2, 7);
                RoofP(w, 3550, 4, 4, 7);
                RoofP(w, 3550, 1, 2, 7);
                RoofP(w, 3550, 4, 4, 7);
            } else {
                RoofP(w, 1550, 4, 2, 8.875);
                RoofP(w, 1550, 4, 4, 8.875);
                RoofP(w, 1550 + 220, 1, 2, 7.4);
                RoofP(w, 1550 + 220, 4, 4, 7.4);
                RoofP(w, 3550, 1, 2, 7);
                RoofP(w, 3550, 4, 4, 7);
                RoofP(w, 3550, 1, 2, 7);
                RoofP(w, 3550, 4, 4, 7);
            }
            // 巨人3143cs命中6普通，考虑约3140窝瓜生效，则约2950种，辣椒则可以2850种
            // 若窝瓜没压到巨人，则巨人本身速度较慢，不构成对核的威胁
            TempC(w, 2850, AFLOWER_POT, 3, 6);
            TempC(w, 2851, AJALAPENO, 3, 6);
            TempC(w, 2952, ASQUASH, 3, 6, 3250);
            N(w, 3550, 3, 6);
        });
    }
}
