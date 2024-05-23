#include "../walib.h"

void AScript() {
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ALILY_PAD, APUFF_SHROOM,
        ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, AWALL_NUT
    });
    const int i_len = 1827, a_len = 824;
    waStopGigaBanCols = {8, 9};
    // I-B-PPDD | PPDD | PSD/PD
    // 冰波600 1016垫，第二加速波208垫
    for (int w: {1, 4, 7, 11, 14, 17}) {
        ManualI(w, 1, 1, 6, a_len);
        // 有冰分离海豚
        P(w, 1233, 3, 8.1125);
        // 垫，上半上波有PSD收尾，问题应该不大
        TempC(w, 600, APUFF_SHROOM, 5, 7, 700);
        // 使用无偏移的植物垫，防止被冰车提前碾压
        TempC(w, 1016, ASCAREDY_SHROOM, 5, 7, 1050);
        // PPDD
        PP(w, i_len - 200, 8.4125);
        DD(w, i_len - 200 + 220, 7.35);
    }
    for (int w: {2, 5, 8, 12, 15, 18}) {
        // PPDD
        MaidDance(w, 493, a_len - 200 + 110);
        PP(w, a_len - 200, 8.3);
        DD(w, a_len - 200 + 110, 7.3125);
    }
    for (int w: {3, 6, 9, 10, 13, 16, 19}) {
        // 垫
        TempC(w, 208, APUFF_SHROOM, 2, 7, 308);
        TempC(w, 208, ASUN_SHROOM, 5, 7, 308);
        // PSD/PD
        MaidDance(w, 493, a_len - 200 + 110);
        if (w != 9 && w != 19) {
            PP(w, a_len - 200, 8.3, {2, 2, 5});
            P(w, a_len - 200 + 110, 5, 7.3125);
            // 此处无法全伤所有红眼，但问题不大，只需要上半投不出小鬼就可以了
            P(w, a_len - 200 + 110, 1, 7.7);
        } else {
            // 下一波没有分离了，这里打一个PD确保是三血红
            PP(w, a_len - 200, 8.3);
            DD(w, a_len - 200 + 110, 7.3125);
            ManualI(w, a_len + 1, 1, 6);
            // 两次垫材
            TempC(w, a_len + 600, APUFF_SHROOM, 2, 7, a_len + 700);
            TempC(w, a_len + 600, ASUN_SHROOM, 5, 7, a_len + 700);
            TempC(w, a_len + 1016, ASCAREDY_SHROOM, 2, 7, a_len + 1050);
            TempC(w, a_len + 1016, AFLOWER_POT, 5, 7, a_len + 1050);
            PP(w, a_len + i_len - 200, 8.4125);
            // 7.2125即可全伤，直接沿用之前的炸点
            DD(w, a_len + i_len - 200 + 220, 7.3125);
            PPExceptOne(w, a_len + i_len + a_len - 200, 7.3125, {APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT});
            PPLast(w, 4300);
        }
    }
    for (int w: {20}) {
        P(w, 225, 4, 7.5875);
        PP(w, 309, 9, {2, 2, 5, 5});
        PP(w, 409, 9, {2, 5});
        N(w, 409, 3, 9);
        PPExceptOne(w, 815);
        BlockLast(w, 820, 4300);
        UntilOneLeft(w, 820, nullptr,
            [=](){
                ACard(APUFF_SHROOM, GetLastZombie()->Row() + 1, 8);
                AConnect(ANowDelayTime(751), [](){ ACard(APUFF_SHROOM, GetLastZombie()->Row() + 1, 7); });
            },
            [=](){
                ARemovePlant(GetLastZombie()->Row() + 1, 8);
                ARemovePlant(GetLastZombie()->Row() + 1, 7);
            }
        );
        PPLast(w, 4300);
    }
}