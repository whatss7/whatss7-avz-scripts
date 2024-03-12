#include "../whatss7-avz2-lib/walib.h"

void FixMaid() {
    AConnect(ATime(1, -599), [](){ AMaidCheats::Dancing(); });
    AConnect(ATime(1, -598), [](){
        // 未知问题导致开局伴舞前进1px
        bool r1ok, r5ok;
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.Type() != ABW_9) continue;
            if (!r1ok && zombie.Row() == 0) {
                zombie.Abscissa() = 324;
                r1ok = true;
            }
            if (!r5ok && zombie.Row() == 4) {
                zombie.Abscissa() = 324;
                r5ok = true;
            }
        }
    });
}

void Puff(int wave, int time, int to_time) {
    ForEnd(wave, time, [=](){
        AConnect(ATime(wave, time), [=](){
            if(AGetSeedPtr(APUFF_SHROOM) && AGetSeedPtr(APUFF_SHROOM)->IsUsable()) {
                TempC(wave, time, APUFF_SHROOM, 4, 9, to_time);
            } else {
                TempC(wave, time, AM_PUFF_SHROOM, 4, 9, to_time);
            }
        });
    });
}

void AScript() {
    WAInit({APUFF_SHROOM, AM_PUFF_SHROOM});
    FixMaid();
    for (int w: WaveList(1, 20)) {
        Puff(w, 160, 600);
        P(w, 316, 2, 9);
        P(w, 359, 4, 9);
        if (w == 9 || w == 19) {
            PPForEnd(w, 359 + 601);
            Puff(w, 160 + 601, 600 + 601);
            PPForEnd(w, 359 + 601 * 2);
            Puff(w, 160 + 601 * 2, 600 + 601 * 2);
            PPForEnd(w, 359 + 601 * 3);
        }
        if (w == 20) {
            PP(w, 350, 8);
            PPForEnd(w, 359 + 601);
            Puff(w, 160 + 601, 600 + 601);
            PPForEnd(w, 359 + 601 * 2);
            Puff(w, 160 + 601 * 2, 600 + 601 * 2);
            PPForEnd(w, 359 + 601 * 3);
            AConnect(ATime(w, 3000), [](){
                AMaidCheats::Move();
            });
            AConnect(ATime(w, 3100), [](){
                AMaidCheats::Dancing();
            });
            TempC(w, 2995, APUFF_SHROOM, 1, 5, 3105);
            TempC(w, 2995, AM_PUFF_SHROOM, 5, 5, 3105);
        }
    }
}