#include "../walib.h"

ACobManager wind, flat, any;
const int i_len = 1720, n_len = 630, p_len = 640;

void AScript() {
    InitWithoutManage({ AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ACHERRY_BOMB, AJALAPENO, AFLOWER_POT, ASUNFLOWER, AUMBRELLA_LEAF });
    AConnect(ATime(1, -599), [](){
        wind.SetList({{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}});
        flat.SetList({{1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}});
        any.SetList({{1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}});
    });
    Remove(1, 12 - ADT - MDT - 1, ASUNFLOWER, 3, 3);
    C(11, 13, ASUNFLOWER, 3, 3);
    Remove(11, i_len + 12 - MDT - ADT, AUMBRELLA_LEAF, 2, 3);
    // I-PPDD
    for (int w: {1, 2, 6, 7, 11, 12, 16, 17}) {
        ManualI3(w, 12, w <= 11 ? 3 : 2, 3, w % 5 == 1 ? p_len : i_len);
        ManualP(w, 850, 2, 6.65, wind);
        ManualP(w, 850, 4, 6.65, flat);
        ManualP(w, i_len - 200, 2, 8.75, any);
        ManualP(w, i_len - 200, 4, 8.75, flat);
        ManualP(w, i_len - 200 + 220, 2, 7.4, wind);
        ManualP(w, i_len - 200 + 220, 4, 7.4, any);
    }
    // BA/PD
    // 樱桃380之后可能蹭巨人，下半激活炮提前至252生效，3列投出的小鬼用上半激活炮收掉
    // 292巨人恢复原速，距252有40cs，对冰波巨人等效272激活，380樱桃拦截
    for (int w: {3, 8, 13, 18}) {
        ManualP(w, 252, 4, 9, flat);
        ManualP(w, 380, 2, 9, any);
        A(w, 380, 4, 8);
        ManualP(w, 380 + 110, 2, 7.7, wind);
    }
    // 3列A'NDD
    for (int w: {4, 9}) {
        J(w, n_len - 200 - 120, 3, 3);
        N(w, n_len - 200, {{3, 9}, {3, 8}});
        ManualP(w, n_len - 200 + 110, 2, 7.5, wind);
        ManualP(w, n_len - 200 + 110, 4, 7.5, flat);
        if (w == 9) {
            ManualP(w, n_len + p_len - 200, 2, 8.9, any);
            ManualP(w, n_len + p_len - 200, 4, 8.9, flat);
            ManualP(w, n_len + p_len - 200 + 110, 2, 7.6, wind);
            ManualP(w, n_len + p_len - 200 + 110, 4, 7.6, any);
            ManualI3(w, n_len + p_len - 200 + 111, 3, 3);
            // 400冰，299*2极限不举锤，134*2锤击，共1266，留容错1260
            ManualP(w, n_len + p_len - 200 + 111 + 1260, 2, 8.5, wind);
            ManualP(w, n_len + p_len - 200 + 111 + 1260, 4, 8.5, flat);
        }
    }
    // 2列A'NDD
    for (int w: {14, 19}) {
        J(w, n_len - 200 - 120, 2, 3);
        N(w, n_len - 200, {{2, 9}, {2, 8}});
        ManualP(w, n_len - 200 + 110, 2, 7.5, wind);
        ManualP(w, n_len - 200 + 110, 4, 7.5, flat);
        if (w == 19) {
            ManualP(w, n_len + p_len - 200, 2, 8.9, any);
            ManualP(w, n_len + p_len - 200, 4, 8.9, flat);
            ManualP(w, n_len + p_len - 200 + 110, 2, 7.6, wind);
            ManualP(w, n_len + p_len - 200 + 110, 4, 7.6, any);
            ManualI3(w, n_len + p_len - 200 + 111, 3, 3);
            // 400冰，299*2极限不举锤，134*2锤击，共1266，留容错1260
            ManualP(w, n_len + p_len - 200 + 111 + 1260, 2, 8.5, wind);
            ManualP(w, n_len + p_len - 200 + 111 + 1260, 4, 8.5, flat);
        }
    }
    // PPDD
    for (int w: {5, 10, 15, 20}) {
        ManualP(w, p_len - 200, 2, 8.9, any);
        ManualP(w, p_len - 200, 4, 8.9, flat);
        ManualP(w, p_len - 200 + 110, 2, 7.4, wind);
        ManualP(w, p_len - 200 + 110, 4, 7.4, any);
    }
}
