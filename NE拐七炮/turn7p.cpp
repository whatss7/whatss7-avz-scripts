#include "../walib.h"

void AScript() {
    const int i_len = 1975, a_len = 750;
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ACHERRY_BOMB, AJALAPENO,
        APOTATO_MINE, APUFF_SHROOM, AFLOWER_POT, AGRAVE_BUSTER
    });
    // 第一冰波 I-PPD
    for (int w: {1, 5, 9, 11, 15, 19, 20}) {
        WhiteI3(w, 96, 2, 1, 750);
        // 炸掉第一波矿工
        if (w == 1) P(w, 104, 1, 8.65);
        if (w == 20) P(w, 164, 1, 8.65);
        if (w == 20) MaidStop(w, -460);
        // 下波精准土豆炸矿工
        if (w != 9 && w != 19 && w != 20) C(w, i_len - 1150, APOTATO_MINE, 1, 7);
        // 激活，垫红眼强行空炸，后场有梯无法尾炸
        // 激活炮8.275全伤三行巨人
        // 1路最左跳跳D时385（考虑延迟引信384），延迟炮可全收
        // 2路最左跳跳463，激活炮全收
        PP(w, i_len - 200, 8.275);
        TempC(w, i_len - 200 + 3, APUFF_SHROOM, 1, 9, i_len - 200 + 3 + 100);
        D(w, i_len - 200 + 212, 1, 7.2875);
        if (w == 9 || w == 19 || w == 20) {
            BlueI(w, i_len + 12, 2, 1);
            // 铲掉土豆雷防止占用辣椒位或引发意外投掷
            Remove(w, i_len + i_len - 200, APOTATO_MINE, 1, 7);
            PP(w, i_len + i_len - 200, 8.4);
            D(w, i_len + i_len - 200 + 212, 1, 7.4);
            // 此时下路2血，上路1血
            N(w, i_len + i_len + a_len - 200, {{3, 9}, {3, 8}, {2, 9}, {2, 8}});
            D(w, i_len + i_len + a_len - 200 + 106, 4, 8);
        }
    }
    // 第二冰波 IC-PPD
    for (int w: {2, 6, 12, 16}) {
        BlueI(w, 12, 2, 1, 1975);
        // 铲掉土豆雷防止占用辣椒位或引发意外投掷
        Remove(w, i_len - 200, APOTATO_MINE, 1, 7);
        // 垫跳跳
        TempC(w, 514, AFLOWER_POT, 1, 9, 594);
        TempC(w, 1403, AFLOWER_POT, 2, 7, 1483);
        // 激活，垫红眼强行空炸，后场有梯无法尾炸
        PP(w, i_len - 200, 8.425);
        TempC(w, i_len - 200 + 3, APUFF_SHROOM, 1, 9, i_len - 200 + 3 + 100);
        D(w, i_len - 200 + 212, 1, 7.3875);
    }
    // ND
    for (int w: {3, 7, 13, 17}) {
        N(w, a_len - 200, {{3, 9}, {3, 8}, {2, 9}, {2, 8}});
        MaidStop(w, a_len - 200 + 1);
        D(w, a_len - 200 + 106, 1, 7.4);
    }
    // PA'D/PA
    // 下半场樱桃加压，防止巨人锤炮
    for (int w: {4, 8, 10, 14, 18}) {
        MaidDance(w, 342 + 150);
        PP(w, a_len - 200, 8.45);
        A(w, a_len - 200, 4, 9);
        J(w, a_len - 200 + 188, 1, 7);
        D(w, a_len - 200 + 188 + 116, 1, 8.65);
    }
    // 解决墓碑僵尸
    AConnect(ATime(20, 350 - ADT), [](){
        for (auto &&item: aAlivePlaceItemFilter) {
            if (item.Type() == 1) {
                int row = item.Row() + 1, col = item.Col() + 1;
                std::vector<APosition> possibles;
                possibles.push_back({row, float(col - 1)});
                if (col != 9) possibles.push_back({row, float(col + 1)});
                if (row != 1) possibles.push_back({row - 1, float(col)});
                if (row != 5) possibles.push_back({row + 1, float(col)});
                ACard(ACHERRY_BOMB, possibles);
                break;
            }
        }
    });
    AtEnd([](){
        for (auto &&item: aAlivePlaceItemFilter) {
            if (item.Type() == 1) {
                int row = item.Row() + 1, col = item.Col() + 1;
                ACard(AGRAVE_BUSTER, row, col);
                break;
            }
        }
    });
}
