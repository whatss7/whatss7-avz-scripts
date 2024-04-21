#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, AFLOWER_POT, ACHERRY_BOMB, AJALAPENO});
    WAAutoManageCob();
    WAFixCobs();
    aIceFiller.Start({{2, 3}, {4, 3}});
    // ASetZ
    
    // I-PP|IP-PP|PP (15.5, 12.5, 7)
    // 15.5: 完美预判冰下，小丑不会炸到7列的最长波长为1551.
    // 12.5: 冰车不会压到7列最长波长为1253

    const int i1_len = 1250;
    const int i2_len = 1550;
    const int a_len = 700;

    for (int w: {1, 4, 7, 11, 14, 17}) {
        I(w, 1, w == 11 ? 601 : i1_len);
        RoofP(w, 400, 3, 3, 8.5625);
        RoofP(w, i2_len - 200, 1, 2, 9);
        RoofP(w, i2_len - 200, 6, 4, 9);
    }
    for (int w: {2, 5, 8, 12, 15, 18}) {
        RoofP(w, a_len - 200, 1, 2, 9);
        RoofP(w, a_len - 200, 6, 4, 9);
    }
    for (int w: {3, 6, 9, 13, 16, 19}) {
        I(w, 1, a_len);
        RoofP(w, i1_len - 200, 1, 2, 9);
        RoofP(w, i1_len - 200, 6, 4, 9);
        if (w == 9 || w == 19) {
            RoofP(w, i1_len + 400, 3, 3, 8.45);
            A(w, 2050, 3, 8);
            RoofP(w, i1_len + i2_len - 200, 1, 2, 7.5);
            RoofP(w, i1_len + i2_len - 200, 6, 4, 7.5);
            RoofP(w, i1_len + i2_len + a_len - 200, 1, 2, 7);
            RoofP(w, i1_len + i2_len + a_len - 200, 6, 4, 7);
            // 防止原速小鬼偷家，种两个花盆
            TempC(w, 0, AFLOWER_POT, 1, 3, 4500);
            TempC(w, 800, AFLOWER_POT, 5, 3, 3700);
        }
    }
    for (int w: {10}) {
        RoofP(w, 401, 1, 2, 9);
        RoofP(w, 401, 6, 4, 9);
    }
    for (int w: {20}) {
        I(w, 400);
        RoofP(w, 750, 3, 3, 7);
        // 400冰下小丑炸7列时机1070
        RoofP(w, 1060, 1, 2, 9);
        RoofP(w, 1060, 6, 4, 9);
        A(w, 2050, 3, 8);
        RoofP(w, i2_len + a_len - 200, 1, 2, 8.5);
        RoofP(w, i2_len + a_len - 200, 6, 4, 8.5);
        RoofP(w, i2_len + a_len + a_len - 200, 1, 2, 8);
        RoofP(w, i2_len + a_len + a_len - 200, 6, 4, 8);
    }
}
