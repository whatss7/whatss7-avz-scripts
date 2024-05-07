#include "../walib.h"

void AScript() {
    Init({ AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, AWALL_NUT });
    AutoManageCob();
    StartIceFiller({{2, 1}, {5, 1}});
    int i_len = 1250;
    // ch6: IPP-PP | BBDD
    SetMaidDefault(1);
    for (int w: { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 }) {
        I(w, 1, 601);
        // 双边热过渡，非收尾波炸虚
        if (w == 9 || w == 19) PP(w, 401, 8.6);
        else PP(w, 468, 7.4125);
        PP(w, i_len - 200);
        if (w == 9 || w == 19) {
            // 同样照着再打一个加速波
            PP(w, i_len + PCP);
            PP(w, i_len + 401);
            PPExceptOne(w, i_len + 601 + PCP, 9, { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT });
            if (w == 9) MaidDance(w, i_len + 601 + PCP, w + 1, PCP);
            else MaidDance(w, i_len + 601 + PCP, w + 1, -200);
            PPLast(w, 4300);
        }
    }
    for (int w: { 2, 4, 6, 8, 10, 12, 14, 16, 18 }) {
        PP(w);
        PP(w, 401);
    }
    for (int w: { 20 }) {
        PP(w, 309, 9, {2, 2, 5, 5});
        PP(w, 409, 9, {2, 2, 5, 5});
        P(w, 225, 4, 7.5875);
        PPExceptOne(w, 815);
        BlockLast(w, 820, 4290);
        PPLast(w, 4290);
    }
}