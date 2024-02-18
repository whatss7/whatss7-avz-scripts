#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, APUMPKIN, ADOOM_SHROOM, AM_DOOM_SHROOM, ALILY_PAD, ACOFFEE_BEAN, ABLOVER});
    WAAutoManageCob();
    waEndCobber.Bucket();
    WAStartBlover();
    
    // P5u-N: ccccPP|ccccPP|ccccPP|ccccPP|N (751, 751, 751, 751, 600)

    // w1-w9: PP|PP|PP|PP|N|PP|PP|PP|PP
    // w10-w19: PP|PP|PP|PP|N|PP|PP|PP|PP|N'
    // w20: PP

    for (int w: WaveList(1, 20)) {
        if (w == 5 || w == 14 || w == 19) continue;

        // cccc
        AConnect(ATime(w, 140), [](){
            const APlantType plants[] = {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT};
            int ptr = 0;
            bool hasDance[6];
            memset(hasDance, 0, sizeof(hasDance));
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Type() == AWW_8) hasDance[zombie.Row()] = true;
            }
            for (int i = 0; i < 6; i++) {
                if (hasDance[i]) {
                    ACard(plants[ptr], i + 1, 9);
                    ptr += 1;
                }
            }
        });
        // remove c
        AConnect(ATime(w, 240), [](){
            ARemovePlant(1, 9);
            ARemovePlant(2, 9);
            ARemovePlant(5, 9);
            ARemovePlant(6, 9);
        });

        // PP
        AConnect(ATime(w, 751 - 200 - CFT), [](){
            aCobManager.Fire({{2, 8.5}, {5, 8.5}});
        });

        if (w == 9 || w == 20) {
            AConnect(ATime(w, 752), waEndCobber);
        }
    }

    // w5 / w14: N
    for (int w: {5, 14}) {
        AConnect(ATime(w, PCP + CFT - CBT - ADT), [](){
            ACard({ALILY_PAD, ADOOM_SHROOM, ACOFFEE_BEAN}, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
        });
    }

    // w19: N'
    for (int w: {19}) {
        AConnect(ATime(w - 1, PCP + CFT - CBT - ADT - MDT + 751), [](){
            ACard({ALILY_PAD, AM_DOOM_SHROOM}, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
            AConnect(ANowDelayTime(MDT),[](){
                ACard(ACOFFEE_BEAN, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
            });
        });
        AConnect(ATime(w, PCP + CFT + 1), waEndCobber);
    }
}