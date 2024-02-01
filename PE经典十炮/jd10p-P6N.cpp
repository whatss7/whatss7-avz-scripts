#include "../whatss7-avz2-lib/walib.h"

ATickRunner bloverTickRunner;
WAEndCobber w20cobber;
APlantFixer sneakSunFixer;

void AScript(){
    WAInit({ALILY_PAD, ADOOM_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, AUMBRELLA_LEAF, ATALL_NUT, ABLOVER, AICE_SHROOM, ASUNFLOWER}, "Cycle");
    WAAutoManageCob();
    aPlantFixer.Start(ATALL_NUT, {}, 8000 / 3 * 2);

    // 为了求稳并且保高坚果，阳光消耗较大，偷几朵花
    sneakSunFixer.Start(ASUNFLOWER, {{2, 1}, {5, 1}, {6, 1}}, 0);

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
    
    // P6: PP|PP|PP|PP|PP|N (12,6,6,6,6)
    // w1-w9: PP|PP|PP|PP|PP|N|PP|PP|PP
    // w10-w19: PP|PP|PP|PP|N|PP|PP|PP|PP|PP
    // w20: PP

    // 非旗帜波除w6/w14: PP
    for (int w: WaveList(1, 9) + WaveList(11, 19)) {
        if (w == 6 || w == 14) continue;
        AConnect(ATime(w, PCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        if (w == 9 || w == 19) AConnect(ATime(w, PCP + CFT + 1), waEndCobber);
    }

    for (int w: { 6, 14 }) {
        AConnect(ATime(w, PCP + CFT - CBT - ADT), [](){
            ACard({ALILY_PAD, ADOOM_SHROOM, ACOFFEE_BEAN}, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
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
            AConnect(ATime(w, DPCP + CFT - ADT), [](){
                ACard(ACHERRY_BOMB, 2, 9);
            });
        }
        // w20 冰消珊瑚 收尾
        if (w == 20) {
            AConnect(ATime(w, -50 - CBT - ADT), [](){
                ACard({AICE_SHROOM, ACOFFEE_BEAN}, {{1, 7}});
            });
            AConnect(ATime(w, DPCP + CFT + 1), waEndCobber);
        }
    }
}