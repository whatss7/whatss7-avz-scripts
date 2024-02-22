#include "../whatss7-avz2-lib/walib.h"

APlantFixer stolenSun;

void AScript(){
    WAInit({ALILY_PAD, ADOOM_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, AUMBRELLA_LEAF, ATALL_NUT, ABLOVER, AICE_SHROOM, ASUNFLOWER});
    WAAutoManageCob();
    WAFixNuts();
    WAStartBlover(2, 7);
    waForEndIgnore = { AKG_17, AXG_24, AQQ_16, APJ_0, ALZ_2, ATM_6 };
    waForEndIgnoreInWater = { AHY_32 };

    // 为了求稳并且保高坚果，阳光消耗较大，偷几朵花
    stolenSun.Start(ASUNFLOWER, {{1, 1}, {2, 1}, {5, 1}, {6, 1}}, 1);
    
    // P6: PP|PP|PP|PP|PP|N (12,6,6,6,6)
    // w1-w9: PP|PP|PP|PP|PP|N|PP|PP|PP|PP
    // w10-w19: PP|PP|PP|PP|PP|N|PP|PP|PP|PP
    // w20: PP

    // 非旗帜波除w6/w14: PP
    for (int w: WaveList(1, 20)) {
        if (w == 6 || w == 15) continue;
        PP(w);
        if (w == 9 || w == 19 || w == 20) {
            PPForEnd(w, 1000);
            PPForEnd(w, 2200);
        }
        if (w == 10) SmartA();
        if (w == 20) ManualI(w, -50, 1, 7);
        if (w == 10 || w == 20) {
            if (AGetZombieTypeList()[ABJ_20]) {
                TempC(w, 300, AUMBRELLA_LEAF, {{3, 8}, {4, 8}}, 100);
            }
        }
    }
    for (int w: { 6, 15 }) {
        N(w, PCP, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
    }
}