#include "test.h"

// 在此处输入用冰位置、带卡、出僵尸等。
// 可能被炸掉的植物也需要在带卡中。
void PreOperations() {
    Init({AICE_SHROOM, ACOFFEE_BEAN, AFLOWER_POT, ASNOW_PEA}, "Auto", true);
    StartIceFiller({{3, 3}});
    StartReloadMode(10);
    SkipToTime(20, 6000);
    RecordWaves();
}

// 在此处输入每波的操作，返回此波波长。所有波的波长必须一致。
// 在返回的波长-200时刻，场上的僵尸会被清除。
int WaveOperations(int w) {
    const int len = 5000;
    I3(w, 11, len);
    return len;
}

// 在此处输入所检测的内容。
// 此函数返回true时，场上的僵尸会被清除。
bool DetectOperations() {
    for (auto &zombie: aAliveZombieFilter) {
        if (zombie.Type() == AHY_32 && zombie.Abscissa() < 592) return true;
    }
    return false;
}

//////////////////////////////////////////////////

int test_cnt = 0, min_time = 99999, max_time = 0;
ALogger<AConsole> logger;
ATickRunner detectRunner;

void AScript() {
    CommonTesting(false);
    PreOperations();
    for (int w: WaveList(1, 20)) {
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
