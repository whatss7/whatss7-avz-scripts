#include "../walib.h"

void AScript() {
    Init({
        ALILY_PAD, ADOOM_SHROOM, AM_DOOM_SHROOM, ACHERRY_BOMB, AJALAPENO,
        APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT, ASUNFLOWER
    });
    const int a_len = 875, n_len = 850;
    // 每个巨人需要施用4次垫材才能严谨不砸炮

    // =================废弃，这段考虑4张垫材是否可行=================
    // 分为早垫（炮生效前垫）和晚垫（炮生效后垫）
    // 655就可能锤不到9列，第一个垫材施用后208+320内在9列施用第二个垫材可垫到巨人
    // 晚垫是为了防止拦截炮蹭巨人，因此必须在9列，且每波1/5列都必须种
    // 因为要拦截，675时巨人不能正在收手，早垫考虑250种450铲
    // =================废弃，这段考虑4张垫材是否可行=================

    // =================废弃，这段考虑4张垫材是否可行=================
    // 先考虑5列，这里每波都必须种晚垫
    // 考虑一个早晚-晚-早晚的红眼：早垫垫不到，第一晚垫可以垫到，然后投掷
    // 676锤+208收手，1550投掷+142收手，walk([676, 666]) = [593, 700]，第二晚垫垫不到了
    // 第三早垫时间巨人位置
    // 考虑一个晚-早晚-晚的巨人：
    // =================废弃，这段考虑4张垫材是否可行=================
    for (int w: {1, 2, 4, 5, 6, 8, 9, 10, 11, 12, 14, 15, 16, 18, 19, 20}) {
        MaidDance(w, 263, 785);
        TempC(w, 100, ASCAREDY_SHROOM, 2, 8, 300);
        TempC(w, 100, AFLOWER_POT, 5, 8, 300);
        PP(w, a_len - 200, 8.4);
        TempC(w, a_len - 200 + 1, ASUNFLOWER, 1, 9, 821);
        TempC(w, a_len - 200 + 1, APUFF_SHROOM, 2, 9, 821);
        TempC(w, a_len - 200 + 1, ASUN_SHROOM, 5, 9, 821);
        DD(w, a_len - 200 + 110, 7.2);
        if (w == 9 || w == 19) {
            // 再打一个PD，剩下的应该都是一血红
            TempC(w, a_len + 100, ASCAREDY_SHROOM, 2, 8, a_len + 300);
            TempC(w, a_len + 100, AFLOWER_POT, 5, 8, a_len + 300);
            PP(w, a_len + a_len - 200, 8.4);
            DD(w, a_len + a_len - 200 + 110, 7.2);
            TempC(w, a_len + a_len - 200 + 1, APUFF_SHROOM, 2, 9, a_len + 821);
            TempC(w, a_len + a_len - 200 + 1, ASUN_SHROOM, 5, 9, a_len + 821);
            // 开始拖收尾
            TempC(w, a_len + a_len + 100, ASCAREDY_SHROOM, 2, 8, 300);
            TempC(w, a_len + a_len + 100, AFLOWER_POT, 5, 8, 300);
            PPExceptOne(w, a_len + a_len + n_len - 200 + 111 + 10, 7.5, { APUFF_SHROOM, ASUN_SHROOM, ASCAREDY_SHROOM, AFLOWER_POT });
            PPLast(w, 4300);
        }
    }
    for (int w: {3, 13}) {
        MaidDance(w, 263, 760);
        TempC(w, 100, ASCAREDY_SHROOM, 2, 8, 300);
        TempC(w, 100, AFLOWER_POT, 5, 8, 300);
        C(w, n_len - 200 - 110 - ADT, { ALILY_PAD, ACHERRY_BOMB }, 3, w == 3 ? 9 : 8);
        C(w, n_len - 200 - ADT, ADOOM_SHROOM, 3, w == 3 ? 9 : 8);
        DD(w, n_len - 200 + 110, 7.2);
        TempC(w, n_len - 200 + 1, APUFF_SHROOM, 2, 9, 821);
        TempC(w, n_len - 200 + 1, ASUN_SHROOM, 5, 9, 821);
    }
    for (int w: {7, 17}) {
        MaidDance(w, 263, 760);
        TempC(w, 100, ASCAREDY_SHROOM, 2, 8, 300);
        TempC(w, 100, AFLOWER_POT, 5, 8, 300);
        J(w, n_len - 200 - 110, 5, 8);
        C(w, n_len - 200 - ADT - MDT, { ALILY_PAD, AM_DOOM_SHROOM }, 4, w == 7 ? 9 : 8);
        DD(w, n_len - 200 + 111, 7.2);
        TempC(w, n_len - 200 + 1, APUFF_SHROOM, 2, 9, 821);
        TempC(w, n_len - 200 + 1, ASUN_SHROOM, 5, 9, 821);
    }
}