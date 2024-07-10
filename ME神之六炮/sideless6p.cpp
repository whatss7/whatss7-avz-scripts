#include "../walib.h"

const int i_len = 1719, n_len = 746;
int p_cob = 1, n_pos = 3;
void SeperateZomboni(int w, int time) {
    AConnect(ATime(w, time - 387), [=](){
        if (p_cob == 1) RoofP(w, time, 1, 3, 8.8);
        else RoofP(w, time, 6, 3, 8.3375);
        p_cob = 7 - p_cob;
    });
}

void ActivateP(int w, int time, int row) {
    AConnect(ATime(w, time - 387), [=](){
        if (p_cob == 1) RoofP(w, time, 1, row, 8.4375);
        else RoofP(w, time, 6, row, 8.4875);
        p_cob = 7 - p_cob;
    });
}

void AScript() {
    Init({AICE_SHROOM, AM_ICE_SHROOM, AFLOWER_POT, ACHERRY_BOMB, ADOOM_SHROOM, AJALAPENO, ASQUASH, APUFF_SHROOM});
    StartReloadMode();

    C(1, -599, AFLOWER_POT, 1, 1);
    C(10, 1420, AFLOWER_POT, 1, 1);
    Remove(20, 1721, AFLOWER_POT, 1, 1);

    // 冰波
    for (int w: {1, 5, 6, 11, 15, 16}) {
        ManualI(w, 1, 1, 1, w == 6 || w == 16 ? 1719 : 601);
        SeperateZomboni(w, 364);
        RoofP(w, i_len - 200, 1, 2, 8.3875);
        RoofP(w, i_len - 200, 6, 4, 8.425);
        if (w == 20) {
            SeperateZomboni(w, 364);
            RoofP(w, i_len + i_len - 200, 1, 2, 8.3875);
            RoofP(w, i_len + i_len - 200, 6, 4, 8.425);
        }
    }
    // 第一加速波，樱桃代奏
    // 若此处车底炸，则核波花盆cd可能不够，此处不车底炸
    // 炸点可能不能全收撑杆，但A如果被碾也不能全收撑杆，无所谓了
    for (int w: {2, 7, 12, 17}) {
        AConnect(ATime(w, 1), [=](){
            if (n_pos == 2) {
                ActivateP(w, 401, 5);
            } else if (n_pos == 3) {
                ActivateP(w, 401, 5);
                J(w, 401, 1, 1);
            } else if (n_pos == 4) {
                ActivateP(w, 401, 2);
            }
            A(w, 396, n_pos, 9);
        });
    }
    // 第二加速波，核代奏
    for (int w: {3, 8, 13, 18}) {
        AConnect(ATime(w, 1), [=](){
            ZomboniN(w, n_len - 200, n_pos, 9);
            n_pos = (n_pos - 1) % 3 + 2;
        });
    }
    // 第三加速波
    for (int w: {4, 9, 10, 14, 19}) {
        // 设置炸点可以收掉撑杆
        RoofP(w, 364, 1, 2, 8.75);
        RoofP(w, 364, 6, 4, 8.7);
        if (w == 10) SmartSquash();
        if (w == 9 || w == 19) {
            ManualI(w, 601 + 1, 1, 1);
            SeperateZomboni(w, 601 + 364);
            RoofP(w, 601 + i_len - 200 , 1, 2, 8.4375);
            RoofP(w, 601 + i_len - 200, 6, 4, 8.4875);
            SeperateZomboni(w, 601 + i_len + 364);
            ForEnd(w, 601 + i_len + 364 + 5, [=](){
                RoofP(w, 601 + i_len + i_len - 200, 1, 1, 7.6125);
                RoofP(w, 601 + i_len + i_len - 200, 6, 5, 7.6125);
            });
        }
    }
    // 最早3238收尾完成，1050冰车消失，3238+500+599-1050=3287，冰道已经消失
    for (int w: {20}) {
        ManualI(w, 1, 1, 1);
        SeperateZomboni(w, 364);
        RoofP(w, i_len - 200, 1, 2, 8.3875);
        RoofP(w, i_len - 200, 6, 4, 8.425);
        ManualI(w, i_len + 1, 1, 1);
        SeperateZomboni(w, i_len + 364);
        RoofP(w, i_len + i_len - 200, 1, 2, 8.3875);
        RoofP(w, i_len + i_len - 200, 6, 4, 8.425);
        SeperateZomboni(w, 3475 + 364);
        RoofP(w, 3475 + i_len - 200, 1, 2, 7.1);
        RoofP(w, 3475 + i_len - 200, 6, 4, 7.1);
    }
}