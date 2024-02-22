#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, APUMPKIN, ADOOM_SHROOM, ALILY_PAD, ABLOVER});
    WAAutoManageCob();
    aIceFiller.Start({{1, 1}, {6, 1}, {2, 7}});
    WAFixNuts();
    WAStartBlover(1, 9);
    
    // ch4: IPP-PP|IPP-PP (18,18)
    // w1-w9: N|PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP
    // w10-w19: PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP|IPP-PP
    // W20: PP
    for (int w: {1}) {
        N(w, PCP, 3, 9);
    }
    for (int w: {2, 10, 20}) {
        PP(w);
    }
    for (int w: WaveList(3, 9) + WaveList(11, 19)) {
        I(w, 100);
        PP(w, 400, 8);
        PP(w, 1800 - 200, 8.5);
    }
}