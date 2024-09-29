#include "../walib.h"
#include "mod/mod.h"
#include "DanceCheat/DanceCheat.h"

ACobManager wind, flat, intercept;
APlantFixer flowerPotFixer, pumpkinFixer;

void AScript() {
    Init({ 
        AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ADOOM_SHROOM, ACHERRY_BOMB, 
        AJALAPENO, AFLOWER_POT, APUMPKIN, AKERNEL_PULT, ACOB_CANNON
    });
    wind.SetList({{1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}});
    flat.SetList({{5, 5}});
    StartIceFiller({{1, 1}, {3, 1}, {5, 1}});
    AConnect(ATime(1, -599), [](){
        pumpkinFixer.Start(APUMPKIN, {{5, 4}}, 4000 / 3 * 2);
    });
    UnlimitedSun(ModState::SCOPED_ON);
    StartReloadMode();
    const int i_len = 1782;
    for (int w: {1}) {
        C(w, -599 + 51, {AFLOWER_POT, ADOOM_SHROOM}, 4, 5);
        P(w, 401, 2, 8.675, wind);
        P(w, 401, 4, 8.675, wind);
        D(w, 401 + 107, 2, 7.4125, wind);
        D(w, 401 + 107, 4, 7.4125, wind);
        // 铲种风炮
        AConnect(ATime(w, 401 + 107 - 146), [](){
            wind.FixLatest();
        });
    }
    for (int w: {10}) {
        P(w, 401, 2, 8.675, wind);
        P(w, 401, 4, 9.0875, wind);
        D(w, 401 + 107, 2, 7.4125, wind);
        C(w, 401 + 204 - ADT, { AFLOWER_POT, APUMPKIN, ACHERRY_BOMB }, 4, 4);
        C(w, 401 + 204 - ADT + 3001, APUMPKIN, 3, 1);
        // 铲种风炮
        AConnect(ATime(w, 401 + 107 - 146), [](){
            wind.FixLatest();
        });
        AConnect(ATime(9, 401 + 204 - ADT + 3001 * 2), [](){
            pumpkinFixer.Start(APUMPKIN, {{5, 4}}, 4000 / 3 * 2);
        });
    }
    for (int w: {2, 5, 8, 13, 16, 19}) {
        I3(w, w > 10 ? 11 : 12, w == 2 ? 601 : i_len);
        if (w > 10) {
            C(w, -29, {AFLOWER_POT, ADOOM_SHROOM}, {{2, 4}, {3, 4}, {2, 5}, {3, 5}});
            C(w, 11 + 770 - 298, ACOFFEE_BEAN, {{2, 4}, {3, 4}, {2, 5}, {3, 5}});
        }
        if (w != 19) {
            P(w, i_len - 200, 2, 8.625, wind);
            P(w, i_len - 200, 4, 8.625, wind);
            D(w, i_len - 200 + 320, 2, 5, flat);
            A(w, i_len - 200 + 230, 4, 7);
            if (w > 10) {
                C(w, i_len  - 200 + 230 - ADT + 751, AFLOWER_POT, 5, 6);
                AConnect(ATime(w, i_len - 200 + 212 - 146), [](){
                    flat.FixLatest();
                });
            }
        } else {
            EnsureZombieExist(w, AHY_32, 4);
            J(w, 1484, 5, 1);
            PS(w, 1494, 5, 8.675, wind);
            A(w, 1494 + 110, 5, 9);
            P(w, 1720, 2, 8.3, flat);
            D(w, 1714 + 222, 2, 7.1625, wind);
            AConnect(ATime(w, 1714 - 164), [](){
                flat.FixLatest();
            });
            C(w, 1494 + 110 - ADT + 751, AFLOWER_POT, 5, 6);
            AConnect(ATime(w, 1494 + 110 - ADT + 751 * 2), [](){
                flowerPotFixer.Start(AFLOWER_POT, {{4, 4}, {4, 5}, {4, 6}, {4, 7}});
            });
            // 5路清场；123路w8剩1，w9剩3；4路w9剩1
            P(w, 3276, 2, 6.5, wind);
            P(w, 3276, 2, 6.5, wind);
            D(w, 3312, 2, 6.5, flat);
            P(w, 4969, 4, 6.5, wind);
            AConnect(ATime(w, 4969 + 3), [](){
                flowerPotFixer.Stop();
                ARemovePlant(4, 4, APUMPKIN);
                ARemovePlant(4, 4, AFLOWER_POT);
                ARemovePlant(4, 5, AFLOWER_POT);
                ARemovePlant(4, 6, AFLOWER_POT);
                ARemovePlant(4, 7, AFLOWER_POT);
            });
        }
    }
    for (int w: {3, 6, 9, 12, 15, 18}) {
        if (w == 18) EnsureZombieExist(w, ACG_3, 3);
        I(w, 12, w == 2 ? 601 : i_len);
        if (w != 9) {
            // 炸25解决扶梯问题
            P(w, i_len - 200, 2, 8.625, wind);
            P(w, i_len - 200, 5, 8.625, wind);
        } else {
            EnsureZombieExist(w, AHY_32, 1);
            // (J-x/PS-N-D/x)-(PD/P) x表示无操作
            // 12路垫材拖延，等到下波尾炸一同炸掉
            J(w, 1360, 3, 1);
            PS(w, 1360 + 133, 4, 8.675, wind);
            N(w, 1360 + 133 + 216, 3, 7);
            D(w, 1360 + 133 + 216 + 220, 2, 7.175, wind);
            C(w, 2162, AFLOWER_POT, 5, 7);
            AConnect(ATime(w, 2163), [](){
                flowerPotFixer.Start(AFLOWER_POT, {{1, 4}, {2, 5}, {1, 5}, {2, 6}});
            });
            // 3路清场；12路w8剩1，w9剩3；45路w9剩1
            P(w, 3276, 2, 6.6125, wind);
            P(w, 3276 + 107, 2, 6.1625, wind);
            D(w, 3591, 4, 6.8, flat);
            C(w, 4300 - CBT - ADT, ACOFFEE_BEAN, 4, 5);
            AConnect(ATime(w, 4300), [](){
                flowerPotFixer.Stop();
                ARemovePlant(5, 7, AFLOWER_POT);
                ARemovePlant(1, 4, AFLOWER_POT);
                ARemovePlant(2, 5, AFLOWER_POT);
                ARemovePlant(1, 5, AFLOWER_POT);
                ARemovePlant(2, 6, AFLOWER_POT);
            });
        }
        AConnect(ATime(9, 1), [](){
            pumpkinFixer.Stop();
        });
    }
    for (int w: {4, 7, 11, 14, 17}) {
        I3(w, w < 10 ? 11 : 12, w == 11 ? 601 : i_len);
        if (w == 4) {
            C(w, -29 + 345, {AFLOWER_POT, ADOOM_SHROOM}, {{2, 4}, {3, 4}, {2, 5}, {3, 5}});
            C(w, 11 + 770 - 298, ACOFFEE_BEAN, {{2, 4}, {3, 4}, {2, 5}, {3, 5}});
        } else if (w == 7) {
            C(w, -29, {AFLOWER_POT, ADOOM_SHROOM}, {{2, 4}, {3, 4}, {2, 5}, {3, 5}});
            C(w, 11 + 770 - 298, ACOFFEE_BEAN, {{2, 4}, {3, 4}, {2, 5}, {3, 5}});
        }
        P(w, i_len - 200, 2, 8.625, wind);
        P(w, i_len - 200, 4, 8.625, wind);
        D(w, i_len - 200 + 220, 2, 7.4, wind);
        D(w, i_len - 200 + 227, 4, 7.4, flat);
        // w7 1648 铲种，下次 w9 3085 
        if (w < 10) {
            AConnect(ATime(w, i_len - 200 + 212 - 146), [](){
                flat.FixLatest();
                ACard(AFLOWER_POT, 5, 6);
            });
        }
    }

    for (int w: {20}) {
        EnsureZombieExist(w, AHY_32, 1);
        I(w, 125);
        P(w, 400, 4, 3.1125, wind);
        RM(w, 400 + 3, APUMPKIN, 3, 1);
        P(w, 1050, 2, 9.55, wind);
        N(w, 1050 + 298, 2, 8);
        D(w, 1050 + 298 + 239, 2, 8.6875, wind);
        D(w, 1050 + 298 + 239, 4, 8.6875, wind);
        D(w, 1050 + 298 + 239 + 236, 4, 8.6875, flat);
        // 烧掉不好处理的5列巨人，炸24路巨人
        J(w, 2114, 5, 1);
        P(w, 3199, 3, 7.6125, wind);
        AConnect(ATime(w, 1583), [](){
            flowerPotFixer.Start(AFLOWER_POT, {{1, 4}, {1, 5}, {1, 6}, {1, 7}});
        });
        P(w, 5500, 1, 5.25, flat);
        AConnect(ATime(w, 5500), [](){
            flowerPotFixer.Stop();
            ARemovePlant(1, 4, AFLOWER_POT);
            ARemovePlant(1, 5, AFLOWER_POT);
            ARemovePlant(1, 6, AFLOWER_POT);
            ARemovePlant(1, 7, AFLOWER_POT);
        });
    }
}
