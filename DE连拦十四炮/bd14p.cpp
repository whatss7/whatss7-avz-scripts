// #define WALIB_DEBUG
#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, APUMPKIN, ABLOVER});
    WAFixNuts();
    aIceFiller.Start({{3, 3}, {3, 4}, {3, 5}});
    const int i_len = 1149;
    // 冰波D
    const int delay_1 = 212;
    // 加速波B
    const int delay_2 = 228;
    // 加速波d，似乎并没有完美时机，先取一个大概的
    const int delay_3 = 270;
    // IP-P/PD | P/Bd
    for (int w: {1, 3, 5, 7, 9, 11, 13, 15, 17, 19}) {
        // FIXME: 不能完美预判冰，需要晚点冰使得后续解冻后巨人能够全部进场；这样的话还需要垫撑杆
        I(w, 1, 601);
        // 上半场热过渡炸实，不然压制力不太够
        P(w, 359, 2, 9);
        // 全部解冻后，垫一次
        // 不知道撑杆最早什么时候对右偏小喷菇起跳，这里先按对南瓜头起跳时机算，952起跳，排除1cs误差，950铲
        TempC(w, 887, APUFF_SHROOM, 1, 9, 950 - 887);
        TempC(w, 887, ASUN_SHROOM, 2, 9, 950 - 887);
        // 激活炮
        PP(w, i_len - 200, 9);
        // D伤本波触发连拦，最多延迟218生效，否则加速波巨人投掷拦不住
        P(w, i_len - 200 + delay_1, 4, 9);
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
                    WAStopGiga(w, i_len + 601 + 949 + 4, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT}, 4300);
                    PPLast(w, 4300);
                } else {
                    // 否则，用上半场红眼收尾。下半场没有红眼，应该只用一炮进入收尾。
                    PPExceptOne(w, i_len + 601 + 359);
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
        BlockLast(w, 818, 5500);
        PPLast(w, 5500);
    }
}