#include <avz.h>
#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB}, "Cycle");
    WAAutoManageCob();
    // 非旗帜波: PP
    for (int w: WaveList(1, 9) + WaveList(11, 19)) {
        AConnect(ATime(w, PCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        if (w == 9 || w == 19) {
            AConnect(ATime(w, PCP + CFT + 1), waEndCobber);
        }
    }
    // w10: PPA 消延迟
    for (int w: {10}) {
        AConnect(ATime(w, DPCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        AConnect(ATime(w, DPCP + CFT - ADT), [](){
            ACard(ACHERRY_BOMB, 2, 9);
        });
    }
    // w20: PP+冰消珊瑚
    for (int w: {20}) {
        AConnect(ATime(w, -50 - ADT - CBT), [](){
            ACard(AICE_SHROOM, 1, 1);
            ACard(ACOFFEE_BEAN, 1, 1);
        });
        AConnect(ATime(w, PCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        AConnect(ATime(w, PCP + CFT + 1), waEndCobber);
    }
}