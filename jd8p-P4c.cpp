#include <avz.h>
#include "whatss7-avz2-lib/walib.h"

void AScript(){
    WAInit({ASCAREDY_SHROOM, AFLOWER_POT, AGARLIC, ASUNFLOWER, APUMPKIN}, "AutoCycle");
    WAAutoManageCob();
    aPlantFixer.Start(APUMPKIN);
    aPlantFixer.SetHp(4000 / 3 * 2);
    
    // P4: ccccPP|ccccPP|ccccPP|ccccPP
    for (int w: WaveList(1, 20)) {
        AConnect(ATime(w, 200), [](){
            const APlantType plants[] = {ASCAREDY_SHROOM, AFLOWER_POT, AGARLIC, ASUNFLOWER};
            int ptr = 0;
            bool hasDance[6];
            memset(hasDance, 0, sizeof(hasDance));
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Type() == AWW_8) hasDance[zombie.Row()] = true;
            }
            for (int i = 0; i < 6; i++) {
                if (hasDance[i]) {
                    ACard(plants[ptr], i + 1, 8);
                    ptr += 1;
                }
            }
        });
        AConnect(ATime(w, 650), [](){
            ARemovePlant(1, 8);
            ARemovePlant(2, 8);
            ARemovePlant(5, 8);
            ARemovePlant(6, 8);
        });
        AConnect(ATime(w, 900 - 200 - CFT), [](){
            aCobManager.Fire({{2, 8.5}, {5, 8.5}});
        });
        if (w == 9 || w == 19 || w == 20) {
            AConnect(ATime(w, 900 - 200 - CFT), [](){
                bool hasGiga = false, hasRed = false;
                for (auto &&zombie: aAliveZombieFilter) {
                    if (zombie.Type() == ABY_23) hasGiga = true;
                    if (zombie.Type() == AHY_32) hasRed = hasGiga = true;
                }
                if (hasGiga) aCobManager.RecoverFire({{2, 8.5}, {5, 8.5}});
                if (hasRed) aCobManager.RecoverFire({{2, 8.5}, {5, 8.5}});
            });
        }
    }
}