#include "../walib.h"

void AScript() {
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, APUMPKIN, ADOOM_SHROOM,
        ACHERRY_BOMB, AJALAPENO, ASNOW_PEA, AKERNEL_PULT, ACOB_CANNON
    });
    StartIceFiller({{1, 1}, {5, 1}, {1, 6}, {5, 6}});
    AutoFixNuts();
    const int i_len = 1750;
    for (int w: {1}) {
        N(w, PCP, 2, 9);
        P(w, PCP + 262, 3, 2.4625);
    }
    for (int w: {2}) {
        A(w, PCP, 1, 9);
        P(w, PCP, 4, 8.7);
        P(w, PCP + 262, 3, 2.4625);
    }
    for (int w: {10}) {
        PP(w, PCP, 8.7);
        P(w, PCP + 262, 3, 2.4625);
    }
    for (int w: WaveList(3, 8) + WaveList(11, 18)) {
        I(w, 12, w == 3 || w == 11 ? 601 : i_len);
        PP(w, i_len - 200, 8.6);
        P(w, i_len - 200 + 365, 3, 2.4625);
        if (w == 8 || w == 18) {
            AConnect(ATime(w, i_len - 200 - 74), [](){
                aCobManager.FixLatest();
            });
        }
    }
    for (int w: {9, 19}) {
        // 铲种使得核可以拦截
        I(w, 12, i_len); 
        // 00100
        J(w, i_len - 200 - 110, 3, 7);
        // 22411
        PP(w, i_len - 200, 8.6, {2, 2, 4});
        // 33422
        N(w, i_len - 200 + 220, 3, 9);
        // 33433
        P(w, i_len - 200 + 220 + 220, 4, 8.6);
        // 读巨人分布决定樱桃用在哪
        AConnect(ATime(w, 1), [=](){
            std::array<int, 6> gigaCount = {0, 0, 0, 0, 0, 0};
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Type() == AHY_32 && zombie.AtWave() + 1 == w) {
                    gigaCount[zombie.Row() + 1] += 1;
                }
            }
            int upper = gigaCount[1] + gigaCount[2], lower = gigaCount[4] + gigaCount[5];
            int upperSingle = gigaCount[1] <= 1 && gigaCount[2] <= 1;
            int lowerSingle = gigaCount[4] <= 1 && gigaCount[5] <= 1;
            // 如果双边都有巨人，才在单边使用樱桃
            // 如果有一边两路都不超过一个，优先这边
            if (upper != 0 && lower != 0) {
                if ((upperSingle && !lowerSingle) || ((upperSingle == lowerSingle) && upper <= lower)) {
                    if (gigaCount[1] && gigaCount[2]) {
                        TempC(w, 1700, ASNOW_PEA, 1, 7, 4300);
                        TempC(w, 1700 + 751, ASNOW_PEA, 2, 7, 4300);
                    } else if (gigaCount[1]) {
                        TempC(w, 1700, ASNOW_PEA, 1, 7, 4300);
                    } else {
                        TempC(w, 1700, ASNOW_PEA, 2, 7, 4300);
                    }
                    A(w, 2800, 4, 7);
                } else {
                    if (gigaCount[4] && gigaCount[5]) {
                        TempC(w, 1700, ASNOW_PEA, 4, 7, 4300);
                        TempC(w, 1700 + 751, ASNOW_PEA, 5, 7, 4300);
                    } else if (gigaCount[4]) {
                        TempC(w, 1700, ASNOW_PEA, 4, 7, 4300);
                    } else {
                        TempC(w, 1700, ASNOW_PEA, 5, 7, 4300);
                    }
                    A(w, 2800, 2, 7);
                }
            } else if (upper != 0) {
                if (gigaCount[1] != 0 && gigaCount[2] != 0) {
                    A(w, 2800, 3, 7);
                    TempC(w, 1700, ASNOW_PEA, 1, 7, 4300);
                } else if (gigaCount[1] != 0) {
                    TempC(w, 1700, ASNOW_PEA, 1, 7, 4300);
                } else {
                    TempC(w, 1700, ASNOW_PEA, 2, 7, 4300);
                }
            } else if (lower != 0) {
                if (gigaCount[4] != 0 && gigaCount[5] != 0) {
                    A(w, 2800, 3, 7);
                    TempC(w, 1700, ASNOW_PEA, 5, 7, 4300);
                } else if (gigaCount[5] != 0) {
                    TempC(w, 1700, ASNOW_PEA, 5, 7, 4300);
                } else {
                    TempC(w, 1700, ASNOW_PEA, 4, 7, 4300);
                }
            }
        });
        MaidDance(w, 1770, w + 1, 0);
        MaidMove(w + 1, 1, w + 1, PCP);
    }
    for (int w: {20}) {
        PP(w, PCP, 8.7, {3, 3});
        PP(w, PCP + 110, 8.7);
        I(w, PCP + 110);
        PP(w, 1830, 8.85);
        C(w, 1, ASNOW_PEA, 1, 7);
        C(w, 1 + 751, ASNOW_PEA, 5, 7);
        AConnect(ATime(w, 1835), [=](){
            int choice = SchedulePPExceptOne(w, PCP + 3475, 8.7);
            StopGiga(w, 1835, {ASNOW_PEA, AKERNEL_PULT}, 5500, choice);
            PPLast(w, 5500);
        });
        AtEnd([](){
            ARemovePlant(1, 7);
            ARemovePlant(5, 7);
        });
    }
}