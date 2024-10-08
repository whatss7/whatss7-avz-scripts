#include "test.h"

// 在此处输入用冰位置、带卡、出僵尸等。
// 可能被炸掉的植物也需要在带卡中。
void PreOperations() {
    Init({AICE_SHROOM, ACOFFEE_BEAN, ADOOM_SHROOM, ASNOW_PEA}, {ATT_18}, true);
    StartIceFiller({{1, 3}});
    StartReloadMode(10);
    SkipToTime(20, 6000);
    // RecordWaves();
}

// 在此处输入每波的操作，返回此波波长。所有波的波长必须一致。
// 在返回的波长-200时刻，场上的僵尸会被清除。
int WaveOperations(int w) {
    const int len = 4000;
    RM(w, 1, AICE_SHROOM, 2, 4);
    C(w, 2, ADOOM_SHROOM, 2, 4);
    I(w, 12, len);
    // 樱桃清掉下半场矿工，因为2路核难收5路矿工
    A(w, 317, 4, 7);
    // 44444
    // PPn，核尾炸同时还能收矿工
    MultiTempC(w, 614, {ASCAREDY_SHROOM, AFLOWER_POT}, 7, {4, 5}, 955);
    PP(w, 1050, 8.825);
    C(w, 1050 + 329 - CBT - ADT, ACOFFEE_BEAN, 2, 4);
    // 33233
    // PPDD
    PP(w, 1935, 8.325, {1, 4});
    D(w, 1973 + 110, 1, 8.325);
    D(w, 1973 + 110, 4, 8.325);
    // N(w, 2650, 3, 1);
    // 11011
    MultiTempC(w, 2249, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT}, 7, {1, 2, 4, 5}, 4300);
    return len;
}

// 在此处输入所检测的内容。
// 此函数返回true时，场上的僵尸会被清除。
bool DetectOperations() {
    for (auto &zombie: aAliveZombieFilter) {
        if (zombie.Type() == ATT_18 && zombie.Abscissa() >= 163) return false;
    }
    return true;
}

//////////////////////////////////////////////////

int test_cnt = 0, min_time = 99999, max_time = 0;
ALogger<AConsole> logger;
ATickRunner detectRunner;

void AScript() {
    CommonTesting(false);
    PreOperations();
    for (int w: WaveList(1, 20)) {
        if (w == 9 || w == 19 || w == 20) {
            AConnect(ATime(w, 1), [](){
                InstantKill();
            });
        } else {
            int len = WaveOperations(w);
            if (w != 9 && w != 19 && w != 20) SetWavelength(w, len);
            AConnect(ATime(w, 1), [](){
                detectRunner.Start([](){
                    if (DetectOperations()) {
                        InstantKill();
                        detectRunner.Stop();
                        int cur_time = ANowTime().time;
                        min_time = std::min(min_time, cur_time);
                        max_time = std::max(max_time, cur_time);
                        test_cnt += 1;
                        logger.Info("Event at #, time range #-#, test count #", cur_time, min_time, max_time, test_cnt);
                    }
                });
            });
            AConnect(ATime(w, len - 200), [](){
                if (!detectRunner.IsStopped()) {
                    detectRunner.Stop();
                    InstantKill();
                    max_time = 99999;
                    logger.Info("Event miss, time range #-#, test count #", min_time, max_time, test_cnt);
                }
            });
        }
    }
}
