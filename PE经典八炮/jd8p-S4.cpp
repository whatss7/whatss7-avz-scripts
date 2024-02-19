#include "../whatss7-avz2-lib/walib.h"

void AScript(){
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, APUMPKIN});
    WAAutoManageCob();
    WAFixNuts();
    
    // S4: IPP-PP|ccccPP|ccccPP (1800, 875, 875)
    // w1-w9: PP|PP|IPP-PP|PP|PP|IPP-PP|PP|PP|IPP-PP
    // w10-w19: PP|PP|IPP-PP|PP|PP|IPP-PP|PP|PP|IPP-PP|PP
    // W20: PP

    // ccccPP
    for (int w: {1, 2, 4, 5, 7, 8, 10, 11, 13, 14, 16, 17, 19, 20}) {
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
    }

    // IPP-PP
    for (int w: {3, 6, 9, 12, 15, 18}) {
        ManualI(w, 100, 1, 1, 0, 875);
        PP(w, 600 - 200, 9);
        PP(w, 1800 - 200, 8.5);
    }
}