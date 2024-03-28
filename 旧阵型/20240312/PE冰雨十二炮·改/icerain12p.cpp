#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, APUMPKIN});
    WAAutoManageCob();
    WAFixNuts();
    // 水路僵尸必须考虑
    waForEndIgnore = { AKG_17, AXG_24, APJ_0, ALZ_2, ADB_5 };
    waForEndIgnoreInWater = { AHY_32 };
    aIceFiller.Start({{4, 9}});
    for (int w: WaveList(1, 20)) {
        if (w == 10) {
            P(w, PCP, 2, 9);
            A(w, PCP, 5, 9);
        } else {
            PP(w);
        }
        if (w == 20) {
            P(w, 225, 4, 7.5875);
        }
        if (w == 10 || w == 20) {
            I(w, 400);
            P(w, 400, 5, 9);
        }
        if (w == 9 || w == 19 || w == 20) {
            PPForEnd(w, PCP + 601);
            PPForEnd(w, PCP + 601 * 2);
            AConnect(ATime(w, PCP + 601 * 3 - CFT), [w](){
                if (WAExistZombie({APJ_0, ALZ_2, ATT_18}, {3, 4})) {
                    PPForEnd(w, PCP + 601 * 3);
                }
            });
        }
    }
}