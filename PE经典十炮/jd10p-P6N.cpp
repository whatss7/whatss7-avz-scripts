#include "../whatss7-avz2-lib/walib.h"

APlantFixer stolenSun;

void AScript(){
    WAInit({ALILY_PAD, ADOOM_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, AUMBRELLA_LEAF, ATALL_NUT, ABLOVER, AICE_SHROOM, ASUNFLOWER});
    WAAutoManageCob();
    WAFixNuts();
    WAStartBlover();
    waForEndIgnore = { AKG_17, AXG_24, AQQ_16, APJ_0, ALZ_2, ATM_6 };
    waForEndIgnoreInWater = { AHY_32 };

    // 为了求稳并且保高坚果，阳光消耗较大，偷几朵花
    stolenSun.Start(ASUNFLOWER, {{2, 1}, {5, 1}, {6, 1}}, 1);
    
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
        if (w == 10) SmartA(w, 400);
        if (w == 20) ManualI(w, -50, 1, 1);
        if (w == 10 || w == 20) {
            if (AGetZombieTypeList()[ABJ_20]) {
                AConnect(ATime(w, 300), [](){
                    ACard({ALILY_PAD, AUMBRELLA_LEAF}, {{3, 8}, {4, 8}});
                });
                AConnect(ATime(w, 500), [](){
                    ARemovePlant(3, 8);
                    ARemovePlant(3, 8, ALILY_PAD);
                    ARemovePlant(4, 8);
                    ARemovePlant(4, 8, ALILY_PAD);
                });
            }
        }
    }

    for (int w: { 6, 15 }) {
        N(w, PCAP, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
    }
}