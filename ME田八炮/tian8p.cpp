#include "../walib.h"

void SlowGiga(int wave, int time) {
    AConnect(ATime(wave, time), [](){
        if (!AGetSeedPtr(AFLOWER_POT) || !AGetSeedPtr(AFLOWER_POT)->IsUsable()) return;
        AZombie *fastestGiga = nullptr;
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.Type() != AHY_32) continue;
            // 巨人最早命中7列炮1566cs
            // 冰波红眼在3798cs解决，11cs和2756cs被冰，冻结时间700cs
            // 等效原速前进时间为1544cs，不会锤炮
            // 因此，只用垫加速波产生的红眼
            // 且3路红眼不需要垫
            if (zombie.Row() + 1 == 3) continue;
            if (((zombie.AtWave() + 1) % 10) % 3 == 1) continue;
            // 巨人若是被冻结，在投掷小鬼或举锤，垫了也没用
            if (zombie.State() == 69 || zombie.State() == 70 || zombie.FreezeCountdown() != 0) continue;
            if (!fastestGiga || zombie.Abscissa() < fastestGiga->Abscissa()) {
                fastestGiga = &zombie;
            }
        }
        // 若巨人锤得到八列植物，垫
        if (fastestGiga && fastestGiga->Abscissa() < 670) {
            int row = fastestGiga->Row() + 1;
            ACard(AFLOWER_POT, row, 8);
            AConnect(ANowDelayTime(100), [row](){ ARemovePlant(row, 8); });
        }
    });
}


void AScript() {
    Init({AICE_SHROOM, AM_ICE_SHROOM, AFLOWER_POT, ACHERRY_BOMB});

    // 对C8u: I-PP|PP|PP|I-PP|PP|PP (1253, 746, 746, 1253, 746, 746)
    const int ice_len = 1253;
    const int a_len = 746;

    C(1, -599, AFLOWER_POT, 3, 3);
    for (int w: {1, 4, 7, 11, 14, 17}) {
        ManualI3(w, 11, 3, 3, w == 11 ? 601 : a_len);
        PP(w, ice_len - 200, 8.65);
        // 653冰车碾压，611全部巨人解冻
        SlowGiga(w, ice_len - 200 + 10);
    }
    for (int w: {2, 5, 8, 12, 15, 18}) {
        PP(w, a_len - 200, 8.8125);
        SlowGiga(w, a_len - 200 + 20);
    }
    for (int w: {3, 6, 9, 13, 16, 19}) {
        PP(w, a_len - 200, 8.8125);
        SlowGiga(w, a_len - 200 + 30);
        if (w == 9 || w == 19) {
            AConnect(ATime(w, 1), [w](){
                if (ExistZombie(AHY_32)) {
                    ManualI3(w, a_len - 200 + 210, 3, 3);
                }
            });
            PPForEnd(w, ice_len + a_len - 200);
            SlowGiga(w, ice_len + a_len - 200 + 10);
            PPForEnd(w, ice_len + a_len * 2 - 200);
            SlowGiga(w, ice_len + a_len * 2 - 200 + 20);
            PPForEnd(w, ice_len + a_len * 3 - 200);
        }
    }
    for (int w: {10}) {
        PP(w, 401);
        SmartA();
    }
    for (int w: {20}) {
        ZomboniN(w, 409, 3, 9);
        ManualI(w, 409, 3, 3);
        PP(w, 750, 7);
        PPForEnd(w, 409 + ice_len);
        SlowGiga(w, 409 + ice_len);
        PPForEnd(w, 409 + ice_len + a_len);
        SlowGiga(w, 409 + ice_len + a_len);
        PPForEnd(w, 409 + ice_len + a_len * 2);
    }
}