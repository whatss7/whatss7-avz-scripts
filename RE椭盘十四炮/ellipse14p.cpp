#include "../walib.h"

int dy_cob = 3;

void DynamicP(int w, int t, int row, float col) {
    AConnect(ATime(w, t - RCFT), [=](){
        RoofP(w, t, dy_cob, row, col);
        dy_cob = 8 - dy_cob;
    });
}

// 将一个巨人移至1路保证收尾正确
void EnsureGiga(int wave) {
    AConnect(ATime(wave, 1), [=](){
        std::vector<AZombie *> candidates;
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.AtWave() + 1 != wave || zombie.Type() != AHY_32) continue;
            if (zombie.Row() + 1 == 1) return;
            candidates.push_back(&zombie);
        }
        auto &&zombie = *candidates[rand() % candidates.size()];
        zombie.Row() = 1 - 1;
        zombie.Ordinate() = 40;
    });
}

void AScript() {
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, AFLOWER_POT, ADOOM_SHROOM, 
        ACHERRY_BOMB, AJALAPENO, ASNOW_PEA, ASQUASH, ATALL_NUT
    });
    StartIceFiller({{2, 3}, {4, 6}, {1, 1}});
    StartReloadMode();
    const int i_len = 1800;
    for (int w: {1}) {
        TempC(w, -599, AFLOWER_POT, 1, 1);
        C(w, -599 + 751, AFLOWER_POT, 3, 9);
        RoofP(w, 265, 4, 4, 9);
        N(w, 450, 3, 9);
        RoofP(w, 450 + 110, 6, 4, 9);
        RoofP(w, 450 + 215, 7, 2, 5);
    }
    for (int w: {2}) {
        // PPDDDA, 第二个D解决下波冰车
        // 可用的炮：?42414, ?=3/5
        DynamicP(w, 379, 2, 9);
        RoofP(w, 379, 4, 4, 9);
        // PP之后，全部开始投掷，2列炮拦上半区，所以4列炮只用拦两行；为了樱桃能炸到冰车，515激活，下波21冰
        // 这里第一D上半因为要拦两波，没办法再同时全伤三行巨人
        RoofP(w, 379 + 119, 2, 2, 8.35);
        RoofP(w, 379 + 136, 4, 4, 8.45);
        RoofP(w, 379 + 119 + 137, 1, 2, 8.7);
        A(w, 379 + 136 + 120, 4, 9);
    }
    for (int w: {10}) {
        // PPDDDdA', 第二个D解决下波冰车，d炸三路解决蹦极，炸不到的一列用辣椒补，上半的冰车随后用樱桃收掉，顺便还能解决跳跳
        // 可用的炮：?62414, ?=3/5
        DynamicP(w, 379, 2, 9);
        RoofP(w, 379, 6, 4, 9);
        RoofP(w, 379 + 119, 2, 2, 8.4);
        RoofP(w, 379 + 119, 4, 4, 8.45);
        J(w, 379 + 119 + 137, 1, 6);
        RoofP(w, 379 + 119 + 205, 1, 3, 4.5);
        RoofP(w, 379 + 119 + 137, 4, 4, 8.8125);
    }
    for (int w: {3, 11}) {
        // I-B-PP
        I3(w, 21, 601);
        if (w == 11) {
            TempC(w, 950 - 751, AFLOWER_POT, 1, 9, 320);
            A(w, 315, 1, 9);
        }
        TempC(w, 950, AFLOWER_POT, 2, 9, 1150);
        C(w, 950 + 751, AFLOWER_POT, 1, 1);
        // 晚10cs冰，所以早10cs分离
        RoofP(w, 1130, 7, 4, 8.1);
        DynamicP(w, i_len - 200, 2, 9);
        RoofP(w, i_len - 200, 6, 6, 9);
    }
    for (int w: {4, 12}) {
        // I3
        I3(w, 11, i_len);
        // Pd/PD，上半解决漏的跳跳
        if (w == 4) J(w, 300, 1, 1);
        RoofP(w, 410, 2, 2, 9);
        RoofP(w, 410, 4, 4, 9);
        RoofP(w, 410 + 220, 1, 4, 8.7);
        RoofP(w, 410 + 335, 4, 2, 4.7625);
        // 垫一下小丑
        TempC(w, 950, AFLOWER_POT, 2, 9, 1150);
        // B
        RoofP(w, 1140, 7, 4, 8.1);
        // PP
        DynamicP(w, i_len - 200, 2, 9);
        RoofP(w, i_len - 200, 6, 4, 9);
    }
    for (int w: WaveList(5, 8) + WaveList(13, 18)) {
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
        // 巨人1282才能对9普通举锤，篮球1091碾压，1039全伤巨人，可以1085生效
        // PA-N-PP
        C(w, 1085 - ADT - 751, AFLOWER_POT, 2, 8);
        A(w, 1085, 2, 9);
        RoofP(w, 1085, 7, 4, 9);
        N(w, 1085 + 220, 2, 8);
        DynamicP(w, 1085 + 220 + 215, 2, 8.95);
        RoofP(w, 1085 + 220 + 215, 6, 4, 8.95);
        // }
        // 现在只剩一血红了
        // 需要原来的热过渡炮收尾，这一炮2085转好
        // 1085+220=1305激活
        // walk([453, 450])=671，原速下1179不会锤8炮，11冰下则是2379不会锤8炮
        EnsureGiga(w);
        RoofP(w, 2370, 2, 3, 8.5);
        RoofP(w, 2370, 4, 4, 9);
        TempC(w, 2000, AFLOWER_POT, 1, 6, 4500 + 745 + 635 + 1);
        TempC(w, 2000, ASNOW_PEA, 1, 6, 4300 - SDT - 1);
        TempC(w, 4300 - SDT, ASQUASH, 1, 6, 4500 + 745);
    }
    for (int w: {20}) {
        I3(w, 1, i_len);
        Remove(w, 2, AFLOWER_POT, 1, 1);
        // 可以参与收尾的炮：1244D67，下一个14在600转好，因此先打一个PSD
        // 热过渡
        RoofP(w, 401, 1, 2, 9);
        RoofP(w, 401, 7, 4, 9);
        // 炸蹦极
        RoofP(w, 401, 4, 3, 4.5);
        // PSD
        DynamicP(w, 1050, 2, 9);
        RoofP(w, 1050, 6, 4, 9);
        RoofP(w, 1050, 2, 2, 9);
        RoofP(w, 1050, 4, 4, 9);
        RoofP(w, 1270, 1, 2, 9);
        RoofP(w, 1270, 4, 4, 9);
        RoofP(w, 1320, 7, 2, 9);
        DynamicP(w, 1480, 4, 9);
        PPExceptOne(w, 2230);
        BlockLast(w, 2235, 5700);
        AConnect(ATime(w, 5500 - SDT), [](){
            for (auto &&plant: aAlivePlantFilter) {
                if (plant.Type() == ATALL_NUT) {
                    int r = plant.Row() + 1, c = plant.Col() + 1;
                    ARemovePlant(r, c, ATALL_NUT);
                    ACard(ASQUASH, r, c);
                }
            }
        });
    }
}