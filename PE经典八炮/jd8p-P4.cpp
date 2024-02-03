#include "../whatss7-avz2-lib/walib.h"

ATickRunner delayCobRunner;
int nukeWave = 0, pureNukeWave = 0, icedWave = 0;

void NormalFire() {
    bool hasDancer = false;
    for (auto &&zombie: aAliveZombieFilter) {
        if (zombie.Type() == AWW_8) {
            hasDancer = true;
            break;
        }
    }
    if (hasDancer) {
        aCobManager.Fire({{2, 7.7}, {5, 7.7}});
    } else {
        aCobManager.Fire({{2, 8.25}, {5, 8.25}});
    }
}

void AScript(){
    WAInit({ALILY_PAD, ABLOVER, ADOOM_SHROOM, AICE_SHROOM, ACOFFEE_BEAN, APUMPKIN});
    WAAutoManageCob();
    WAStartBlover();
    aPlantFixer.Start(APUMPKIN);
    aPlantFixer.SetHp(4000 / 3 * 2);
    
    // P4: PP|PP|PP|PP (9, 9, 9, 9)
    // 大体分为几种情况：略大于9s(不管)，大于12s（下一波同时点核或打12s冰波），发炮后意外刷新（下一波核代奏或18s冰波），18s（再打一炮）。

    for (int w: WaveList(1, 20)) {
        // PP
        AConnect(ATime(w, (w == 1 || w == 10 || w == 20) ? -599 : -200), [w](){
            delayCobRunner.Stop();
            if (w == 1 || w == 10 || w == 20) nukeWave = pureNukeWave = icedWave = 0;
        });
        AConnect(ATime(w, -199), [w](){
            if (AGetSeedPtr(ADOOM_SHROOM) && AGetSeedPtr(ADOOM_SHROOM)->IsUsable()){
                if (w == nukeWave) {
                    AConnect(ATime(w, 900 - 200 - CBT - ADT), [](){
                        ACard({ALILY_PAD, ADOOM_SHROOM, ACOFFEE_BEAN}, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
                    });
                }
                if (w != pureNukeWave) {
                    AConnect(ATime(w, 900 - 200 - CFT), NormalFire);
                }
            } else {
                if (w == nukeWave) {
                    icedWave = w;
                    ACard({ALILY_PAD, AICE_SHROOM, ACOFFEE_BEAN}, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
                    AConnect(ANowDelayTime(CBT + ADT), [](){
                        ARemovePlant(3, 8, ALILY_PAD);
                        ARemovePlant(3, 9, ALILY_PAD);
                        ARemovePlant(4, 8, ALILY_PAD);
                        ARemovePlant(4, 9, ALILY_PAD);
                    });
                    if (w != pureNukeWave) {
                        AConnect(ATime(w, 1800 - 200 - CFT), [](){
                            aCobManager.Fire({{2, 8}, {5, 8}});
                        });
                    } else {
                        AConnect(ATime(w, 1200 - 200 - CFT), [](){
                            aCobManager.Fire({{2, 9}, {5, 9}});
                        });
                    }
                } else {
                    AConnect(ATime(w, 900 - 200 - CFT), NormalFire);
                }
            }
        });
        AConnect(ATime(w, 1), [w](){
            delayCobRunner.Start([w](){
                bool isAlive = false;
                for (auto &&zombie: aAliveZombieFilter) {
                    if (zombie.Type() == AKG_17 || zombie.Type() == AXG_24) continue;
                    isAlive = true;
                    break;
                }
                if (!isAlive) {
                    delayCobRunner.Stop();
                    return;
                }
                if (ANowTime().time == 0) {
                    nukeWave = pureNukeWave = w;
                }
                if (ANowTime().time == 699) {
                    nukeWave = pureNukeWave = 0;
                }
                if (w != icedWave && ANowTime().time == 1000) {
                    nukeWave = w + 1;
                }
                if (w != icedWave && ANowTime().time == 1600 - CFT) {
                    NormalFire();
                    pureNukeWave = w + 1;
                }
                if (ANowTime().time == 1599) {
                    nukeWave = 0;
                    pureNukeWave = 0;
                }
                // 两炮都没刷新大概是在收尾，再来一炮
                if (ANowTime().time == 2500 - CFT) {
                    NormalFire();
                }
                // 收尾没炸完？再来一炮
                if (ANowTime().time == 3400 - CFT) {
                    NormalFire();
                }
            });
        });
    }
}