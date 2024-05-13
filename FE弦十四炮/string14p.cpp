#include "../walib.h"

void AScript() {
    Init({
        ALILY_PAD, ADOOM_SHROOM, AM_DOOM_SHROOM, ACHERRY_BOMB, AJALAPENO,
        APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, AWALL_NUT
    });
    const int a_len = 875, n_len = 850;
    const int c1_time = 196, c2_a_time = a_len - 200 + 143, c2_n_time = n_len - 200 + 143;
    // 小丑591上炸下，603下炸上
    for (int w: {1, 2, 4, 5, 6, 8, 9, 10, 11, 12, 14, 15, 16, 18, 19}) {
        TempC(w, c1_time, ASCAREDY_SHROOM, 2, 9, c1_time + 100);
        TempC(w, c1_time, AFLOWER_POT, 5, 9, c1_time + 100);
        PP(w, a_len - 200, 8.4);
        DD(w, a_len - 200 + 116, 7.1125);
        TempC(w, c2_a_time, APUFF_SHROOM, 2, 8, c2_a_time + 100);
        TempC(w, c2_a_time, ASUN_SHROOM, 5, 8, c2_a_time + 100);
        if (w == 9 || w == 19) {
            // 再打一个PD，剩下的应该都是一血红
            TempC(w, a_len + c1_time, ASCAREDY_SHROOM, 2, 9, a_len + c1_time + 100);
            TempC(w, a_len + c1_time, AFLOWER_POT, 5, 9, a_len + c1_time + 100);
            PP(w, a_len + a_len - 200, 8.4);
            DD(w, a_len + a_len - 200 + 116, 7.4);
            TempC(w, a_len + c2_a_time, APUFF_SHROOM, 2, 8, a_len + c2_a_time + 100);
            TempC(w, a_len + c2_a_time, ASUN_SHROOM, 5, 8, a_len + c2_a_time + 100);
            // 开始拖收尾
            TempC(w, a_len + a_len + c1_time, ASCAREDY_SHROOM, 2, 8, a_len + a_len + c1_time + 100);
            TempC(w, a_len + a_len + c1_time, AFLOWER_POT, 5, 8, a_len + a_len + c1_time + 100);
            PPExceptOne(w, a_len + a_len + n_len - 200 + 116 + 5, 7.125, { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT });
            PPLast(w, 4300);
        }
    }
    for (int w: {3, 13}) {
        TempC(w, c1_time, ASCAREDY_SHROOM, 2, 9, c1_time + 100);
        TempC(w, c1_time, AFLOWER_POT, 5, 9, c1_time + 100);
        C(w, n_len - 200 - ADT - 110, { ALILY_PAD, ACHERRY_BOMB }, 3, w == 3 ? 9 : 8);
        C(w, n_len - 200 - ADT, ADOOM_SHROOM, 3, w == 3 ? 9 : 8);
        DD(w, n_len - 200 + 116, 7.1875);
        TempC(w, c2_n_time, APUFF_SHROOM, 2, 8, c2_n_time + 100);
        TempC(w, c2_n_time, ASUN_SHROOM, 5, 8, c2_n_time + 100);
    }
    for (int w: {7, 17}) {
        TempC(w, c1_time, ASCAREDY_SHROOM, 2, 9, c1_time + 100);
        TempC(w, c1_time, AFLOWER_POT, 5, 9, c1_time + 100);
        if (w == 7) {
            C(w, n_len - 200 - ADT - 110, AJALAPENO, 5, 7);
            C(w, n_len - 200 - ADT - MDT, { ALILY_PAD, AM_DOOM_SHROOM }, 4, 9);
        } else {
            C(w, n_len - 200 - ADT - 110, AJALAPENO, 5, 7);
            C(w, n_len - 200 - ADT - MDT, { ALILY_PAD, AM_DOOM_SHROOM }, 4, 8);
        }
        DD(w, n_len - 200 + 116, 7.1875);
        TempC(w, c2_n_time, APUFF_SHROOM, 2, 8, c2_n_time + 100);
        TempC(w, c2_n_time, ASUN_SHROOM, 5, 8, c2_n_time + 100);
    }
    for (int w: {20}) {
        P(w, 225, 4, 7.5875);
        PP(w, 309, 9, {2, 2, 5, 5});
        PP(w, 409, 9, {2, 2, 5, 5});
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