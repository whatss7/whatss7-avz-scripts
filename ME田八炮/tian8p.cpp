// #define WALIB_DEBUG
#include "../whatss7-avz2-lib/walib.h"

ATickRunner slowGigaRunner;

std::map<AZombie*, std::deque<int>> lastState;

void SlowGiga() {
    if (!AGetSeedPtr(AFLOWER_POT) || !AGetSeedPtr(AFLOWER_POT)->IsUsable()) return;
    AZombie *fastestGiga = nullptr;
    for (auto &&zombie: aAliveZombieFilter) {
        // if (ANowTime().time == 1) waDebugLogger.Info(std::to_string(zombie.AtWave()));
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
        // ICE3取消投掷时，有几帧state会变回0，因此记录上帧状态，刚完成投掷的也不垫
        if (!lastState[&zombie].empty() && (lastState[&zombie].front() == 69 || lastState[&zombie].front() == 70)) continue;
        if (lastState[&zombie].size() > 16) lastState[&zombie].pop_front();
        if (!fastestGiga || zombie.Abscissa() < fastestGiga->Abscissa()) {
            fastestGiga = &zombie;
        }
    }
    // 巨人锤得到八列植物，且本路没有冰车碾压的话，垫
    if (fastestGiga && fastestGiga->Abscissa() < 670 && !(WAExistZombie(ABC_12, {fastestGiga->Row() + 1}) && ANowTime().time >= 653)) {
        int row = fastestGiga->Row() + 1;
        ACard(AFLOWER_POT, row, 8);
        AConnect(ANowDelayTime(100), [row](){ ARemovePlant(row, 8); });
    }
}

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, AFLOWER_POT, ACHERRY_BOMB});
    // 对C8u: I-PP|PP|PP|I-PP|PP|PP (1253, 746, 746, 1253, 746, 746)

    // w1-w9: I-PP|PP|PP|I-PP|PP|PP|I-PP|PP|PP
    // w10-w19: PP(601)|I-PP|PP|PP|I-PP|PP|PP|I-PP|PP|PP
    // w20: PP

    C(1, -599, AFLOWER_POT, 3, 3);
    AConnect(ATime(1, -599), [](){
        lastState.clear();
        slowGigaRunner.Start(SlowGiga);
    });
    // 给毁灭菇留花盆
    AConnect(ATime(20, -500), [](){ slowGigaRunner.Stop(); });
    AConnect(ATime(20, 401), [](){
        lastState.clear();
        slowGigaRunner.Start(SlowGiga);
    });
    for (int w: {1, 4, 7, 11, 14, 17}) {
        ManualI3(w, 11, 3, 3, w == 11 ? 601 : 746);
        PP(w, 1053, 8.5);
    }
    for (int w: {2, 5, 8, 12, 15, 18}) {
        PP(w, 546, 8.75);
    }
    for (int w: {3, 6, 9, 13, 16, 19}) {
        PP(w, 546, 8.75);
        if (w == 9 || w == 19) {
            // 在判断需要收尾时立刻点冰
            AConnect(ATime(w, 1), [w](){
                if (WAExistZombie(AHY_32)) {
                    ManualI3(w, 746 + 11, 3, 3);
                }
            });
            PPForEnd(w, 546 + 1253);
            PPForEnd(w, 546 + 1253 + 746);
            PPForEnd(w, 546 + 1253 + 746 + 746);
        }
    }
    for (int w: {10}) {
        PP(w, 401);
        SmartA();
    }
    for (int w: {20}) {
        ZomboniN(w, 409, 3, 9);
        ManualI(w, 420, 3, 3);
        PP(w, 750, 7);
        PPForEnd(w, 409 + 1253);
        PPForEnd(w, 409 + 1253 + 746);
        PPForEnd(w, 409 + 1253 + 746 + 746);
    }
}