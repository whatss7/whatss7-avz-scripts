#include "test.h"

struct PlantInfo {
    int row, col;
    APlantType type;
    PlantInfo(int r, int c, APlantType t) : row(r), col(c), type(t) {}
};

// 需要额外输出信息时，设置此变量可以将其附加在每波信息的后面。
std::string logMessage;

// 在此处输入需要保护的植物。
std::vector<PlantInfo> plants = {
    PlantInfo(2, 6, ACOB_CANNON),
    PlantInfo(3, 7, ACOB_CANNON),
    PlantInfo(4, 7, ACOB_CANNON),
    PlantInfo(5, 6, ACOB_CANNON),
};

// 以下是walib默认出怪，可供参考
// if (scene == "PE" || scene == "FE") {
//     zombies = { APJ_0, ACG_3, AWW_8, ABC_12, AHT_14, AXC_15, AQQ_16, AKG_17, ABJ_20, AFT_21, ABY_23, AHY_32 };
// } else if (scene == "DE") {
//     // DE没有水路僵尸
//     // 与DE2相比多路障、扶梯和跳跳（为了选僵尸合理选择的路障）
//     zombies = { APJ_0, ALZ_2, ACG_3, AWW_8, ABC_12, AXC_15, AKG_17, ATT_18, ABJ_20, AFT_21, ABY_23, AHY_32 };
// } else if (scene == "DE2") {
//     // 与DE相比多橄榄、气球和投篮
//     zombies = { APJ_0, ACG_3, AGL_7, AWW_8, ABC_12, AXC_15, AQQ_16, AKG_17, ABJ_20, ATL_22, ABY_23, AHY_32 };
// } else if (scene == "NE") {
//     // NE没有水路僵尸和冰车
//     zombies = { APJ_0, ALZ_2, ACG_3, AWW_8, AXC_15, AQQ_16, AKG_17, ATT_18, ABJ_20, ATL_22, ABY_23, AHY_32 };
// } else if (scene == "RE" || scene == "ME") {
//     // RE和FE没有水路僵尸、舞王和矿工
//     zombies = { APJ_0, ALZ_2, ACG_3, ABC_12, AXC_15, AQQ_16, ATT_18, ABJ_20, AFT_21, ATL_22, ABY_23, AHY_32 };
// }

// 在此处输入用冰位置、带卡、出僵尸等。
// 可能被炸掉的植物也需要在带卡中。
void PreOperations() {
    Init({AICE_SHROOM, ACOFFEE_BEAN, AFLOWER_POT, ACOB_CANNON}, "Auto", true);
    AConnect(ATime(1, -599), [](){ aIceFiller.Start({{2, 3}}); });
    StartReloadMode(10);
    SkipToTime(20, 2049);
}

// 在此处输入每波的操作，返回此波波长。所有波的波长必须一致。
// 在返回的波长-200时刻，场上的僵尸会被清除。
int WaveOperations(int wave) {
    const int len = 1750;
    int w = wave;
    I3(w, 11, len);
    RoofP(w, 410, 2, 2, 9);
    RoofP(w, 410, 6, 4, 9);
    RoofP(w, 630, 1, 2, 8.5);
    RoofP(w, 630, 3, 4, 8.5);
    TempC(w, 950, AFLOWER_POT, 2, 9, 1150);
    RoofP(w, 1140, 7, 4, 8.1);
    return len;
}

//////////////////////////////////////////////////

// 设置一波的波长，并在波长-200处干掉所有僵尸。
// 设置不超过2500的波长时，使用AvZ原生函数；设置超过2500的波长时，使用暂停刷新的方式。
void SetWavelength(int wave, int time) {
    if (time <= 2500) {
        ASetWavelength({ATime(wave, time)});
        AConnect(ATime(wave, time - 200), [](){
            StopZombieSpawn(ModState::OFF);
            InstantKill();
        });
    } else {
        AConnect(ATime(wave, 601), [](){
            StopZombieSpawn(ModState::SCOPED_ON);
        });
        AConnect(ATime(wave, time), [](){
            StopZombieSpawn(ModState::OFF);
            InstantKill();
        });
    }
}

int success_count = 0, fail_count = 0;
ALogger<AFile> logger("D:\\log.txt");

void AScript() {
    CommonTesting(false);
    PreOperations();
    int len = 0;
    for (int w: WaveList(1, 20)) {
        len = WaveOperations(w);
        if (w != 9 && w != 19 && w != 20) SetWavelength(w, len);
        AConnect(ATime(w, len - 200), [](){
            InstantKill();
            int check_count = 0;
            std::string dmg_str = "", miss_str = "";
            for (auto &&plant: aAlivePlantFilter) {
                for (auto &objective: plants) {
                    if (plant.Row() + 1 == objective.row && plant.Col() + 1 == objective.col && plant.Type() == objective.type) {
                        if (plant.Hp() != plant.HpMax()) {
                            std::string tmp = "(00)";
                            tmp[1] += objective.row;
                            tmp[2] += objective.col;
                            dmg_str += tmp;
                        } else {
                            check_count++;
                        }
                    }
                }
            }
            std::string msg;
            if (!logMessage.empty()) msg = " MSG@" + logMessage;
            if (check_count < plants.size()) {
                std::string scene = GetCurrentScene();
                for (auto &objective: plants) {
                    if (!ExistPlant(objective.type, objective.row, objective.col)) {
                        std::string tmp = "(00)";
                        tmp[1] += objective.row;
                        tmp[2] += objective.col;
                        miss_str += tmp;
                    }
                    ARemovePlant(objective.row, objective.col);
                    if (scene == "RE" || scene == "ME") {
                        if (objective.type == ACOB_CANNON) ACard(AFLOWER_POT, objective.row, objective.col + 1);
                        ACard(AFLOWER_POT, objective.row, objective.col);
                    } else if ((scene == "PE" || scene == "FE") && (objective.row == 3 || objective.row == 4)) {
                        if (objective.type == ACOB_CANNON) ACard(ALILY_PAD, objective.row, objective.col + 1);
                        ACard(ALILY_PAD, objective.row, objective.col);
                    }
                    ACard(objective.type, objective.row, objective.col);
                }
                fail_count++;
                logger.Info("FAIL #-# DMG@# MISS@##", success_count, fail_count, dmg_str, miss_str, msg);
            } else {
                success_count++;
                logger.Info("OK #-##", success_count, fail_count, msg);
            }
        });
    }
}