#include "../walib.h"

void AScript() {
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ALILY_PAD, ACHERRY_BOMB, 
        AJALAPENO, ASQUASH, ASPIKEWEED, AGARLIC, APUMPKIN
    });
    AutoFixNuts();
    // C6u: ICC-PA|PP|ICC-PA'a|N (19, 6, 19, 6)
    // w1-w9: ICC-PA|PP|ICC-PA'a|N|ICC-PA|PP|ICC-PA'a|N|ICC-PA
    // w10-w19: N|ICC-PA|PP|ICC-PA'a|N|ICC-PA|PP|ICC-PA'a|N|ICC-PA
    // w20: PP

    const int i_len = 1900;
    for (int w: {1, 5, 9, 11, 15, 19}) {
        ManualI(w, 1, 6, 6, 601);
        // 冰车位于729时，地刺可攻击到；最慢冰车320到达729
        AConnect(ATime(w, 1), [w](){
            if (ExistZombie(ABC_12, {2})) TempC(w, 320, ASPIKEWEED, 2, 9, 320 + 100);
            if (ExistZombie(ABC_12, {5})) TempC(w, 320 + 751, ASPIKEWEED, 5, 7, 320 + 751 + 100);
        });
        P(w, i_len - 200, 5, 8.5);
        A(w, i_len - 200, 2, 9);
        if (w == 9 || w == 19) {
            PP(w, i_len + PCP, 8.5);
            ManualI(w, i_len + 601 + 1, 6, 6);
            P(w, i_len + 601 + i_len - 200, 5, 8.5);
            J(w, i_len + 601 + i_len - 200, 1, 6);
            C(w, i_len + 601 + i_len - 200 - SDT, ASQUASH, 2, 8);
        }
    }
    for (int w: {2, 6, 12, 16}) {
        PP(w);
    }
    for (int w: {3, 7, 13, 17}) {
        ManualI(w, 1, 6, 6, 601);
        AConnect(ATime(w, 1), [w](){
            if (ExistZombie(ABC_12, {2})) TempC(w, 320, ASPIKEWEED, 2, 9, 320 + 100);
            if (ExistZombie(ABC_12, {5})) TempC(w, 320 + 751, ASPIKEWEED, 5, 7, 320 + 751 + 100);
        });
        // 考虑9列蒜刺控丑
        // 小丑位于710时可以啃到9列大蒜；完美预判冰下最慢小丑1265来到710，最快小丑823
        // 小丑位于639时不再啃到9列大蒜；完美预判冰下最快小丑1224来到639
        // 考虑到小丑1150开始爆炸，于1100种植大蒜，尽可能驱赶，1300铲
        TempC(w, 1100, AGARLIC, 2, 9, 1300);
        P(w, i_len - 200, 5, 8.5);
        J(w, i_len - 200, 1, 6);
        C(w, i_len - 200 - SDT, ASQUASH, 2, 9);
    }
    for (int w: {4, 8, 10, 14, 18, 20}) {
        N(w, PCP, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
        if (w == 20) {
            ManualI(w, 601 + 1, 6, 6);
            P(w, 601 + i_len - 200, 5, 8.5);
            A(w, 601 + i_len - 200, 2, 9);
            PP(w, 601 + i_len + PCP);
        }
    }
}