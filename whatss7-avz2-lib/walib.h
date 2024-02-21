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

// 玉米加农炮发射到生效用时
const int COB_FLYING_TIME = 373;
// 屋顶修正玉米加农炮发射到生效用时
const int ROOF_COB_FLYING_TIME = 387;
// 灰烬植物和寒冰菇种下到生效用时
const int ASH_DELAY_TIME = 100;
// 6秒加速波预判炸时间点
const int PRE_COB_POINT = -95;
// 旗帜波6秒加速波预判炸时间点
const int DELAYED_PRE_COB_POINT = -55;
// 咖啡豆生效时间198cs或199cs（此处取198cs）
const int COFFEE_BEAN_TIME = 198;
// 模仿者种下至生效时间319cs或320cs（此处取320cs）
const int IMITATOT_DELAY_TIME = 320;
// 6秒加速波预判炸生效时间点
const int PRE_COB_ACTIVATE_POINT = PRE_COB_POINT + COB_FLYING_TIME;
// 旗帜波6秒加速波预判炸生效时间点
const int DELAYED_PRE_COB_ACTIVATE_POINT = DELAYED_PRE_COB_POINT + COB_FLYING_TIME;

// 玉米加农炮发射到生效用时
const int CFT = COB_FLYING_TIME;
// 玉米加农炮发射到生效用时
const int RCFT = COB_FLYING_TIME;
// 灰烬植物和寒冰菇种下到生效用时
const int ADT = ASH_DELAY_TIME;
// 6秒加速波预判炸时间点
const int PCP = PRE_COB_POINT;
// 旗帜波6秒加速波预判炸时间点
const int DPCP = DELAYED_PRE_COB_POINT;
// 旗帜波6秒加速波预判炸时间点
const int W10PCP = DPCP, W20PCP = DPCP;
// 咖啡豆生效时间198cs或199cs（此处取198cs）
const int CBT = COFFEE_BEAN_TIME;
// 模仿者种下至生效时间319cd或320cs（此处取319cs）
const int MDT = IMITATOT_DELAY_TIME;
// 6秒加速波预判炸生效时间点
const int PCAP = PRE_COB_ACTIVATE_POINT;
// 旗帜波6秒加速波预判炸生效时间点
const int DPCAP = DELAYED_PRE_COB_ACTIVATE_POINT;

#ifdef WALIB_DEBUG
ALogger<AConsole> waDebugLogger;
#define DEBUG_LOG(x) waDebugLogger.Info(x)
#else
#define DEBUG_LOG(x)
#endif
ALogger<AMsgBox> waLogger;
ALogger<APvzGui> waIngameLogger;
ATickRunner waRecoverEndRunner;
ATickRunner waCheckRunner;
ATickRunner waBloverTickRunner;
APlantFixer waWallNutFixer, waTallNutFixer, waPumpkinFixer;
ACobManager waRoofR1R2CobManager, waRoofR3CobManager;

// 控制 `WACheck()` 函数所检查的植物类型。
std::vector<APlantType> waCheckPlants = { ACOB_CANNON, AGLOOM_SHROOM, AWINTER_MELON };

// 控制 `ForEnd()` 和 `PPForEnd()` 函数所无视的僵尸类型。其中设置的类型在 w20 也生效。
std::vector<AZombieType> waForEndIgnore = { AKG_17, AXG_24 };

// 控制 `ForEnd()` 和 `PPForEnd()` 函数所无视的水路僵尸类型。若为空，则沿用 `waForEndIgnore` 的设置。
// 在其中插入一个不会在水路生成的僵尸以禁用上述行为。
std::vector<AZombieType> waForEndIgnoreInWater = {};

// 有概率漏气球时，加上三叶草保险
void WAStartBlover(int row = 1, int column = 1) {
    waBloverTickRunner.Start([row, column](){
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

// 获得当前所处的场地。
std::string WAGetCurrentScene() {
    std::string scenes[] = { "DE", "NE", "PE", "FE", "RE", "ME" };
    int scene_id = AGetMainObject()->Scene();
    if (scene_id < 0 || scene_id > 5) { waLogger.Error("未知的场地"); return ""; }
    else return scenes[scene_id];
}

// 判断场上某行是否有指定类型的僵尸。此处行从 1 开始编号。
bool WAExistZombie(std::vector<AZombieType> types, std::vector<int> rows = {1, 2, 3, 4, 5, 6}) {
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
bool WAExistZombie(AZombieType type, std::vector<int> rows = {1, 2, 3, 4, 5, 6}) {   
    return WAExistZombie(std::vector<AZombieType>({type}), rows);
}

// 判断指定位置是否有指定的植物。
bool WAExistPlant(APlantType type, int row, int col) {
    for (auto &&plant: aAlivePlantFilter) {
        if (plant.Type() == type && plant.Col() + 1 == col && plant.Row() + 1 == row) {
            return true;
        }
    }
    return false;
}

// 判断指定位置是否有指定的植物。
bool WAExistPlant(std::vector<APlantType> types, int row, int col) {
    for (auto type: types) {
        if (WAExistPlant(type, row, col)) return true;
    }
    return false;
}

// 根据场地选择合理的僵尸。
// 场地支持传入的参数：
// `"None"` 或其他任意下方未提到的参数: 不进行僵尸选择，使用自然出怪
// `"Auto"` 或不传入参数: 自动根据场地选择下面的组合
// `"DE"`: 路障 撑杆 橄榄 舞王 冰车 小丑 气球 矿工 蹦极 白眼 红眼
// `"NE"`: 路障 撑杆 橄榄 舞王 小丑 气球 矿工 跳跳 蹦极 白眼 红眼
// `"PE"` 或 `"FE"`: 撑杆 橄榄 舞王 冰车 海豚 小丑 气球 矿工 蹦极 白眼 红眼
// `"RE"` 或 `"ME"`: 路障 撑杆 橄榄 冰车 小丑 气球 跳跳 蹦极 扶梯 白眼 红眼
// `"PEF"` PE快速关: 路障 撑杆 舞王 潜水 冰车 海豚 小丑 矿工 跳跳 蹦极 扶梯
void WASelectZombies(std::string scene = "Auto") {
    for (int i = 0; i < scene.length(); i++) {
        scene[i] = toupper(scene[i]);
    }
    if (scene == "AUTO")  scene = WAGetCurrentScene();

    std::vector<AZombieType> zombies;
    if (scene == "PE" || scene == "FE") {
        zombies = { ACG_3, AGL_7, AWW_8, ABC_12, AHT_14, AXC_15, AQQ_16, AKG_17, ABJ_20, ABY_23, AHY_32 };
    } else if (scene == "DE") {
        // DE没有水路僵尸
        zombies = { ALZ_2, ACG_3, AGL_7, AWW_8, ABC_12, AXC_15, AQQ_16, AKG_17, ABJ_20, ABY_23, AHY_32 };
    } else if (scene == "NE") {
        // NE没有水路僵尸和冰车
        zombies = { ALZ_2, ACG_3, AGL_7, AWW_8, AXC_15, AQQ_16, AKG_17, ATT_18, ABJ_20, ABY_23, AHY_32 };
    } else if (scene == "RE" || scene == "ME") {
        // RE和FE没有水路僵尸、舞王和矿工
        zombies = { ALZ_2, ACG_3, AGL_7, ABC_12, AXC_15, AQQ_16, ATT_18, ABJ_20, AFT_21, ABY_23, AHY_32 };
    } else if (scene == "PEF") {
        zombies = { ALZ_2, ACG_3, AWW_8, AQS_11, ABC_12, AHT_14, AXQ_13, AKG_17, ATT_18, ABJ_20, AFT_21 };
    }
    if (!zombies.empty()) ASetZombies(std::vector<int>(zombies.begin(), zombies.end()));
}

void WASelectCards(std::vector<APlantType> plants = {}, bool fast = false) {
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

// 初始化选卡并指定僵尸。传入空数组不指定僵尸，使用自然生成的僵尸。
// 选卡剩下的格子会用一些常用的植物填充防止漏选。
void WAInit(const std::vector<APlantType> &plants, const std::vector<AZombieType> &zombies, bool cycle = false, bool fast = false) {
    if (!zombies.empty()) ASetZombies(std::vector<int>(zombies.begin(), zombies.end()));
    WASelectCards(plants, fast);
}

// 初始化选卡，并根据场地选择合理的僵尸。
// 选卡剩下的格子会用一些常用的植物填充防止漏选。
// 场景可传入的参数参见 `WASelectZombies()`.
void WAInit(const std::vector<APlantType> &plants, const char *scene = "Auto", bool fast = false) {
    WASelectZombies(scene);
    WASelectCards(plants, fast);
}

// 自动管理全场炮。若需要使用后续轨道语言函数，则此处必须进行自动管理。
// 在屋顶场景，炮尾处于1-2列的炮和3列的炮分别单独归类。
void WAAutoManageCob() {
    AConnect(ATime(1, -599), [] {
        std::string scene = WAGetCurrentScene();
        if (scene == "RE" || scene == "ME") {
            std::vector<AGrid> R1R2, R3, others;
            for (auto &&plant: aAlivePlantFilter) {
                if (plant.Type() == ACOB_CANNON) {
                    if (plant.Col() <= 2) R1R2.push_back({plant.Row() + 1, plant.Col() + 1});
                    else if (plant.Col() == 3) R3.push_back({plant.Row() + 1, plant.Col() + 1});
                    else others.push_back({plant.Row() + 1, plant.Col() + 1});
                }
            }
            waRoofR1R2CobManager.SetList(R1R2);
            waRoofR3CobManager.SetList(R3);
            aCobManager.SetList(others);
        } else {
            aCobManager.AutoSetList();
        }
    });
}

void WAFixNuts(int wave = 1, int time = -599) {
    AConnect(ATime(wave, time), [] {
        if(AGetSeedIndex(AWALL_NUT) != -1){
            waWallNutFixer.Start(AWALL_NUT, {}, 4000 / 3 * 2);
        }
        if(AGetSeedIndex(ATALL_NUT) != -1){
            waTallNutFixer.Start(ATALL_NUT, {}, 8000 / 3 * 2);
        }
        if(AGetSeedIndex(APUMPKIN) != -1){
            waPumpkinFixer.Start(APUMPKIN, {}, 4000 / 3 * 2);
        }
    });
}

void WASkipTo(int wave, int time = -199) {
    AConnect(ATime(1, -590), [wave, time](){
        ASkipTick(wave, time);
    });
}

// 启动测试模式：开启脚本循环，10倍速，当忧郁菇、冰瓜投手或玉米加农炮受损时弹窗提示。
// 检测受损的植物类型可通过修改 waCheckPlants 进行设置。
void WACheck() {
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    ASetGameSpeed(10);
    waCheckRunner.Start([](){
        for (auto &&plant: aAlivePlantFilter) {
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

void WARecordWaves() {
    for (int w: WaveList(1, 20)) {
        AConnect(ATime(w, -1), [w](){
            waIngameLogger.Info("Wave " + std::to_string(w));
        });
    }
}

// 判断是否为有效的时间。
// w1 / w10 / w20 的时间总是有效，而其他波次小于 -200 的时间无效。
bool WAIsValidTime(int wave, int time) {
    if (wave == 1 || wave == 10 || wave == 20) return true;
    else return time >= -200;
}

// 使用墓碑吞噬者尝试种植所有可能生长墓碑的位置。
void WARemoveGraves(int wave, int time) {
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

// 从 `aCobManager` 发射一对炮。
// 若不设置位置，则泳池场景默认炸2-9和5-9，其他场景默认炸2-9和4-9。
// 请注意，本函数先填列数，再填行数。
// 若不设置时间，则 w10 或 w20 318cs (`DPCAP`) 时生效，其他时间 278cs (`PCAP`) 时生效
// 屋顶场景，1-2路的炮优先选择一二列炮，其次三列炮，最后平炮；3-5路相反。
void PP(int wave, int time = -1, float col = 9, std::vector<int> rows = {}) {
    if (rows.empty()) {
        std::string scene = WAGetCurrentScene();
        if (scene == "PE" || scene == "FE") {
            rows = {2, 5};
        } else {
            rows = {2, 4};
        }
    }
    if (time < 0) {
        if (wave == 10 || wave == 20) time = DPCAP;
        else time = PCAP;
    }
    std::string scene = WAGetCurrentScene();
    if (scene == "RE" || scene == "ME") {
        for (int row: rows) {
            if (row <= 2) {
                AConnect(ATime(wave, time - RCFT), [row, col](){
                    if (waRoofR1R2CobManager.GetRoofUsablePtr(col)) {
                        waRoofR1R2CobManager.RoofFire(row, col);
                    } else if (waRoofR3CobManager.GetRoofUsablePtr(col)) {
                        waRoofR3CobManager.RoofFire(row, col);
                    } else {
                        aCobManager.RoofFire(row, col);
                    }
                });
            } else {
                AConnect(ATime(wave, time - RCFT), [row, col](){
                    if (aCobManager.GetRoofUsablePtr(col)) {
                        aCobManager.RoofFire(row, col);
                    } else if (waRoofR3CobManager.GetRoofUsablePtr(col)) {
                        waRoofR3CobManager.RoofFire(row, col);
                    } else {
                        waRoofR1R2CobManager.RoofFire(row, col);
                    }
                });
            }
        }
    } else {
        std::vector<APosition> pos;
        for (int i: rows) pos.push_back({i, col});
        AConnect(ATime(wave, time - CFT), [pos](){
            aCobManager.Fire(pos);
        });
    }
}

// 从 `aCobManager` 发射一炮。
void P(int wave, int time, int row, float col) {
    std::vector<int> rows;
    rows.push_back(row);
    PP(wave, time, col, rows);
}


// 用于收尾的函数。在指定时间是对应波次（处于刷新倒计时也算）且场上有僵尸才执行对应的操作。此函数w9/w19不计伴舞，且所有波次默认不计矿工和小鬼。
void ForEnd(int wave, int time, std::function<void()> action) {
    AConnect(ATime(wave, time), [wave, action](){
        std::string scene = WAGetCurrentScene();
        if ((scene == "PE" || scene == "FE") && waForEndIgnoreInWater.empty()) {
            waForEndIgnoreInWater = waForEndIgnore;
        }
        ATime now = ANowTime();
        if (now.wave != wave) return;
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
            if (zombie.Type() != ABW_9 || (wave != 9 && wave != 19)) {
                hasZombie = true;
            }
        }
        if (!hasZombie) return;
        action();
    });
}

// 用于收尾的炮。是对应波次（处于下一波的刷新倒计时也算本波）且场上有僵尸才发射。注意此函数w9/w19不计伴舞。
void PPForEnd(int wave, int time, float col = 9, std::vector<int> rows = {}) {
    std::string scene = WAGetCurrentScene();
    int VCFT = (scene == "RE" || scene == "ME" ? 387 : 373);
    ForEnd(wave, time - VCFT, [=](){ PP(wave, time, col, rows); });
}

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

// 开启自动存冰时，从 `aIceFiller` 进行点冰。若需要非旗帜波的完美预判冰，则需要假设波长或提供上一波波长。
// 由于咖啡豆的不确定性，有概率延迟1cs生效。
void I(int wave, int time = 11, int last_wave_length = -1) {
    time -= CBT + ADT;
    if (!WAIsValidTime(wave, time) && last_wave_length > 0) {
        wave -= 1;
        time += last_wave_length;
    }
    AConnect(ATime(wave, time), [](){
        aIceFiller.Coffee();
    });
}

// 手动种植毁灭菇或寒冰菇。
void ManualShroom(int wave, int time, std::vector<APosition> pos, APlantType card, int protect, int last_wave_length) {
    bool isDay = true;
    APlantType imitated = (card == AICE_SHROOM ? AM_ICE_SHROOM : AM_DOOM_SHROOM);
    std::string scene = WAGetCurrentScene();
    if (scene == "NE" || scene == "FE" || scene == "ME") {
        isDay = false;
    }
    int VCBT = isDay ? CBT : 0;
    if (AGetCardPtr(imitated)) {
        // 携带了模仿植物的情况
        if (!WAIsValidTime(wave, time - (MDT + (isDay ? 1 : 0)) - VCBT - ADT) && last_wave_length > 0) {
            wave -= 1;
            time += last_wave_length;
        }
        // 若为白昼，早种植1cs，模仿者即使319cs完成变身也等到320cs再种咖啡豆，保证延迟最大为1cs。
        // 若为黑夜，则不能早种植，否则有概率提前1cs。
        AConnect(ATime(wave, time - (MDT + (isDay ? 1 : 0)) - VCBT - ADT), [wave, time, card, imitated, pos, scene, isDay, VCBT, protect](){
            if (AGetCardPtr(imitated)->IsUsable() && !(AGetCardPtr(card) && AGetCardPtr(card)->IsUsable())) {
                // 若模仿能种而普通不能种（此判断提前完成，存在普通到时间能转好但还是使用模仿的现象）
                // 则立即种植模仿
                for (APosition p: pos) {
                    APlant *ptr = nullptr;
                    bool should_remove = false;
                    bool should_remove_pumpkin = false;
                    if ((scene == "RE" || scene == "ME") && !WAExistPlant(AFLOWER_POT, p.row, p.col)) {
                        ptr = ACard({AFLOWER_POT, imitated}, p.row, p.col)[1];
                        should_remove = true;
                    } else if ((scene == "PE" || scene == "FE") && p.row >= 3 && p.row <= 4 && !WAExistPlant(ALILY_PAD, p.row, p.col)) {
                        ptr = ACard({ALILY_PAD, imitated}, p.row, p.col)[1];
                        should_remove = true;
                    } else {
                        ptr = ACard(imitated, p.row, p.col);
                    }
                    if (ptr) {
                        if (protect > 0 && !WAExistPlant(APUMPKIN, p.row, p.col)) {
                            should_remove_pumpkin = true;
                            ACard(APUMPKIN, p.row, p.col);
                        }
                        if (isDay) {
                            AConnect(ATime(wave, time - CBT - ADT), [p](){
                                ACard(ACOFFEE_BEAN, p.row, p.col);
                            });
                        }
                        if (card == AICE_SHROOM && should_remove) {
                            AConnect(ATime(wave, time + 1), [p](){
                                ARemovePlant(p.row, p.col, {AFLOWER_POT, ALILY_PAD});
                            });
                        }
                        if (card == AICE_SHROOM && should_remove_pumpkin) {
                            AConnect(ATime(wave, time + 1), [p](){
                                ARemovePlant(p.row, p.col, APUMPKIN);
                            });
                        }
                        break;
                    }
                }
            } else {
                // 否则稍后种植普通
                AConnect(ATime(wave, time - VCBT - ADT), [wave, time, card, pos, scene, isDay, protect](){
                    for (APosition p: pos) {
                        APlant *ptr = nullptr;
                        bool should_remove = false;
                        bool should_remove_pumpkin = false;
                        if ((scene == "RE" || scene == "ME") && !WAExistPlant(AFLOWER_POT, p.row, p.col)) {
                            ptr = ACard({AFLOWER_POT, card}, p.row, p.col)[1];
                            should_remove = true;
                        } else if ((scene == "PE" || scene == "FE") && p.row >= 3 && p.row <= 4 && !WAExistPlant(ALILY_PAD, p.row, p.col)) {
                            ptr = ACard({ALILY_PAD, card}, p.row, p.col)[1];
                            should_remove = true;
                        } else {
                            ptr = ACard(card, p.row, p.col);
                        }
                        if (ptr) {
                            if (protect > 1 && !WAExistPlant(APUMPKIN, p.row, p.col)) {
                                should_remove_pumpkin = true;
                                ACard(APUMPKIN, p.row, p.col);
                            }
                            if (isDay) ACard(ACOFFEE_BEAN, p.row, p.col);
                            if (card == AICE_SHROOM && should_remove) {
                                AConnect(ATime(wave, time + 1), [p](){
                                    ARemovePlant(p.row, p.col, {AFLOWER_POT, ALILY_PAD});
                                });
                            }
                            if (card == AICE_SHROOM && should_remove_pumpkin) {
                                AConnect(ATime(wave, time + 1), [p](){
                                    ARemovePlant(p.row, p.col, APUMPKIN);
                                });
                            }
                            break;
                        }
                    }
                });
            }
        });
    } else {
        // 未携带模仿核同之前的“否则”情况。
        if (!WAIsValidTime(wave, time - VCBT - ADT)) {
            wave -= 1;
            time += last_wave_length;
        }
        AConnect(ATime(wave, time - VCBT - ADT), [wave, time, card, pos, scene, isDay, protect](){
            for (APosition p: pos) {
                APlant *ptr = nullptr;
                bool should_remove = false;
                bool should_remove_pumpkin = false;
                if ((scene == "RE" || scene == "ME") && !WAExistPlant(AFLOWER_POT, p.row, p.col)) {
                    ptr = ACard({AFLOWER_POT, card}, p.row, p.col)[1];
                    should_remove = true;
                } else if ((scene == "PE" || scene == "FE") && p.row >= 3 && p.row <= 4 && !WAExistPlant(ALILY_PAD, p.row, p.col)) {
                    ptr = ACard({ALILY_PAD, card}, p.row, p.col)[1];
                    should_remove = true;
                } else {
                    ptr = ACard(card, p.row, p.col);
                }
                if (ptr) {
                    if (protect > 1 && !WAExistPlant(APUMPKIN, p.row, p.col)) {
                        should_remove_pumpkin = true;
                        ACard(APUMPKIN, p.row, p.col);
                    }
                    if (isDay) ACard(ACOFFEE_BEAN, p.row, p.col);
                    if (card == AICE_SHROOM && should_remove) {
                        AConnect(ATime(wave, time + 1), [p](){
                            ARemovePlant(p.row, p.col, {AFLOWER_POT, ALILY_PAD});
                        });
                    }
                    if (card == AICE_SHROOM && should_remove_pumpkin) {
                        AConnect(ATime(wave, time + 1), [p](){
                            ARemovePlant(p.row, p.col, APUMPKIN);
                        });
                    }
                    break;
                }
            }
        });
    }
}

// 种植寒冰菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// 若存在预判冰或模仿冰等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿冰时，使用此函数请不要携带模仿冰。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void ManualI(int wave, int time, std::vector<APosition> pos, int protect = 0, int last_wave_length = -1){
    ManualShroom(wave, time, pos, AICE_SHROOM, protect, last_wave_length);
}

// 种植寒冰菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// 若存在预判冰或模仿冰等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿冰时，使用此函数请不要携带模仿冰。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void ManualI(int wave, int time, int row, float col, int protect = 0, int last_wave_length = -1){
    ManualShroom(wave, time, {{row, col}}, AICE_SHROOM, protect, last_wave_length);
}

// 种植毁灭菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// 若存在模仿核等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿核时，使用此函数请不要携带模仿核。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿核；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void N(int wave, int time, std::vector<APosition> pos, int protect = 0, int last_wave_length = -1) {
    ManualShroom(wave, time, pos, ADOOM_SHROOM, protect, last_wave_length);
}


// 种植毁灭菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// 若存在模仿核等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿核时，使用此函数请不要携带模仿核。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿核；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void N(int wave, int time, int row, float col, int protect = 0, int last_wave_length = -1) {
    ManualShroom(wave, time, {{row, col}}, ADOOM_SHROOM, protect, last_wave_length);
}

// 种植一个临时植物并在一段时间后移除。此函数还会帮忙临时种植花盆或睡莲。
// 若给定的时长为负数，则不会移除该植物。
void TempC(int wave, int time, APlantType card, std::vector<APosition> pos, int duration) {
    std::string scene = WAGetCurrentScene();
    AConnect(ATime(wave, time), [wave, time, card, pos, scene, duration](){
        for (APosition p: pos) {
            bool should_remove = false;
            APlant *ptr = nullptr;
            if ((scene == "RE" || scene == "ME") && !WAExistPlant(AFLOWER_POT, p.row, p.col)) {
                ptr = ACard({AFLOWER_POT, card}, p.row, p.col)[1];
                should_remove = true;
            } else if ((scene == "PE" || scene == "FE") && p.row >= 3 && p.row <= 4 && !WAExistPlant(ALILY_PAD, p.row, p.col)) {
                ptr = ACard({ALILY_PAD, card}, p.row, p.col)[1];
                should_remove = true;
            } else {
                ptr = ACard(card, p.row, p.col);
            }
            if (ptr) {
                if (duration >= 0) {
                    if (should_remove){
                        AConnect(ATime(wave, time + duration), [p, card](){
                            ARemovePlant(p.row, p.col, {card, AFLOWER_POT, ALILY_PAD});
                        });
                    } else {
                        AConnect(ATime(wave, time + duration), [p, card](){
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
// 若给定的时长为负数，则不会移除该植物。
void TempC(int wave, int time, APlantType card, int row, float col, int duration) {
    TempC(wave, time, card, {{row, col}}, duration);
}

// 使用一个樱桃炸弹。此函数不会使用模仿樱桃炸弹。
void A(int wave, int time, int row, float col) {
    TempC(wave, time - ADT, ACHERRY_BOMB, row, col, 101);
}

// 使用一个火爆辣椒。此函数不会使用模仿火爆辣椒。
void J(int wave, int time, int row, float col) {
    TempC(wave, time - ADT, AJALAPENO, row, col, 101);
}

// 使用一个樱桃炸弹用于P6节奏旗帜波中的消延迟。此函数不会使用模仿樱桃炸弹。
void DelayRemovingA(int wave, int time) {
    std::string scene = WAGetCurrentScene();
    if (scene == "PE" || scene == "FE") {
        AConnect(ATime(wave, time - ADT), [wave, time](){
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
                TempC(wave, time - ADT, ACHERRY_BOMB, {{5, 9}, {2, 9}}, 101);
            } else {
                TempC(wave, time - ADT, ACHERRY_BOMB, {{2, 9}, {5, 9}}, 101);
            }
        });
    } else {
        AConnect(ATime(wave, time - ADT), [wave, time](){
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
            TempC(wave, time - ADT, ACHERRY_BOMB, choices, 101);
        });
    }
}

void DRA(int wave, int time) { DelayRemovingA(wave, time); }

#endif // WHATSS7_WALIB_H 
