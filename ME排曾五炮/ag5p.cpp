#include "../walib.h"
#include "mod/mod.h"

void AScript() {
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, AFLOWER_POT, ADOOM_SHROOM, ACHERRY_BOMB,
        AJALAPENO, AKERNEL_PULT, ACOB_CANNON, AUMBRELLA_LEAF, APUMPKIN
    });
    UnlimitedSun(ModState::SCOPED_ON);
    AutoFixNuts();
    const int i_len = 1527, n_len = 746;
    C(1, -599, AFLOWER_POT, 2, 1);
    C(1, -599 + 751, { AFLOWER_POT, AUMBRELLA_LEAF }, 3, 1);
    C(1, -599 + 751 + 751, AFLOWER_POT, 4, 1);

    // 第三加速波 PP
    for (int w: {1, 6, 13, 18, 20}) {
        if (w != 20) ASetWavelength({ATime(w, 601)});
        // 屋顶具体分离时间不清楚，选择在落地瞬间修补，此处铲种的使用时间非常宽松
        AConnect(ATime(w, 401), [](){
            waRoofCobManager[2].FixLatest();
        });
        if (w != 20) {
            PP(w, 401, 8.7125);
        } else {
            P(w, 401, 2, 8.7125);
            P(w, 401, 4, 9.2125);
            // 收尾I-PP
            WhiteI(w, 601 + 1, 2, 1);
            PP(w, 601 + i_len - 200, 8.9, {2, 5});
            // 收尾I-PP
            BlueI(w, 601 + i_len + 11, 2, 1, 601);

            RM(w, 601 + i_len + 12, AFLOWER_POT, 2, 1);
            MultiRM(w, 601 + i_len + 12, { AUMBRELLA_LEAF, AFLOWER_POT }, 3, 1);
            RM(w, 601 + i_len + 12, AFLOWER_POT, 4, 1);
            RM(w, 601 + i_len + 12, AFLOWER_POT, 5, 1);

            PP(w, 601 + i_len + i_len - 200, 8.9);
            // 收尾PA，A提前把花盆留给下一波
            P(w, 601 + i_len + i_len + 401, 2, 7.45);
            A(w, 601 + i_len + i_len + 401 - 250, 4, 8);
        }
    }

    // 第一冰波 I-PP
    for (int w: {2, 7, 14, 19}) {
        if (w != 19) ASetWavelength({ATime(w, i_len)});
        WhiteI(w, 1, 2, 1, 601);
        // 炸25路，收上波撑杆，放过3路撑杆和部分橄榄给下一波收
        PP(w, i_len - 200, 8.7125, {2, 5});
        if (w == 19) {
            // 收尾I-PP
            BlueI(w, i_len + 11, 2, 1);
            PP(w, i_len + i_len - 200, 8.6875);
            // 收尾PA
            P(w, i_len + i_len + 401, 2, 7.45);
            J(w, i_len + i_len + 276, 5, 1);
            A(w, i_len + i_len + 396, 5, 8);
            // 收尾N
            N(w, i_len + i_len + 601 + n_len - 200, 4, 7);
        }
    }
    for (int w: {3, 8, 10, 15}) {
        ASetWavelength({ATime(w, i_len)});
        // w3漏的撑杆在N波可收，w10漏的撑杆在PA波可收
        // 其他波会漏一堆，但1-4路不漏扶梯小丑，在PA波可收
        if (w == 3) {
            BlueI(w, 11, 2, 1, 601);
            // 右移炸点收小丑
            PP(w, i_len - 200, 8.7125);
        } else if (w != 10) {
            BlueI(w, 11, 2, 1, 601);
            TempC(w, 965, AFLOWER_POT, 5, 6, 1050);
            // 左移炸点多收一点点巨人
            PP(w, i_len - 200, 8.6875);
        } else {
            BlueI(w, 1, 2, 1, 601);
            P(w, i_len - 200, 2, 8.7125);
            // 进一步右移炸点收旗帜波靠右小丑
            P(w, i_len - 200, 4, 9.2125);
            TempC(w, 300 - 751, AUMBRELLA_LEAF, 2, 5, 400);
            TempC(w, 300, AUMBRELLA_LEAF, 4, 5, 400);
            C(w, 300 + 751, AFLOWER_POT, 5, 1);
        }
    }
    for (int w: {4, 9, 11, 16}) {
        if (w != 9) ASetWavelength({ATime(w, 601)});
        if (w == 4) {
            // P炸5防止漏炸N波巨人
            // w3不会漏炸小丑，A可以放4路
            P(w, 401, 2, 8.675);
            J(w, 276, 4, 1);
            A(w, 396, 4, 9);
        } else if (w == 9) {
            // 为收巨人漏炸5路小丑，此处2路放樱桃
            P(w, 401, 5, 8.675);
            J(w, 276, 2, 1);
            A(w, 396, 2, 9);
            // 收尾N
            N(w, 601 + n_len - 200, 2, 7);
            // 收尾PP
            PP(w, 601 + n_len + 401, 8.675);
            // 收尾I-PP，PP左移因为没有下一个冰让曾打io了
            WhiteI(w, 601 + n_len + 601 + 1, 2, 1);
            PP(w, 601 + n_len + 601 + i_len - 200, 7.45);
        } else if (w == 11 || w == 16) {
            // 为收巨人漏炸小丑，此处2路放樱桃
            P(w, 401, 5, 8.675);
            J(w, 276, 2, 1);
            A(w, 396, 2, 9);
        }
    }
    for (int w: {5, 12, 17}) {
        ASetWavelength({ATime(w, n_len)});
        if (w == 5) N(w, 546, 4, 8);
        if (w == 12) N(w, 546, 3, 7);
        if (w == 17) N(w, 546, 2, 8);
    }
}