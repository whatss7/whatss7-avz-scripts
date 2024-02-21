#include "../whatss7-avz2-lib/walib.h"

ATickRunner slowGigaRunner;

void SlowGiga() {
    if (!AGetSeedPtr(AFLOWER_POT) || !AGetSeedPtr(AFLOWER_POT)->IsUsable()) return;
    AZombie *fastestGiga = nullptr;
    for (auto &&zombie: aAliveZombieFilter) {
        if (zombie.Type() != AHY_32) continue;
        if (zombie.Row() + 1 == 3) continue;
        if (!fastestGiga || zombie.Abscissa() < fastestGiga->Abscissa()) {
            fastestGiga = &zombie;
        }
    }
    if (fastestGiga && fastestGiga->Abscissa() < 720) {
        ACard(AFLOWER_POT, fastestGiga->Row() + 1, 8);
    }
}

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, AFLOWER_POT, ACHERRY_BOMB});
    // 对C8u: I-PP|PP|PP|I-PP|PP|PP (1253, 746, 746, 1253, 746, 746)
    // 巨人最早命中7列炮1566cs
    // w1巨人在3798cs解决，0cs和2745cs被冰，冻结时间700cs
    // 等效原速前进时间为1549cs，不会锤炮
    // 因此，只用垫加速波产生的红眼
    // 且3路红眼不需要垫

    // w1-w9: I-PP|PP|PP|I-PP|PP|PP|I-PP|PP|PP
    // w10-w19: PP(601)|I-PP|PP|PP|I-PP|PP|PP|I-PP|PP|PP
    // w20: PP

    // 先只写极红脚本，后续再优化为挂机
    // w9或许需要拖收尾等待冰道恢复，w10使用核弹并炸消延迟，暂时先只使用樱桃
    // 砸率有点高，还有小丑问题，先放放
    C(1, -599, AFLOWER_POT, 3, 1);
    AConnect(ATime(1, 0), [](){ slowGigaRunner.Start(SlowGiga); });
    for (int w: {1, 4, 7, 11, 14, 17}) {
        ManualI(w, 1, 3, 1, w == 11 ? 601 : 746);
        PP(w, 1053, 8.5);
    }
    for (int w: {2, 3, 5, 6, 8, 9, 12, 13, 15, 16, 18, 19}) {
        PP(w, 546, 8.75);
    }
    for (int w: {10}) {
        PP(w, 401);
        SmartA(w, 401);
    }
    for (int w: {20}) {
        PP(w, 546, 8.75);
    }
}