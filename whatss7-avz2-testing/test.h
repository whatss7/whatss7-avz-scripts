#include "../walib.h"
#include "mod/mod.h"

Mod ForbidEnterHome {
    {0x52b308, '\x90', '\x74'},
    {0x52b309, '\x90', '\x07'},
};

void UnifyFlags() {
    std::set<AZombieType> exclude_zombie_list = { AQZ_1, ACG_3, ABC_12, ABJ_20, ATL_22, ABY_23, AHY_32 };
    for (int w: {10, 20}) {
        AConnect(ATime(w, 1), [=](){
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Type() == AQZ_1 || zombie.Type() == ABJ_20) zombie.State() = 3;
                if (zombie.ExistTime() > 100) continue;
                if (exclude_zombie_list.find((AZombieType)zombie.Type()) != exclude_zombie_list.end()) continue;
                zombie.Abscissa() -= 40;
            }
        });
    }
}

// 植物无敌（可通过参数取消），禁用特殊进攻，免费种植，立刻装填，进家不食脑，旗帜波常规化
void CommonTesting(bool invincible = true) {
    if(invincible) PlantInvincible(ModState::SCOPED_ON);
    DisableSpecialAttack(ModState::SCOPED_ON);
    FreePlantingCheat(ModState::SCOPED_ON);
    CobInstantRecharge(ModState::SCOPED_ON);
    ForbidEnterHome(ModState::SCOPED_ON);
    UnifyFlags();
}

void InstantKill() {
    for (auto &&zombie: aAliveZombieFilter) {
        zombie.State() = 3;
    }
}
