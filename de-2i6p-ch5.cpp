#include <avz.h>
#include "whatss7-avz2-lib/walib.h"

void AScript(){
    WAInit("DE", {AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, ADOOM_SHROOM, APUMPKIN});
    WAAutoManageCob();
    aIceFiller.Start({{1, 1}, {5, 1}});
    aPlantFixer.Start(APUMPKIN);
    aPlantFixer.SetHp(4000 / 3 * 2);
    // ch5: I-PP|I-PP|PP (15, 15, 6)

    // w1-w9: N|PP|PP|I-PP|I-PP|PP|I-PP|I-PP|PP
    // w10-w19: PP|I-PP|I-PP|PP|I-PP|I-PP|PP|I-PP|I-PP|PP
    // w20: PP

    // w1: N
    for (int w: {1}) {
        AConnect(ATime(w, PCP + CFT - ADT - CBT), [](){
            ACard({ADOOM_SHROOM, ACOFFEE_BEAN}, 3, 7);
        });
    }

    // w2, w3, w6, w9, w13, w16, w19: PP
    for (int w: {2, 3, 6, 9, 13, 16, 19}) {
        AConnect(ATime(w, PCP), [](){
            aCobManager.Fire({{2, 9}, {4, 9}});
        });
    }

    // w10, w20: delayed PP, w10: PPA
    for (int w: {10, 20}) {
        AConnect(ATime(w, DPCP), [](){
            aCobManager.Fire({{2, 9}, {4, 9}});
        });
        if (w == 10) {
            AConnect(ATime(w, DPCP - ADT), [](){
                ACard(ACHERRY_BOMB, {{2, 9}});
            });
        }
    }

    // w4, w5, w7, w8, w11, w12, w14, w15, w17, w18: I-PP
    for (int w: {4, 5, 7, 8, 11, 12, 14, 15, 17, 18}) {
        AConnect(ATime(w, 100 - ADT - CBT), [](){
            aIceFiller.Coffee();
        });
        AConnect(ATime(w, 1500 - CFT), [](){
            aCobManager.Fire({{2, 8.5}, {4, 8.5}});
        });
    }
}