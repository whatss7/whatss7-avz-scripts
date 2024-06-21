#include "../walib.h"

void SlowGiga() {
    std::vector<std::pair<int, int>> fast;
    for (int i = 0; i < 5; i++) {
        fast.push_back(std::make_pair(i + 1, 1000.0f));
    }
    for (auto &&zombie : aAliveZombieFilter) {
        if (zombie.Type() != AHY_32) continue;
        fast[zombie.Row()].second = std::min(fast[zombie.Row()].second, int(zombie.Abscissa()));
    }
    std::sort(fast.begin(), fast.end(), [](std::pair<int, int> a, std::pair<int, int> b){
        return a.second < b.second;
    });
    if (fast[0].second < 999) {
        TempCNow(APUFF_SHROOM, {{ 
            fast[0].first, float(std::min(9, (fast[0].second + 44) / 80))
        }, {
            fast[0].first, float(std::min(9, (fast[0].second + 65) / 80))
        }}, 400);
    } 
    if (fast[1].second < 999) {
        TempCNow(AM_PUFF_SHROOM, {{
            fast[1].first, float(std::min(9, (fast[1].second + 44) / 80))
        }, { 
            fast[1].first, float(std::min(9, (fast[1].second + 65) / 80))
        }}, 400);
    }
}

ATickRunner enterHomeTickRunner;

void AScript() {
    Init({ADOOM_SHROOM, AICE_SHROOM, AGRAVE_BUSTER, ACHERRY_BOMB, APUFF_SHROOM, AM_PUFF_SHROOM, ABLOVER});

    // 测试跳跳是否进家
    #if 0
    StartReloadMode(10);
    SelectCardsAndFill({ ADOOM_SHROOM, AICE_SHROOM, AGRAVE_BUSTER, ACHERRY_BOMB, APUFF_SHROOM, AM_PUFF_SHROOM, ABLOVER }, true);
    AutoManageCob();
    ASetZombies(ACreateRandomTypeList({ATT_18}), ASetZombieMode::AVERAGE);
    AConnect(ATime(1, -599), [](){
        ASkipTick([](){
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Abscissa() < -80) {
                    waLogger.Info("进家可能");
                    ASetGameSpeed(1);
                    return false;
                }
            }
            return true;
        });
    });
    #endif

    AutoBlover(1, 8);
    waForEndIgnore = { AXG_24, ATT_18 };

    // P6: PP|PP|PP|PP|PP|N
    // w1-w9: PP|PP|PP|PP|N|PP|PP|PP|PP
    // w10-w19: PP|PP|PP|PP|PP|N|PP|PP|PP|PP
    // w20: PP
    for (int w: WaveList(1, 20)) {
        if (w == 5 || w == 15) continue;
        PP(w);
        if (w == 10) SmartA();
        if (w == 9 || w == 19 || w == 20) {
            PPForEnd(w, 601 + PCP, 8.85);
            ForEnd(w, 601 + PCP, SlowGiga);
            ForEnd(w, 601 + PCP + 751, SlowGiga);
            ForEnd(w, 601 + PCP + 751 * 2, SlowGiga);
            PPForEnd(w, 601 * 3 + PCP, 8.85);
            PPForEnd(w, 601 * 4 + PCP, 8.85);
        }
        if (w == 10 && AGetZombieTypeList()[ABJ_20]) ManualI(w, 401, {{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}});
        if (w == 20) ManualI(w, 401, {{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}});
    }
    for (int w: {5, 15}) {
        N(w, PCP, {{3, 9}, {3, 8}, {2, 9}, {2, 8}});
    }
    // 解决本轮墓碑
    AConnect(ATime(20, 200), [](){
        for (auto &&item: aAlivePlaceItemFilter) {
            if (item.Type() == 1) {
                int row = item.Row() + 1, col = item.Col() + 1;
                std::vector<APosition> possibles;
                possibles.push_back({row, float(col - 1)});
                if (col != 9) possibles.push_back({row, float(col + 1)});
                if (row != 1) possibles.push_back({row - 1, float(col)});
                if (row != 5) possibles.push_back({row + 1, float(col)});
                C(20, 350 - ADT, ACHERRY_BOMB, possibles);
                C(20, 401, AGRAVE_BUSTER, row, col);
                break;
            }
        }
    });
}