// #define WALIB_DEBUG
#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, APUMPKIN, ABLOVER});
    WAFixNuts();
    aIceFiller.Start({{3, 3}, {3, 4}, {3, 5}});
    const int i_len = 1149;
    // 冰波D
    const int delay_1 = 213;
    // 加速波B
    const int delay_2 = 229;
    // 加速波d
    const int delay_3 = 260;
    // IP-P/PD | P/Bd
    for (int w: {1, 3, 5, 7, 9, 11, 13, 15, 17, 19}) {
        I(w, 100, 601);
        // 旗帜波会漏气球，这里冰住之后再种三叶草，防止撑杆意外跳过
        if (w == 11) {
            AConnect(ATime(w, 105), [](){
                for (auto &&zombie: aAliveZombieFilter) {
                    if (zombie.Type() == AQQ_16 && zombie.AtWave() + 1 == 10) {
                        ACard(ABLOVER, 3, 8);
                        break;
                    }
                }
            });
        }
        // 上半场热过渡炸实，不然压制力不太够
        P(w, 359, 2, 9);
        // 激活炮
        PP(w, i_len - 200, 9);
        // D伤本波触发连拦，此处炸9列不能全拦
        P(w, i_len - 200 + delay_1, 4, 8.8375);
        if (w == 9 || w == 19) {
            // 先照着再打一个加速波
            // 上半场炸，但是补一个樱桃
            P(w, i_len + 316, 2, 9);
            A(w, i_len + 316, 2, 9);
            // 下半场连拦
            P(w, i_len + (i_len - 200 + delay_1 + delay_2 - i_len), 4, 9);
            P(w, i_len + (i_len - 200 + delay_1 + delay_2 - i_len + delay_3), 4, 2.425);
            // 上半场：w9 P，收尾炮+樱桃，一血红
            // 下半场：w9 激活炮+连拦炮，收尾连拦炮，一血红
            AConnect(ATime(w, i_len + 316 + 4), [w](){
                if (WAExistZombie(AHY_32, {4, 5})) {
                    // 如果下半场有红眼，那么之前的热过渡炮拿来收掉上半场，用下半场红眼收尾
                    P(w, i_len + 601 + 359, 2, 9);
                    PPExceptOne(w, i_len + 601 + 949);
                    waStopGigaBanCols = {9};
                    WAStopGiga(w, i_len + 601 + 949 + 4, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT}, 4300);
                    PPLast(w, 4300);
                } else {
                    // 否则，用上半场红眼收尾。下半场没有红眼，应该只用一炮进入收尾。
                    PPExceptOne(w, i_len + 601 + 359);
                    waStopGigaBanCols = {};
                    WAStopGiga(w, i_len + 601 + 359 + 4, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT}, 4300);
                    PPLast(w, 4300);
                }
            });
            // 收尾时开启女仆，直到下一波预判炸时
            AConnect(ATime(w, i_len + 601 + 359), [](){ AMaidCheats::Dancing(); });
            if (w == 9) AConnect(ATime(w + 1, 316), [](){ AMaidCheats::Stop(); });
        }
    }
    for (int w: {2, 4, 6, 8, 10, 12, 14, 16, 18}) {
        // 上半场炸
        P(w, 316, 2, 9);
        // 垫撑杆
        TempC(w, 420, APUFF_SHROOM, 1, 9, 600 - 420);
        TempC(w, 420, ASUN_SHROOM, 2, 9, 600 - 420);
        // 下半场连拦
        P(w, i_len - 200 + delay_1 + delay_2 - i_len, 4, 9);
        P(w, i_len - 200 + delay_1 + delay_2 - i_len + delay_3, 4, 2.45);
    }
    for (int w: {20}) {
        AConnect(ATime(w, -191), [](){ AMaidCheats::Move(); });
        // 标准收尾
        PP(w, 309, 9, {2, 2, 4, 4});
        P(w, 400, 4, 2);
        PP(w, 409, 9, {2, 2, 4, 4});
        // 两炮下去，还没入场的伴舞就别入场了
        AConnect(ATime(w, 409), [](){ AMaidCheats::Dancing(); });
        PPExceptOne(w, 814);
        // 延迟4cs再放南瓜
        BlockLast(w, 818, 4000);
        PPLast(w, 4000);
    }
}