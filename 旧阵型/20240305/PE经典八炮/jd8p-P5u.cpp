#include "../whatss7-avz2-lib/walib.h"

#define NATURAL_MODE 0

APlantFixer stolenSun;

void AScript() {
    #if NATURAL_MODE
    if (!AGetZombieTypeList()[AWW_8]) {
        WASelectCards({
            APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, ASUNFLOWER, APUMPKIN,
             ADOOM_SHROOM, AM_DOOM_SHROOM, ALILY_PAD, ACOFFEE_BEAN, ABLOVER
        }, true);
        if (!AGetZombieTypeList()[AKG_17]) {
            stolenSun.Start(ASUNFLOWER, {{2, 1}, {5, 1}, {6, 1}, {1, 7}, {2, 7}, {5, 7}, {6, 7}}, 1);
        } else {
            stolenSun.Start(ASUNFLOWER, {{1, 7}, {2, 7}, {5, 7}, {6, 7}}, 1);
        }
    } else {
        WASelectCards({
            APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, APUMPKIN,
             ADOOM_SHROOM, AM_DOOM_SHROOM, ALILY_PAD, ACOFFEE_BEAN, ABLOVER
        }, true);
    }
    WACheck();
    #else
    WAInit({
        APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, APUMPKIN, 
        ADOOM_SHROOM, AM_DOOM_SHROOM, ALILY_PAD, ACOFFEE_BEAN, ABLOVER
    });
    #endif
    WAAutoManageCob();
    WAStartBlover();
    // 南瓜需要保护模仿核，所以到w20后再开始修补
    WAFixNuts(20, 0);
    waForEndIgnore = { AXG_24, AKG_17, APJ_0, ALZ_2, AQQ_16 };
    
    // P5-N: ccccPP|ccccPP|ccccPP|ccccPP|ccccN (7.5, 7.5, 7.5, 7.5, 7.5)

    // w1-w9: PP|PP|PP|PP|N|PP|PP|PP|PP
    // w10-w19: PPN'|PP|PP|PP|N|PP|PP|PP|PP|N'
    // w20: PP

    auto cccc = [](){
        // cccc
        const APlantType plants[] = {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT};
        int ptr = 0;
        for (int i = 1; i <= 6; i++) {
            if (WAExistZombie(AWW_8, {i})) {
                ACard(plants[ptr], i, 9);
                ptr += 1;
            }
        }
        // remove c
        AConnect(ANowDelayTime(100), [](){
            ARemovePlant(1, 9);
            ARemovePlant(2, 9);
            ARemovePlant(5, 9);
            ARemovePlant(6, 9);
        });
    };

    for (int w: WaveList(1, 20)) {
        if (w == 5 || w == 14 || w == 19) continue;
        AConnect(ATime(w, 140), cccc);
        PP(w, 751 - 200, 8.5);

        if (w == 9 || w == 20) {
            ForEnd(w, 1500 - 200, [](){ aCobManager.RecoverFire({{2, 8.25}, {5, 8.25}}); });
            ForEnd(w, 2400 - 200, [](){ aCobManager.RecoverFire({{2, 8.5}, {5, 8.5}}); });
        }
        if (w == 10 && AGetZombieTypeList()[AHY_32]) {
            N(w, 751 - 200, {{3, 8}, {3, 9}, {4, 8}, {4, 9}}, 1);
        }
    }

    // w5 / w14: N
    for (int w: {5, 14, 19}) {
        AConnect(ATime(w, 140), cccc);
        N(w, 751 - 200, {{3, 8}, {3, 9}, {4, 8}, {4, 9}}, 1, 751);

        if (w == 19) {
            ForEnd(w, 1500 - 200, [](){ aCobManager.RecoverFire({{2, 8.25}, {5, 8.25}}); });
            ForEnd(w, 2400 - 200, [](){ aCobManager.RecoverFire({{2, 8}, {5, 8}}); });
        }
    }
}