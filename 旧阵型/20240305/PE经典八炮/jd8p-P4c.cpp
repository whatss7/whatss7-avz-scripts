#include "../whatss7-avz2-lib/walib.h"

void AScript(){
    WAInit({APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, APUMPKIN});
    WAAutoManageCob();
    WAFixNuts();
    waForEndIgnore = { AXG_24, AKG_17, APJ_0, ALZ_2 };
    
    // P4: ccccPP|ccccPP|ccccPP|ccccPP (875, 875, 875, 875)
    for (int w: WaveList(1, 20)) {
        // cccc
        AConnect(ATime(w, 140), [](){
            const APlantType plants[] = {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT};
            int ptr = 0;
            bool hasDance[6];
            memset(hasDance, 0, sizeof(hasDance));
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Type() == AWW_8) hasDance[zombie.Row()] = true;
            }
            for (int i = 0; i < 6; i++) {
                if (hasDance[i]) {
                    ACard(plants[ptr], i + 1, 9);
                    ptr += 1;
                }
            }
        });
        // remove cards
        AConnect(ATime(w, 240), [](){
            ARemovePlant(1, 9);
            ARemovePlant(2, 9);
            ARemovePlant(5, 9);
            ARemovePlant(6, 9);
        });
        // PP
        PP(w, 875 - 200, 8.5);
        if (w == 9 || w == 19 || w == 20) {
            PPForEnd(w, 1750 - 200);
            PPForEnd(w, 2625 - 200);
        }
    }
}