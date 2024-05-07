#include "../walib.h"

void AScript() {
    Init({ACHERRY_BOMB, APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT});
    for (int w: WaveList(1, 20)) {
        PP(w);
        P(w, PCP + 230, 1, 4);
        TempC(w, PCP + 142, w % 2 == 1 || w == 20 ? APUFF_SHROOM : ASCAREDY_SHROOM, 1, 9, PCP + 142 + 100);
        TempC(w, PCP + 142, w % 2 == 1 || w == 20 ? ASUN_SHROOM : AFLOWER_POT, 2, 9, PCP + 142 + 100);
        if (w == 10) SmartA(w, PCP);
        if (w == 20) P(w, 225, 4, 7.5875);
        if (w == 9 || w == 19 || w == 20) {
            PP(w, 601 + PCP);
            P(w, 601 + PCP + 230, 1, 4);
            TempC(w, 601 + PCP + 142, ASCAREDY_SHROOM, 1, 9, PCP + 142 + 100);
            TempC(w, 601 + PCP + 142, AFLOWER_POT, 2, 9, PCP + 142 + 100);
            PP(w, 601 * 2 + PCP);
            PP(w, 601 * 3 + PCP);
        }
    }
}