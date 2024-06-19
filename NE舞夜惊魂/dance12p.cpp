#include "../walib.h"

// 若需挂机，则必须掉节操写内存调整伴舞位置
// 否则，此脚本只能保证完成2f
// 解除下行注释来挂机
// #define CHEATING

void FixMaid() {
    #ifdef CHEATING
    StartReloadMode();
    #endif
    AConnect(ATime(1, -599), [](){
        AMaidCheats::Dancing();
        #ifdef CHEATING
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.Type() != ABW_9) continue;
            if (zombie.Row() == 0 || zombie.Row() == 4) {
                zombie.Abscissa() = 324.8;
            }
        }
        #endif
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
    Init({APUFF_SHROOM, AM_PUFF_SHROOM});
    FixMaid();
    for (int w: WaveList(1, 20)) {
        Puff(w, 160, 600);
        P(w, PCP, 2, 9);
        P(w, 359, 4, 9);
        if (w == 9 || w == 19) {
            PForEnd(w, 601 + PCP, 2, 9);
            PForEnd(w, 601 + 359, 4, 9);
            Puff(w, 160 + 601, 600 + 601);
            PForEnd(w, 601 * 2 + PCP, 2, 9);
            PForEnd(w, 601 * 2 + 359, 4, 9);
            Puff(w, 160 + 601 * 2, 600 + 601 * 2);
            PForEnd(w, 601 * 3 + PCP, 2, 9);
            PForEnd(w, 601 * 3 + 359, 4, 9);
        }
        if (w == 20) {
            PP(w, 350, 8);
            PForEnd(w, 601 + PCP, 2, 9);
            PForEnd(w, 601 + 359, 4, 9);
            Puff(w, 160 + 601, 600 + 601);
            PForEnd(w, 601 * 2 + PCP, 2, 9);
            PForEnd(w, 601 * 2 + 359, 4, 9);
            Puff(w, 160 + 601 * 2, 600 + 601 * 2);
            PForEnd(w, 601 * 3 + PCP, 2, 9);
            PForEnd(w, 601 * 3 + 359, 4, 9);
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