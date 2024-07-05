#ifndef WALIB_CARD_H
#define WALIB_CARD_H

#include "const.h"
#include "info.h"

#pragma region 自动操作

ATickRunner autoBloverTickRunner;
// 有概率漏气球时，加上三叶草保险
void AutoBlover(int row = 1, int column = 1) {
    autoBloverTickRunner.Start([row, column](){
        bool needBlow = false;
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.Type() == AQQ_16 && zombie.Abscissa() < 50) {
                needBlow = true;
            }
        }
        if (needBlow) {
            auto bloverSeed = AGetSeedPtr(ABLOVER);
            if (bloverSeed->IsUsable()) {
                ACard(ABLOVER, row, column);
            }
        }
    });
}

APlantFixer autoWallNutFixer, autoTallNutFixer, autoPumpkinFixer;
// 在参数指定的时间，开始自动修补全场坚果。
void AutoFixNuts(int wave = 1, int time = -599) {
    AConnect(ATime(wave, time), [] {
        if(AGetSeedIndex(AWALL_NUT) != -1){
            autoWallNutFixer.Start(AWALL_NUT, {}, 4000 / 3 * 2);
        }
        if(AGetSeedIndex(ATALL_NUT) != -1){
            autoTallNutFixer.Start(ATALL_NUT, {}, 8000 / 3 * 2);
        }
        if(AGetSeedIndex(APUMPKIN) != -1){
            autoPumpkinFixer.Start(APUMPKIN, {}, 4000 / 3 * 2);
        }
    });
}

ATickRunner waFixCobRunner;
// 在参数指定的时间，开始自动修补全场炮。
// 当炮的装填倒计时大于20秒时，才会进行修补。
void AutoFixCobs(int wave = 1, int time = -599) {
    AConnect(ATime(wave, time), [](){
        if (AGetSeedPtr(ACOB_CANNON) && AGetSeedPtr(AKERNEL_PULT)) {
            waFixCobRunner.Start([](){
                if (!AGetSeedPtr(AKERNEL_PULT)->IsUsable() && !AGetSeedPtr(ACOB_CANNON)->IsUsable()) return;
                for (auto &&plant: aAlivePlantFilter) {
                    if (plant.Type() == ACOB_CANNON && plant.Hp() < 150 && plant.StateCountdown() > 2000) {
                        int row = plant.Row() + 1, col = plant.Col() + 1;
                        ARemovePlant(row, col);
                        ACard(AKERNEL_PULT, row, col);
                        AConnect(ANowDelayTime(751), [row, col](){
                            ACard(AKERNEL_PULT, row, col + 1);
                            ACard(ACOB_CANNON, row, col);
                        });
                    }
                }
            });
        }
    });
    // 提前停止，防止最后时刻补种导致下轮意外停止运行
    AConnect(ATime(20, -500), [](){
        waFixCobRunner.Stop();
    });
}

// 在参数指定的时间，使用墓碑吞噬者尝试种植所有可能生长墓碑的位置。
void RemoveGraves(int wave, int time) {
    AConnect(ATime(wave, time), [](){
        ACard(AGRAVE_BUSTER, {
            {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9},
            {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8},
            {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7},
            {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6},
            {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}
        });
    });
}

ATickRunner waStopGigaRunner;
int waStopGiga_last_row, waStopGiga_last_col;

// 禁止 `StopGiga()` 在特定列放置垫材。这是为了防止反复尝试在冰道上放置垫材导致发出大量音效。
std::vector<int> waStopGigaBanCols;

// 持续在最前面的巨人面前种植垫材。
// 不设置to_time时，一直垫到下波僵尸刷新。
// 不设置row时，自动寻找巨人；设置row时，只垫对应路巨人。
void StopGiga(int wave, int time, const std::vector<APlantType> &plants_to_stop, int to_time = -999, int row = -1) {
    AConnect(ATime(wave, time), [plants_to_stop, row](){
        waStopGiga_last_row = waStopGiga_last_col = -1;
        waStopGigaRunner.Start([plants_to_stop, row](){
            float min_x = 1000;
            int min_x_row = 0;
            AZombie *min_zombie = nullptr;
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Type() != AHY_32 && zombie.Type() != ABY_23) continue;
                if (row != -1 && zombie.Row() + 1 != row) continue;
                if (zombie.Abscissa() < min_x) {
                    min_x = zombie.Abscissa();
                    min_x_row = zombie.Row() + 1;
                    min_zombie = &zombie;
                }
            }
            // 没有巨人时不垫，并且停止种植
            if (!min_zombie) {
                if (waStopGigaRunner.IsStopped()) return;
                waStopGigaRunner.Stop();
                ARemovePlant(waStopGiga_last_row, waStopGiga_last_col, std::vector<int>(plants_to_stop.begin(), plants_to_stop.end()));
                return;
            }
            // 位于115时，恰可在1列垫；位于116时，恰不可在1列垫。
            // 位于15时，恰可在1列垫；位于14时，恰不可在1列垫。
            // 先使用最左可垫位置
            int now_row = min_x_row;
            int now_col = (min_x + 44) / 80;
            // 若已初始化，且更换了垫的位置，则铲掉旧垫
            if (waStopGiga_last_col != -1) {
                if (waStopGiga_last_row != now_row || waStopGiga_last_col != now_col) {
                    ARemovePlant(waStopGiga_last_row, waStopGiga_last_col, std::vector<int>(plants_to_stop.begin(), plants_to_stop.end()));
                }
            }
            // 超出范围的不垫
            if (now_col > 9 || now_col < 1) return;
            // 在投掷小鬼或在举锤的不垫
            if (min_zombie->State() == 69 || min_zombie->State() == 70) return;
            if (!ExistPlant(plants_to_stop, now_row, now_col) && !ExistPlant(plants_to_stop, now_row, now_col)) {
                for (APlantType plant: plants_to_stop) {
                    if (AGetSeedPtr(plant) && AGetSeedPtr(plant)->IsUsable()) {
                        if (std::find(waStopGigaBanCols.begin(), waStopGigaBanCols.end(), now_col) == waStopGigaBanCols.end()) {
                            ACard(plant, now_row, now_col);
                            waStopGiga_last_row = now_row;
                            waStopGiga_last_col = now_col;
                            break;
                        }
                    }
                }
            }
        });
    });
    if (to_time <= -999) {
        if (wave == 20) {
            to_time = 5999;
        } else {
            wave = wave + 1;
            to_time = 0;
        }
    }
    AConnect(ATime(wave, to_time), [plants_to_stop](){
        if (waStopGigaRunner.IsStopped()) return;
        waStopGigaRunner.Stop();
        ARemovePlant(waStopGiga_last_row, waStopGiga_last_col, std::vector<int>(plants_to_stop.begin(), plants_to_stop.end()));
    });
}

int waMaidDefaultMode = 0;

// 设置默认的女仆秘籍模式。0表示关闭时采用Stop，1表示关闭时采用Move。
void SetMaidDefault(int mode) {
    if (mode == 1) AConnect(ATime(1, -599), [](){ AMaidCheats::Move(); });
    waMaidDefaultMode = mode;
}

// 启用女仆秘籍。当到达to_wave波次的to_time时停止。
void MaidDance(int wave, int time, int to_wave, int to_time) {
    AConnect(ATime(wave, time), [](){ AMaidCheats::Dancing(); });
    AConnect(ATime(to_wave, to_time), [](){ 
        if (waMaidDefaultMode == 0) AMaidCheats::Stop();
        else AMaidCheats::Move();
    });
}

// 启用女仆秘籍。当到达to_time时停止。
// 若不设置to_time，则不会停止。
void MaidDance(int wave, int time, int to_time = -1000) {
    AConnect(ATime(wave, time), [](){ AMaidCheats::Dancing(); });
    if (to_time > -1000) {
        AConnect(ATime(wave, to_time), [](){
            if (waMaidDefaultMode == 0) AMaidCheats::Stop();
            else AMaidCheats::Move();
        });
    }
}

// 启用女仆秘籍前进模式。当到达to_wave波次的to_time时停止。
void MaidMove(int wave, int time, int to_wave, int to_time) {
    AConnect(ATime(wave, time), [](){ AMaidCheats::Move(); });
    AConnect(ATime(to_wave, to_time), [](){ 
        if (waMaidDefaultMode == 0) AMaidCheats::Stop();
    });
}

// 启用女仆秘籍前进模式。当到达to_time时停止。
// 若不设置to_time，则不会停止。
void MaidMove(int wave, int time, int to_time = -1000) {
    AConnect(ATime(wave, time), [](){ AMaidCheats::Move(); });
    if (to_time > -1000) {
        AConnect(ATime(wave, to_time), [](){
            if (waMaidDefaultMode == 0) AMaidCheats::Stop();
        });
    }
}

#pragma endregion



#pragma region 仿轨道语言：用卡相关

// 种植卡片到对应位置。
void C(int wave, int time, std::vector<APlantType> plants, std::vector<APosition> pos) {
    AConnect(ATime(wave, time), [plants, pos](){
        ACard(plants, pos);
    });
}

// 种植卡片到对应位置。
void C(int wave, int time, APlantType plant, std::vector<APosition> pos) {
    AConnect(ATime(wave, time), [plant, pos](){
        ACard(plant, pos);
    });
}

// 种植卡片到对应位置。
void C(int wave, int time, std::vector<APlantType> plants, int col, float row) {
    AConnect(ATime(wave, time), [plants, col, row](){
        ACard(plants, col, row);
    });
}

// 种植卡片到对应位置。
void C(int wave, int time, APlantType plant, int col, float row) {
    AConnect(ATime(wave, time), [plant, col, row](){
        ACard(plant, col, row);
    });
}

// 种植一个临时植物并在一段时间后移除。此函数还会帮忙临时种植花盆或睡莲。
// 若不设定铲除时间，则不会移除该植物。
void TempC(int wave, int time, APlantType card, std::vector<APosition> pos, int to_time = -1000) {
    std::string scene = GetCurrentScene();
    APlantType to_remove = card;
    if (card >= AM_PEASHOOTER) to_remove = static_cast<APlantType>(card - AM_PEASHOOTER);
    AConnect(ATime(wave, time), [wave, time, card, pos, scene, to_time, to_remove](){
        for (APosition p: pos) {
            bool should_remove = false;
            APlant *ptr = nullptr;
            if ((scene == "RE" || scene == "ME") && card != AFLOWER_POT && !ExistPlant(AFLOWER_POT, p.row, p.col)) {
                ptr = ACard({AFLOWER_POT, card}, p.row, p.col)[1];
                should_remove = true;
            } else if ((scene == "PE" || scene == "FE") && card != ALILY_PAD && p.row >= 3 && p.row <= 4 && !ExistPlant(ALILY_PAD, p.row, p.col)) {
                ptr = ACard({ALILY_PAD, card}, p.row, p.col)[1];
                should_remove = true;
            } else {
                ptr = ACard(card, p.row, p.col);
            }
            if (ptr) {
                if (to_time >= time) {
                    if (should_remove){
                        AConnect(ATime(wave, to_time), [p, to_remove](){
                            ARemovePlant(p.row, p.col, std::vector<int>{to_remove, AIMITATOR});
                            ARemovePlant(p.row, p.col, std::vector<int>{AFLOWER_POT});
                            ARemovePlant(p.row, p.col, std::vector<int>{ALILY_PAD});
                        });
                    } else {
                        AConnect(ATime(wave, to_time), [p, to_remove](){
                            ARemovePlant(p.row, p.col, std::vector<int>{to_remove, AIMITATOR});
                        });
                    }
                }
                break;
            }
        }
    });
}

// 种植一个临时植物并在一段时间后移除。此函数还会帮忙临时种植花盆或睡莲。
// 若不设定铲除时间，则不会移除该植物。
void TempC(int wave, int time, APlantType card, int row, float col, int to_time = -1000) {
    TempC(wave, time, card, {{row, col}}, to_time);
}

// 种植一个临时植物并在一段时间后移除。此函数还会帮忙临时种植花盆或睡莲。
// 此函数立即执行，因此必须在 `AConnect()` 中使用。
// 若不设定铲除时间，则不会移除该植物。
void TempCNow(APlantType card, std::vector<APosition> pos, int duration = -1000) {
    TempC(ANowTime().wave, ANowTime().time, card, pos, ANowTime().time + duration);
}

// 种植一个临时植物并在一段时间后移除。此函数还会帮忙临时种植花盆或睡莲。
// 此函数立即执行，因此必须在 `AConnect()` 中使用。
// 若不设定铲除时间，则不会移除该植物。
void TempCNow(APlantType card, int row, float col, int duration = -1000) {
    TempC(ANowTime().wave, ANowTime().time, card, row, col, ANowTime().time + duration);
}

void MultiTempC(int wave, int time, const std::vector<APlantType> &plants, float col, const std::vector<int> &rows, int to_time = -1000) {
    AConnect(ATime(wave, time), [=](){
        int plant_ptr = 0;
        for (int row: rows) {
            while (plant_ptr < plants.size()) {
                APlantType plant = plants[plant_ptr];
                plant_ptr++;
                if (AGetSeedPtr(plant) && AGetSeedPtr(plant)->IsUsable()) {
                    TempCNow(plant, row, col, to_time - time);
                    break;
                }
            }
        }
    });
}

void MultiTempC(int wave, int time, const std::vector<APlantType> &plants, std::vector<APosition> pos, int to_time = -1000) {
    AConnect(ATime(wave, time), [=](){
        int plant_ptr = 0;
        for (APosition p: pos) {
            while (plant_ptr < plants.size()) {
                APlantType plant = plants[plant_ptr];
                plant_ptr++;
                if (AGetSeedPtr(plant) && AGetSeedPtr(plant)->IsUsable()) {
                    TempCNow(plant, p.row, p.col, to_time - time);
                    break;
                }
            }
        }
    });
}

// 在场上的最后一列有僵尸的位置种植一个坚果类。
// 本函数已进行 `ForEnd()` 判定。
void ActionToLast(int wave, int time, std::function<void(int)> action) {
    ForEnd(wave, time, [=](){
        AConnect(ATime(wave, time), [=](){
            AZombie *zombie_to_stop = nullptr;
            for (auto &&zombie: aAliveZombieFilter) {
                zombie_to_stop = &zombie;
                if (zombie.Type() != ABW_9) break;
            }
            if (zombie_to_stop) action(zombie_to_stop->Row() + 1);
        });
    });
}

// 在场上的最后一列有僵尸的位置种植一个坚果类。
// 本函数已进行 `ForEnd()` 判定。
void BlockLast(int wave, int time, int to_time = -1000) {
    ForEnd(wave, time, [=](){
        AConnect(ATime(wave, time), [=](){
            AZombie *zombie_to_stop = nullptr;
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Hp() < 0) continue;
                zombie_to_stop = &zombie;
                if (zombie.Type() != ABW_9) break;
            }
            if (!zombie_to_stop) return;
            float col = (zombie_to_stop->Abscissa() + 40) / 80.0f;
            if (col < 1) col = 1;
            if (col > 9) col = 9;
            if (AGetSeedPtr(ATALL_NUT) && AGetSeedPtr(ATALL_NUT)->IsUsable()) {
                TempC(wave, time, ATALL_NUT, zombie_to_stop->Row() + 1, col, to_time);
            } else if (AGetSeedPtr(AWALL_NUT) && AGetSeedPtr(AWALL_NUT)->IsUsable()) {
                TempC(wave, time, AWALL_NUT, zombie_to_stop->Row() + 1, col, to_time);
            } else {
                TempC(wave, time, APUMPKIN, zombie_to_stop->Row() + 1, col, to_time);
            }
        });
    });
}

void Remove(int wave, int time, std::vector<APlantType> cards, int row, float col) {
    AConnect(ATime(wave, time), [row, col, cards](){
        ARemovePlant(row, col, std::vector<int>(cards.begin(), cards.end()));
    });
}

void Remove(int wave, int time, APlantType card, int row, float col) {
    Remove(wave, time, std::vector<APlantType>{card}, row, col);
}

#pragma endregion

#endif // WALIB_CARD_H