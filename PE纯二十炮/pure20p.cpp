#include "../walib.h"

void AScript() {
    Init({APUFF_SHROOM, AM_PUFF_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, AWALL_NUT});
    const int short_len = 657, long_len = 752;
    for (int w: {1, 2, 3, 5, 7, 8, 10, 11, 13, 15, 16, 18}) {
        PP(w, short_len - 200, 8.4625);
        DD(w, short_len - 200 + 112, 7.4);
    }
    for (int w: {4, 6, 9, 12, 14, 17, 19}) {
        PP(w, long_len - 200, 8.375);
        dd(w, long_len - 200 + 224, 4.2);
        // 垫跳跳和舞王
        MultiTempC(w, 160, 
            {AFLOWER_POT, APUFF_SHROOM, AM_PUFF_SHROOM, ASCAREDY_SHROOM}, 
            9, {1, 2, 5, 6}, 230);
        if (w == 9 || w == 19) {
            PP(w, long_len + short_len - 200, 8.4625);
            DD(w, long_len + short_len - 200 + 112, 7.4);
            PP(w, long_len + short_len + long_len - 200, 8.375);
        }
    }
    for (int w: {20}) {
        P(w, 225, 4, 7.5875);
        PP(w, 309, 9, {2, 2, 5, 5});
        DD(w, 309 + 107, 9);
        PP(w, 481, 8.4875);
        PPExceptOne(w, 1121);
        BlockLast(w, 1125, 4100);
        PPLast(w, 4100);
    }
}