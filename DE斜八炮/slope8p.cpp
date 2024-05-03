#include "../walib.h"
#include "../whatss7-avz2-testing/test.h"

#define SMART 0

void AScript() {
    Init({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ASPIKEWEED, ASPIKEROCK, APOTATO_MINE}, {ATT_18});
    ForbidEnterHome(ModState::SCOPED_ON);
    StartIceFiller({{1, 1}, {1, 2}, {2, 1}});
    const int short_len = 1615, short_extended_len = 1635, long_len = 1860;
    C(1, -599, {ASPIKEWEED, ASPIKEROCK}, 5, 1);
    // TODO: 1. 垫材拖延巨人防止锤6列炮和土豆雷
    // 635cs最慢的矿工到达399，啃不到土豆，冰波波长最长要取1635cs
    // 考虑一个长波出生的3路红眼，会在短波被干掉，对6炮没有威胁
    // 考虑一个长波出生的4路红眼，会在下一个长波被干掉，
    for (int w: {1, 3, 5, 7, 9, 11, 13, 15, 17, 19}) {
        I(w, 12, long_len);
        TempC(w, 318, ASPIKEWEED, 2, 9, 318 + 100);
        #if SMART
        AConnect(ATime(w, short_len - 1000), [w](){
            // 检测是否还有能啃到土豆的矿工，若有，延迟20cs再放
            bool eatable = false;
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Row() + 1 == 4 && zombie.Type() == AKG_17 && zombie.Abscissa() >= 400) {
                    eatable = true;
                    break;
                }
            }
            if (eatable) {
                C(w, short_extended_len - 1000, APOTATO_MINE, 4, 6);
                PP(w, short_extended_len - 200, 8.6);
                P(w, short_extended_len - 200 + 220, 1, 7.4125);
                P(w, short_extended_len - 200 + 370, 4, 2.45);
                I(w + 1, 12, short_extended_len);
            } else {
                C(w, short_len - 1000, APOTATO_MINE, 4, 6);
                PP(w, short_len - 200, 8.6);
                P(w, short_len - 200 + 220, 1, 7.4125);
                P(w, short_len - 200 + 370, 4, 2.45);
                I(w + 1, 12, short_len);
            }
        });
        #else
        Remove(w, short_extended_len - 1001, APOTATO_MINE, 4, 6);
        C(w, short_extended_len - 1000, APOTATO_MINE, 4, 6);
        PP(w, short_extended_len - 200, 8.6);
        P(w, short_extended_len - 200 + 220, 1, 7.4125);
        P(w, short_extended_len - 200 + 370, 4, 2.45);
        I(w + 1, 12, short_extended_len);
        // if (w != 9 && w != 19 && w != 20) ASetWavelength({ATime(w, short_extended_len)});
        #endif
    }
    for (int w: {2, 4, 6, 8, 10, 12, 14, 16, 18, 20}) {
        // 已在上波处理点冰
        // I(w, 12, short_len);
        TempC(w, 318, ASPIKEWEED, 2, 9, 318 + 100);
        TempC(w, 318 + 751, ASPIKEWEED, 3, 7, 318 + 751 + 100);
        PP(w, long_len - 200, 8.5);
        P(w, long_len - 200 + 220, 1, 7.3875);
        P(w, long_len - 200 + 370, 4, 2.45);
        // if (w != 9 && w != 19 && w != 20) ASetWavelength({ATime(w, long_len)});
    }
}