#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, APUMPKIN, ADOOM_SHROOM, ALILY_PAD, ABLOVER});
    WAAutoManageCob();
    aIceFiller.Start({{1, 1}, {6, 1}, {2, 7}});
    WAFixNuts();
    WAStartBlover();
    
    // ch4: IPP-PP|IPP-PP (18,18)
    // w1-w9: N|PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP
    // w10-w19: PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP
    // W20: PP
    for (int w: {1}) {
        AConnect(ATime(w, PCP + CFT - CBT - ADT), [](){
            ACard({ALILY_PAD, ADOOM_SHROOM, ACOFFEE_BEAN}, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
        });
    }
    for (int w: {2}) {
        AConnect(ATime(w, PCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
    }
    for (int w: WaveList(3, 9) + WaveList(11, 19)) {
        AConnect(ATime(w, -199), [](){
            aIceFiller.Coffee();
        });
        AConnect(ATime(w, 400 - CFT), [](){
            aCobManager.Fire({{2, 8}, {5, 8}});
        });
        AConnect(ATime(w, 1800 - 200 - CFT), [](){
            aCobManager.Fire({{2, 8.5}, {5, 8.5}});
        });
    }
    for (int w: {10, 20}) {
        AConnect(ATime(w, DPCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
    }
}