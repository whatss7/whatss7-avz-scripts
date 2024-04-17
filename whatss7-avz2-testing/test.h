#include "../walib.h"
#include "mod/mod.h"

Mod ForbidEnterHome {
    {0x52b308, '\x90', '\x74'},
    {0x52b309, '\x90', '\x07'},
};

// 植物无敌（可通过参数取消），禁用特殊进攻，免费种植，立刻装填，进家不食脑
void CommonTesting(bool invincible = true) {
    if(invincible) PlantInvincible(ModState::SCOPED_ON);
    DisableSpecialAttack(ModState::SCOPED_ON);
    FreePlantingCheat(ModState::SCOPED_ON);
    CobInstantRecharge(ModState::SCOPED_ON);
    ForbidEnterHome(ModState::SCOPED_ON);
}

void InstantKill() {
    for (auto &&zombie: aAliveZombieFilter) {
        zombie.State() = 3;
    }
}
