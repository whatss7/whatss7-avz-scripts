#include "../whatss7-avz2-lib/walib.h"

ATickRunner stopGigaRunner;

bool ExistNewGiga() {
    for (auto &&zombie: aAliveZombieFilter) {
        if (zombie.Type() == AHY_32 && zombie.Hp() > 5400) return true;
    }
    return false;
}

void StopGiga(int row) {
    int min_x = 1000;
    for (auto &&zombie: aAliveZombieFilter) {
        if (zombie.Type() != AHY_32) continue;
        if (zombie.Row() != row - 1) continue;
        if (zombie.Abscissa() < min_x) {
            min_x = zombie.Abscissa();
        }
    }
    APosition grid_to_stop = {
        row, floorf((min_x + 40) / 80.0f)
    };
    std::vector<APlantType> plants_to_stop = {
        APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT
    };
    if (!WAExistPlant(plants_to_stop, grid_to_stop.row, grid_to_stop.col)) {
        for (APlantType plant: plants_to_stop) {
            if (AGetSeedPtr(plant) && AGetSeedPtr(plant)->IsUsable()) {
                ACard(plant, {grid_to_stop});
                break;
            }
        }
    }
}

int gigaEnd_row;

bool toRefresh(int wave) {
    int currentHp = 0;
    for (auto&& zombie : aAliveZombieFilter) {
        if (zombie.AtWave() == wave && //
            !ARangeIn(zombie.Type(), {ABACKUP_DANCER, ABUNGEE_ZOMBIE})) {
            currentHp += zombie.Hp() + zombie.OneHp() + zombie.TwoHp() / 5;
        }
    }
    int refreshHp = AGetMainObject()->ZombieRefreshHp();
    return currentHp < refreshHp;
}

// 清理多余红眼，然后拖住最后一个红眼。
void GigaEnd(int wave, int time, int to_time = 4300) {
    AConnect(ATime(wave, time - 387), [time](){
        int dist[6] = { 0, 0, 0, 0, 0, 0 };
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.Type() != AHY_32) continue;
            if (zombie.Hp() < 0) continue;
            dist[zombie.Row()]++;
        }
        gigaEnd_row = 5;
        if (dist[0] == 1) {
            PP(ANowTime().wave, time, 8.5, {3, 5});
            gigaEnd_row = 1;
        } else if (dist[5] == 1) {
            PP(ANowTime().wave, time, 8.5, {2, 4});
            gigaEnd_row = 6;
        } else if (dist[0] == 0 && dist[1] == 1) {
            P(ANowTime().wave, time, 5, 8.5);
            gigaEnd_row = 2;
        } else if (dist[5] == 0 && dist[4] == 1) {
            P(ANowTime().wave, time, 2, 8.5);
            gigaEnd_row = 5;
        } else if (dist[0]) {
            PP(ANowTime().wave, time, 8.5, {3, 5});
            gigaEnd_row = 1;
        } else if (dist[5]) {
            PP(ANowTime().wave, time, 8.5, {2, 4});
            gigaEnd_row = 6;
        } else if (dist[1]) {
            P(ANowTime().wave, time, 5, 8.5);
            gigaEnd_row = 2;
        }
    });
    AConnect(ATime(wave, time + 1), [](){
        stopGigaRunner.Start([](){ StopGiga(gigaEnd_row); });
        AMaidCheats::Dancing();
    });
    AConnect(ATime(wave, to_time - 387), [wave, to_time](){
        int min_x = 1000, min_x_row = 0;
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.Type() != AHY_32) continue;
            if (zombie.Abscissa() + zombie.AttackAbscissa() < min_x) {
                min_x = zombie.Abscissa() + zombie.AttackAbscissa();
                min_x_row = zombie.Row();
            }
        }
        P(wave, to_time, min_x_row + 1, floorf((min_x + 40) / 80.0f));
    });
    AConnect(ATime(wave, to_time - 1), [](){
        stopGigaRunner.Stop();
        AMaidCheats::Stop();
        ARemovePlant(gigaEnd_row, 7, { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT });
        ARemovePlant(gigaEnd_row, 8, { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT });
        ARemovePlant(gigaEnd_row, 9, { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT });
    });
}

void StolenSun() {
    // 有红眼时不能偷花，如果还有撑杆就还要把前场花铲了
    if (AGetZombieTypeList()[AHY_32]) {
        if (AGetZombieTypeList()[ACG_3]) {
            AConnect(ATime(3, 135), [](){
                ARemovePlant(1, 7, ASUNFLOWER);
                ARemovePlant(2, 7, ASUNFLOWER);
                ARemovePlant(5, 7, ASUNFLOWER);
                ARemovePlant(6, 7, ASUNFLOWER);
            });
        }
        return;
    }
    std::vector<AGrid> SunPlace = {{1, 7}, {2, 7}, {5, 7}, {6, 7}};
    // 无白眼时，七列可以偷花，但要留下寒冰菇位置
    if (!AGetZombieTypeList()[ABY_23]) {
        SunPlace.push_back({2, 4});
        SunPlace.push_back({5, 4});
        SunPlace.push_back({6, 4});
    }
    aPlantFixer.Start(ASUNFLOWER, SunPlace);
}

void AScript() {
    #define NATURAL_MODE 1
    #if NATURAL_MODE
    if (AGetZombieTypeList()[AHY_32]) {
        WASelectCards({
            AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ALILY_PAD, ACOFFEE_BEAN, 
            APUMPKIN, APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT
        }, true);
    } else {
        WASelectCards({
            AICE_SHROOM, ALILY_PAD, ACOFFEE_BEAN, ASUNFLOWER
        }, true);
    }
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    ASetGameSpeed(10);
    // WARecordWaves();
    // WACheck();
    #else
    WAInit({
        AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ALILY_PAD, ACOFFEE_BEAN, 
        APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, APUMPKIN
    });
    #endif
    WAAutoManageCob();
    StolenSun();
    // 存在红眼时，使用S6节奏；否则，使用P6节奏。
    if (AGetZombieTypeList()[AHY_32]) {
        // S6: I-PP|PP|PPDD|PP|PP (11.5, 6, 6, 6, 6)
        // 所有红眼需要在3波内被冻一次或3波内补炸一次才能解决
        // 第三波被冻的红眼，1350cs被冻，存活2628cs，最早命中1350+400冻结+(1997-1350)*2减速=3044cs，可以解决
        // 第三波补炸的红眼，存活1583cs，最早命中1997cs，可以解决
        // 由此，此循环全收红眼守6列炮
        // 由于有8列炮，冰波为防丑只能是1149cs；转对C9u是因为冰波想严谨不炸的话，旗帜波的PPNdd在下一次需要PPDD时无法转好。
        // 此外，冰波要全伤巨人，否则w9收尾时不同波次巨人混淆会导致问题，所以
        // w1-w9: PP|PP|I-PP|PP|PPDD|PP|PP|I-PP|PP-PPDD-PP-P
        // w10-w19: PPNdd|PP|PP|I-PP|PP|PPDD|PP|PP|I-PP|NDD-PP-PP
        // w20: Idd-PP-PP-PP-PP

        // w9无红眼时，改用PP-PP(12s)
        // w19无红眼时，改用PPN-PP(12s)

        // 加速波；w9, w19, w20收尾需要各自特殊处理
        for (int w: WaveList(1, 8) + WaveList(10, 18)) {
            if (w == 3 || w == 8 || w == 13 || w == 18) continue;
            PP(w);
            // w5/w15 空炸
            if (w == 5 || w == 15) PP(w, PCAP + 110, 8.7, {1, 5});
            // w10 点核+炸蹦极，或者没有蹦极就PPSS
            if (w == 10) {
                if (AGetZombieTypeList()[ABJ_20]) {
                    N(w, 400, {{3, 9}, {4, 9}});
                    PP(w, 400, 2);
                } else {
                    PP(w, 400);
                }
            }
        }
        // 冰波
        for (int w: {3, 8, 13, 18}) {
            ManualI(w, 135, 1, 4, 601, 1);
            PP(w, 1149 - 200);
        }
        // w9: PP-PPDD-PP-P
        for (int w: {9}) {
            PP(w);
            AConnect(ATime(w, 1), [w](){
                if (ExistNewGiga()) {
                    PP(w, 1000, 8.75);
                    PP(w, 1000 + 110, 8.7, {1, 5});
                    GigaEnd(w, 1600);
                } else {
                    PP(w, 1000);
                    PPForEnd(w, 1600);
                }
            });
        }
        // w19: NDD-PP-PP
        for (int w: {19}) {
            N(w, PCAP, {{3, 9}, {4, 9}});
            AConnect(ATime(w, 1), [w](){
                if (ExistNewGiga()) {
                    PP(w, PCAP + 110, 8.7, {1, 5});
                    PP(w, 1000);
                    PP(w, 1600);
                } else {
                    PP(w, PCAP + 250, 3);
                    PP(w, 1000);
                    PPForEnd(w, 1600);
                }
            });
        }
        // w20 应该必有红眼
        for (int w: {20}) {
            ManualI(w, 135, 1, 4, -1, 1);
            if (AGetZombieTypeList()[ABJ_20]) PP(w, 400, 2);
            PP(w, 949);
            PP(w, 1600);
            PP(w, 1600 + 220, 8.75, {1, 5});
            PP(w, 2200, 8.75);
            // 漏炸舞王的情况
            PPForEnd(w, 3400, 8.5);
        }
    } else {
        // 有蹦极的话，需要分一炮出来解决蹦极
        // P6: PP|PP|PP|PP|PP|PP
        // w1-w9: PP|PP|PP|PP|PP|PP|PP|PP|PP
        // w10-w19: Ndd|PP|PP|PP|PP|PP|PP|PP|PP|PP
        // w20: Idd-PP
        for (int w: WaveList(1, 9) + WaveList(11, 19)) {
            PP(w);
            if (w == 9 || w == 19) {
                PPForEnd(w, PCAP + 600);
                PPForEnd(w, 1800 - 200);
            }
        }
        for (int w: {10}) {
            if (AGetZombieTypeList()[ABJ_20]) {
                N(w, DPCAP, {{3, 9}, {4, 9}});
                PP(w, DPCAP + 124, 2.5);
            } else {
                PP(w);
            }
        }
        for (int w: {20}) {
            ManualI(w, 135, 1, 4, -1, 1);
            if (AGetZombieTypeList()[ABJ_20]) PP(w, 400, 2);
            PP(w, 1149 - 200); 
            if (w == 20) {
                PPForEnd(w, 1800 - 200);
                PPForEnd(w, 2400 - 200);
            }
        }
    }
}