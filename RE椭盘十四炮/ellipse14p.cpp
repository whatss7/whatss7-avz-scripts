#include "../walib.h"

int dy_cob = 3;

void DynamicP(int w, int t, int row, float col) {
    AConnect(ATime(w, t - RCFT), [=](){
        RoofP(w, t, dy_cob, row, col);
        dy_cob = 8 - dy_cob;
    });
}

void AScript() {
    Init({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, AFLOWER_POT});
    StartIceFiller({{2, 3}, {4, 6}});
    const int i_len = 1800;
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
        DynamicP(w, 1700 - 200, 2, 9);
        RoofP(w, 1700 - 200, 6, 6, 9);
    }
    for (int w: {3, 12}) {
        // I3
        I3(w, 11, 1700);
        // Pd/PD，上半解决漏的跳跳
        RoofP(w, 410, 2, 2, 9);
        RoofP(w, 410, 4, 4, 9);
        RoofP(w, 410 + 320, 1, 2, 4.5);
        RoofP(w, 410 + 220, 4, 4, 8.5);
        // 垫一下小丑
        TempC(w, 950, AFLOWER_POT, 2, 9, 1150);
        // B
        RoofP(w, 1140, 7, 4, 8.1);
        // PP
        DynamicP(w, i_len - 200, 2, 9);
        RoofP(w, i_len - 200, 6, 4, 9);
    }
    for (int w: WaveList(4, 8) + WaveList(13, 18)) {
        // I3
        I3(w, 11, i_len);
        // PPDD
        RoofP(w, 410, 2, 2, 9);
        RoofP(w, 410, 4, 4, 9);
        RoofP(w, 630, 1, 2, 8.5);
        RoofP(w, 630, 4, 4, 8.5);
        // 垫一下小丑
        TempC(w, 950, AFLOWER_POT, 2, 9, 1150);
        // B
        RoofP(w, 1140, 7, 4, 8.1);
        // PP
        DynamicP(w, i_len - 200, 2, 9);
        RoofP(w, i_len - 200, 6, 4, 9);
    }
    for (int w: {9, 19}) {
        // I3
        I3(w, 11, i_len);
        RoofP(w, 410, 2, 2, 9);
        RoofP(w, 410, 4, 4, 9);
        RoofP(w, 630, 1, 2, 8.5);
        RoofP(w, 630, 4, 4, 8.5);
        // 不分离了，直接炸，巨人1282才能对9普通举锤，篮球1091碾压，1039全伤巨人，可以1085生效
        // 考虑核弹间隔，w9 1085, 乐观认为w9拖到2990+745, w10 601, w11 1700, w12-w18 1800，间隔17565
        // 因此，w9需要考虑提前用核
        if (w == 9) {
            C(w, 1085 - ADT - 751, AFLOWER_POT, 2, 8);
            A(w, 1085, 2, 9);
            RoofP(w, 1085, 7, 4, 9);
            N(w, 1085 + 220, 2, 8);
        } else {
            C(w, 1085 - ADT - 751, AFLOWER_POT, 2, 8);
            A(w, 1085, 2, 9);
            RoofP(w, 1085, 7, 4, 9);
            N(w, 1085 + 220, 2, 8);
        }
        DynamicP(w, 1085 + 220 + 220, 2, 8.95);
        RoofP(w, 1085 + 220 + 220, 6, 4, 8.95);
        // 现在只剩一血红了
        // 需要原来的热过渡炮收尾，这一炮2085转好
        // 1085+220=1305激活
        // walk([453, 450])=671，原速下1179不会锤8炮，11冰下则是2379不会锤8炮
        // walk([453, 865])=592，原速下1594不会锤7炮，11冰下则是2794不会锤7炮
        // 上路2790收尾，下路2380收尾炮
        RoofP(w, 2790, 2, 2, 8.5);
        RoofP(w, 2380, 4, 4, 9);
    }
}