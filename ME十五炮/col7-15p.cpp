#include "../walib.h"

ACobManager wind, flat, any;
const int i_len = 1750, a_len = 700;

void AScript() {
    InitWithoutManage({ AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ACHERRY_BOMB, AJALAPENO, AFLOWER_POT, ASUNFLOWER, AUMBRELLA_LEAF });
    AConnect(ATime(1, -599), [](){
        wind.SetList({{1, 1}, {2, 1}, {3, 1}, {4, 1}});
        flat.SetList({{1, 6}, {2, 6}, {3, 6}, {4, 6}});
        any.SetList({{5, 1}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {5, 6}});
    });
    // I-PPDD
    for (int w: {1, 2, 6, 7, 11, 12, 16, 17}) {
        ManualI3(w, 12, w < 10 ? 3 : 2, 3, w % 2 == 1 ? 650 : 1800);
        ManualP(w, 850, 2, 6.35, any);
        ManualP(w, 850, 4, 6.35, flat);
        ManualP(w, i_len - 200, 2, 8.75, any);
        ManualP(w, i_len - 200, 4, 8.75, flat);
        ManualP(w, i_len - 200 + 225, 2, 7, wind);
        ManualP(w, i_len - 200 + 225, 4, 7, any);
    }
    // 3列A'NDD
    Remove(1, -598, ASUNFLOWER, 3, 3);
    for (int w: {3, 8}) {
        J(w, a_len - 200 - 110, 3, 3);
        N(w, a_len - 200, {{3, 9}, {3, 8}});
        ManualP(w, a_len - 200 + 110, 2, 7.4, wind);
        ManualP(w, a_len - 200 + 110, 4, 7.4, any);
    }
    C(13, a_len - 200, ASUNFLOWER, 3, 3);
    // 2列A'NDD
    Remove(10, a_len + 1 - ADT - MDT, AUMBRELLA_LEAF, 2, 3);
    for (int w: {13, 18}) {
        J(w, a_len - 200 - 110, 2, 3);
        N(w, a_len - 200, {{2, 9}, {2, 8}});
        ManualP(w, a_len - 200 + 110, 2, 7.4, wind);
        ManualP(w, a_len - 200 + 110, 4, 7.4, any);
    }
    C(18, a_len - 200, AUMBRELLA_LEAF, 2, 3);
    // PPDA
    // 樱桃380之后可能蹭巨人，下半激活炮提前至272生效，3列投出的小鬼用上半激活炮收掉
    for (int w: {4, 9, 14, 19}) {
        ManualP(w, 272, 4, 8.6, flat);
        ManualP(w, 380, 2, 8.9125, any);
        A(w, 380, 4, 8);
        ManualP(w, 380 + 110, 2, 8, wind);
    }
    // PPDD
    for (int w: {5, 10, 15, 20}) {
        ManualP(w, a_len - 200, 2, 8.9, any);
        ManualP(w, a_len - 200, 4, 8.9, flat);
        ManualP(w, a_len - 200 + 110, 2, 7.4, wind);
        ManualP(w, a_len - 200 + 110, 4, 7.4, any);
    }
}
