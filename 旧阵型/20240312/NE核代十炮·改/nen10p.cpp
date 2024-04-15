#include "../whatss7-avz2-lib/walib.h"

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

void AScript() {
    WAInit({ ADOOM_SHROOM, AICE_SHROOM, AGRAVE_BUSTER, ACHERRY_BOMB, APUFF_SHROOM, AM_PUFF_SHROOM });
    WAAutoManageCob();
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
            PPForEnd(w, 601 + PCP, 9);
            ForEnd(w, 601 + PCP, SlowGiga);
            ForEnd(w, 601 + PCP + 751, SlowGiga);
            ForEnd(w, 601 + PCP + 751 * 2, SlowGiga);
            PPForEnd(w, 601 * 3 + PCP, 9);
            PPForEnd(w, 601 * 4 + PCP, 8.5);
        }
        if (w == 10 && AGetZombieTypeList()[ABJ_20]) ManualI(w, 401, {{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}});
        if (w == 20) ManualI(w, 401, {{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}});
    }
    for (int w: {5, 15}) {
        N(w, PCP, {{3, 9}, {3, 8}, {2, 9}, {2, 8}});
    }
    // 上轮墓碑吞噬者被意外干掉的情况
    // WARemoveGraves(10, -700);
    // 解决本轮墓碑
    AConnect(ATime(20, 200), [](){
        bool success = false;
        for (int i = 1; i <= 5; i++) {
            for (int j = 7; j <= 9; j++) {
                if (ACard(AGRAVE_BUSTER, i, j)) {
                    std::vector<APosition> possibles;
                    possibles.push_back({i, float(j - 1)});
                    if (j != 9) possibles.push_back({i, float(j + 1)});
                    if (i != 1) possibles.push_back({i - 1, float(j)});
                    if (i != 5) possibles.push_back({i + 1, float(j)});
                    C(20, 350 - ADT, ACHERRY_BOMB, possibles);
                    success = true;
                    break;
                }
            }
            if (success) break;
        }
    });
}