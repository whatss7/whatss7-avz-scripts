#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({ADOOM_SHROOM, AM_DOOM_SHROOM, ALILY_PAD, ACOFFEE_BEAN, ABLOVER, AKERNEL_PULT, ACOB_CANNON, ACHERRY_BOMB, APUFF_SHROOM, ASUN_SHROOM});
    WAAutoManageCob();
    WAStartBlover();

    // P6-2N: PP|PP|PP|N|PP|N'
    // w1-w9: PP|PP|PP|N|PP|N'|PP|PP|PP
    // w10-w19: PPA|PP|PP|N|PP|N'|PP|PP|PP|P'A
    // w20: PP
    // 核坑位比较极限，需要拖满收尾，但是io较高，快速关不一定能拖

    for (int w: WaveList(1, 20)) {
        if (w == 4 || w == 6 || w == 13 || w == 15 || w == 19) continue;
        // PP
        PP(w);
        // 消延迟
        if (w == 10) SmartA();
        // 铲种炮
        if (w == 16) {
            AConnect(ATime(w, PCP - CFT + 210), [](){
                aCobManager.FixLatest();
            });
        }
        // 炮炸珊瑚
        if (w == 20) P(w, 225, 4, 7);
    } 
    for (int w: {4, 6, 13, 15}) {
        // N
        N(w, PCP, {{3, 8}, {4, 8}, {3, 9}, {4, 9}}, 601);
    }
    for (int w: {19}) {
        // P'A
        P(w, PCP, 2, 9);
        A(w, PCP, 5, 9);
    }
}