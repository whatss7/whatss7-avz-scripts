#include <avz.h>
#include "whatss7-avz2-lib/walib.h"

ATickRunner bloverTickRunner;
APlantFixer sneakSunFixer;

void AScript(){
    // WACheck();
    WAInit({AICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, ALILY_PAD, AUMBRELLA_LEAF, ABLOVER, ASUNFLOWER, ATALL_NUT}, "Cycle");
    WAAutoManageCob();
    waEndCobber.setColumn(8.5);
    waEndCobber.Bucket();
    sneakSunFixer.Start(ASUNFLOWER, {{5, 1}, {6, 1}}, 0);

    // 有概率收尾漏气球，加上三叶草保险
    bloverTickRunner.Start([](){
        bool needBlow = false;
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.Type() == AQQ_16 && zombie.Abscissa() < 50) {
                needBlow = true;
            }
        }
        if (needBlow) {
            auto bloverSeed = AGetSeedPtr(ABLOVER);
            if (bloverSeed->IsUsable()) {
                ACard(ABLOVER, 1, 1);
            }
        }
    });

    // 2-1 存蓝冰，w5/w11/w19种，w6/w15/w20用，避开矿工并合理安排冷却
    AConnect(ATime(5, 0), [](){ ACard(AICE_SHROOM, 2, 1); });
    AConnect(ATime(11, 0), [](){ ACard(AICE_SHROOM, 2, 1); });
    AConnect(ATime(19, 0), [](){ ACard(AICE_SHROOM, 2, 1); });

    aPlantFixer.Start(ATALL_NUT, {}, 8000 / 3 * 2);
    
    // S6: I-PP|PP|PP|PP|PP (12,6,6,6,6)
    // w1-w9: PP|PP|PP|PP|PP|I-PP|PP|PP|PP
    // w10-w19: PP|PP|PP|PP|PP|I-PP|PP|PP|PP|PP
    // w20: PP

    // 非旗帜波除w6/w15: PP
    for (int w: WaveList(1, 9) + WaveList(11, 19)) {
        if (w == 6 || w == 15) continue;
        AConnect(ATime(w, PCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        if (w == 9 || w == 19) {
            AConnect(ATime(w, 821 - CFT), waEndCobber);
        }
    }

    // w6/w15: I-PP
    for (int w: { 6, 15 }) {
        AConnect(ATime(w, -199), [](){
            ACard(ACOFFEE_BEAN, 2, 1);
        });
        AConnect(ATime(w, 1200 - 200 - CFT), [](){
            aCobManager.Fire({{2, 8.75}, {5, 8.75}});
        });
    }

    for (int w: { 10, 20 }) {
        AConnect(ATime(w, DPCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        // 临时保护伞防小偷
        AConnect(ATime(w, 300), [w](){
            if (WAExistZombie(ABJ_20)) {
                ACard({ALILY_PAD, AUMBRELLA_LEAF}, {{3, 8}, {4, 8}});
                AConnect(ATime(w, 500), [](){
                    ARemovePlant(3, 8);
                    ARemovePlant(3, 8, ALILY_PAD);
                    ARemovePlant(4, 8);
                    ARemovePlant(4, 8, ALILY_PAD);
                });
            }
        });
        // w10 消延迟
        if (w == 10) {
            AConnect(ATime(w, 400 - ADT), [](){
                ACard(ACHERRY_BOMB, 2, 9);
            });
        }
        // w20 冰消珊瑚 收尾
        if (w == 20) {
            AConnect(ATime(w, -50 - CBT - ADT), [](){ ACard(ACOFFEE_BEAN, 2, 1); });
            AConnect(ATime(w, 821 - CFT), waEndCobber);
        }
    }
}