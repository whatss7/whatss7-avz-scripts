#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({APUMPKIN, ADOOM_SHROOM, AM_DOOM_SHROOM, ALILY_PAD, ACOFFEE_BEAN, ABLOVER, AKERNEL_PULT, ACOB_CANNON, ACHERRY_BOMB, APUFF_SHROOM});
    WAAutoManageCob();
    WAStartBlover();

    // P6-2N: PP|PP|PP|N|PP|N'
    // w1-w9: PP|PP|PP|N|PP|N'|PP|PP|PP
    // w10-w19: PPA|PP|PP|N|PP|N'|PP|PP|PP|P'A
    // w20: PP
    // 核坑位比较极限，需要拖满收尾，但是io较高，快速关不一定能拖
    // 收尾用小喷菇和玉米投手垫，阳光消耗也较大

    for (int w: WaveList(1, 9) + WaveList(11, 18)) {
        if (w == 4 || w == 6 || w == 13 || w == 15) continue;
        // PP
        AConnect(ATime(w, PCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        // 铲种炮
        if (w == 16) {
            AConnect(ATime(w, PCP + 210), [](){
                aCobManager.FixLatest();
            });
        }
    } 
    for (int w: {10, 20}) {
        AConnect(ATime(w, DPCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        if (w == 10) {
            AConnect(ATime(w, 400 - ADT), [](){
                ACard(ACHERRY_BOMB, 2, 9);
            });
        }
    }
    for (int w: {4, 13}) {
        // N
        AConnect(ATime(w, PCP + CFT - CBT - ADT), [](){
            ACard({ALILY_PAD, ADOOM_SHROOM, ACOFFEE_BEAN}, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
        });
    }
    for (int w: {6, 15}) {
        // N'
        AConnect(ATime(w - 1, PCP + CFT - CBT - ADT - MDT + 600), [](){
            ACard({ALILY_PAD, AM_DOOM_SHROOM}, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
            AConnect(ANowDelayTime(MDT), [](){
                ACard(ACOFFEE_BEAN, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
            });
        });
    }
    for (int w: {19}) {
        // P'A
        AConnect(ATime(w, PCP), [](){
            aCobManager.Fire({{5, 9}});
        });
        AConnect(ATime(w, PCP + CFT - ADT), [](){
            ACard(ACHERRY_BOMB, 2, 9);
        });
    }
}