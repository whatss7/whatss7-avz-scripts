#include "../whatss7-avz2-lib/walib.h"

ATickRunner slowGigaRunner;
ATickRunner R1SlowStopRunner;

void SlowGiga() {
    if (AGetSeedPtr(APUFF_SHROOM)  && AGetSeedPtr(APUFF_SHROOM)->IsUsable()) {
        std::vector<APosition> candidates;
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.Type() == AHY_32 && zombie.Abscissa() + zombie.AttackAbscissa() < 600) {
                float attackCol = (zombie.Abscissa() + zombie.AttackAbscissa() + 40) / 80.0f;
                candidates.push_back({zombie.Row() + 1, attackCol});
            }
        }
        sort(candidates.begin(), candidates.end(), [](APosition a, APosition b){
            return a.col < b.col;
        });
        if (!candidates.empty()) ACard(APUFF_SHROOM, candidates);
    }
}

void R1SlowStop() {
    if (WAExistPlant(ATALL_NUT, 1, 6)) {
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.Row() != 0 || zombie.Abscissa() + zombie.AttackAbscissa() > 480) continue;
            if (zombie.Type() == AKG_17 || zombie.Type() == AQQ_16 || zombie.Type() == ACG_3 || zombie.Type() == ATT_18) continue;
            return;
        }
        ARemovePlant(1, 6, ATALL_NUT);
    } else if (AGetSeedPtr(ATALL_NUT)  && AGetSeedPtr(ATALL_NUT)->IsUsable()) {
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.Row() != 0 || zombie.Abscissa() + zombie.AttackAbscissa() > 480) continue;
            if (zombie.Type() == AHY_32 || zombie.Type() == ABY_23) return;
            if (zombie.Type() == AKG_17 || zombie.Type() == AQQ_16 || zombie.Type() == ACG_3 || zombie.Type() == ATT_18) continue;
            ACard(ATALL_NUT, 1, 6);
            return;
        }
    }
}

void AScript() {
    WAInit({ADOOM_SHROOM, AICE_SHROOM, AGRAVE_BUSTER, APUFF_SHROOM, ACHERRY_BOMB, AKERNEL_PULT, ACOB_CANNON, ATALL_NUT}, "None", true);
    waCheckPlants = {};
    WACheck();
    WAAutoManageCob();
    WAStartBlover(1, 9);
    R1SlowStopRunner.Start(R1SlowStop);

    // P6: PP|PP|PP|PP|PP|N
    // w1-w9: PP|PP|PP|PP|PP|N|PP|PP|PP
    // w10-w19: PP|PP|PP|PP|PP|N|PP|PP|PP|PP
    // w20: PP
    for (int w: WaveList(1, 20)) {
        if (w == 6 || w == 15) continue;
        PP(w);
        if (w == 10) DRA(w, 400);
        if (w == 9 || w == 19 || w == 20) {
            PPForEnd(w, 1200 - 200, 8.75);
            PPForEnd(w, 2400 - 200, 8.5);
            PPForEnd(w, 3000 - 200, 8.25);
            AConnect(ATime(w, 1200 - 200), [](){ slowGigaRunner.Start(SlowGiga); });
            AConnect(ATime(w % 20 + 1, -200), [](){
                slowGigaRunner.Stop();
                for (int i = 1; i <= 5; i++) {
                    for (int j = 7; j <= 9; j++) {
                        ARemovePlant(i, j, APUFF_SHROOM);
                    }
                }
            });
        }
        if (w == 10 || w == 20) ManualI(w, 575, {{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}});
    }
    for (int w: {6, 15}) {
        N(w, PCAP, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    }
    // 解决墓碑
    AConnect(ATime(20, 200), [](){
        bool success = false;
        for (int i = 1; i <= 5; i++) {
            for (int j = 7; j <= 9; j++) {
                if (ACard(AGRAVE_BUSTER, i, j)) {
                    A(20, 350, i, (j == 9 ? 8: j + 1));
                    success = true;
                    break;
                }
            }
            if (success) break;
        }
    });
}