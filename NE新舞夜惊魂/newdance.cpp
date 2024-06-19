#include "../walib.h"

void Puff(int wave, int time, int to_time) {
    AConnect(ATime(wave, time), [=](){
        if(AGetSeedPtr(APUFF_SHROOM) && AGetSeedPtr(APUFF_SHROOM)->IsUsable()) {
            TempCNow(APUFF_SHROOM, 4, 9, to_time - time);
        } else {
            TempCNow(AM_PUFF_SHROOM, 4, 9, to_time - time);
        }
    });
}

void AScript() {
    Init({APUFF_SHROOM, AM_PUFF_SHROOM});
    SkipToTime(20, -200);
    for (int w: WaveList(1, 20)) {
        Puff(w, 160, 600);
        P(w, PCP, 2, 9);
        P(w, 359, 4, 9);
        if (w == 9 || w == 19) {
            P(w, PCP + 601, 2, 9);
            P(w, 359 + 601, 4, 9);
            Puff(w, 160 + 601, 600 + 601);
            P(w, PCP + 601 * 2, 2, 9);
            P(w, 359 + 601 * 2, 4, 9);
            Puff(w, 160 + 601 * 2, 600 + 601 * 2);
            P(w, PCP + 601 * 3, 2, 9);
            P(w, 359 + 601 * 3, 4, 9);
            Puff(w, 160 + 601 * 3, 600 + 601 * 3);
        }
        if (w == 20) {
            PP(w, 345, 7.5);
            P(w, PCP + 110, 2, 9);
            P(w, 359 + 110, 4, 9);
            P(w, PCP + 220, 2, 9);
            P(w, 359 + 220, 4, 9);
            P(w, PCP + 330, 2, 9);
            P(w, 359 + 330, 4, 9);
            P(w, PCP + 550, 2, 9);
            P(w, 359 + 550, 4, 9);
        }
    }
}