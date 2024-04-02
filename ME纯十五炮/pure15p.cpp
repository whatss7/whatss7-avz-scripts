#include "../walib.h"
#include "mod/mod.h"

ACobManager DownP, UpD, Other;

void AScript() {
    AConnect(ATime(1, -599), [](){
        UnlimitedSun(ModState::SCOPED_ON);
        DownP.SetList({{1, 5}, {2, 5}, {3, 5}});
        UpD.SetList({{2, 1}, {3, 1}, {4, 1}, {5, 1}});
        Other.SetList({{1, 1}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {4, 5}, {5, 5}});
    });
    InitWithoutManage({
        AFLOWER_POT, AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, AJALAPENO
    });
    StartReloadMode();
    const int i_len = 1750, a_len = 620;
    // I-PPDD | I-PPDD | PPDD | NDD | PPDD (17.5, 17.5, 6.2, 6.2, 6.2)
    C(1, -598, AFLOWER_POT, 3, 7);
    AConnect(ATime(20, 13), [](){ ARemovePlant(3, 7, AFLOWER_POT); });
    for (int w: { 1, 5, 6, 11, 15, 16, 20 }) {
        // I-PPDD
        ManualI(w, 12, 3, 7, w == 5 || w == 11 || w == 15 ? a_len : i_len);
        if (w != 20) ManualP(w, 600, 3, 7, Other);
        ManualP(w, i_len - 200, 2, 8.5, Other);
        ManualP(w, i_len - 200, 4, 8.5, DownP);
        ManualP(w, i_len - 200 + 220, 2, 7.05, UpD);
        ManualP(w, i_len - 200 + 220, 4, 7.05, Other);
        if (w == 20) {
            ManualP(w, i_len + a_len - 200, 2, 8.75, Other);
            ManualP(w, i_len + a_len - 200, 4, 8.75, DownP);
            ManualP(w, i_len + a_len - 200 + 110, 2, 8.2, UpD);
            ManualP(w, i_len + a_len - 200 + 110, 4, 8.2, Other);
            ManualP(w, 3100, 2, 8.5, Other);
            ManualP(w, 3100, 4, 8.5, DownP);
        }
    }
    for (int w: { 2, 4, 7, 9, 10, 12, 14, 17, 19 }) {
        // PPDD
        ManualP(w, a_len - 200, 2, 8.75, Other);
        ManualP(w, a_len - 200, 4, 8.75, DownP);
        ManualP(w, a_len - 200 + 110, 2, 7.5, UpD);
        ManualP(w, a_len - 200 + 110, 4, 7.5, Other);
        if (w == 9 || w == 19) {
            ManualI(w, a_len + 12, 3, 7);
            ManualP(w, a_len + i_len - 200, 2, 8.5, Other);
            ManualP(w, a_len + i_len - 200, 4, 8.5, DownP);
            ManualP(w, a_len + i_len - 200 + 220, 2, 8.1, UpD);
            ManualP(w, a_len + i_len - 200 + 220, 4, 8.1, Other);
            ManualP(w, 3100, 2, 8.5, Other);
            ManualP(w, 3100, 4, 8.5, DownP);
        }
    }
    for (int w: { 3, 8, 13, 18 }) {
        // NDD
        if (w < 10) {
            J(w, a_len - 200 - 110, 3, 7);
            N(w, a_len - 200, {{3, 9}, {3, 8}});
        } else {
            // 第二冰波的二列巨人，12冰，2170激活，2790死
            // walk([970, 294]) = [601, 681]，walk([970, 295]) = [600, 681]
            // 激活后投掷小鬼142cs，因此对7列花盆举锤437cs，命中7列花盆571cs，激活后620cs死，有概率锤
            // 因此补一个樱桃保证花盆不被锤
            TempC(w - 1, 125, AFLOWER_POT, 2, 7, a_len + a_len - 200);
            A(w - 1, 225, 2, 7);
            J(w, a_len - 200 - 110, 2, 7);
            N(w, a_len - 200, {{2, 9}, {2, 8}});
        }
        ManualP(w, a_len - 200 + 110, 2, 7.5, UpD);
        ManualP(w, a_len - 200 + 110, 4, 7.5, Other);
    }
}