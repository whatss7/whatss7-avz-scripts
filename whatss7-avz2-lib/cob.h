#ifndef WALIB_COB_H
#define WALIB_COB_H

#include "const.h"
#include "card.h"
#include "info.h"

#pragma region 仿轨道语言：炮相关

bool RoofCMUsed[9];
ACobManager waRoofCobManager[9];

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
                if (!grids[i].empty()) {
                    waRoofCobManager[i].SetList(grids[i]);
                    #ifdef WALIB_DEBUG
                    waDebugLogger.Info("Added # cobs to col #", grids[i].size(), i);
                    #endif
                    RoofCMUsed[i] = true;
                } else {
                    RoofCMUsed[i] = false;
                }
            }
        } else {
            aCobManager.AutoSetList();
        }
    });
}

// 从 `aCobManager` 发射一对炮。
// 若不设置位置，则泳池场景默认炸2-9和5-9，其他场景默认炸2-9和4-9。
// 请注意，本函数先填列数，再填行数。
// 若不设置时间，则 318cs (`PCP`) 时生效。
// 屋顶场景，1-2路的炮优先选择风炮；3-5路优先选择平炮。
void PP(int wave, int time = -1000, float col = 9, std::vector<int> rows = {}) {
    if (rows.empty()) {
        std::string scene = GetCurrentScene();
        if (scene == "PE" || scene == "FE") {
            rows = {2, 5};
        } else {
            rows = {2, 4};
        }
    }
    if (time < -999) time = PCP;
    std::string scene = GetCurrentScene();
    if (scene == "RE" || scene == "ME") {
        #ifdef WALIB_DEBUG
        waDebugLogger.Info("Roof scene");
        #endif
        for (int row: rows) {
            if (row <= 2) {
                AConnect(ATime(wave, time - RCFT), [row, col](){
                    bool success = false;
                    for (int i = 1; i <= 8; i++) {
                        if (RoofCMUsed[i] && waRoofCobManager[i].GetRoofUsablePtr(col) != nullptr) {
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
                        if (RoofCMUsed[i] && waRoofCobManager[i].GetRoofUsablePtr(col)) {
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
                AConnect(ATime(wave, time - PCFT), [row, col](){
                    aCobManager.Fire(row, col);
                });
            } else {
                AConnect(ATime(wave, time - CFT), [row, col](){
                    aCobManager.Fire(row, col);
                });
            }
        }
    }
}

// 从 `aCobManager` 发射一对炮。
// 本函数与 `PP()` 完全相同，但除所炸行数外没有默认值。可用作更好的语义解释。
void BB(int wave, int time, float col, std::vector<int> rows = {}) {
    PP(wave, time, col, rows);
}

// 从 `aCobManager` 发射一对炮。
// 若不设置位置，则前院场景默认炸1-8和4-8，则泳池场景默认炸1-8和5-8，屋顶场景默认炸2-8和4-8。
// 请注意，本函数先填列数，再填行数。
// 若不设置时间，则 428cs (`PCP + 110`) 时生效。
// 屋顶场景，1-2路的炮优先选择风炮；3-5路优先选择平炮。
void DD(int wave, int time = -1, float col = 8, std::vector<int> rows = {}) {
    std::string scene = GetCurrentScene();
    if (rows.empty()) {
        if (scene == "PE" || scene == "FE") {
            rows = {1, 5};
        } else if (scene == "DE" || scene == "NE") {
            rows = {1, 4};
        } else {
            rows = {2, 4};
        }
    }
    if (time < 0) time = PCP + 110;
    PP(wave, time, col, rows);
}

// 从 `aCobManager` 发射一对炮。
// 若不设置位置，则前院场景默认炸2-4和4-4，则泳池场景默认炸1-4和5-4，屋顶场景默认炸2-5和4-5。
// 请注意，本函数先填列数，再填行数。
// 若不设置时间，则前院场景 579cs (`PCP + 261`) 时生效，后院场景 548cs (`PCP + 230`) 时生效，屋顶场景 538cs (`PCP + 220`) 时生效。
// 屋顶场景，1-2路的炮优先选择风炮；3-5路优先选择平炮。
void dd(int wave, int time = -1, float col = -1, std::vector<int> rows = {}) {
    std::string scene = GetCurrentScene();
    if (col < 0) {
        if (scene == "RE" || scene == "ME") {
            col = 5;
        } else {
            col = 4;
        }
    }
    if (rows.empty()) {
        if (scene == "PE" || scene == "FE") {
            rows = {1, 5};
        } else if (scene == "DE" || scene == "NE") {
            rows = {1, 4};
        } else {
            rows = {2, 4};
        }
    }
    if (time < 0) {
        if (scene == "DE" || scene == "NE"){
            time = PCP + 261;
        } else if (scene == "PE" || scene == "FE")  {
            time = PCP + 230;
        } else {
            time = PCP + 220;
        }
    }
    PP(wave, time, col, rows);
}

// 从 `aCobManager` 发射一炮。
void P(int wave, int time, int row, float col) {
    std::vector<int> rows;
    rows.push_back(row);
    PP(wave, time, col, rows);
}

// 从 `aCobManager` 发射一炮。
// 本函数与 `P()` 完全相同，可用作更好的语义解释。
void S(int wave, int time, int row, float col) {
    P(wave, time, row, col);
}

// 从 `aCobManager` 发射两炮至同一位置。
// 本函数与调用两次 `P()` 完全相同，可用作更好的语义解释。
void PS(int wave, int time, int row, float col) {
    P(wave, time, row, col);
    S(wave, time, row, col);
}

// 从 `aCobManager` 发射一炮。
// 本函数与 `P()` 完全相同，可用作更好的语义解释。
void B(int wave, int time, int row, float col) {
    P(wave, time, row, col);
}

// 从 `aCobManager` 发射一炮。
// 本函数与 `P()` 完全相同，可用作更好的语义解释。
void D(int wave, int time, int row, float col) {
    P(wave, time, row, col);
}

// 从 `aCobManager` 发射一炮。
// 本函数与 `P()` 完全相同，可用作更好的语义解释。
void d(int wave, int time, int row, float col) {
    P(wave, time, row, col);
}

// 在屋顶场景使用炮尾在指定列的炮发射一炮。
void RoofP(int wave, int time, std::vector<int> cobCols, int row, float col) {
    std::string scene = GetCurrentScene();
    if (scene != "RE" && scene != "ME") {
        waLogger.Error("RoofP() 只能在屋顶使用");
        return;
    }
    for (int i: cobCols) {
        if (i < 1 || i > 8) {
            waLogger.Error("炮列数超出范围");
            return;
        }
    }
    AConnect(ATime(wave, time - RCFT), [cobCols, row, col](){
        bool success;
        for (int i: cobCols) {
            if (RoofCMUsed[i] && waRoofCobManager[i].GetRoofUsablePtr(col)) {
                waRoofCobManager[i].RoofFire(row, col);
                success = true;
                break;
            }
        }
        if (!success) waLogger.Error("指定列数的所有炮都无法发射");
    });
}

// 在屋顶场景使用炮尾在指定列的炮发射一炮。
void RoofP(int wave, int time, int cobCol, int row, float col) {
    std::string scene = GetCurrentScene();
    if (scene != "RE" && scene != "ME") {
        waLogger.Error("RoofP() 只能在屋顶使用");
        return;
    }
    if (cobCol < 1 || cobCol > 8) {
        waLogger.Error("炮列数超出范围");
        return;
    }
    AConnect(ATime(wave, time - RCFT), [cobCol, row, col](){
        waRoofCobManager[cobCol].RoofFire(row, col);
    });
}

// 使用指定的 ACobManager 对指定位置开炮。
void ManualP(int wave, int time, int row, float col, ACobManager &mgr) {
    std::string scene = GetCurrentScene();
    if (scene == "RE" || scene == "ME") {
        AConnect(ATime(wave, time - RCFT), [&mgr, row, col](){
            mgr.RoofFire(row, col);
        });
    } else if ((scene == "PE" || scene == "FE") && (row == 3 || row == 4)) {
        AConnect(ATime(wave, time - PCFT), [row, col](){
            aCobManager.Fire(row, col);
        });
    } else {
        AConnect(ATime(wave, time - CFT), [&mgr, row, col](){
            mgr.Fire(row, col);
        });
    }
}

ATickRunner atEndRunner;
void AtEnd(std::function<void()> action) {
    AConnect(ATime(20, 1), [=](){
        atEndRunner.Start([=](){
            for (auto &&_ : aAliveZombieFilter) {
                (void)_;
                return;
            }
            action();
            atEndRunner.Stop();
        });
    });
}

// 用于收尾的炮。是对应波次（处于下一波的刷新倒计时也算本波）且场上有僵尸才发射。注意此函数w9/w19不计伴舞。
void PPForEnd(int wave, int time, float col = 9, std::vector<int> rows = {}) {
    std::string scene = GetCurrentScene();
    int VCFT = (scene == "RE" || scene == "ME" ? 387 : 373);
    ForEnd(wave, time - VCFT, [=](){ PP(wave, time, col, rows); });
}

// 用于收尾的炮。是对应波次（处于下一波的刷新倒计时也算本波）且场上有僵尸才发射。注意此函数w9/w19不计伴舞。
void PForEnd(int wave, int time, int row, float col) {
    std::string scene = GetCurrentScene();
    int VCFT = (scene == "RE" || scene == "ME" ? 387 : 373);
    ForEnd(wave, time - VCFT, [=](){ P(wave, time, row, col); });
}

// 此函数必须在 `AConnect` 中使用。
// 对除了某列以外的所有红眼开炮。常用于拖收尾。
// 传递的时间是计划生效炮的时间，返回计划留下的列。
// 若场上没有红眼，且当前是w20，则改为对除了某列以外的所有僵尸开炮。
// 注意，此函数是按照调用时的僵尸分布进行决定。
int SchedulePPExceptOne(int wave, int time, float col) {
    int choice = -1;
    int dist[7] = { 0, 0, 0, 0, 0, 0, 0 };
    int sum = 0;
    std::string scene = GetCurrentScene();
    for (auto &&zombie: aAliveZombieFilter) {
        if (zombie.Type() != AHY_32) continue;
        if (zombie.AtWave() + 1 != wave) continue;
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
    // 初始化发炮函数，使得在天台优先使用平炮
    std::function<void(int, int, int, int)> AutoP = nullptr;
    if (scene == "RE" || scene == "ME") {
        AutoP = [](int wave, int time, int row, float col) {
            RoofP(wave, time, {8, 7, 6, 5, 4, 3, 2, 1}, row, col);
        };
    } else {
        AutoP = [](int wave, int time, int row, float col) {
            P(wave, time, row, col);
        };
    }
    if (scene == "PE" || scene == "FE") {
        // 六行场地收尾
        if (dist[1] == 1) {
            choice = 1;
            if (dist[2] || dist[3]) { AutoP(wave, time, 3, col); }
            if (dist[4] || dist[5] || dist[6]) { AutoP(wave, time, 5, col); }
        } else if (dist[6] == 1) {
            choice = 6;
            if (dist[4] || dist[5]) { AutoP(wave, time, 4, col); }
            if (dist[1] || dist[2] || dist[3]) { AutoP(wave, time, 2, col); }
        } else if (dist[1] == 0 && dist[2] == 1) {
            choice = 2;
            bool middle_done = false;
            if (dist[3]) { AutoP(wave, time, 4, col); middle_done = true; }
            if (dist[6]) { AutoP(wave, time, 5, col); middle_done = true; }
            if (!middle_done && (dist[4] || dist[5])) { AutoP(wave, time, 4, col); }
        } else if (dist[6] == 0 && dist[5] == 1) {
            choice = 5;
            bool middle_done = false;
            if (dist[1]) { AutoP(wave, time, 2, col); middle_done = true; }
            if (dist[4]) { AutoP(wave, time, 3, col); middle_done = true; }
            if (!middle_done && (dist[2] || dist[3])) { AutoP(wave, time, 2, col); }
        } else if (dist[1]) {
            choice = 1;
            if (dist[2] || dist[3]) { AutoP(wave, time, 3, col); }
            if (dist[4] || dist[5] || dist[6]) { AutoP(wave, time, 5, col); }
        } else if (dist[6]) {
            choice = 6;
            if (dist[4] || dist[5]) { AutoP(wave, time, 4, col); }
            if (dist[1] || dist[2] || dist[3]) { AutoP(wave, time, 2, col); }
        } else if (dist[2]) {
            choice = 2;
            if (dist[3] || dist[4] || dist[5]) { AutoP(wave, time, 4, col); }
        } else if (dist[5]) {
            choice = 5;
            if (dist[3] || dist[4]) { AutoP(wave, time, 3, col); }
        }
    } else {
        // 五行场地收尾
        if (dist[1] == 1) {
            choice = 1;
            bool middled = false;
            if (dist[2]) { AutoP(wave, time, 3, col); middled = true; }
            if (dist[5]) { AutoP(wave, time, 4, col); middled = true; }
            if (!middled && (dist[3] || dist[4])) { AutoP(wave, time, 3, col); }
        } else if (dist[3] == 1) {
            choice = 3;
            if (dist[1] || dist[2]) { AutoP(wave, time, 1, col); }
            if (dist[4] || dist[5]) { AutoP(wave, time, 5, col); }
        } else if (dist[5] == 1) {
            choice = 5;
            bool middled = false;
            if (dist[1]) { AutoP(wave, time, 2, col); middled = true; }
            if (dist[4]) { AutoP(wave, time, 3, col); middled = true; }
            if (!middled && (dist[2] || dist[3])) { AutoP(wave, time, 2, col); }
        } else if (dist[1] == 0 && dist[2] == 1) {
            choice = 2;
            if (dist[3] || dist[4] || dist[5]) { AutoP(wave, time, 4, col); }
        } else if (dist[5] == 0 && dist[4] == 1) {
            choice = 4;
            if (dist[1] || dist[2] || dist[3]) { AutoP(wave, time, 2, col); }
        } else if (dist[1]) {
            choice = 1;
            bool middled = false;
            if (dist[2]) { AutoP(wave, time, 3, col); middled = true; }
            if (dist[5]) { AutoP(wave, time, 4, col); middled = true; }
            if (!middled && (dist[3] || dist[4])) { AutoP(wave, time, 3, col); }
        } else if (dist[3]) {
            choice = 3;
            if (dist[1] || dist[2]) { AutoP(wave, time, 1, col); }
            if (dist[4] || dist[5]) { AutoP(wave, time, 5, col); }
        } else if (dist[5]) {
            choice = 5;
            bool middled = false;
            if (dist[1]) { AutoP(wave, time, 2, col); middled = true; }
            if (dist[4]) { AutoP(wave, time, 3, col); middled = true; }
            if (!middled && (dist[2] || dist[3])) { AutoP(wave, time, 2, col); }
        } else if (dist[2]) {
            choice = 2;
            if (dist[3] || dist[4] || dist[5]) { AutoP(wave, time, 4, col); }
        } else if (dist[4]) {
            choice = 4;
        }
    }
    return choice;
}

// 对除了某列以外的所有红眼开炮。常用于拖收尾。
// 若场上没有红眼，且当前是w20，则改为对除了某列以外的所有僵尸开炮。
// 本函数已进行 `ForEnd()` 判定。
// 若设置 `stop_giga_plants`，则会使用其中的植物阻挡巨人到4300cs或5500cs(w20)。
void PPExceptOne(int wave, int time, float col = 9, std::vector<APlantType> stop_giga_plants = {}, int stop_giga_to_time = -1000) {
    std::string scene = GetCurrentScene();
    int VCFT = GetCFT();
    ForEnd(wave, time - VCFT, [=](){
        int choice = SchedulePPExceptOne(wave, time, col);
        if (!stop_giga_plants.empty()) StopGiga(wave, time, stop_giga_plants, stop_giga_to_time, choice);
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

#pragma region 仿轨道语言：屋顶炮相关

// 在屋顶场景使用炮尾在1列的炮发射一炮。
void P1(int wave, int time, int row, float col) {
    std::string scene = GetCurrentScene();
    if (scene != "RE" && scene != "ME") {
        waLogger.Error("Px(), Bx(), Dx() 和 dx() 只能在屋顶使用");
        return;
    }
    RoofP(wave, time, 1, row, col);
}

// 在屋顶场景使用炮尾在2列的炮发射一炮。
void P2(int wave, int time, int row, float col) {
    std::string scene = GetCurrentScene();
    if (scene != "RE" && scene != "ME") {
        waLogger.Error("Px(), Bx(), Dx() 和 dx() 只能在屋顶使用");
        return;
    }
    RoofP(wave, time, 2, row, col);
}

// 在屋顶场景使用炮尾在3列的炮发射一炮。
void P3(int wave, int time, int row, float col) {
    std::string scene = GetCurrentScene();
    if (scene != "RE" && scene != "ME") {
        waLogger.Error("Px(), Bx(), Dx() 和 dx() 只能在屋顶使用");
        return;
    }
    RoofP(wave, time, 3, row, col);
}

// 在屋顶场景使用炮尾在4列的炮发射一炮。
void P4(int wave, int time, int row, float col) {
    std::string scene = GetCurrentScene();
    if (scene != "RE" && scene != "ME") {
        waLogger.Error("Px(), Bx(), Dx() 和 dx() 只能在屋顶使用");
        return;
    }
    RoofP(wave, time, 4, row, col);
}

// 在屋顶场景使用炮尾在5列的炮发射一炮。
void P5(int wave, int time, int row, float col) {
    std::string scene = GetCurrentScene();
    if (scene != "RE" && scene != "ME") {
        waLogger.Error("Px(), Bx(), Dx() 和 dx() 只能在屋顶使用");
        return;
    }
    RoofP(wave, time, 5, row, col);
}

// 在屋顶场景使用炮尾在6列的炮发射一炮。
void P6(int wave, int time, int row, float col) {
    std::string scene = GetCurrentScene();
    if (scene != "RE" && scene != "ME") {
        waLogger.Error("Px(), Bx(), Dx() 和 dx() 只能在屋顶使用");
        return;
    }
    RoofP(wave, time, 6, row, col);
}

// 在屋顶场景使用炮尾在7列的炮发射一炮。
void P7(int wave, int time, int row, float col) {
    std::string scene = GetCurrentScene();
    if (scene != "RE" && scene != "ME") {
        waLogger.Error("Px(), Bx(), Dx() 和 dx() 只能在屋顶使用");
        return;
    }
    RoofP(wave, time, 7, row, col);
}

// 在屋顶场景使用炮尾在8列的炮发射一炮。
void P8(int wave, int time, int row, float col) {
    std::string scene = GetCurrentScene();
    if (scene != "RE" && scene != "ME") {
        waLogger.Error("Px(), Bx(), Dx() 和 dx() 只能在屋顶使用");
        return;
    }
    RoofP(wave, time, 8, row, col);
}

// 在屋顶场景使用炮尾在指定列的炮发射一炮。与Px()系列函数完全相同，可用作更好的语义解释。
void B1(int wave, int time, int row, int col) { P1(wave, time, row, col); }
void B2(int wave, int time, int row, int col) { P2(wave, time, row, col); }
void B3(int wave, int time, int row, int col) { P3(wave, time, row, col); }
void B4(int wave, int time, int row, int col) { P4(wave, time, row, col); }
void B5(int wave, int time, int row, int col) { P5(wave, time, row, col); }
void B6(int wave, int time, int row, int col) { P6(wave, time, row, col); }
void B7(int wave, int time, int row, int col) { P7(wave, time, row, col); }
void B8(int wave, int time, int row, int col) { P8(wave, time, row, col); }

// 在屋顶场景使用炮尾在指定列的炮发射一炮。与Px()系列函数完全相同，可用作更好的语义解释。
void D1(int wave, int time, int row, int col) { P1(wave, time, row, col); }
void D2(int wave, int time, int row, int col) { P2(wave, time, row, col); }
void D3(int wave, int time, int row, int col) { P3(wave, time, row, col); }
void D4(int wave, int time, int row, int col) { P4(wave, time, row, col); }
void D5(int wave, int time, int row, int col) { P5(wave, time, row, col); }
void D6(int wave, int time, int row, int col) { P6(wave, time, row, col); }
void D7(int wave, int time, int row, int col) { P7(wave, time, row, col); }
void D8(int wave, int time, int row, int col) { P8(wave, time, row, col); }

// 在屋顶场景使用炮尾在指定列的炮发射一炮。与Px()系列函数完全相同，可用作更好的语义解释。
void d1(int wave, int time, int row, int col) { P1(wave, time, row, col); }
void d2(int wave, int time, int row, int col) { P2(wave, time, row, col); }
void d3(int wave, int time, int row, int col) { P3(wave, time, row, col); }
void d4(int wave, int time, int row, int col) { P4(wave, time, row, col); }
void d5(int wave, int time, int row, int col) { P5(wave, time, row, col); }
void d6(int wave, int time, int row, int col) { P6(wave, time, row, col); }
void d7(int wave, int time, int row, int col) { P7(wave, time, row, col); }
void d8(int wave, int time, int row, int col) { P8(wave, time, row, col); }

#pragma region 仿轨道语言：屋顶炮相关

#endif // WALIB_COB_H