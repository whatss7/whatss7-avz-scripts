#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({ AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, ATALL_NUT });
    WAAutoManageCob();
    aIceFiller.Start({{2, 1}, {5, 1}});
    WAMaidDefault(1);
    int i_len = 1250;
    // ch6: IPP-PP | BBDD
    // 考虑一个加速波巨人，出生到砸炮需要1029cs，602cs被冻结，最早602+400+854+142投掷=1998砸炮
    // 下一个加速波不可能148就生效炮，所以需要垫一下
    for (int w: { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 }) {
        I(w, 1, 601);
        // 双边热过渡要炸虚
        PP(w, 468, 7.4125);
        // 巨人全部解冻后垫
        TempC(w, 602, APUFF_SHROOM, 1, 9, 702);
        TempC(w, 602, ASUN_SHROOM, 2, 9, 702);
        TempC(w, 602, ASCAREDY_SHROOM, 5, 9, 702);
        TempC(w, 602, AFLOWER_POT, 6, 9, 702);
        PP(w, i_len - 200);
        if (w == 9 || w == 19) {
            // 同样照着再打一个加速波
            PP(w, i_len + PCP);
            PP(w, i_len + 359);
            PPExceptOne(w, i_len + 601 + PCP);
            WAStopGiga(w, i_len + 601 + PCP, { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT }, 4300);
            if (w == 9) WAMaidDance(w, i_len + 601 + PCP, w + 1, PCP);
            else WAMaidDance(w, i_len + 601 + PCP, w + 1, -200);
            PPLast(w, 4300);
        }
    }
    for (int w: { 2, 4, 6, 8, 10, 12, 14, 16, 18 }) {
        PP(w);
        PP(w, 359);
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