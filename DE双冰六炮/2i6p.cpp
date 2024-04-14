#include "../walib.h"

ATickRunner slowGigaRunner;

void AScript(){
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, ADOOM_SHROOM,
        APUMPKIN, APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT
    });
    aIceFiller.Start({{1, 1}, {5, 1}});
    AutoFixNuts();

    // ch5: I-PP|I-PP|PP (15, 15, 6)
    const int i_len = 1500;

    // I-PP 第一冰波
    for (int w: {3, 6, 9, 11, 13, 16, 19}) {
        I(w, 1, 601);
        PP(w, i_len - 200, 8.6);
        if (w == 9 || w == 19) {
            PP(w, i_len + i_len - 200, 8.5);
            PP(w, i_len + i_len + 601 - 200, 8.5);
            AConnect(ATime(w, 2805), [](){
                slowGigaRunner.Start([](){
                    for (APlantType plant: { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT }) {
                        if (!AGetSeedPtr(plant) || !AGetSeedPtr(plant)->IsUsable()) continue;
                        AZombie *fastestGiga = nullptr;
                        for (auto &&zombie: aAliveZombieFilter) {
                            // 不是红眼不垫
                            if (zombie.Type() != AHY_32) continue;
                            // 巨人若是在投掷小鬼或举锤，垫了也没用
                            if (zombie.State() == 69 || zombie.State() == 70) continue;
                            // 求得以上条件下最快的僵尸
                            if (!fastestGiga || zombie.Abscissa() < fastestGiga->Abscissa()) {
                                fastestGiga = &zombie;
                            }
                        }
                        // 若巨人锤得到七列植物，垫
                        if (fastestGiga && fastestGiga->Abscissa() < 595) {
                            int row = fastestGiga->Row() + 1;
                            ACard(plant, row, 7);
                        }
                        return;
                    }
                });
            });
            AConnect(ATime(w + 1, PCP), [](){
                slowGigaRunner.Stop();
                ARemovePlant(1, 7, { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT });
                ARemovePlant(2, 7, { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT });
                ARemovePlant(3, 7, { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT });
                ARemovePlant(4, 7, { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT });
                ARemovePlant(5, 7, { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT });
            });
        }
    }

    // I-PP 第二冰波
    for (int w: {4, 7, 14, 17}) {
        I(w, 1, i_len);
        PP(w, i_len - 200, 8.6);
    }

    // PP
    for (int w: {1, 2, 5, 8, 10, 12, 15, 18, 20}) {
        PP(w);
        if (w == 20) {
            I(w, 601 + 1);
            PP(w, 601 + i_len - 200, 8.5);
            PP(w, 601 + i_len + i_len - 200, 8.5);
        }
    }
}