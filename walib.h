#ifndef WHATSS7_WALIB_H
#define WHATSS7_WALIB_H

#include "avz.h"
#include <algorithm>

#if __AVZ_VERSION__ <= 221001
#error "walib is designed for AvZ 2, which is incompatible with AvZ 1."
#elif __AVZ_VERSION__ < 240113
#warning "walib is designed for AvZ 2 version 240113. You're using an older version, which might cause issues."
#elif __AVZ_VERSION__ > 240113
#warning "walib is designed for AvZ 2 version 240113. You're using an newer version, which might cause issues."
#endif

// 常见预判炸时间点（有8列炮情况下最晚舞王不召唤时间点）
const int PRE_COB_POINT = 316;
// 考虑泳池延迟后，玉米加农炮发射到生效修正用时
const int COB_FLYING_TIME = 378;
// 屋顶修正玉米加农炮发射到生效用时
const int ROOF_COB_FLYING_TIME = 387;
// 灰烬植物和寒冰菇种下到生效用时
const int ASH_DELAY_TIME = 100;
// 咖啡豆生效时间198cs或199cs（此处取198cs）
const int COFFEE_BEAN_TIME = 198;
// 模仿者种下至生效时间319cs或320cs（此处取319cs）
const int IMITATOT_DELAY_TIME = 319;
// 窝瓜种下至生效时间182cs
const int SQUASH_DELAY_TIME = 182;

// 常见预判炸时间点（有8列炮情况下最晚舞王不召唤时间点）
const int PCP = PRE_COB_POINT;
// 玉米加农炮发射到生效用时
const int CFT = COB_FLYING_TIME;
// 屋顶修正玉米加农炮发射到生效用时
const int RCFT = ROOF_COB_FLYING_TIME;
// 灰烬植物和寒冰菇种下到生效用时
const int ADT = ASH_DELAY_TIME;
// 咖啡豆生效时间198cs或199cs（此处取198cs）
const int CBT = COFFEE_BEAN_TIME;
// 模仿者种下至生效时间319cs或320cs（此处取319cs）
const int MDT = IMITATOT_DELAY_TIME;
// 窝瓜种下至生效时间182cs
const int SDT = SQUASH_DELAY_TIME;

#ifdef WALIB_DEBUG
ALogger<AConsole> waDebugLogger;
#define DEBUG_LOG(x) waDebugLogger.Info(x)
#else
#define DEBUG_LOG(x)
#endif
ALogger<AMsgBox> waLogger;
ALogger<APvzGui> waIngameLogger;
ACobManager waRoofCobManager[9];

// 控制 `StartCheckMode()` 函数所检查的植物类型。
std::vector<APlantType> waCheckPlants = { ACOB_CANNON, AGLOOM_SHROOM, AWINTER_MELON };

// 控制 `StartCheckMode()` 函数所排除的植物位置。
std::vector<APosition> waCheckIgnore = {  };

// 控制 `ForEnd()` 和 `PPForEnd()` 函数所无视的僵尸类型。
std::vector<AZombieType> waForEndIgnore = { AKG_17, AXG_24 };

// 控制 `ForEnd()` 和 `PPForEnd()` 函数所无视的水路僵尸类型。若为空，则沿用 `waForEndIgnore` 的设置。
// 在其中插入一个不会在水路生成的僵尸以禁用上述行为。
std::vector<AZombieType> waForEndIgnoreInWater = {};


#pragma region 辅助类

class WaveList {
public:
    using iterator = std::vector<int>::iterator;
    WaveList(int _start, int _end) {
        if (_start > _end) std::swap(_start, _end);
        for (int i = _start; i <= _end; i++) {
            l.push_back(i);
        }
    }
    WaveList operator+(const WaveList &other) {
        WaveList new_list = *this;
        for (int i : other.l) {
            new_list.l.push_back(i);
        }
        sort(new_list.begin(), new_list.end());
        new_list.l.resize(unique(new_list.begin(), new_list.end()) - new_list.begin());
        return new_list;
    }
    iterator begin() { return l.begin(); }
    iterator end() { return l.end(); }
private:
    std::vector<int> l;
};

#pragma endregion

#pragma region 场上信息获取
// 获得当前所处的场地。
std::string GetCurrentScene() {
    std::string scenes[] = { "DE", "NE", "PE", "FE", "RE", "ME" };
    int scene_id = AGetMainObject()->Scene();
    if (scene_id < 0 || scene_id > 5) { waLogger.Error("未知的场地"); return ""; }
    else return scenes[scene_id];
}

// 判断场上某行是否有指定类型的僵尸。此处行从 1 开始编号。
bool ExistZombie(std::vector<AZombieType> types, std::vector<int> rows = {1, 2, 3, 4, 5, 6}) {
    for (auto &&zombie: aAliveZombieFilter) {
        if (std::find(types.begin(), types.end(), zombie.Type()) != types.end()) {
            if (std::find(rows.begin(), rows.end(), zombie.Row() + 1) != rows.end()) {
                return true;
            }
        }
    }
    return false;
}

// 判断场上某行是否有指定类型的僵尸。此处行从 1 开始编号。
bool ExistZombie(AZombieType type, std::vector<int> rows = {1, 2, 3, 4, 5, 6}) {   
    return ExistZombie(std::vector<AZombieType>({type}), rows);
}

// 判断指定位置是否有指定的植物。
bool ExistPlant(APlantType type, int row, int col) {
    for (auto &&plant: aAlivePlantFilter) {
        if (plant.Type() == type && plant.Col() + 1 == col && plant.Row() + 1 == row) {
            return true;
        }
    }
    return false;
}

// 判断指定位置是否有指定的植物。
bool ExistPlant(std::vector<APlantType> types, int row, int col) {
    for (auto type: types) {
        if (ExistPlant(type, row, col)) return true;
    }
    return false;
}
#pragma endregion

#pragma region 初始化相关

// 根据场地选择合理的僵尸。
// 以下出怪尽可能在合理的情况下选出最难的出怪组合，但部分威胁较大的出怪也未选上。
// 此时可以使用备选方案进一步测试（如`"DE2"`等）。
// 场地支持传入的参数：
// `"None"` 或其他任意下方未提到的参数: 不进行僵尸选择，使用自然出怪
// `"Auto"` 或不传入参数: 自动根据场地选择下面的组合
// `"Random"`: 均匀的随机出怪
// `"DE"`: 撑杆 舞王 冰车 小丑 气球 矿工 跳跳 蹦极 扶梯 白眼 红眼
// `"DE2"`: 撑杆 橄榄 舞王 冰车 小丑 矿工 蹦极 扶梯 投篮 白眼 红眼  
// `"NE"`: 路障 撑杆 橄榄 舞王 小丑 气球 矿工 跳跳 蹦极 白眼 红眼
// `"PE"` 或 `"FE"`: 撑杆 橄榄 舞王 冰车 海豚 小丑 气球 矿工 蹦极 白眼 红眼
// `"RE"` 或 `"ME"`: 路障 撑杆 橄榄 冰车 小丑 气球 跳跳 蹦极 扶梯 白眼 红眼
// `"PEM"` PE中速关: 路障 撑杆 舞王 潜水 冰车 海豚 小丑 矿工 跳跳 蹦极 扶梯
// `"PEF"` PE快速关: 路障 撑杆 舞王 潜水 冰车 海豚 小丑 矿工 蹦极 扶梯 白眼
// `"DEA"`, `"NEA"`, `"PEA"`, `"FEA"`, `"REA"`, `"MEA"`: 同时选择所有可能出现在场上的僵尸，禁止使用自然出怪
void SelectZombiesForScene(std::string scene = "Auto", bool natural = false) {
    for (int i = 0; i < scene.length(); i++) {
        scene[i] = toupper(scene[i]);
    }
    if (scene == "AUTO")  scene = GetCurrentScene();

    std::vector<AZombieType> zombies;
    if (scene == "RANDOM") {
        ASetZombies(ACreateRandomTypeList(), natural ? ASetZombieMode::INTERNAL : ASetZombieMode::AVERAGE);
    } else if (scene == "PE" || scene == "FE") {
        zombies = { APJ_0, ACG_3, AWW_8, ABC_12, AHT_14, AXC_15, AQQ_16, AKG_17, ABJ_20, AFT_21, ABY_23, AHY_32 };
    } else if (scene == "DE") {
        // DE没有水路僵尸
        // 与DE2相比多路障、扶梯和跳跳（为了选僵尸合理选择的路障）
        zombies = { APJ_0, ALZ_2, ACG_3, AWW_8, ABC_12, AXC_15, AKG_17, ATT_18, ABJ_20, AFT_21, ABY_23, AHY_32 };
    } else if (scene == "DE2") {
        // 与DE相比多橄榄、气球和投篮
        zombies = { APJ_0, ACG_3, AGL_7, AWW_8, ABC_12, AXC_15, AQQ_16, AKG_17, ABJ_20, ATL_22, ABY_23, AHY_32 };
    } else if (scene == "NE") {
        // NE没有水路僵尸和冰车
        zombies = { APJ_0, ALZ_2, ACG_3, AGL_7, AWW_8, AXC_15, AQQ_16, AKG_17, ATT_18, ABJ_20, ABY_23, AHY_32 };
    } else if (scene == "RE" || scene == "ME") {
        // RE和FE没有水路僵尸、舞王和矿工
        zombies = { APJ_0, ALZ_2, ACG_3, AGL_7, ABC_12, AXC_15, AQQ_16, ATT_18, ABJ_20, AFT_21, ABY_23, AHY_32 };
    } else if (scene == "PEF") {
        zombies = { APJ_0, ALZ_2, ACG_3, AWW_8, AQS_11, ABC_12, AHT_14, AXQ_13, AKG_17, ATT_18, ABJ_20, AFT_21 };
    } else if (scene == "PEM") {
        zombies = { APJ_0, ALZ_2, ACG_3, AWW_8, AQS_11, ABC_12, AHT_14, AXQ_13, AKG_17, ABJ_20, AFT_21, ABY_23 };
    } else if (scene == "DEA") {
        zombies = { APJ_0, ALZ_2, ACG_3, ATT_4, ADB_5, ATM_6, AGL_7, AWW_8, ABC_12, AXC_15, AQQ_16, AKG_17, ATT_18, ABJ_20, AFT_21, ATL_22, ABY_23, AHY_32 };
    } else if (scene == "NEA") {
        zombies = { APJ_0, ALZ_2, ACG_3, ATT_4, ADB_5, ATM_6, AGL_7, AWW_8, AXC_15, AQQ_16, AKG_17, ATT_18, ABJ_20, AFT_21, ATL_22, ABY_23, AHY_32 };
    } else if (scene == "PEA" || scene == "FEA") {
        zombies = { APJ_0, ALZ_2, ACG_3, ATT_4, ADB_5, ATM_6, AGL_7, AWW_8, AQS_11, ABC_12, AHT_14, AXC_15, AQQ_16, AKG_17, ATT_18, ABJ_20, AFT_21, ATL_22, ABY_23, AHY_32 };
    } else if (scene == "REA" || scene == "MEA") {
        zombies = { APJ_0, ALZ_2, ACG_3, ATT_4, ADB_5, ATM_6, AGL_7, ABC_12, AXC_15, AQQ_16, ATT_18, ABJ_20, AFT_21, ATL_22, ABY_23, AHY_32 };
    }
    if (!zombies.empty()) ASetZombies(std::vector<int>(zombies.begin(), zombies.end()), natural ? ASetZombieMode::INTERNAL : ASetZombieMode::AVERAGE);
}

void SelectCardsAndFill(std::vector<APlantType> plants = {}, bool fast = false) {
    // 使用常用植物填充植物格防止漏带
    const std::vector<APlantType> extra_plants = {
        AICE_SHROOM,        // 寒冰菇
        ACOFFEE_BEAN,       // 咖啡豆
        ACHERRY_BOMB,       // 樱桃炸弹
        ADOOM_SHROOM,       // 毁灭菇
        ABLOVER,            // 三叶草
        ALILY_PAD,          // 睡莲
        APUFF_SHROOM,       // 垫材四人组：小喷菇
        ASUN_SHROOM,        // 垫材四人组：阳光菇
        ASCAREDY_SHROOM,    // 垫材四人组：胆小菇
        AFLOWER_POT,        // 垫材四人组：花盆
    };
    std::vector<int> plant_ids(plants.begin(), plants.end());
    for (APlantType plant: extra_plants) {
        if (plant_ids.size() >= 10) break;
        // 检查植物是否已在列表中，若不在则用此植物填充
        if (std::find(plants.begin(), plants.end(), plant) == plants.end())  {
            plant_ids.push_back(plant);
        }
    }
    if (fast) ASelectCards(plant_ids, 0);
    else ASelectCards(plant_ids);
}

// 绑定一些快捷键。
// `Q`: 1倍速
// `W`: 2倍速
// `E`: 5倍速
// `R`: 10倍速
// `T`: 0.5倍速
void BindSpeedKeys() {
    AConnect('Q', [](){ ASetGameSpeed(1); });
    AConnect('W', [](){ ASetGameSpeed(2); });
    AConnect('E', [](){ ASetGameSpeed(5); });
    AConnect('R', [](){ ASetGameSpeed(10); });
    AConnect('T', [](){ ASetGameSpeed(0.5); });
}

// 自动管理全场炮。若需要使用后续轨道语言函数，则此处必须进行自动管理。
// 在屋顶场景，炮尾处于1-2列的炮和3列的炮分别单独归类。
void AutoManageCob() {
    AConnect(ATime(1, -599), [] {
        std::string scene = GetCurrentScene();
        if (scene == "RE" || scene == "ME") {
            std::vector<AGrid> grids[9];
            for (auto &&plant: aAlivePlantFilter) {
                if (plant.Type() == ACOB_CANNON) {
                    grids[plant.Col() + 1].push_back({plant.Row() + 1, plant.Col() + 1});
                }
            }
            for (int i = 1; i <= 8; i++) {
                #ifdef WALIB_DEBUG
                for (auto j: grids[i]) {
                    waDebugLogger.Info(std::to_string(i) + " " + std::to_string(j.row) + " " + std::to_string(j.col));
                }
                #endif
                waRoofCobManager[i].SetList(grids[i]);
            }
        } else {
            aCobManager.AutoSetList();
        }
    });
}


// 初始化选卡，指定僵尸，并自动管理全场炮。传入空数组不指定僵尸，使用自然生成的僵尸。
// 选卡剩下的格子会用一些常用的植物填充防止漏选。
void Init(const std::vector<APlantType> &plants, const std::vector<AZombieType> &zombies, bool fast = false) {
    if (!zombies.empty()) ASetZombies(std::vector<int>(zombies.begin(), zombies.end()));
    SelectCardsAndFill(plants, fast);
    BindSpeedKeys();
    AutoManageCob();
}

// 初始化选卡，根据场地选择合理的僵尸，并自动管理全场炮。
// 选卡剩下的格子会用一些常用的植物填充防止漏选。
// 场景可传入的参数参见 `SelectZombiesForScene()`.
void Init(const std::vector<APlantType> &plants, const char *scene = "Auto", bool fast = false) {
    SelectZombiesForScene(scene);
    SelectCardsAndFill(plants, fast);
    BindSpeedKeys();
}

void SkipToTime(int wave, int time = -199) {
    AConnect(ATime(1, -590), [wave, time](){
        ASkipTick(wave, time);
    });
}

ATickRunner waCheckRunner;

// 启动测试模式：开启脚本循环，10倍速，当忧郁菇、冰瓜投手或玉米加农炮受损时弹窗提示。
// 检测受损的植物类型可通过修改 waCheckPlants 进行设置。
void StartCheckMode(float speed = 10, bool reload = true) {
    if (reload) ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    ASetGameSpeed(speed);
    waCheckRunner.Start([](){
        for (auto &&plant: aAlivePlantFilter) {
            bool ignored = false;
            for (const auto &pos: waCheckIgnore) {
                if (pos.row == plant.Row() + 1 && fabs(pos.col - (plant.Col() + 1)) < 0.5f) {
                    ignored = true;
                    break;
                }
            }
            if (ignored) continue;
            if (std::find(waCheckPlants.begin(), waCheckPlants.end(), plant.Type()) != waCheckPlants.end()) {
                if (plant.Hp() != plant.HpMax()) {
                    waLogger.Error("第" + std::to_string(plant.Row() + 1) + "行第" + std::to_string(plant.Col() + 1) + "列植物受损");
                    waCheckRunner.Stop();
                    break;
                }
            }
        }
    });
}

// 启动重载模式：开启脚本循环，1倍速。与 `StartCheckMode()` 不同在于，不检查植物受损情况。
void StartReloadMode(float speed = 1, bool reload = true) {
    if (reload) ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    ASetGameSpeed(speed);
}

void RecordWaves() {
    for (int w: WaveList(1, 20)) {
        AConnect(ATime(w, -1), [w](){
            waIngameLogger.Info("Wave " + std::to_string(w));
        });
    }
}

#pragma endregion

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

#pragma endregion

#pragma region 仿轨道语言：炮相关

// 判断是否为有效的时间。
// w1 / w10 / w20 的时间总是有效，而其他波次小于 -200 的时间无效。
bool IsValidTime(int wave, int time) {
    if (wave == 1 || wave == 10 || wave == 20) return true;
    else return time >= -200;
}

// 从 `aCobManager` 发射一对炮。
// 若不设置位置，则泳池场景默认炸2-9和5-9，其他场景默认炸2-9和4-9。
// 请注意，本函数先填列数，再填行数。
// 若不设置时间，则 316cs (`PCP`) 时生效
// 屋顶场景，1-2路的炮优先选择风炮；3-5路优先选择平炮。
void PP(int wave, int time = -1, float col = 9, std::vector<int> rows = {}) {
    if (rows.empty()) {
        std::string scene = GetCurrentScene();
        if (scene == "PE" || scene == "FE") {
            rows = {2, 5};
        } else {
            rows = {2, 4};
        }
    }
    if (time < 0) time = PCP;
    std::string scene = GetCurrentScene();
    if (scene == "RE" || scene == "ME") {
        for (int row: rows) {
            if (row <= 2) {
                AConnect(ATime(wave, time - RCFT), [row, col](){
                    bool success = false;
                    for (int i = 1; i <= 8; i++) {
                        if (waRoofCobManager[i].GetRoofUsablePtr(col)) {
                            waRoofCobManager[i].RoofFire(row, col);
                            success = true;
                            break;
                        }
                    }
                    if (!success) waLogger.Error("场上所有炮都无法发射");
                });
            } else {
                AConnect(ATime(wave, time - RCFT), [row, col](){
                    bool success = false;
                    for (int i = 8; i >= 1; i--) {
                        if (waRoofCobManager[i].GetRoofUsablePtr(col)) {
                            waRoofCobManager[i].RoofFire(row, col);
                            success = true;
                            break;
                        }
                    }
                    if (!success) waLogger.Error("场上所有炮都无法发射");
                });
            }
        }
    } else {
        for (int row: rows) {
            if ((scene == "PE" || scene == "FE") && (row == 3 || row == 4)) {
                AConnect(ATime(wave, time - 378), [row, col](){
                    aCobManager.Fire(row, col);
                });
            } else {
                AConnect(ATime(wave, time - 373), [row, col](){
                    aCobManager.Fire(row, col);
                });
            }
        }
    }
}

// 从 `aCobManager` 发射一炮。
void P(int wave, int time, int row, float col) {
    std::vector<int> rows;
    rows.push_back(row);
    PP(wave, time, col, rows);
}

// 从 `aCobManager` 发射一对炮。仅可用于泳池和屋顶场景。
// 若不设置位置，则泳池场景默认炸1-8和5-8，屋顶场景默认炸2-8和4-8。
// 请注意，本函数先填列数，再填行数。
// 若不设置时间，则 423cs (`PCP + 107`) 时生效
// 屋顶场景，1-2路的炮优先选择风炮；3-5路优先选择平炮。
void DD(int wave, int time = -1, float col = 8, std::vector<int> rows = {}) {
    std::string scene = GetCurrentScene();
    if (scene == "DE" || scene == "NE") {
        waLogger.Error("DD() 不可用于前院。");
        return;
    }
    if (rows.empty()) {
        if (scene == "PE" || scene == "FE") {
            rows = {1, 5};
        } else {
            rows = {2, 4};
        }
    }
    if (time < 0) time = PCP + 107;
    PP(wave, time, col, rows);
}

// 在屋顶场景使用炮尾在指定列的炮发射一对炮。
// 若不设置位置，默认炸2-9和4-9。
// 请注意，本函数先填列数，再填行数。
void RoofPP(int wave, int time, int cobCol, float col = 9, std::vector<int> rows = {2, 4}) {
    std::string scene = GetCurrentScene();
    if (scene != "RE" && scene != "ME") {
        waLogger.Error("RoofPP() 只能在屋顶使用");
        return;
    }
    if (cobCol < 1 || cobCol > 8) {
        waLogger.Error("炮列数超出范围");
        return;
    }
    std::vector<APosition> pos;
    for (int i: rows) pos.push_back({i, col});
    AConnect(ATime(wave, time - RCFT), [pos, cobCol](){
        waRoofCobManager[cobCol].RoofFire(pos);
    });
}


// 在屋顶场景使用炮尾在指定列的炮发射一炮。
void RoofP(int wave, int time, int cobCol, int row, float col) {
    std::vector<int> rows;
    rows.push_back(row);
    RoofPP(wave, time, cobCol, col, rows);
}

bool ForEndJudge(int wave) {
    std::string scene = GetCurrentScene();
    if ((scene == "PE" || scene == "FE") && waForEndIgnoreInWater.empty()) {
        waForEndIgnoreInWater = waForEndIgnore;
    }
    ATime now = ANowTime();
    if (now.wave != wave) return false;
    bool hasZombie = false;
    for (auto &&zombie: aAliveZombieFilter) {
        if ((scene == "PE" || scene == "FE") && (zombie.Row() == 2 || zombie.Row() == 3)) {
            if (std::find(waForEndIgnoreInWater.begin(), waForEndIgnoreInWater.end(), zombie.Type()) != waForEndIgnoreInWater.end()) {
                continue;
            }
        } else {
            if (std::find(waForEndIgnore.begin(), waForEndIgnore.end(), zombie.Type()) != waForEndIgnore.end()) {
                continue;
            }
        }
        if ((zombie.Type() != ABW_9 && zombie.AtWave() + 1 == wave) || (wave != 9 && wave != 19)) {
            hasZombie = true;
        }
    }
    if (!hasZombie) return false;
    return true;
}

// 用于收尾的函数。在指定时间是对应波次（处于刷新倒计时也算）且场上有僵尸才执行对应的操作。
// 此函数w9/w19不计非本波僵尸与伴舞，且所有波次默认不计矿工和小鬼。
void ForEnd(int wave, int time, std::function<void()> action) {
    AConnect(ATime(wave, time), [wave, action](){
        if (ForEndJudge(wave)) action();
    });
}

// 用于收尾的炮。是对应波次（处于下一波的刷新倒计时也算本波）且场上有僵尸才发射。注意此函数w9/w19不计伴舞。
void PPForEnd(int wave, int time, float col = 9, std::vector<int> rows = {}) {
    std::string scene = GetCurrentScene();
    int VCFT = (scene == "RE" || scene == "ME" ? 387 : 373);
    ForEnd(wave, time - VCFT, [=](){ PP(wave, time, col, rows); });
}

// 在泳池场景，对除了某列以外的所有红眼开炮。常用于拖收尾。
// 若场上没有红眼，且当前是w20，则改为对除了某列以外的所有僵尸开炮。
// 为了收尾的正常运行，请确保场上的红眼都是本波红眼。
// 本函数已进行 `ForEnd()` 判定。
void PPExceptOne(int wave, int time, float col = 9) {
    std::string scene = GetCurrentScene();
    int VCFT = (scene == "RE" || scene == "ME" ? RCFT : CFT);
    ForEnd(wave, time - VCFT, [=](){
        AConnect(ATime(wave, time - VCFT), [wave, time, col](){
            int dist[7] = { 0, 0, 0, 0, 0, 0, 0 };
            int sum = 0;
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Type() != AHY_32) continue;
                dist[zombie.Row() + 1]++;
                sum++;
            }
            if (wave == 20 && sum == 0) {
                #ifdef WALIB_DEBUG
                waDebugLogger.Info("no red found");
                #endif
                for (auto &&zombie: aAliveZombieFilter) {
                    if (zombie.Type() == ABJ_20) continue;
                    #ifdef WALIB_DEBUG
                    waDebugLogger.Info("found zombie # at #", zombie.Type(), zombie.Row() + 1);
                    #endif
                    dist[zombie.Row() + 1]++;
                    sum++;
                }
            }
            #ifdef WALIB_DEBUG
            for (int i = 1; i <= 6; i++) {
                waDebugLogger.Info("distr of #: #", i, dist[i]);
            }
            #endif
            std::string scene = GetCurrentScene();
            if (scene == "PE" || scene == "FE") {
                // 六行场地收尾
                if (dist[1] == 1) {
                    if (dist[2] != 0) {
                        P(ANowTime().wave, time, 3, col);
                    }
                    if (dist[5] != 0 || dist[6] != 0) {
                        P(ANowTime().wave, time, 5, col);
                    }
                } else if (dist[6] == 1) {
                    if (dist[5] != 0) {
                        P(ANowTime().wave, time, 4, col);
                    }
                    if (dist[1] != 0 || dist[2] != 0) {
                        P(ANowTime().wave, time, 2, col);
                    }
                } else if (dist[1] == 0 && dist[2] == 1) {
                    if (dist[5] != 0 || dist[6] != 0) {
                        P(ANowTime().wave, time, 5, col);
                    }
                } else if (dist[5] == 0 && dist[6] == 1) {
                    if (dist[1] != 0 || dist[2] != 0) {
                        P(ANowTime().wave, time, 2, col);
                    }
                } else if (dist[1]) {
                    if (dist[2] != 0) {
                        P(ANowTime().wave, time, 3, col);
                    }
                    if (dist[5] != 0 || dist[6] != 0) {
                        P(ANowTime().wave, time, 5, col);
                    }
                } else if (dist[6]) {
                    if (dist[5] != 0) {
                        P(ANowTime().wave, time, 4, col);
                    }
                    if (dist[1] != 0 || dist[2] != 0) {
                        P(ANowTime().wave, time, 2, col);
                    }
                } else if (dist[2]) {
                    if (dist[5] != 0 || dist[6] != 0) {
                        P(ANowTime().wave, time, 5, col);
                    }
                }
            } else {
                // 五行场地收尾
                if (dist[1] == 1) {
                    bool middled = false;
                    if (dist[2]) {
                        P(ANowTime().wave, time, 3, col);
                        middled = true;
                    }
                    if (dist[5]) {
                        P(ANowTime().wave, time, 4, col);
                        middled = true;
                    }
                    if (!middled && (dist[3] || dist[4])) {
                        P(ANowTime().wave, time, 3, col);
                    }
                } else if (dist[3] == 1) {
                    if (dist[1] || dist[2]) {
                        P(ANowTime().wave, time, 1, col);
                    }
                    if (dist[4] || dist[5]) {
                        P(ANowTime().wave, time, 5, col);
                    }
                } else if (dist[5] == 1) {
                    bool middled = false;
                    if (dist[1]) {
                        P(ANowTime().wave, time, 2, col);
                        middled = true;
                    }
                    if (dist[4]) {
                        P(ANowTime().wave, time, 3, col);
                        middled = true;
                    }
                    if (!middled && (dist[2] || dist[3])) {
                        P(ANowTime().wave, time, 2, col);
                    }
                } else if (dist[1] == 0 && dist[2] == 1) {
                    if (dist[3] || dist[4] || dist[5]) {
                        P(ANowTime().wave, time, 4, col);
                    }
                } else if (dist[5] == 0 && dist[4] == 1) {
                    if (dist[1] || dist[2] || dist[3]) {
                        P(ANowTime().wave, time, 2, col);
                    }
                } else if (dist[1]) {
                    bool middled = false;
                    if (dist[2]) {
                        P(ANowTime().wave, time, 3, col);
                        middled = true;
                    }
                    if (dist[5]) {
                        P(ANowTime().wave, time, 4, col);
                        middled = true;
                    }
                    if (!middled && (dist[3] || dist[4])) {
                        P(ANowTime().wave, time, 3, col);
                    }
                } else if (dist[3]) {
                    if (dist[1] || dist[2]) {
                        P(ANowTime().wave, time, 1, col);
                    }
                    if (dist[4] || dist[5]) {
                        P(ANowTime().wave, time, 5, col);
                    }
                } else if (dist[5]) {
                    bool middled = false;
                    if (dist[1]) {
                        P(ANowTime().wave, time, 2, col);
                        middled = true;
                    }
                    if (dist[4]) {
                        P(ANowTime().wave, time, 3, col);
                        middled = true;
                    }
                    if (!middled && (dist[2] || dist[3])) {
                        P(ANowTime().wave, time, 2, col);
                    }
                } else if (dist[2]) {
                    if (dist[3] || dist[4] || dist[5]) {
                        P(ANowTime().wave, time, 4, col);
                    }
                }
            }
        });
    });
}

// 对场上的最后一列有红眼的位置开炮。
// 如果场上没有红眼，则对最后一列有僵尸的位置开炮。
// 本函数已进行 `ForEnd()` 判定。
void PPLast(int wave, int time) {
    std::string scene = GetCurrentScene();
    int VCFT = (scene == "RE" || scene == "ME" ? 387 : 373);
    ForEnd(wave, time - VCFT, [=](){
        AConnect(ATime(wave, time - VCFT), [wave, time](){
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Type() != AHY_32) continue;
                if (zombie.Hp() < 0) continue;
                float col = (zombie.Abscissa() + 40) / 80.0f;
                if (col < 1) col = 1;
                if (col > 9) col = 9;
                P(wave, time, zombie.Row() + 1, col);
                return;
            }
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Type() == ABJ_20) continue;
                if (zombie.Hp() < 0) continue;
                float col = (zombie.Abscissa() + 40) / 80.0f;
                if (col < 1) col = 1;
                if (col > 9) col = 9;
                P(wave, time, zombie.Row() + 1, col);
                return;
            }
        });
    });
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
    AConnect(ATime(wave, time), [wave, time, card, pos, scene, to_time](){
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
                        AConnect(ATime(wave, to_time), [p, card](){
                            ARemovePlant(p.row, p.col, card);
                            ARemovePlant(p.row, p.col, AFLOWER_POT);
                            ARemovePlant(p.row, p.col, ALILY_PAD);
                        });
                    } else {
                        AConnect(ATime(wave, to_time), [p, card](){
                            ARemovePlant(p.row, p.col, card);
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

#pragma endregion

#pragma region 仿轨道语言：冰核相关

// 开启自动存冰时，从 `aIceFiller` 进行点冰。若需要非旗帜波的完美预判冰，则需要假设波长或提供上一波波长。
// 由于咖啡豆的不确定性，有概率延迟1cs生效。
void I(int wave, int time = 1, int last_wave_length = -1) {
    time -= CBT + ADT;
    if (!IsValidTime(wave, time) && last_wave_length > 0) {
        wave -= 1;
        time += last_wave_length;
    }
    AConnect(ATime(wave, time), [](){
        aIceFiller.Coffee();
    });
}

// 开启自动存冰时，从 `aIceFiller` 进行点冰。若需要非旗帜波的完美预判冰，则需要假设波长或提供上一波波长。
// 此函数使得寒冰菇精准生效。
void I3(int wave, int time = 11, int last_wave_length = -1) {
    time -= CBT + ADT;
    if (!IsValidTime(wave, time) && last_wave_length > 0) {
        wave -= 1;
        time += last_wave_length;
    }
    AConnect(ATime(wave, time), [](){
        aIceFiller.Coffee();
        AIce3(CBT + ADT);
    });
}

bool CanPlaceImitate(int wave, int time, int last_wave_length = -1) {
    bool isDay = true;
    std::string scene = GetCurrentScene();
    if (scene == "NE" || scene == "FE" || scene == "ME") {
        isDay = false;
    }
    int VCBT = isDay ? CBT : 0;
    int imitate_wave = wave, imitate_time = time - (MDT + (isDay ? 1 : 0)) - VCBT - ADT;
    if (!IsValidTime(imitate_wave, imitate_time) && last_wave_length > 0) {
        imitate_wave -= 1;
        imitate_time += last_wave_length;
    }
    return ANowTime(imitate_wave) < imitate_time && !(imitate_wave == 1 && imitate_time < -599);
}

// 手动种植毁灭菇或寒冰菇。
void ManualShroom(int wave, int time, std::vector<APosition> pos, APlantType card, int last_wave_length, int protect, bool accurate = false) {
    bool isDay = true;
    APlantType imitated = (card == AICE_SHROOM ? AM_ICE_SHROOM : AM_DOOM_SHROOM);
    std::string scene = GetCurrentScene();
    if (scene == "NE" || scene == "FE" || scene == "ME") {
        isDay = false;
    }
    int VCBT = isDay ? CBT : 0;

    // 获取对应种植的时间
    int imitate_wave = wave, imitate_time = time - (MDT + (isDay ? 1 : 0)) - VCBT - ADT;
    if (!IsValidTime(imitate_wave, imitate_time) && last_wave_length > 0) {
        imitate_wave -= 1;
        imitate_time += last_wave_length;
    }
    int normal_wave = wave, normal_time = time - VCBT - ADT;
    if (!IsValidTime(normal_wave, normal_time) && last_wave_length > 0) {
        normal_wave -= 1;
        normal_time += last_wave_length;
    }

    // 种植蘑菇。种前检查是否有荷叶花盆；种后修正生效时间/种南瓜/唤醒/铲南瓜/铲荷叶花盆。
    auto plant_shroom_at = [scene, protect, accurate, isDay, VCBT](int wave, int time, APlantType card, const std::vector<APosition> &pos, bool imitate) {
        AConnect(ATime(wave, time), [=](){
            for (APosition p: pos) {
                APlant *ptr = nullptr;
                bool should_remove = false;
                if ((scene == "RE" || scene == "ME") && !ExistPlant(AFLOWER_POT, p.row, p.col)) {
                    ptr = ACard({AFLOWER_POT, card}, p.row, p.col)[1];
                    should_remove = true;
                } else if ((scene == "PE" || scene == "FE") && p.row >= 3 && p.row <= 4 && !ExistPlant(ALILY_PAD, p.row, p.col)) {
                    ptr = ACard({ALILY_PAD, card}, p.row, p.col)[1];
                    should_remove = true;
                } else {
                    ptr = ACard(card, p.row, p.col);
                }
                if (ptr) {
                    AConnect(ANowDelayTime(imitate ? MDT + (isDay ? 1 : 0) : 0), [=](){
                        bool should_remove_pumpkin = false;
                        if (accurate && isDay) ASetPlantActiveTime(card, (VCBT + ADT));
                        if (protect > 1 && !ExistPlant(APUMPKIN, p.row, p.col)) {
                            should_remove_pumpkin = true;
                            ACard(APUMPKIN, p.row, p.col);
                        }
                        if (isDay) ACard(ACOFFEE_BEAN, p.row, p.col);
                        if ((card == AICE_SHROOM || card == AM_ICE_SHROOM) && should_remove_pumpkin) {
                            AConnect(ANowDelayTime(VCBT + ADT + 1), [p](){
                                ARemovePlant(p.row, p.col, APUMPKIN);
                            });
                        }
                        if ((card == AICE_SHROOM || card == AM_ICE_SHROOM) && should_remove) {
                            AConnect(ANowDelayTime(VCBT + ADT + 1), [p](){
                                ARemovePlant(p.row, p.col, {AFLOWER_POT, ALILY_PAD});
                            });
                        }
                    });
                    break;
                }
            }
        });
    };

    if (AGetCardPtr(imitated) && CanPlaceImitate(wave, time)) {
        // 携带了模仿植物的情况
        // 若为白昼，早种植1cs，模仿者即使319cs完成变身也等到320cs再种咖啡豆，保证延迟最大为1cs。
        // 若为黑夜，则不能早种植，否则有概率提前1cs。
        AConnect(ATime(imitate_wave, imitate_time), [=](){
            if (AGetCardPtr(imitated)->IsUsable() && !(AGetCardPtr(card) && AGetCardPtr(card)->IsUsable())) {
                // 若模仿能种而普通不能种（此判断提前完成，存在普通到时间能转好但还是使用模仿的现象）
                // 则立即种植模仿
                plant_shroom_at(imitate_wave, imitate_time, imitated, pos, true);
            } else {
                // 否则稍后种植普通
                plant_shroom_at(normal_wave, normal_time, card, pos, false);
            }
        });
    } else {
        // 未携带模仿核同之前的“否则”情况。
        plant_shroom_at(normal_wave, normal_time, card, pos, false);
    }
}

// 种植寒冰菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// 若存在预判冰或模仿冰等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿冰时，使用此函数请不要携带模仿冰。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void ManualI(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0){
    ManualShroom(wave, time, pos, AICE_SHROOM, last_wave_length, protect);
}

// 种植寒冰菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// 若存在预判冰或模仿冰等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿冰时，使用此函数请不要携带模仿冰。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void ManualI(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0){
    ManualShroom(wave, time, {{row, col}}, AICE_SHROOM, last_wave_length, protect);
}

// 种植寒冰菇。此函数使得寒冰菇精准生效。
// 若存在预判冰或模仿冰等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿冰时，使用此函数请不要携带模仿冰。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void ManualI3(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0) {
    ManualShroom(wave, time, pos, AICE_SHROOM, last_wave_length, protect, true);
}

// 种植寒冰菇。此函数使得寒冰菇精准生效。
// 若存在预判冰或模仿冰等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿冰时，使用此函数请不要携带模仿冰。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void ManualI3(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0) {
    ManualShroom(wave, time, {{row, col}}, AICE_SHROOM, last_wave_length, protect, true);
}

// 若寒冰菇冷却已好，在指定临时冰位使用寒冰菇；否则，使用存冰。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void TempI(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0, bool accurate = false) {
    bool isDay = true;
    std::string scene = GetCurrentScene();
    if (scene == "NE" || scene == "FE" || scene == "ME") {
        isDay = false;
    }
    int VCBT = isDay ? CBT : 0;
    int imitate_wave = wave, imitate_time = time - (MDT + (isDay ? 1 : 0)) - VCBT - ADT;
    if (!IsValidTime(imitate_wave, imitate_time) && last_wave_length > 0) {
        imitate_wave -= 1;
        imitate_time += last_wave_length;
    }
    int normal_wave = wave, normal_time = time - VCBT - ADT;
    if (!IsValidTime(normal_wave, normal_time) && last_wave_length > 0) {
        normal_wave -= 1;
        normal_time += last_wave_length;
    }
    ATime connect_time = ATime(normal_wave, normal_time);
    if (AGetCardPtr(AM_ICE_SHROOM) && CanPlaceImitate(wave, time, last_wave_length)) {
        connect_time = ATime(imitate_wave, imitate_time);
    }
    AConnect(connect_time, [wave, time, pos, last_wave_length, protect, accurate](){
        if (AGetCardPtr(AICE_SHROOM)->IsUsable() || AGetCardPtr(AM_ICE_SHROOM)->IsUsable()) {
            if (accurate) ManualI3(wave, time, pos, last_wave_length, protect);
            else ManualI(wave, time, pos, last_wave_length, protect);
        } else {
            if (accurate) I3(wave, time, last_wave_length);
            else I(wave, time, last_wave_length);
        }
    });

}

// 若寒冰菇冷却已好，在指定临时冰位使用寒冰菇；否则，使用存冰。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void TempI(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0, bool accurate = false) {
    TempI(wave, time, {{row, col}}, last_wave_length, protect, accurate);
}

// 若寒冰菇冷却已好，在指定临时冰位使用寒冰菇；否则，使用存冰。此函数使得寒冰菇精准生效。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void TempI3(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0) {
    TempI(wave, time, pos, last_wave_length, protect, true);
}

// 若寒冰菇冷却已好，在指定临时冰位使用寒冰菇；否则，使用存冰。此函数使得寒冰菇精准生效。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void TempI3(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0) {
    TempI(wave, time, row, col, last_wave_length, protect, true);
}


// 种植毁灭菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// 若存在模仿核等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿核时，使用此函数请不要携带模仿核。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿核；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void N(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0) {
    ManualShroom(wave, time, pos, ADOOM_SHROOM, last_wave_length, protect);
}

// 种植毁灭菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// 若存在模仿核等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿核时，使用此函数请不要携带模仿核。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿核；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void N(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0) {
    ManualShroom(wave, time, {{row, col}}, ADOOM_SHROOM, last_wave_length, protect);
}

// 种植毁灭菇，但进行车底炸。仅用于夜间场景。
// 本路无冰车时，与N函数相同；而有冰车时，在生效时间点再放。
void ZomboniN(int wave, int time, int row, float col) {
    const std::string scene = GetCurrentScene();
    if (scene != "FE" || scene != "ME") {
        waLogger.Warning("ZomboniN 仅用于 ME. 将改用 N()");
        N(wave, time, row, col);
    } else {
        AConnect(ATime(wave, 1), [wave, time, row, col](){
            if (ExistZombie(ABC_12, {row})) TempC(wave, time, ADOOM_SHROOM, row, col);
            else N(wave, time, row, col);
        });
    }
}

// 使用一个樱桃炸弹。此函数不会使用模仿樱桃炸弹。
void A(int wave, int time, int row, float col) {
    TempC(wave, time - ADT, ACHERRY_BOMB, row, col, time + 1);
}

// 种植樱桃炸弹，但进行车底炸。
// 本路无冰车时，与A函数相同；而有冰车时，在生效时间点再放。
void ZomboniA(int wave, int time, int row, float col) {
    AConnect(ATime(wave, 1), [wave, time, row, col](){
        if (ExistZombie(ABC_12, {row})) TempC(wave, time, ACHERRY_BOMB, row, col);
        else A(wave, time, row, col);
    });
}

// 使用一个火爆辣椒。此函数不会使用模仿火爆辣椒。
void J(int wave, int time, int row, float col) {
    TempC(wave, time - ADT, AJALAPENO, row, col, time + 1);
}

// 种植火爆辣椒，但进行车底炸。
// 本路无冰车时，与J函数相同；而有冰车时，在生效时间点再放。
void ZomboniJ(int wave, int time, int row, float col) {
    AConnect(ATime(wave, 1), [wave, time, row, col](){
        if (ExistZombie(ABC_12, {row})) TempC(wave, time, AJALAPENO, row, col);
        else J(wave, time, row, col);
    });
}

// 使用智能樱桃消延迟。此函数不会使用模仿樱桃炸弹。
// 默认有巨人时400cs生效，没有巨人时550cs生效。
// 本函数未考虑冰车碾压。
void SmartA(int wave = 10, int time = 400, int no_red_time = 550) {
    if (!AGetZombieTypeList()[AHY_32]) time = no_red_time;
    std::string scene = GetCurrentScene();
    if (scene == "PE" || scene == "FE") {
        AConnect(ATime(wave, time - ADT), [wave, time](){
            if (!ForEndJudge(wave)) return;
            int uby = 0, uhy = 0, dby = 0, dhy = 0;
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Type() == ABY_23) {
                    if (zombie.Row() < 3) uby++;
                    else dby++;
                } else if (zombie.Type() == AHY_32) {
                    if (zombie.Row() < 3) uhy++;
                    else dhy++;
                }
            }
            if (uby * 2 + uhy * 3 < dby * 2 + dhy * 3) {
                TempC(wave, time - ADT, ACHERRY_BOMB, {{5, 9}, {2, 9}}, time + 1);
            } else {
                TempC(wave, time - ADT, ACHERRY_BOMB, {{2, 9}, {5, 9}}, time + 1);
            }
        });
    } else {
        AConnect(ATime(wave, time - ADT), [wave, time](){
            if (!ForEndJudge(wave)) return;
            std::vector<APosition> choices = {{2, 9}, {3, 9}, {4, 9}};
            int status[3];
            for (auto &&zombie: aAliveZombieFilter) {
                int score = 0;
                if (zombie.Type() == ABY_23) score = 2;
                else if (zombie.Type() == AHY_32) score = 3;
                if (zombie.Row() == 1 || zombie.Row() == 2 || zombie.Row() == 3) {
                    status[0] += score;
                }
                if (zombie.Row() == 2 || zombie.Row() == 3 || zombie.Row() == 4) {
                    status[1] += score;
                }
                if (zombie.Row() == 3 || zombie.Row() == 4 || zombie.Row() == 5) {
                    status[2] += score;
                }
            }
            std::sort(choices.begin(), choices.end(), [status](APosition a, APosition b){
                return status[a.row - 2] < status[b.row - 2];
            });
            TempC(wave, time - ADT, ACHERRY_BOMB, choices, time + 1);
        });
    }
}

#pragma endregion

#endif // WHATSS7_WALIB_H 
