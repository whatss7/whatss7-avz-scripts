#include "../walib.h"

void AScript() {
    Init({AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ACOFFEE_BEAN, ALILY_PAD, 
            ATALL_NUT, ACHERRY_BOMB, AUMBRELLA_LEAF, ABLOVER, APUFF_SHROOM});
    // ch4-N: I-PP | I-PP | I-N | PP
    const int long_i_len = 1709, short_i_len = 1250;
    aIceFiller.Start({{3, 1}, {4, 1}});
    AutoBlover(1, 1);
    // w1-w5: N | PP | I-PP (16.55) | I-PP (18.2) | I-N入轨...
    // 需要布好的睡莲：3-9核，3-7高坚果，4-7高坚果，3-1存冰位荷叶，4-1存冰位荷叶，3-4叶子保护伞
    // 3-9核 1, -599
    C(1, -599, ALILY_PAD, 3, 9);
    // 3-7高坚 1, -599
    C(1, 152, {ALILY_PAD, ATALL_NUT}, 3, 7);
    // 3-1存冰 1, 152
    C(2, 302, ALILY_PAD, 3, 1);
    // 4-1存冰 2, 302
    C(3, 452, ALILY_PAD, 4, 1);
    // 3-4保护 2, 1053
    C(3, 1203, {ALILY_PAD, AUMBRELLA_LEAF}, 3, 4);
    // 4-7高坚 3, 149
    C(4, 299, {ALILY_PAD, ATALL_NUT}, 4, 7);
    for (int w: {1}) {
        C(w, PCP - CBT - ADT, {ADOOM_SHROOM, ACOFFEE_BEAN}, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
    }
    for (int w: {2, 6, 10, 12, 16}) {
        PP(w, PCP, 8.6);
        if (w == 10) {
            Remove(w, 299, ATALL_NUT, 3, 7);
            TempC(w, 300, AUMBRELLA_LEAF, 3, 7, 400);
            if (w == 10) C(w, 401, ATALL_NUT, 3, 7);
        }
    }
    for (int w: {3}) {
        C(w - 1, 1 + 601 - CBT - ADT, ACOFFEE_BEAN, 2, 1);
        PP(w, 1655 - 200, 8.5);
    }
    for (int w: {4}) {
        C(w - 1, 1 + 1655 - CBT - ADT, ACOFFEE_BEAN, 5, 1);
        PP(w, 1820 - 200, 8.5);
    }
    for (int w: {5, 9, 11, 15, 19}) {
        if (w == 5) I(w, 1, 1820);
        else if (w == 11) I(w, 1, 601);
        else I(w, 1, long_i_len);
        if (w == 19) {
            AConnect(ATime(w, 2), [](){
                aIceFiller.Start({{2, 1}, {5, 1}});
            });
        }
        AConnect(ATime(w, short_i_len - 200 - CBT - ADT - ADT - 1), [w](){
            auto plant = ACard({ ALILY_PAD, ACHERRY_BOMB }, {{3, 9}, {4, 9}, {3, 8}, {4, 8}})[0];
            if (plant) {
                N(w, short_i_len - 200, plant->Row() + 1, plant->Col() + 1);
            }
        });
        if (w == 9 || w == 19) {
            PP(w, short_i_len + PCP, 8.5);   
            PP(w, short_i_len + 601 + long_i_len - 200, 8.5);
        }
    }
    for (int w: {7, 8, 13, 14, 17, 18}) {
        if (w == 7 || w == 13 || w == 17) I(w, 1, 601);
        else I(w, 1, long_i_len);
        PP(w, long_i_len - 200, 8.5);
    }
    for (int w: {20}) {
        I(w, 1);
        AConnect(ATime(w, short_i_len - 200 - CBT - ADT - ADT - 1), [w](){
            auto plant = ACard({ ALILY_PAD, ACHERRY_BOMB }, {{3, 9}, {4, 9}, {3, 8}, {4, 8}})[0];
            if (plant) {
                N(w, short_i_len - 200, plant->Row() + 1, plant->Col() + 1);
            }
        });
        PP(w, long_i_len - 200, 8.5);
        I(w, long_i_len);
        PP(w, long_i_len + long_i_len - 200, 8.5);
    }
}