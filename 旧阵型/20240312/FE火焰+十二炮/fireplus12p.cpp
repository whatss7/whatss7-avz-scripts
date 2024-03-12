#include "../whatss7-avz2-lib/walib.h"

bool extreme = false;
ATickRunner extremeRunner;

void AScript() {
    extremeRunner.Start([](){
        for (auto &&plant: aAlivePlantFilter) {
            if (plant.Type() == ABLOVER) {
                extreme = true;
                extremeRunner.Stop();
            }
        }
    });
    WAInit({AICE_SHROOM, ACHERRY_BOMB, ATORCHWOOD, APUMPKIN, ABLOVER});
    WACheck(1);
    WAAutoManageCob();
    WAFixNuts();
    aPlantFixer.Start(ATORCHWOOD, {}, 10);
    // 水路僵尸必须考虑
    waForEndIgnore = { AKG_17, AXG_24, APJ_0, ALZ_2, ADB_5 };
    waForEndIgnoreInWater = { AHY_32 };
    for (int w: WaveList(1, 20)) {
        AConnect(ATime(w, 1), [w](){
            if (extreme) {
                // 将红眼以一定概率移至1路，用于以更大的概率砸火树进行演示
                for (auto &&zombie: aAliveZombieFilter) {
                    if (zombie.Type() == AHY_32 && zombie.AtWave() + 1 == w) {
                        if (rand() % 4 < 3) {
                            zombie.Row() = 0;
                            zombie.Ordinate() = 50;
                        }
                    }
                }
            }
        });
        if (w == 10) {
            P(w, PCP, 2, 9);
            A(w, PCP, 5, 9);
        } else {
            PP(w);
        }
        if (w == 20) {
            P(w, 225, 4, 7.5875);
        }
        if (w == 10 || w == 20) {
            ManualI(w, 400, 1, 8);
            P(w, 400, 3, 9);
        }
        if (w == 9 || w == 19 || w == 20) {
            PPForEnd(w, PCP + 601);
            PPForEnd(w, PCP + 601 * 2);
            AConnect(ATime(w, PCP + 601 * 3 - CFT), [w](){
                if (WAExistZombie({APJ_0, ALZ_2, ATT_18}, {3, 4})) {
                    PPForEnd(w, PCP + 601 * 3);
                }
            });
        }
    }
}