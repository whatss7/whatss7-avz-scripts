#include "../walib.h"

void AScript() {
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, AFLOWER_POT, ACOFFEE_BEAN, AJALAPENO, ACHERRY_BOMB, AUMBRELLA_LEAF, APUMPKIN
    });
    aIceFiller.Start({{2, 1}, {4, 1}});
    AutoFixNuts();
    const int i_len = 1250, p_len = 650;
    C(1, -599, AFLOWER_POT, 3, 1);
    TempC(10, 300, AUMBRELLA_LEAF, 3, 1, 400);
    TempC(20, -500, AUMBRELLA_LEAF, 3, 7, 600);
    TempC(20, 300, AUMBRELLA_LEAF, 3, 1, 400);
    // 首代
    for (int w: {1}) {
        PP(w, 401);
        J(w, 401, 3, 1);
    }
    // 第三冰波，辣椒清理冰道
    for (int w: {6, 11, 16}) {
        I(w, 1, w == 11 ? 601 : i_len);
        PP(w, i_len - 200);
        J(w, i_len - 200, 3, 1);
    }
    // 核波，3-9点核时，樱桃护核
    for (int w: {2, 7, 12, 17}) {
        AConnect(ATime(w, -100), [](){
            auto plant = ACard(AFLOWER_POT, {{3, 9}, {3, 8}, {2, 8}, {4, 8}});
            if (plant && plant->Row() + 1 == 3 && plant->Col() + 1 == 9) {
                ACard(ACHERRY_BOMB, 3, 9);
            }
        });
        AConnect(ATime(w, PCP - ADT - CBT), [](){
            auto plant = ACard({ADOOM_SHROOM, ACOFFEE_BEAN}, {{3, 9}, {3, 8}, {2, 8}, {4, 8}});
        });
    }
    // 加速波
    for (int w: {3, 8, 13, 18}) {
        PP(w, p_len - 200);
    }
    // 第一冰波
    for (int w: {4, 9, 14, 19}) {
        I(w, 1, p_len);
        PP(w, i_len - 200);
        if (w == 9 || w == 19) {
            PP(w, i_len * 2 - 200);
            PP(w, i_len * 3 - 200);
        }
    }
    // w10首代
    for (int w: {10}) {
        PP(w, 401);
    }
    // 第二冰波
    for (int w: {5, 15}) {
        I(w, 1, i_len);
        PP(w, i_len - 200);
    }
    for (int w: {20}) {
        PP(w, 401);
        I(w, 601 + 1);
        PP(w, 601 + i_len - 200);
        PP(w, 601 + i_len * 2 - 200);
    }
}