#include "../walib.h"

void AScript() {
    Init({AICE_SHROOM, AM_ICE_SHROOM, ACHERRY_BOMB, ADOOM_SHROOM, APUFF_SHROOM, AGRAVE_BUSTER});
    // I-PP | I-PP | PA | N | PP
    const int i_len = 1800;
    for (int w: {2, 6, 7, 10, 14, 15, 19}) {
        if (w == 6 || w == 14 || w == 19) WhiteI(w, 1, 1, 1, 601);
        else BlueI(w, 1, 1, 1, w == 2 ? 601 : i_len);
        PP(w, i_len - 200, 8.6);
        if (w == 19) {
            PP(w, i_len + i_len - 200, 8.6);
            P(w, i_len + i_len + PCP, 2, 9);
            A(w, i_len + i_len + PCP, 4, 9);
        }
    }
    for (int w: {3, 8, 11, 16}) {
        P(w, PCP, 2, 9);
        A(w, PCP, 4, 9);
    }
    for (int w: {4, 9, 12, 17, 20}) {
        N(w, PCP, {{3, 9}, {2, 9}, {3, 8}, {2, 8}});
        if (w == 9) {
            PP(w, 601 + PCP);
            PP(w, 601 + 601 + i_len - 200, 8.6);
        }
        if (w == 20) {
            TempC(w, -100, APUFF_SHROOM, {{3, 9}, {2, 9}, {3, 8}, {2, 8}}, 100);
            PP(w, 345, 7.4);
            WhiteI(w, 601 + 1, 1, 1);
            PP(w, 601 + i_len - 200, 8.6);
            PP(w, 601 + i_len * 2 - 200, 8.6);
            AtEnd([=](){
                for (auto &&item: aAlivePlaceItemFilter) {
                    // 1 = tomb, 2 = crate, 3 = ladder
                    if (item.Type() == 1 && item.Col() + 1 >= 8) {
                        ACard(AGRAVE_BUSTER, item.Row() + 1, item.Col() + 1);
                        break;
                    }
                }
            });
        }
    }
    for (int w: {1, 5, 13, 18}) {
        PP(w);
    }
}