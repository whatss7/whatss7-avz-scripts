#include "test.h"

struct PlantInfo {
    int row, col;
    APlantType type;
    PlantInfo(int r, int c, APlantType t) : row(r), col(c), type(t) {}
};

// 在此处输入需要保护的植物。
std::vector<PlantInfo> plants = {
    PlantInfo(2, 6, ACOB_CANNON),
    PlantInfo(3, 7, ACOB_CANNON),
    PlantInfo(4, 7, ACOB_CANNON),
};

// 在此处输入用冰位置、带卡、出僵尸等。
// 可能被炸掉的植物也需要在带卡中。
void PreOperations() {
    Init({AICE_SHROOM, ACOFFEE_BEAN, AFLOWER_POT, ACOB_CANNON}, {AFT_21, AXC_15, ATL_22}, true);
    AConnect(ATime(1, -599), [](){ aIceFiller.Start({{2, 1}}); });
    StartReloadMode(10);
    SkipToTime(20, 1);
}

// 在此处输入每波的操作，返回此波波长。所有波的波长必须一致。
// 在返回的波长-200时刻，场上的僵尸会被清除。
int WaveOperations(int wave) {
    const int len = 1750;
    int w = wave;
    I3(w, 11, 1800);
    RoofP(w, 410, 2, 2, 9);
    RoofP(w, 410, 6, 4, 9);
    RoofP(w, 630, 1, 2, 8.5);
    RoofP(w, 630, 3, 4, 8.5);
    TempC(w, 1000, AFLOWER_POT, 2, 9, 1200);
    RoofP(w, 1140, 7, 4, 8.1);
    return len;
}

//////////////////////////////////////////////////

int success_count = 0, fail_count = 0;
ALogger<AFile> logger("D:\\log.txt");

void AScript() {
    CommonTesting(false);
    PreOperations();
    int len = 0;
    for (int w: WaveList(1, 9) + WaveList(11, 19)) {
        len = WaveOperations(w);
        ASetWavelength({ATime(w, len)});
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
                logger.Info("FAIL #-# DMG@# MISS@#", success_count, fail_count, dmg_str, miss_str);
            } else {
                success_count++;
                logger.Info("OK #-#", success_count, fail_count);
            }
        });
    }
    for (int w: { 10, 20 }) {
        AConnect(ATime(w, 1), [](){
            InstantKill();
        });
    }
    ASetWavelength({ATime(10, len)});
    
}