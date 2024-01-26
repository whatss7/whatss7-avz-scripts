#include <avz.h>
#include "whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB}, "Cycle");
    WAAutoManageCob();
    // ASetGameSpeed(10);
    // 非旗帜波: PP
    for (int w: WaveList(1, 9) + WaveList(11, 19)) {
        AConnect(ATime(w, PCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        if (w == 9 || w == 19) {
            AConnect(ATime(w, PCP + CFT + 1), WARecoverEnd());
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
    // w20: I-PP 冰消珊瑚，12秒减速波
    for (int w: {20}) {
        AConnect(ATime(w, -199), [](){
            ACard(AICE_SHROOM, 1, 1);
            ACard(ACOFFEE_BEAN, 1, 1);
        });
        AConnect(ATime(w, 1200 - 200 - CFT), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        AConnect(ATime(w, 1200 - 200 + 1), WARecoverEnd());
    }
}