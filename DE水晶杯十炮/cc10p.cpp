#include "../walib.h"

void SmartFodder(int w, int time, int to_time) {
    AConnect(ATime(w, time), [=](){
        bool should_fodder[6];
        for (int i = 1; i <= 5; i++) should_fodder[i] = false;
        for (auto &zombie: aAliveZombieFilter) {
            if (zombie.Type() == AHY_32 && zombie.Abscissa() < 596) {
                should_fodder[zombie.Row() + 1] = true;
            }
        }
        std::vector<int> rows;
        for (int i = 1; i <= 5; i++) {
            if (should_fodder[i] && i != 3) rows.push_back(i);
        }
        MultiTempC(w, time, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT}, 7, rows, to_time);
    });
}

ATickRunner stopZombieRunner;

void StopZombie(int wave, int time, int to_time, int row) {
    AConnect(ATime(wave, time), [=](){
        stopZombieRunner.Start([=](){
            AZombie *fast_zombie = nullptr;
            for (auto &zombie: aAliveZombieFilter) {
                if (zombie.Row() + 1 == row) {
                    if (!fast_zombie || fast_zombie->Abscissa() > zombie.Abscissa()) {
                        fast_zombie = &zombie;
                    }
                }
            }
            if (fast_zombie) {
                if (fast_zombie->Abscissa() < 551) {
                    if (!ExistPlant(row, 7)) {
                        if (AGetSeedPtr(APUFF_SHROOM) && AGetSeedPtr(APUFF_SHROOM)->IsUsable()) {
                            ACard(APUFF_SHROOM, row, 7);
                        } else if (AGetSeedPtr(AFLOWER_POT) && AGetSeedPtr(AFLOWER_POT)->IsUsable()) {
                            ACard(AFLOWER_POT, row, 7);
                        }
                    }
                } else if (fast_zombie->Abscissa() < 631) {
                    if (!ExistPlant(row, 8)) {
                        if (AGetSeedPtr(APUFF_SHROOM) && AGetSeedPtr(APUFF_SHROOM)->IsUsable()) {
                            ACard(APUFF_SHROOM, row, 8);
                        } else if (AGetSeedPtr(AFLOWER_POT) && AGetSeedPtr(AFLOWER_POT)->IsUsable()) {
                            ACard(AFLOWER_POT, row, 8);
                        }
                    }
                } else if (fast_zombie->Abscissa() < 711) {
                    if (!ExistPlant(row, 9)) {
                        if (AGetSeedPtr(APUFF_SHROOM) && AGetSeedPtr(APUFF_SHROOM)->IsUsable()) {
                            ACard(APUFF_SHROOM, row, 9);
                        } else if (AGetSeedPtr(AFLOWER_POT) && AGetSeedPtr(AFLOWER_POT)->IsUsable()) {
                            ACard(AFLOWER_POT, row, 9);
                        }
                    }
                }
            }
        });
    });
    AConnect(ATime(wave, to_time), [=](){
        stopZombieRunner.Stop();
        ARemovePlant(row, 7, {APUFF_SHROOM, AFLOWER_POT});
        ARemovePlant(row, 8, {APUFF_SHROOM, AFLOWER_POT});
        ARemovePlant(row, 9, {APUFF_SHROOM, AFLOWER_POT});
    });
}

void AScript() {
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ADOOM_SHROOM, ACHERRY_BOMB,
        AJALAPENO, APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT
    });
    StartIceFiller({{1, 3}, {1, 4}, {2, 3}, {2, 4}});
    const int i_len = 1564;
    waStopGigaBanCols = {8, 9};
    for (int w: {1}) {
        N(w, 318, 2, 8);
        D(w, 318 + 110, 4, 7.9875);
        d(w, 318 + 261, 2, 4);
    }
    for (int w: {2}) {
        PP(w, 318, 8.625);
        DD(w, 318 + 110, 7.9875);
        J(w, 318 + 110, 3, 7);
    }
    for (int w: {10}) {
        PP(w, 318, 8.7125);
        A(w, 318, 4, 9);
        D(w, 318 + 110, 4, 7.9875);
        J(w, 318 + 110, 4, 8);
        d(w, 318 + 264, 2, 4.25);
    }
    for (int w: WaveList(3, 8) + WaveList(11, 18)) {
        if (w == 18) EnsureZombieExist(w, AHY_32, 3);
        I(w, 12, w == 3 || w == 11 ? 601 : i_len);
        PP(w, i_len - 200, 8.575);
        dd(w, i_len - 200 + 369, 2.4625);
        if (w != 3 && w != 11) {
            SmartFodder(w, 614, 955);
            SmartFodder(w, i_len - 200 + 1, i_len - 200 + 2);
        }
        if (w == 7) {
            AConnect(ATime(w, 12), [](){
                ACard(ADOOM_SHROOM, 2, 4);
                aIceFiller.SetList({{1, 3}, {1, 4}, {2, 3}, {3, 6}});
            });
        }
        if (w == 14) {
            AConnect(ATime(w, 12), [](){
                ACard(ADOOM_SHROOM, 3, 6);
                aIceFiller.SetList({{1, 3}, {1, 4}, {2, 3}, {2, 4}});
            });
        }
    }
    for (int w: {9}) {
        EnsureZombieExist(w, ATT_18, 1);
        I(w, 12, i_len);
        // 樱桃清掉下半场矿工，因为2路核难收5路矿工
        A(w, 317, 4, 7);
        // 44444
        // PPn，核尾炸同时还能收矿工
        MultiTempC(w, 614, {ASCAREDY_SHROOM, AFLOWER_POT}, 7, {1, 2}, 955);
        PP(w, 1050, 8.825);
        C(w, 1050 + 329 - CBT - ADT, ACOFFEE_BEAN, 2, 4);
        // 33233
        // PPDD
        PP(w, 1935, 8.325);
        DD(w, 1973 + 110, 8.325);
        MaidDance(w, 1973 + 110, w + 1, 318 - 460);
        N(w, 2550, 3, 1);
        // 11011
        MultiTempC(w, 2249, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT}, 7, {1, 2, 4, 5}, 4300);
        AConnect(ATime(w, 2083 + 5), [=](){
            int row = SchedulePPExceptOne(w, 3275, 8.5);
            StopGiga(w, 3000, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT}, 4300, row);
            PPLast(w, 4300);
        });
    }
    for (int w: {19}) {
        EnsureZombieExist(w, AHY_32, 1);
        I(w, 12, i_len);
        // 樱辣清掉半场矿工；这次因为1050激活，无法同时尾炸和收矿工
        // 樱桃兼有清理w6巨人的作用，这样下半场不用垫了；辣椒兼有开冰道的作用
        A(w, 317, 4, 7);
        J(w, 570, 3, 7);
        // 44444
        // Ndd，垫材防止红眼锤核
        TempC(w, 614, APUFF_SHROOM, 3, 9, 614 + 70);
        MultiTempC(w, 614, {ASCAREDY_SHROOM, AFLOWER_POT}, 7, {4, 5}, 955);
        TempC(w, 614 + 208, ASUN_SHROOM, 3, 9, 614 + 208 + 70);
        N(w, 1050, 3, 8);
        d(w, 1050 + 357, 1, 2.4625);
        d(w, 1050 + 370, 4, 2.8625);
        // 33333
        // PPDd
        // 2011恢复原速，大致等价于1973激活
        PP(w, 1935, 8.325);
        D(w, 1973 + 110, 4, 8.325);
        d(w, 1973 + 255, 2, 3);
        // 22111
        // cc-cc-N 垫住12路巨人，等待本波巨人全部进入3-6核范围内
        MultiTempC(w, 2163, {ASCAREDY_SHROOM, AFLOWER_POT}, 7, {1, 2}, 2163 + 70);
        MultiTempC(w, 2371, {APUFF_SHROOM, ASUN_SHROOM}, 7, {1, 2}, 2371 + 70);
        C(w, 2826 - CBT - ADT, ACOFFEE_BEAN, 3, 6);
        // 11000
        MaidDance(w, 2826, w + 1, 318 - 460);
        AConnect(ATime(w, 2826 + 5), [=](){
            if (ExistZombie(AHY_32, {1})) {
                StopGiga(w, 2914, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT}, 5245 + 309, 1);
                if (ExistZombie(AHY_32, {2, 3, 4})) {
                    P(w, 3275, 3, 8);
                }
            } else {
                StopGiga(w, 2914, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT}, 5245 + 309, 2);
                if (ExistZombie(AHY_32, {3, 4, 5})) {
                    P(w, 3275, 4, 8);
                }
            }
        });
    }
    for (int w: {20}) {
        PP(w, 309, 9, {2, 2, 4, 4});
        DD(w, 409, 9, {1, 2, 4});
        A(w, 410, 4, 9);
        J(w, 410, 4, 7);
        P(w, 509, 2, 4);
        AConnect(ATime(w, 509 + 5), [=](){
            int row = SchedulePPExceptOne(w, 1505, 9);
            StopZombie(w, 514, 5500, row);
            PPLast(w, 5500);
        });
    }
}
