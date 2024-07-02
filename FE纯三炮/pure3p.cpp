#include "../walib.h"
#include "mod/mod.h"

ALogger<AConsole> logger;

APlantFixer TallNutFixer, GarlicFixer, PuffShroomFixer;

APlant *GetLowestHpPuff() {
    APlant *result = nullptr;
    for (APlant &plant: aAlivePlantFilter) {
        if (plant.Row() + 1 != 2 || plant.Type() != APUFF_SHROOM) {
            continue;
        }
        if (!result || plant.Hp() < result->Hp()) {
            result = &plant;
        }
    }
    return result;
}

APlant *GetLowestHpGarlic() {
    APlant *result = nullptr;
    for (APlant &plant: aAlivePlantFilter) {
        if (plant.Row() + 1 != 2 || plant.Type() != AGARLIC) {
            continue;
        }
        if (!result || plant.Hp() < result->Hp()) {
            result = &plant;
        }
    }
    return result;
}

// 垫材函数将综合判断各路威胁，用在威胁最大的地方。
// 威胁从大到小
//   1. 接近或超出理论最快：必须垫
//   2. 进入范围，距离较近：若2路缺失植物，优先填补；否则垫
//   3. 进入范围，距离较远：看2路植物有没有大残，若有优先修补
//   4. 未进入范围：不垫，修补2路植物

const int plant_offset = 30, fix_offset = 60;

struct FrontInfo {
    int r1f, r1b, r5, r6;
    FrontInfo(int r1f = 0, int r1b = 0, int r5 = 0, int r6 = 0): r1f(r1f), r1b(r1b), r5(r5), r6(r6) {}
};

int GetZombieFront(int row, int atwave) {
    float front = 1000;
    for (auto &zombie: aAliveZombieFilter) {
        if (zombie.Type() == AHY_32 && zombie.Row() + 1 == row && zombie.AtWave() + 1 == atwave) {
            front = std::min(front, zombie.Abscissa());
        }
    }
    return int(front);
}

struct FodderAllInfo {
    int r1_front_atwave, r1_front_fastest;
    int r1_back_atwave, r1_back_fastest;
    int r56_atwave, r56_fastest;
};

float GetFodderRow(int pos) {
    // 对2列，确保能垫到的是[96, 195] （考虑小喷偏移和巨人走的1cs）
    // 96垫2列，95垫1列
    return float((pos + 64) / 80);
}

void FixPuff() {
    int hps[9];
    memset(hps, 0, sizeof(hps));
    for (APlant &plant: aAlivePlantFilter) {
        if (plant.Row() + 1 != 2) continue;
        if (plant.Type() == APUFF_SHROOM) {
            hps[plant.Col()] = plant.Hp();
        }
    }
    if (hps[5 - 1] == 0) ACard(APUFF_SHROOM, 2, 5);
    else if (hps[6 - 1] == 0) ACard(APUFF_SHROOM, 2, 6);
    else if (hps[7 - 1] == 0) ACard(APUFF_SHROOM, 2, 7);
    else if (hps[5 - 1] < hps[6 - 1] && hps[5 - 1] < hps[7 - 1]) {
        ARemovePlant(2, 5, APUFF_SHROOM);
        ACard(APUFF_SHROOM, 2, 5);
    } else if (hps[6 - 1] > hps[7 - 1]) {
        ARemovePlant(2, 6, APUFF_SHROOM);
        ACard(APUFF_SHROOM, 2, 6);
    } else {
        ARemovePlant(2, 7, APUFF_SHROOM);
        ACard(APUFF_SHROOM, 2, 7);
    }
}

void FixGarlic() {
    int hps[9];
    memset(hps, 0, sizeof(hps));
    for (APlant &plant: aAlivePlantFilter) {
        if (plant.Row() + 1 != 2) continue;
        if (plant.Type() == AGARLIC) {
            hps[plant.Col()] = plant.Hp();
        }
    }
    if (hps[2 - 1] == 0) ACard(AGARLIC, 2, 2);
    else if (hps[3 - 1] == 0) ACard(AGARLIC, 2, 3);
    else if (hps[4 - 1] == 0) ACard(AGARLIC, 2, 4);
    else if (hps[2 - 1] < hps[3 - 1] && hps[2 - 1] < hps[3 - 1]) {
        ARemovePlant(2, 2, AGARLIC);
        ACard(AGARLIC, 2, 2);
    } else if (hps[2 - 1] > hps[3 - 1]) {
        ARemovePlant(2, 3, AGARLIC);
        ACard(AGARLIC, 2, 3);
    } else {
        ARemovePlant(2, 4, AGARLIC);
        ACard(AGARLIC, 2, 4);
    }
}

void FodderAll(int wave, int time, const FodderAllInfo &info) {
    AConnect(ATime(wave, time), [=](){
        int r1f_front = GetZombieFront(1, info.r1_front_atwave);
        int r1b_front = GetZombieFront(1, info.r1_back_atwave);
        int r5_front = GetZombieFront(5, info.r56_atwave);
        int r6_front = GetZombieFront(6, info.r56_atwave);
        // 检测最靠前的巨人与理论最快的位置差
        // first 1=r1f 2=r1b 3=r5 4=r6
        std::vector<std::pair<int, int>> fronts;
        fronts.push_back(std::make_pair(1, r1f_front - info.r1_front_fastest));
        fronts.push_back(std::make_pair(2, r1b_front - info.r1_back_fastest));
        fronts.push_back(std::make_pair(3, r5_front - info.r56_fastest));
        fronts.push_back(std::make_pair(4, r6_front - info.r56_fastest));
        sort(fronts.begin(), fronts.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b){
            return a.second < b.second;
        });
        // 查看2路损耗
        int garlic_count = 0, puff_count = 0, min_garlic_hp = 300, min_puff_hp = 300;
        for (APlant &plant: aAlivePlantFilter) {
            if (plant.Row() + 1 != 2) continue;
            if (plant.Type() == AGARLIC) {
                garlic_count++;
                min_garlic_hp = std::min(min_garlic_hp, plant.Hp());
            } else if (plant.Type() == APUFF_SHROOM) {
                puff_count++;
                min_puff_hp = std::min(min_puff_hp, plant.Hp());
            }
        }
        // 若需要补种，安全距离较短；否则，安全距离较长
        int safe_offset = (garlic_count == 3 && puff_count == 3) ? plant_offset : fix_offset;
        // 查看前两个位置是否在安全距离以内
        int spare_fodder = 0;
        std::vector<APosition> fodder_pos;
        for (int i = 0; i < 2; i++) {
            int fodder_type = fronts[i].first, fodder_offset = fronts[i].second;
            if (fodder_offset < safe_offset) {
                switch (fodder_type) {
                case 1: fodder_pos.push_back({1, GetFodderRow(r1f_front)}); break;
                case 2: fodder_pos.push_back({1, GetFodderRow(r1b_front)}); break;
                case 3: fodder_pos.push_back({5, GetFodderRow(r5_front)}); break;
                case 4: fodder_pos.push_back({6, GetFodderRow(r6_front)}); break;
                }
            } else {
                spare_fodder++;
            }
        }
        logger.Info("r1f-w#:#, r1b-w#: #, r5-w#: #, r6-w#: #",
            info.r1_front_atwave, r1f_front, 
            info.r1_back_atwave, r1b_front, 
            info.r56_atwave, r5_front, 
            info.r56_atwave, r6_front);
        logger.Info("Dists:");
        for (int i = 0; i < 4; i++) {
            logger.Info("(#, #)", fronts[i].first, fronts[i].second);
        }
        logger.Info("Chosen:");
        for (int i = 0; i < int(fodder_pos.size()); i++) {
            logger.Info("(#, #)", fodder_pos[i].col, fodder_pos[i].row);
        }
        // 对结果进行总结
        if (spare_fodder == 2) {
            FixPuff();
            FixGarlic();
        } else if (spare_fodder == 1) {
            if (garlic_count == 3 && puff_count == 3) {
                if (min_garlic_hp < min_puff_hp) {
                    FixGarlic();
                    TempCNow(APUFF_SHROOM, {fodder_pos[0]}, 100);
                } else {
                    FixPuff();
                    TempCNow(AGARLIC, {fodder_pos[0]}, 100);
                }
            } else {
                if (garlic_count - puff_count >= 2) {
                    FixGarlic();
                    TempCNow(APUFF_SHROOM, {fodder_pos[0]}, 100);
                } else {
                    FixPuff();
                    TempCNow(AGARLIC, {fodder_pos[0]}, 100);
                }
            }
            // 大蒜比小喷多2，则种小喷菇
        }
    });
}

int SubtractWave(int currentWave, int subtractWave, bool ending = false) {
    // w1-w9 > 1-9
    // w9收尾 > 10
    // w10-w19 > 11-20
    // w19收尾 > 21
    // w20 > 22

    // w10-3 > w8
    // w9收尾-3 > w7
    int originalWave = currentWave - subtractWave;
    if (ending || originalWave < 10 && currentWave >= 10 || originalWave < 20 && currentWave >= 20) {
        return originalWave + 1;
    } else {
        return originalWave;
    }
}

// 844cs 时的垫材函数。
// 若用于5/6路，垫在5-2/6-2；若用在1路前场，垫在1-5；若用在1路后场，垫在1-3.
void Fodder1(int wave, int time) {
    // 1-5处理论最快374，范围335-435；1-3处理论最快219，范围175-275
    // 5-2/6-2处理论最快152，范围95-195
    FodderAllInfo info;
    info.r1_back_atwave = SubtractWave(wave, 2, time >= 2501);
    info.r1_back_fastest = 374;
    info.r1_front_atwave = SubtractWave(wave, 3, time >= 2501);
    info.r1_front_fastest = 219;
    info.r56_atwave = SubtractWave(wave, 3, time >= 2501);
    info.r56_fastest = 152;
    FodderAll(wave, time, info);
}

// 1606cs 时的垫材函数。
// 若用于5/6路，垫在5-3/6-3；若用在1路前场，垫在1-4；若用在1路后场，垫在1-2.
void Fodder2(int wave, int time) {
    // 1-4处理论最快328，范围255-355；1-2处理论最快173，范围95-195
    // 5-3/6-3处理论最快279，范围175-275
    FodderAllInfo info;
    info.r1_back_atwave = SubtractWave(wave, 2, time >= 2501);
    info.r1_back_fastest = 328;
    info.r1_front_atwave = SubtractWave(wave, 3, time >= 2501);
    info.r1_front_fastest = 173;
    info.r56_atwave = SubtractWave(wave, 2, time >= 2501);
    info.r56_fastest = 279;
    FodderAll(wave, time, info);
}

// 2391cs 时的垫材函数。
// 若用于5/6路，垫在5-1/6-1；若用在1路前场，垫在1-5；若用在1路后场，垫在1-3.
void Fodder3(int wave, int time) {
    // 1-5处理论最快406，范围335-435；1-3处理论最快264，范围255-355
    // 5-3/6-3处理论最快25，范围15-115
    FodderAllInfo info;
    info.r1_back_atwave = SubtractWave(wave, 1, time >= 2501);
    info.r1_back_fastest = 406;
    info.r1_front_atwave = SubtractWave(wave, 2, time >= 2501);
    info.r1_front_fastest = 264;
    info.r56_atwave = SubtractWave(wave, 3, time >= 2501);
    info.r56_fastest = 25;
    FodderAll(wave, time, info);
}

void AScript() {
    UnlimitedSun(ModState::SCOPED_ON);
    // 1冰2301下，最快梯子到达337，最慢巨人到达729
    // 3-8核对巨人全收
    // 3-8核对扶梯漏1路6路，可以考虑1路垫一下，6路用大蒜驱赶

    // 4-7核对扶梯漏1路，垫一下即可
    // 4-7核漏1路15px巨人

    // 4-8核对扶梯漏12路，需要垫+驱赶
    // 4-8核对巨人全收

    // 3-7核对扶梯全收
    // 3-7核对巨人全收

    // 3-6核对扶梯全收
    // 3-6核漏1路15px巨人，漏6路30px巨人

    // 还是选择3-6/3-7/3-8/4-7；4-7对应的两波2路用窝瓜，

    Init({ AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ACHERRY_BOMB, AJALAPENO, ALILY_PAD, ATALL_NUT, ASQUASH, AGARLIC, APUFF_SHROOM });

    AConnect(ATime(1, -599), [](){
        TallNutFixer.Start(ATALL_NUT, {{1, 1}});
        // GarlicFixer.Start(AGARLIC, {{2, 2}, {2, 3}, {2, 4}});
        // PuffShroomFixer.Start(APUFF_SHROOM, {{2, 5}, {2, 6}, {2, 7}});
    });
    
    const int i_len = 2501;

    C(1, -599, ALILY_PAD, 4, 3);
    C(1, -599, AGARLIC, 2, 2);
    C(1, -599, APUFF_SHROOM, 2, 5);

    // 2598扶梯完全进入5-3的311樱桃范围
    for (int w: { 1, 3, 5, 7, 9, 10, 12, 14, 16, 18 }) {
        // I-B-Nd
        ManualI(w, 98, 4, 3, i_len);
        B(w, 1137, 3, 8.5375);
        N(w, i_len - 200, {{3, 7}, {3, 8}, {4, 7}, {3, 6}});
        d(w, 2598, 5, 3.0875);
        // 智能垫材，即有红锤得到才垫，否则挪作他用
        Fodder1(w, 844);
        Fodder2(w, 1606);
        Fodder3(w, 2391);
        // 考虑1路，w4 2301死，需要5次垫材
        // 2路小喷提供io，理论上无需垫材，其他路用不掉的垫材也会支援2路
        if (w == 9 || w == 19) {
            ManualI(w, i_len + 98, 4, 3);
            B(w, i_len + 1137, 3, 8.1125);
            P(w, i_len + i_len - 200, 5, 7.55);
            A(w, i_len + 2599, 5, 3);
            J(w, i_len + i_len - 200, 1, 2);
            Fodder1(w, 2501 + 844);
            Fodder2(w, 2501 + 1606);
            Fodder3(w, 2501 + 2391);
        }
    }
    for (int w: { 2, 4, 6, 8, 11, 13, 15, 17, 19 }) {
        // I-B-PAA'
        ManualI(w, 98, 4, 3, i_len);
        B(w, 1137, 3, 8.5375);
        P(w, i_len - 200, 5, 7.6375);
        // 同帧先植物后僵尸，用A的话要延迟一帧
        A(w, 2599, 5, 3);
        J(w, i_len - 200, 1, 2);
        // 下半场用垫材拖住红眼
        Fodder1(w, 844);
        Fodder2(w, 1606);
        Fodder3(w, 2391);
        if (w == 19) {
            ManualI(w, i_len + 98, 4, 3);
            P(w, i_len + 1234, 3, 8.1125);
            N(w, i_len + i_len - 200, {{3, 7}});
            P(w, i_len + 2598, 5, 3.0875);
            Fodder1(w, 2501 + 844);
            Fodder2(w, 2501 + 1606);
            Fodder3(w, 2501 + 2391);
        }
    }
}
