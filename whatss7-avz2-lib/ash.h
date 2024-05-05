#ifndef WALIB_ASH_H
#define WALIB_ASH_H

#include "card.h"
#include "info.h"

#pragma region 仿轨道语言：冰核相关

// 开启自动存冰时，从 `aIceFiller` 进行点冰。若需要非旗帜波的完美预判冰，则需要假设波长或提供上一波波长。
// 由于咖啡豆的不确定性，有概率延迟1cs生效。
void I(int wave, int time = 1, int last_wave_length = -1) {
    time -= CBT + ADT;
    if (!IsValidTime(wave, time) && last_wave_length > 0) {
        wave -= 1;
        time += last_wave_length;
    }
    AConnect(ATime(wave, time), [](){
        aIceFiller.Coffee();
    });
}

// 开启自动存冰时，从 `aIceFiller` 进行点冰。若需要非旗帜波的完美预判冰，则需要假设波长或提供上一波波长。
// 此函数使得寒冰菇精准生效。
void I3(int wave, int time = 11, int last_wave_length = -1) {
    time -= CBT + ADT;
    if (!IsValidTime(wave, time) && last_wave_length > 0) {
        wave -= 1;
        time += last_wave_length;
    }
    AConnect(ATime(wave, time), [](){
        aIceFiller.Coffee();
        AIce3(CBT + ADT);
    });
}

bool CanPlaceImitate(int wave, int time, int last_wave_length = -1) {
    bool isDay = true;
    std::string scene = GetCurrentScene();
    if (scene == "NE" || scene == "FE" || scene == "ME") {
        isDay = false;
    }
    int VCBT = isDay ? CBT : 0;
    int imitate_wave = wave, imitate_time = time - (MDT + (isDay ? 1 : 0)) - VCBT - ADT;
    if (!IsValidTime(imitate_wave, imitate_time) && last_wave_length > 0) {
        imitate_wave -= 1;
        imitate_time += last_wave_length;
    }
    return ANowTime(imitate_wave) < imitate_time && !(imitate_wave == 1 && imitate_time < -599);
}

void SetToValidTime(int &wave, int &time, int last_wave_length) {
    if (!IsValidTime(wave, time) && last_wave_length > 0) {
        wave -= 1;
        time += last_wave_length;
    }
}

void PlantShroomImpl(int wave, int time, APlantType card, const std::vector<APosition> &pos, bool imitate, int protect, bool accurate) {
    std::string scene = GetCurrentScene();
    bool isDay = IsDayScene();
    int VCBT = isDay ? CBT : 0;
    AConnect(ATime(wave, time), [=](){
        for (APosition p: pos) {
            APlant *ptr = nullptr;
            bool should_remove = false;
            // 判断是否需要种植可能需要的底座，然后种植植物
            if ((scene == "RE" || scene == "ME") && !ExistPlant(AFLOWER_POT, p.row, p.col)) {
                ptr = ACard({AFLOWER_POT, card}, p.row, p.col)[1];
                should_remove = true;
            } else if ((scene == "PE" || scene == "FE") && p.row >= 3 && p.row <= 4 && !ExistPlant(ALILY_PAD, p.row, p.col)) {
                ptr = ACard({ALILY_PAD, card}, p.row, p.col)[1];
                should_remove = true;
            } else {
                ptr = ACard(card, p.row, p.col);
            }
            // 种植成功后，做事后处理
            if (ptr) {
                AConnect(ANowDelayTime(imitate ? MDT + (isDay ? 1 : 0) : 0), [=](){
                    bool should_remove_pumpkin = false;
                    // 设置精准生效时，设置生效时间
                    if (accurate) ASetPlantActiveTime(card, (VCBT + ADT));
                    // 需要保护时，且种植位置无南瓜时，种植南瓜
                    if (protect > 1 && !ExistPlant(APUMPKIN, p.row, p.col)) {
                        should_remove_pumpkin = true;
                        ACard(APUMPKIN, p.row, p.col);
                    }
                    // 白昼场景种植咖啡豆
                    if (isDay) ACard(ACOFFEE_BEAN, p.row, p.col);
                    // 寒冰菇生效后，铲除南瓜
                    if ((card == AICE_SHROOM || card == AM_ICE_SHROOM) && should_remove_pumpkin) {
                        AConnect(ANowDelayTime(VCBT + ADT + 1), [p](){
                            ARemovePlant(p.row, p.col, APUMPKIN);
                        });
                    }
                    // 寒冰菇生效后，铲除底座
                    if ((card == AICE_SHROOM || card == AM_ICE_SHROOM) && should_remove) {
                        AConnect(ANowDelayTime(VCBT + ADT + 1), [p](){
                            ARemovePlant(p.row, p.col, {AFLOWER_POT, ALILY_PAD});
                        });
                    }
                });
                break;
            }
        }
    });
}

// 手动种植毁灭菇或寒冰菇。
void ManualShroom(int wave, int time, std::vector<APosition> pos, APlantType card, int last_wave_length, int protect, bool accurate = false) {
    std::string scene = GetCurrentScene();
    bool isDay = IsDayScene();
    APlantType imitated = (card == AICE_SHROOM ? AM_ICE_SHROOM : AM_DOOM_SHROOM);
    int VCBT = isDay ? CBT : 0;

    // 计算种植时间
    // 若为白昼，早种植1cs，模仿者即使319cs完成变身也等到320cs再种咖啡豆，保证延迟最大为1cs。
    // 若为黑夜，则不能早种植，否则有概率提前1cs。
    int imitate_wave = wave, imitate_time = time - (MDT + (isDay ? 1 : 0)) - VCBT - ADT;
    int normal_wave = wave, normal_time = time - VCBT - ADT;
    SetToValidTime(imitate_wave, imitate_time, last_wave_length);
    SetToValidTime(normal_wave, normal_time, last_wave_length);

    if (AGetCardPtr(imitated) && CanPlaceImitate(wave, time)) {
        // 携带了模仿植物的情况
        AConnect(ATime(imitate_wave, imitate_time), [=](){
            if (AGetCardPtr(imitated)->IsUsable() && !(AGetCardPtr(card) && AGetCardPtr(card)->IsUsable())) {
                // 若模仿能种而普通不能种（此判断提前完成，存在普通到时间能转好但还是使用模仿的现象）
                // 则立即种植模仿
                PlantShroomImpl(imitate_wave, imitate_time, imitated, pos, true, protect, accurate);
            } else {
                // 否则稍后种植普通
                PlantShroomImpl(normal_wave, normal_time, card, pos, false, protect, accurate);
            }
        });
    } else {
        // 未携带模仿核同之前的“否则”情况。
        PlantShroomImpl(normal_wave, normal_time, card, pos, false, protect, accurate);
    }
}

// 种植寒冰菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// 若存在预判冰或模仿冰等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿冰时，使用此函数请不要携带模仿冰。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void ManualI(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0){
    ManualShroom(wave, time, pos, AICE_SHROOM, last_wave_length, protect);
}

// 种植寒冰菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// 若存在预判冰或模仿冰等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿冰时，使用此函数请不要携带模仿冰。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void ManualI(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0){
    ManualShroom(wave, time, {{row, col}}, AICE_SHROOM, last_wave_length, protect);
}

// 种植寒冰菇。此函数使得寒冰菇精准生效。
// 若存在预判冰或模仿冰等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿冰时，使用此函数请不要携带模仿冰。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void ManualI3(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0) {
    ManualShroom(wave, time, pos, AICE_SHROOM, last_wave_length, protect, true);
}

// 种植寒冰菇。此函数使得寒冰菇精准生效。
// 若存在预判冰或模仿冰等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿冰时，使用此函数请不要携带模仿冰。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
// 不考虑模仿花盆、模仿睡莲、模仿咖啡豆和模仿南瓜头。
void ManualI3(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0) {
    ManualShroom(wave, time, {{row, col}}, AICE_SHROOM, last_wave_length, protect, true);
}

// 种植原版寒冰菇。由于咖啡豆的不确定性，有概率延迟1cs生效。
// `protect` 为 2 时，用南瓜头保护。
void BlueI(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0){
    bool isDay = IsDayScene();
    int VCBT = isDay ? CBT : 0;

    // 计算种植时间
    int normal_wave = wave, normal_time = time - VCBT - ADT;
    SetToValidTime(normal_wave, normal_time, last_wave_length);

    // 进行种植
    PlantShroomImpl(normal_wave, normal_time, AICE_SHROOM, pos, false, protect, false);
}

// 种植原版寒冰菇。由于咖啡豆的不确定性，有概率延迟1cs生效。
// `protect` 为 2 时，用南瓜头保护。
void BlueI(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0){
    BlueI(wave, time, {{row, col}}, last_wave_length, protect);
}

// 种植原版寒冰菇。此函数使得寒冰菇精准生效。
// `protect` 为 2 时，用南瓜头保护。
void BlueI3(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0) {
    bool isDay = IsDayScene();
    int VCBT = isDay ? CBT : 0;

    // 计算种植时间
    int normal_wave = wave, normal_time = time - VCBT - ADT;
    SetToValidTime(normal_wave, normal_time, last_wave_length);

    // 进行种植
    PlantShroomImpl(normal_wave, normal_time, AICE_SHROOM, pos, false, protect, true);
}

// 种植原版寒冰菇。此函数使得寒冰菇精准生效。
// `protect` 为 2 时，用南瓜头保护。
void BlueI3(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0) {
    BlueI3(wave, time, {{row, col}}, last_wave_length, protect);
}

// 种植模仿寒冰菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// `protect` 为 1 时，用南瓜头保护。
void WhiteI(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0){
    bool isDay = IsDayScene();
    int VCBT = isDay ? CBT : 0;

    // 计算种植时间
    int normal_wave = wave, normal_time = time - VCBT - ADT;
    SetToValidTime(normal_wave, normal_time, last_wave_length);

    // 进行种植
    PlantShroomImpl(normal_wave, normal_time, AM_ICE_SHROOM, pos, true, protect, false);
}

// 种植模仿寒冰菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// `protect` 为 1 时，用南瓜头保护。
void WhiteI(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0){
    WhiteI(wave, time, {{row, col}}, last_wave_length, protect);
}

// 种植模仿寒冰菇。此函数使得寒冰菇精准生效。
// `protect` 为 1 时，用南瓜头保护。
void WhiteI3(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0) {
    bool isDay = IsDayScene();
    int VCBT = isDay ? CBT : 0;

    // 计算种植时间
    int normal_wave = wave, normal_time = time - VCBT - ADT;
    SetToValidTime(normal_wave, normal_time, last_wave_length);

    // 进行种植
    PlantShroomImpl(normal_wave, normal_time, AM_ICE_SHROOM, pos, true, protect, true);
}

// 种植模仿寒冰菇。此函数使得寒冰菇精准生效。
// `protect` 为 1 时，用南瓜头保护。
void WhiteI3(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0) {
    WhiteI3(wave, time, {{row, col}}, last_wave_length, protect);
}

// 若寒冰菇冷却已好，在指定临时冰位使用寒冰菇；否则，使用存冰。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
void TempI(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0, bool accurate = false) {
    bool isDay = true;
    std::string scene = GetCurrentScene();
    if (scene == "NE" || scene == "FE" || scene == "ME") {
        isDay = false;
    }
    int VCBT = isDay ? CBT : 0;
    int imitate_wave = wave, imitate_time = time - (MDT + (isDay ? 1 : 0)) - VCBT - ADT;
    if (!IsValidTime(imitate_wave, imitate_time) && last_wave_length > 0) {
        imitate_wave -= 1;
        imitate_time += last_wave_length;
    }
    int normal_wave = wave, normal_time = time - VCBT - ADT;
    if (!IsValidTime(normal_wave, normal_time) && last_wave_length > 0) {
        normal_wave -= 1;
        normal_time += last_wave_length;
    }
    ATime connect_time = ATime(normal_wave, normal_time);
    if (AGetCardPtr(AM_ICE_SHROOM) && CanPlaceImitate(wave, time, last_wave_length)) {
        connect_time = ATime(imitate_wave, imitate_time);
    }
    AConnect(connect_time, [wave, time, pos, last_wave_length, protect, accurate](){
        if (AGetCardPtr(AICE_SHROOM)->IsUsable() || AGetCardPtr(AM_ICE_SHROOM)->IsUsable()) {
            if (accurate) ManualI3(wave, time, pos, last_wave_length, protect);
            else ManualI(wave, time, pos, last_wave_length, protect);
        } else {
            if (accurate) I3(wave, time, last_wave_length);
            else I(wave, time, last_wave_length);
        }
    });

}

// 若寒冰菇冷却已好，在指定临时冰位使用寒冰菇；否则，使用存冰。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
void TempI(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0, bool accurate = false) {
    TempI(wave, time, {{row, col}}, last_wave_length, protect, accurate);
}

// 若寒冰菇冷却已好，在指定临时冰位使用寒冰菇；否则，使用存冰。此函数使得寒冰菇精准生效。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
void TempI3(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0) {
    TempI(wave, time, pos, last_wave_length, protect, true);
}

// 若寒冰菇冷却已好，在指定临时冰位使用寒冰菇；否则，使用存冰。此函数使得寒冰菇精准生效。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿冰；为 2 时，都进行保护。
void TempI3(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0) {
    TempI(wave, time, row, col, last_wave_length, protect, true);
}

// 种植毁灭菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// 若存在模仿核等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿核时，使用此函数请不要携带模仿核。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿核；为 2 时，都进行保护。
void N(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0) {
    ManualShroom(wave, time, pos, ADOOM_SHROOM, last_wave_length, protect);
}

// 种植毁灭菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// 若存在模仿核等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿核时，使用此函数请不要携带模仿核。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿核；为 2 时，都进行保护。
void N(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0) {
    ManualShroom(wave, time, {{row, col}}, ADOOM_SHROOM, last_wave_length, protect);
}

// 种植毁灭菇。此函数使得毁灭菇精准生效。
// 若存在模仿核等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿核时，使用此函数请不要携带模仿核。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿核；为 2 时，都进行保护。
void PreciseN(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0) {
    ManualShroom(wave, time, pos, ADOOM_SHROOM, last_wave_length, protect, true);
}

// 种植毁灭菇。此函数使得毁灭菇精准生效。
// 若存在模仿核等需要早种的情况，则需要假设波长或提供上波波长。所以用不到模仿核时，使用此函数请不要携带模仿核。
// `protect` 为 0 时，不进行保护；为 1 时，仅保护模仿核；为 2 时，都进行保护。
void PreciseN(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0) {
    ManualShroom(wave, time, {{row, col}}, ADOOM_SHROOM, last_wave_length, protect, true);
}

// 种植原版毁灭菇。由于咖啡豆的不确定性，有概率延迟1cs生效。
// `protect` 为 2 时，用南瓜头保护。
void BlackN(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0){
    bool isDay = IsDayScene();
    int VCBT = isDay ? CBT : 0;

    // 计算种植时间
    int normal_wave = wave, normal_time = time - VCBT - ADT;
    SetToValidTime(normal_wave, normal_time, last_wave_length);

    // 进行种植
    PlantShroomImpl(normal_wave, normal_time, ADOOM_SHROOM, pos, false, protect, false);
}

// 种植原版毁灭菇。由于咖啡豆的不确定性，有概率延迟1cs生效。
// `protect` 为 2 时，用南瓜头保护。
void BlackN(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0){
    BlackN(wave, time, {{row, col}}, last_wave_length, protect);
}

// 种植原版毁灭菇。此函数使得寒冰菇精准生效。
// `protect` 为 2 时，用南瓜头保护。
void PreciseBlackN(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0) {
    bool isDay = IsDayScene();
    int VCBT = isDay ? CBT : 0;

    // 计算种植时间
    int normal_wave = wave, normal_time = time - VCBT - ADT;
    SetToValidTime(normal_wave, normal_time, last_wave_length);

    // 进行种植
    PlantShroomImpl(normal_wave, normal_time, ADOOM_SHROOM, pos, false, protect, true);
}

// 种植原版毁灭菇。此函数使得寒冰菇精准生效。
// `protect` 为 2 时，用南瓜头保护。
void PreciseBlackN(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0) {
    PreciseBlackN(wave, time, {{row, col}}, last_wave_length, protect);
}

// 种植模仿毁灭菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// `protect` 为 1 时，用南瓜头保护。
void WhiteN(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0){
    bool isDay = IsDayScene();
    int VCBT = isDay ? CBT : 0;

    // 计算种植时间
    int normal_wave = wave, normal_time = time - VCBT - ADT;
    SetToValidTime(normal_wave, normal_time, last_wave_length);

    // 进行种植
    PlantShroomImpl(normal_wave, normal_time, AM_DOOM_SHROOM, pos, true, protect, false);
}

// 种植模仿毁灭菇。由于咖啡豆和模仿者的不确定性，有概率延迟1cs生效。
// `protect` 为 1 时，用南瓜头保护。
void WhiteN(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0){
    WhiteN(wave, time, {{row, col}}, last_wave_length, protect);
}

// 种植模仿毁灭菇。此函数使得寒冰菇精准生效。
// `protect` 为 1 时，用南瓜头保护。
void PreciseWhiteN(int wave, int time, std::vector<APosition> pos, int last_wave_length = -1, int protect = 0) {
    bool isDay = IsDayScene();
    int VCBT = isDay ? CBT : 0;

    // 计算种植时间
    int normal_wave = wave, normal_time = time - VCBT - ADT;
    SetToValidTime(normal_wave, normal_time, last_wave_length);

    // 进行种植
    PlantShroomImpl(normal_wave, normal_time, AM_DOOM_SHROOM, pos, true, protect, true);
}

// 种植模仿毁灭菇。此函数使得寒冰菇精准生效。
// `protect` 为 1 时，用南瓜头保护。
void PreciseWhiteN(int wave, int time, int row, float col, int last_wave_length = -1, int protect = 0) {
    PreciseWhiteN(wave, time, {{row, col}}, last_wave_length, protect);
}


// 种植毁灭菇，但进行车底炸。仅用于夜间场景。
// 本路无冰车时，与BlackN函数相同；而有冰车时，在生效时间点再放。
void ZomboniN(int wave, int time, int row, float col) {
    const std::string scene = GetCurrentScene();
    if (scene != "ME") {
        waLogger.Warning("ZomboniN 仅用于 ME. 将改用 PreciseBlackN()");
        PreciseBlackN(wave, time, row, col);
    } else {
        AConnect(ATime(wave, 1), [wave, time, row, col](){
            if (ExistZombie(ABC_12, {row})) TempC(wave, time, ADOOM_SHROOM, row, col);
            else PreciseBlackN(wave, time, row, col);
        });
    }
}

// 使用一个樱桃炸弹。此函数不会使用模仿樱桃炸弹。
void A(int wave, int time, int row, float col) {
    TempC(wave, time - ADT, ACHERRY_BOMB, row, col, time + 1);
}

// 种植樱桃炸弹，但进行车底炸。
// 本路无冰车时，与A函数相同；而有冰车时，在生效时间点再放。
void ZomboniA(int wave, int time, int row, float col) {
    AConnect(ATime(wave, 1), [wave, time, row, col](){
        if (ExistZombie(ABC_12, {row})) TempC(wave, time, ACHERRY_BOMB, row, col);
        else A(wave, time, row, col);
    });
}

// 使用一个火爆辣椒。此函数不会使用模仿火爆辣椒。
void J(int wave, int time, int row, float col) {
    TempC(wave, time - ADT, AJALAPENO, row, col, time + 1);
}

// 种植火爆辣椒，但进行车底炸。
// 本路无冰车时，与J函数相同；而有冰车时，在生效时间点再放。
void ZomboniJ(int wave, int time, int row, float col) {
    AConnect(ATime(wave, 1), [wave, time, row, col](){
        if (ExistZombie(ABC_12, {row})) TempC(wave, time, AJALAPENO, row, col);
        else J(wave, time, row, col);
    });
}

// 使用智能樱桃消延迟。此函数不会使用模仿樱桃炸弹。
// 默认有巨人时400cs生效，没有巨人时550cs生效。
// 本函数未考虑冰车碾压。
void SmartA(int wave = 10, int time = 400, int no_red_time = 550) {
    if (!AGetZombieTypeList()[AHY_32]) time = no_red_time;
    std::string scene = GetCurrentScene();
    if (scene == "PE" || scene == "FE") {
        AConnect(ATime(wave, time - ADT), [wave, time](){
            if (!ForEndJudge(wave)) return;
            int uby = 0, uhy = 0, dby = 0, dhy = 0;
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Type() == ABY_23) {
                    if (zombie.Row() < 3) uby++;
                    else dby++;
                } else if (zombie.Type() == AHY_32) {
                    if (zombie.Row() < 3) uhy++;
                    else dhy++;
                }
            }
            if (uby * 2 + uhy * 3 < dby * 2 + dhy * 3) {
                TempC(wave, time - ADT, ACHERRY_BOMB, {{5, 9}, {2, 9}}, time + 1);
            } else {
                TempC(wave, time - ADT, ACHERRY_BOMB, {{2, 9}, {5, 9}}, time + 1);
            }
        });
    } else {
        AConnect(ATime(wave, time - ADT), [wave, time](){
            if (!ForEndJudge(wave)) return;
            std::vector<APosition> choices = {{2, 9}, {3, 9}, {4, 9}};
            int status[3];
            for (auto &&zombie: aAliveZombieFilter) {
                int score = 0;
                if (zombie.Type() == ABY_23) score = 2;
                else if (zombie.Type() == AHY_32) score = 3;
                if (zombie.Row() == 1 || zombie.Row() == 2 || zombie.Row() == 3) {
                    status[0] += score;
                }
                if (zombie.Row() == 2 || zombie.Row() == 3 || zombie.Row() == 4) {
                    status[1] += score;
                }
                if (zombie.Row() == 3 || zombie.Row() == 4 || zombie.Row() == 5) {
                    status[2] += score;
                }
            }
            std::sort(choices.begin(), choices.end(), [status](APosition a, APosition b){
                return status[a.row - 2] < status[b.row - 2];
            });
            TempC(wave, time - ADT, ACHERRY_BOMB, choices, time + 1);
        });
    }
}

#pragma endregion

#endif // WALIB_ASH_H