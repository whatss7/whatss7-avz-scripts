#include "../walib.h"

void AScript() {
    Init({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN}, "Random", true);
    StartReloadMode(10);
    aIceFiller.Start({{4, 9}});
    if (AGetZombieTypeList()[AHY_32]) {
        // 有红眼时，P6-2I: PPDD | PPDD | PPI | PPDD | PPDD | PPI
        for (int w: {1, 3, 4, 6, 7, 9, 10, 11, 13, 14, 16, 17, 19}) {
            PP(w);
            PP(w, 401);
            if (w == 9 || w == 19) {
                PPForEnd(w, 601 + PCP);
                PPForEnd(w, 601 + 401);
            }
        }
        for (int w: {2, 5, 8, 12, 15, 18}) {
            PP(w);
            I(w, PCP);
        }
        for (int w: {20}) {
            P(w, 225, 4, 7.5875);
            P(w, PCP, 2, 9);
            A(w, PCP, 5, 9);
            PP(w, 401);
            PPForEnd(w, 601 + PCP);
            PPForEnd(w, 601 + 401);
            PPForEnd(w, 601 * 2 + PCP);
        }
    } else {
        // 无红眼时，P6: PP | BBDD | PP | BBDD | PP | BBDD
        for (int w: { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 }) {
            PP(w);
            if (w == 9 || w == 19) {
                PPForEnd(w, 601 + 180);
                PPForEnd(w, 601 + 401);
                PPForEnd(w, 601 * 2 + PCP);
            }
        }
        for (int w: { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 }) {
            PP(w, 180);
            PP(w, 401);
            if (w == 20) {
                P(w, 225, 4, 7.5875);
                PPForEnd(w, 601 + PCP);
                PPForEnd(w, 601 * 2 + 180);
                PPForEnd(w, 601 * 2 + 401);
            }
        }
    }
}