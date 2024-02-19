#include "../whatss7-avz2-lib/walib.h"

ATickRunner bloverTickRunner;
APlantFixer sneakSunFixer;

void AScript(){
    // WACheck();
    WAInit({AICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, ALILY_PAD, AUMBRELLA_LEAF, ABLOVER, ASUNFLOWER, ATALL_NUT}, "None", true);
    WACheck();
    WAAutoManageCob();
    waForEndIgnore = { AKG_17, AXG_24, AQQ_16, APJ_0, ALZ_2, ADB_5, ATM_6 };
    waForEndIgnoreInWater = { AHY_32 };

    WAStartBlover();
    sneakSunFixer.Start(ASUNFLOWER, {{5, 1}, {6, 1}}, 0);

    // 2-1 存蓝冰，w5/w11/w19种，w6/w15/w20用，避开矿工并合理安排冷却
    AConnect(ATime(5, 0), [](){ ACard(AICE_SHROOM, 2, 1); });
    AConnect(ATime(11, 100), [](){ ACard(AICE_SHROOM, 2, 1); });
    AConnect(ATime(19, 0), [](){ ACard(AICE_SHROOM, 2, 1); });

    aPlantFixer.Start(ATALL_NUT, {}, 8000 / 3 * 2);
    
    // S6: I-PP|PP|PP|PP|PP (12,6,6,6,6)
    // w1-w9: PP|PP|PP|PP|PP|I-PP|PP|PP|PP
    // w10-w19: PP|PP|PP|PP|PP|I-PP|PP|PP|PP|PP
    // w20: PP

    // 非旗帜波除w6/w15: PP
    for (int w: WaveList(1, 20)) {
        if (w == 6 || w == 15) continue;
        PP(w);
        if (w == 9 || w == 19 || w == 20) {
            PPForEnd(w, w == 19 ? 1600 : 1000, 8.75);
            PPForEnd(w, 2200, 8.5);
        }
        if (w == 10) DelayRemovingA(w, 400);
        if (w == 10 || w == 20) {
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
        }
        if (w == 20) C(w, -50 - CBT - ADT, ACOFFEE_BEAN, 2, 1);
    }

    // w6/w15: I-PP
    for (int w: { 6, 15 }) {
        AConnect(ATime(w, -199), [](){
            ACard(ACOFFEE_BEAN, 2, 1);
        });
        PP(w, 1200 - 200, 8.75);
    }
}