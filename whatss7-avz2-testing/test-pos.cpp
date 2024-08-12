#include "test.h"

// 在此处输入用冰位置、带卡、出僵尸等。
// 可能被炸掉的植物也需要在带卡中。
void PreOperations() {
    Init({AICE_SHROOM, ACOFFEE_BEAN}, {AHT_14}, true);
    AConnect(ATime(1, -599), [](){ aIceFiller.Start({{1, 1}}); });
    StartReloadMode(10);
    // SkipToTime(20, 2300);
    RecordWaves();
}

// 在此处输入每波的操作，返回此波波长。所有波的波长必须一致。
// 在返回的波长-200时刻，场上的僵尸会被清除。
int WaveOperations(int wave) {
    const int len = 4000;
    int w = wave;
    I3(w, 1, len);
    return len;
}

//////////////////////////////////////////////////

float min_pos = 1000, max_pos = -1000;
int zombie_cnt = 0;
ALogger<AConsole> logger;

void AScript() {
    CommonTesting();
    PreOperations();
    for (int w: WaveList(1, 20)) {
        int len = WaveOperations(w);
        if (w != 9 && w != 19 && w != 20) SetWavelength(w, len);
        AConnect(ATime(w, len - 200), [](){
            float cur_min_pos = 1000, cur_max_pos = -1000;
            for (auto &&zombie: aAliveZombieFilter) {
                cur_min_pos = std::min(cur_min_pos, zombie.Abscissa());
                cur_max_pos = std::max(cur_max_pos, zombie.Abscissa());
                zombie_cnt += 1;
                zombie.State() = 3;
            }
            min_pos = std::min(min_pos, cur_min_pos);
            max_pos = std::max(max_pos, cur_max_pos);
            logger.Info(
                "总数：# 本波：#-# 累计：#-#", 
                zombie_cnt, cur_min_pos, cur_max_pos, min_pos, max_pos
            );
        });
    }
}
