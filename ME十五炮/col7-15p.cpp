#include "../walib.h"

ACobManager wind, flat, any;
const int i1_len = 1630, i2_len = 1720, n_len = 620, p_len = 625;

void AScript() {
    InitWithoutManage({ AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ACHERRY_BOMB, AJALAPENO, AFLOWER_POT, ASUNFLOWER, AUMBRELLA_LEAF });
    AConnect(ATime(1, -599), [](){
        wind.SetList({{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}});
        flat.SetList({{1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}});
        any.SetList({{1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}});
    });

    // w2 2路铲花给辣椒让位
    Remove(2, n_len - 200 - 120 - ADT - 5, ASUNFLOWER, 2, 3);

    // w10 种2路伞，铲3路花给辣椒让位，种回2路花
    Remove(10, n_len - 200 - 120 - ADT - 5, ASUNFLOWER, 3, 3);
    TempC(10, 300, AUMBRELLA_LEAF, 2, 3, 400);
    C(10, 401, ASUNFLOWER, 2, 3);

    // w18 种回3路花
    C(18, 13, ASUNFLOWER, 3, 3);

    // w19 铲4路花给辣椒让位
    Remove(19, 601 + n_len - 200 - 120 - ADT - 1, ASUNFLOWER, 4, 3);

    // w20 种回4路花
    C(20, i1_len + 12 + 1, ASUNFLOWER, 4, 3);

    // IPP-PPDD 短波
    for (int w: {4, 9, 12, 17, 20}) {
        int r = w < 10 ? 2 : 3;
        if (w == 20) r = 4;
        ManualI3(w, 1, r, 3, p_len);
        ManualP(w, 850, 2, 6.9, wind);
        ManualP(w, 850, 4, 6.9, flat);
        ManualP(w, i1_len - 200, 2, 8.9, any);
        ManualP(w, i1_len - 200, 4, 8.9, flat);
        ManualP(w, i1_len - 200 + 220, 2, 7.4, wind);
        ManualP(w, i1_len - 200 + 220, 4, 7.4, any);
        if (w == 9 || w == 20) {
            if (w == 20) ManualP(w, 400, 2, 3, any);
            ManualI3(w, i1_len + 12, r, 3, i1_len);
            if (w == 9) {
                ManualP(w, i1_len + 850, 2, 6.65, wind);
                ManualP(w, i1_len + 850, 4, 6.65, flat);
            } else {
                ManualP(w, 400, 4, 3, flat);
            }
            ManualP(w, i1_len + i2_len - 200, 2, 8.9, any);
            ManualP(w, i1_len + i2_len - 200, 4, 8.9, flat);
            ManualP(w, i1_len + i2_len - 200 + 220, 2, 7.6, wind);
            ManualP(w, i1_len + i2_len - 200 + 220, 4, 7.6, any);
            ManualP(w, 3725, 2, 7.6, wind);
            ManualP(w, 3725, 4, 7.6, flat);
        }
    }
    
    // IPP-PPDD 长波
    for (int w: {5, 13, 18}) {
        ManualI3(w, 12, w < 10 ? 2 : 3, 3, i1_len);
        ManualP(w, 850, 2, 6.55, wind);
        ManualP(w, 850, 4, 6.55, flat);
        ManualP(w, i2_len - 200, 2, 8.9, any);
        ManualP(w, i2_len - 200, 4, 8.9, flat);
        ManualP(w, i2_len - 200 + 220, 2, 7.4, wind);
        ManualP(w, i2_len - 200 + 220, 4, 7.4, any);
    }

    // BA/PD
    // 樱桃380之后可能蹭巨人，下半激活炮提前至252生效，3列投出的小鬼用上半激活炮收掉
    // 292巨人恢复原速，距252有80cs，对冰波巨人等效272激活，380樱桃拦截
    for (int w: {1, 6, 14, 19}) {
        ManualP(w, 252, 4, 9, flat);
        TempC(w, 601 + (n_len - 200) - 100 - 751, AFLOWER_POT, 4, 8, 381);
        A(w, 380, 4, 8);
        ManualP(w, 370, 2, 9, any);
        ManualP(w, 370 + 110, 2, 7.7, wind);
        if (w == 19) {
            // w19清理冰道，4-9点核收尾，只剩巨人撑杆不用担心漏炸
            J(w, 601 + n_len - 200 - 120, 4, 3);
            N(w, 601 + n_len - 200, 4, 9);
            ManualP(w, 601 + n_len - 200 + 120, 2, 7.6, wind);
            ManualP(w, 601 + n_len - 200 + 120, 4, 7.6, flat);
            ManualP(w, 601 + n_len + p_len - 200, 2, 8.9, any);
            ManualP(w, 601 + n_len + p_len - 200, 4, 8.9, flat);
        }
    }

    // A'NDD
    for (int w: {2, 7, 10, 15}) {
        int r = w < 10 ? 2 : 3;
        J(w, n_len - 200 - 120, r, 3);
        N(w, n_len - 200, {{r, 9}, {r, 8}});
        ManualP(w, n_len - 200 + 120, 2, 7.5, wind);
        ManualP(w, n_len - 200 + 120, 4, 7.5, flat);
        if (w == 10) ManualP(w, 400, 4, 3, any);
    }

    // PPDD
    for (int w: {3, 8, 11, 16}) {
        ManualP(w, p_len - 200, 2, 8.9, any);
        ManualP(w, p_len - 200, 4, 8.9, flat);
        ManualP(w, p_len - 200 + 130, 2, 7.45, wind);
        ManualP(w, p_len - 200 + 130, 4, 7.45, any);
    }
}
