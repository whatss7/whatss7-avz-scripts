#include <avz.h>
#include "whatss7-avz2-lib/walib.h"

void AScript(){
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, ADOOM_SHROOM, ALILY_PAD, APUMPKIN});
    WAAutoManageCob();
    aIceFiller.Start({{2, 7}, {5, 7}});
    aPlantFixer.Start(APUMPKIN);
    aPlantFixer.SetHp(4000 / 3 * 2);
    // ch6: I-PP|PP|I-PP|PP

    // w1-w9: N|PP|PP|I-PP|PP|I-PP|PP|I-PP|PP
    // w10-w19: PPA|I-PP|PP|I-PP|PP|I-PP|PP|I-PP|PP|I-PP
    // w20: I-PP

    // w1: N
    for (int w: {1}) {
        AConnect(ATime(w, PCP + CFT - CBT - ADT), [](){
            ACard({ALILY_PAD, ADOOM_SHROOM, ACOFFEE_BEAN}, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
        });
    }
    // w2, w3, w5, w7, w9, w12, w14, w16, w18: PP
    for (int w: {2, 3, 5, 7, 9, 12, 14, 16, 18}) {
        AConnect(ATime(w, PCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
    }

    // w4, w6, w8, w11, w13, w15, w17, w19: I-PP
    for (int w: {4, 6, 8, 11, 13, 15, 17, 19}) {
        AConnect(ATime(w, -200), [](){
            aIceFiller.Coffee();
        });
        AConnect(ATime(w, 1200 - 200 - CFT), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
    }

    // w10: PPA
    for (int w: {10}) {
        AConnect(ATime(w, W10PCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        AConnect(ATime(w, W10PCP + CFT - ADT), [](){
            ACard(ACHERRY_BOMB, 2, 9);
        });
    }

    // w20: PPSS
    for (int w: {20}) {
        AConnect(ATime(w, -50 - ADT - CBT),[](){
            aIceFiller.Coffee();
        });
        AConnect(ATime(w, W20PCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        AConnect(ATime(w, 400 - CFT), [](){
            aCobManager.Fire({{2, 7}, {5, 7}});
        });
    }
}