#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WASelectCards({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, APUMPKIN, ACHERRY_BOMB}, true);
    WABindKeys();
    // WASelectZombies();
    WACheck(true, true);

    aIceFiller.Start({{4, 9}});
    WAFixNuts();
    if (AGetZombieTypeList()[AHY_32]) {
        // 有红眼时，双边完美公式
        for (int w: {1, 4, 7, 11, 14, 17}) {
            PP(w, 359);
            DD(w, 359 + 107, 7.8);
        }
        for (int w: {2, 5, 8, 12, 15, 18}) {
            PP(w);
            I(w, PCP + 4);
        }
        for (int w: {3, 6, 9, 10, 13, 16, 19}) {
            PP(w, PCP, 9, {2, 2, 5, 5});
            DD(w, PCP + 110, 9);
            if (w == 9 || w == 19) {
                PPForEnd(w, 601 + 359);
            }
            if (w == 20) {
                P(w, 225, 4, 7.5875);
            }
        }
        for (int w: {20}) {
            // 炮炸珊瑚
            P(w, 225, 4, 7.5875);
            // PPSADD，使用一个樱桃代炮把炮炸珊瑚的炮补回来
            PP(w, PCP, 9, {2, 2, 5});
            A(w, PCP + 1, 5, 9);
            DD(w, PCP + 110, 9);
            PPForEnd(w, 601 + 359);
        }
    } else {
        // 没有红眼时，逐波PD
        for (int w: WaveList(1, 20)) {
            if (w == 10 || w == 20) {
                // 旗帜波部分出怪下，即使极晚生效，也存在刷新延迟的情况（但是想想上面红眼部分，PPI也有不低的刷新延迟率）
                // 如果使用类似于精舞的操作，延迟炮为了炸伴舞必须左移，但是这样就炸不到进场晚的慢速僵尸
                // 所以要在舞王召唤前生效炮
                PP(w, 341);
                // 9列拦截最长延迟125
                DD(w, 341 + 125, 9);
            } else {
                // 测试知非旗帜波必刷新
                PP(w);
                PP(w, 400, 9);
            }
            if (w == 9 || w == 19 || w == 20) {
                PPForEnd(w, 601 + PCP);
            }
            if (w == 20) {
                P(w, 225, 4, 7.5875);
            }
        }
    }
}
