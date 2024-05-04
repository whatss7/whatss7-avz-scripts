#include "../walib.h"
#include "../whatss7-avz2-testing/test.h"

#define SMART 0

void AScript() {
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ASPIKEWEED, APOTATO_MINE,
        ASQUASH, APUFF_SHROOM, AFLOWER_POT, AGARLIC, ADOOM_SHROOM
    });
    ForbidEnterHome(ModState::SCOPED_ON);
    StartIceFiller({{1, 1}, {1, 2}, {2, 1}});
    // TODO: 长波花盆垫扶梯防止啃7列炮
    // 635cs最慢的矿工到达399，啃不到土豆，冰波波长最长要取1635cs
    const int short_len = 1615, short_extended_len = 1635, long_len = 1860;
    for (int w: {1, 10}) {
        PP(w);
        P(w, PCP + 110, 1, 8);
        P(w, PCP + 260, 4, 3);
        TempC(w, 374, AGARLIC, 2, 9, 474);
        TempC(w, 374, AFLOWER_POT, 4, 9, 474);
        if (w == 10) {
            Remove(w, 601 - 1001, APOTATO_MINE, 4, 6);
            C(w, 601 - 1000, APOTATO_MINE, 4, 6);
        }
    }
    for (int w: {2, 4, 6, 8, 12, 14, 16, 18}) {
        I(w, 12, w == 2 ? 601 : long_len);

        // 扎2路冰车
        TempC(w, 292, ASPIKEWEED, 2, 9, 292 + 100);

        // 垫3路巨人防止锤精准土豆
        // 地刺前垫
        TempC(w, 1043 - 416, APUFF_SHROOM, 4, 7, 1043 - 416 + 100);
        // 扎4路冰车防止后续垫材被碾，并顺便垫巨人
        TempC(w, 1043, ASPIKEWEED, 4, 7, 1043 + 100);
        // 地刺后垫
        TempC(w, 1043 + 416, APUFF_SHROOM, 4, 7, 1043 + 416 + 100);

        #if SMART
        // 精准土豆，智能脚本降低炮损
        AConnect(ATime(w, short_len - 1000), [w](){
            // 检测是否还有能啃到土豆的矿工，若有，延迟20cs再放，并对应调整波长
            bool eatable = false;
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Row() + 1 == 4 && zombie.Type() == AKG_17 && zombie.Abscissa() >= 400) {
                    eatable = true;
                    break;
                }
            }
            int len = eatable ? short_extended_len : short_len;

            // 精准土豆
            Remove(w, len - 1001, APOTATO_MINE, 4, 6);
            C(w, len - 1000, APOTATO_MINE, 4, 6);

            // 垫5路巨人防止离开炮范围
            TempC(w, 615, ASCAREDY_SHROOM, 4, 7, 615 + 100);
            TempC(w, 615 + 416, AFLOWER_POT, 4, 7, 615 + 416 + 100);

            // PPDd
            PP(w, len - 200, 8.6);
            P(w, len - 200 + 220, 1, 7.4125);
            P(w, len - 200 + 370, 4, 2.45);

            // 不定波长下，下一波点冰提前完成
            I(w + 1, 12, len);
        });
        #else
        // 精准土豆，固定操作用于模拟最差情况
        Remove(w, short_extended_len - 1001, APOTATO_MINE, 4, 6);
        C(w, short_extended_len - 1000, APOTATO_MINE, 4, 6);

        // 垫5路巨人防止离开炮范围
        TempC(w, short_extended_len - 200 - 416 - 416, AGARLIC, 5, 6, long_len - 200 - 416 - 416 + 100);
        TempC(w, short_extended_len - 200 - 416, AFLOWER_POT, 5, 6, long_len - 200 - 416 + 100);

        // PPDd
        PP(w, short_extended_len - 200, 8.6);
        P(w, short_extended_len - 200 + 220, 1, 7.4125);
        P(w, short_extended_len - 200 + 370, 4, 2.45);

        // 不定波长下，下一波点冰提前完成
        I(w + 1, 12, short_extended_len);
        // if (w != 9 && w != 19 && w != 20) ASetWavelength({ATime(w, short_extended_len)});
        #endif
    }
    for (int w: {3, 5, 7, 9, 11, 13, 15, 17, 19}) {
        if (w == 11) I(w, 12, 601);
        // 已在上波处理点冰
        // else I(w, 12, short_len);

        // 扎2路冰车，驱赶梯子
        TempC(w, 292, ASPIKEWEED, 2, 9, 318 + 100);
        TempC(w, 850, AGARLIC, 2, 9, 850 + 100);

        // 用窝瓜处理3路冰车
        AConnect(ATime(w, long_len - 200 - 220 - SDT), [](){
            if (ExistZombie(ABC_12, {3})) ACard(ASQUASH, 3, 7);
        });

        // 垫4路巨人防止锤精准土豆
        // 地刺前垫
        TempC(w, 1043 - 416, APUFF_SHROOM, 4, 7, 1043 - 416 + 100);
        // 扎4路冰车顺便垫巨人
        TempC(w, 1043, ASPIKEWEED, 4, 7, 1043 + 100);
        // 地刺后垫
        TempC(w, 1043 + 416, APUFF_SHROOM, 4, 7, 1043 + 416 + 100);

        // 垫5路巨人防止离开炮范围
        TempC(w, 1601 - 416, AFLOWER_POT, 5, 6, 1601 - 416 + 140);
        TempC(w, 1601, AGARLIC, 5, 6, 1601 + 140);

        if (w != 9 && w != 19) {
            // PPDd
            PP(w, long_len - 200, 8.5);
            P(w, long_len - 200 + 220, 1, 7.3875);
            P(w, long_len - 200 + 370, 4, 2.45);
            // if (w != 9 && w != 19 && w != 20) ASetWavelength({ATime(w, long_len)});
        } else {
            // 考虑一个w8出生的2路巨人，
            PP(w, long_len - 200, 8.5);
            P(w, long_len - 200 + 220, 1, 8.5);
            P(w, long_len - 200 + 370, 4, 2.45);
        }
    }
}