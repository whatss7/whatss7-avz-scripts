#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, APUMPKIN});
    aIceFiller.Start({{3, 3}, {3, 4}, {3, 5}});
    const int i_len = 1149;
    // IP-P/PD | P/Bd
    for (int w: {1, 3, 5, 7, 9, 11, 13, 15, 17, 19}) {
        I(w, 1, 601);
        // 上半场热过渡炸实，不然压制力不太够
        P(w, 359, 2, 9);
        // 激活炮
        PP(w, i_len - 200, 9);
        // D伤本波触发连拦
        P(w, i_len - 200 + 212, 4, 8.7125);
        if (w == 9 || w == 19) {
            // 先照着再打一个加速波
            // 上半场炸，但是补一个樱桃
            P(w, i_len + 316, 2, 9);
            A(w, i_len + 316, 2, 9);
            // 下半场连拦
            P(w, i_len + (i_len - 200 + 212 + 212 - i_len), 4, 9);
            P(w, i_len + (i_len - 200 + 212 + 212 - i_len + 263), 4, 2.425);
            // 上半场：w9 P，收尾炮+樱桃，因为收尾炮需要时间转好，干脆再来一炮全收
            P(w, i_len + 601 + 370, 2, 9);
            // 下半场：w9 激活炮+连拦炮，收尾连拦炮，一血红
            PPExceptOne(w, i_len + 601 + 949);
            WAStopGiga(w, i_len + 601 + 949 + 1, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT}, 4300);
            PPLast(w, 4300);
            // 收尾时开启女仆，直到下一波预判炸时
            AConnect(ATime(w, i_len + 601 + 370), [](){ AMaidCheats::Dancing(); });
            AConnect(ATime(w + 1, 316), [](){ AMaidCheats::Stop(); });
        }
    }
    for (int w: {2, 4, 6, 8, 10, 12, 14, 16, 18}) {
        // 上半场炸
        P(w, 316, 2, 9);
        // 下半场连拦
        P(w, i_len - 200 + 212 + 212 - i_len, 4, 9);
        P(w, i_len - 200 + 212 + 212 - i_len + 263, 4, 2.425);
    }
    for (int w: {20}) {
        // 标准收尾
        PP(w, 309, 9, {2, 2, 4, 4});
        P(w, 400, 4, 2);
        PP(w, 409, 9, {2, 2, 4, 4});
    }
}