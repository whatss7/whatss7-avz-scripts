#include "../whatss7-avz2-lib/walib.h"

void AScript(){
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, ALILY_PAD, APUMPKIN, AUMBRELLA_LEAF, APUFF_SHROOM, ASUN_SHROOM});
    WAAutoManageCob();
    aIceFiller.Start({{2, 7}, {5, 7}, {6, 7}});
    aPlantFixer.Start(APUMPKIN);
    aPlantFixer.SetHp(4000 / 3 * 2);

    // ch6: I-PP|PP|I-PP|PP (12, 6, 12, 6)
    // 12秒冰波守7列，可以7列存冰，零冰开存冰比较极限，收尾必须手动拖满
    // 没有核弹首代是因为w9如果是加速波，收尾很难处理撑杆

    // w1-w9: PP|PP|I-PP|PP|I-PP|PP|I-PP|PP|I-PP
    // w10-w19: PPA|PP|I-PP|PP|I-PP|PP|I-PP|PP|I-PP|PP
    // w20: I-PP

    // w1, w2, w4, w5, w8, w12, w14, w16, w18: PP
    for (int w: {1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20}) {
        PP(w);
        if (w == 10) SmartA();
        if (w == 20) I(w, -50);
        if (w == 10 || w == 20) TempC(w, 300, AUMBRELLA_LEAF, 5, 8, 100);
    }

    // w3, w5, w7, w9, w11, w13, w15, w17, w19: I-PP
    for (int w: {3, 5, 7, 9, 11, 13, 15, 17, 19}) {
        I(w, 100);
        PP(w, 1200 - 200);
    }
}