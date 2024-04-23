#ifndef WALIB_INIT_H
#define WALIB_INIT_H

#include "cob.h"
#include "info.h"

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
        zombies = { APJ_0, ALZ_2, ACG_3, AWW_8, AXC_15, AQQ_16, AKG_17, ATT_18, ABJ_20, ATL_22, ABY_23, AHY_32 };
    } else if (scene == "RE" || scene == "ME") {
        // RE和FE没有水路僵尸、舞王和矿工
        zombies = { APJ_0, ALZ_2, ACG_3, ABC_12, AXC_15, AQQ_16, ATT_18, ABJ_20, AFT_21, ATL_22, ABY_23, AHY_32 };
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
    AutoManageCob();
}

// 初始化选卡，并根据场地选择合理的僵尸。
// 选卡剩下的格子会用一些常用的植物填充防止漏选。
// 场景可传入的参数参见 `SelectZombiesForScene()`.
void InitWithoutManage(const std::vector<APlantType> &plants, const char *scene = "Auto", bool fast = false) {
    SelectZombiesForScene(scene);
    SelectCardsAndFill(plants, fast);
    BindSpeedKeys();
}

void StartIceFiller(const std::vector<AGrid> &pos, int wave = 1, int time = -599) {
    AConnect(ATime(wave, time), [pos](){
        aIceFiller.Start(pos);
    });
}

void SkipToTime(int wave, int time = -199) {
    AConnect(ATime(1, -599), [wave, time](){
        ASkipTick(wave, time);
    });
}

ATickRunner waCheckRunner;


// 控制 `StartCheckMode()` 函数所检查的植物类型。
std::vector<APlantType> waCheckPlants = { ACOB_CANNON, AGLOOM_SHROOM, AWINTER_MELON };

// 控制 `StartCheckMode()` 函数所排除的植物位置。
std::vector<APosition> waCheckIgnore = {  };

// 启动测试模式：开启脚本循环，10倍速，当忧郁菇、冰瓜投手或玉米加农炮受损时弹窗提示。
// 检测受损的植物类型可通过修改 waCheckPlants 进行设置。
void StartCheckMode(float speed = 10, bool reload = true) {
    if (reload) ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    AConnect(ATime(1, -599), [speed](){ ASetGameSpeed(speed); });
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
    AConnect(ATime(1, -599), [speed](){ ASetGameSpeed(speed); });
}

// 启动记录模式：在每波刷新前一刻打印消息。可用于获取波长。
void RecordWaves() {
    for (int w: WaveList(1, 20)) {
        AConnect(ATime(w, -1), [w](){
            waIngameLogger.Info("Wave " + std::to_string(w));
        });
    }
}

#pragma endregion

#endif