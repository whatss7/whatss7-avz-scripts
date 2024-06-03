#include "../walib.h"

void AScript() {
    Init({
        AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, APUMPKIN, ADOOM_SHROOM,
        ACHERRY_BOMB, AJALAPENO, ASPIKEWEED, APUFF_SHROOM, ASUN_SHROOM 
    });
    StartIceFiller({{1, 1}, {1, 6}, {5, 1}, {5, 6}}); 
    int i_len = 1750;
    for (int w: {1}) {
        N(w, PCP, 2, 9);
        P(w, PCP + 262, 3, 2.4625);
    }
    for (int w: {2}) {
        A(w, PCP, 1, 9);
        P(w, PCP, 4, 8.7);
        P(w, PCP + 262, 3, 2.4625);
    }
    for (int w: {10, 20}) {
        PP(w, PCP, 8.7);
        P(w, PCP + 262, 3, 2.4625);
    }
    for (int w: WaveList(3, 8) + WaveList(11, 18)) {
        I(w, 12, w == 3 ? 601 : i_len);
        PP(w, i_len - 200);
        P(w, i_len - 200 + 365, 3, 2.4625);
    }
    for (int w: {9, 19}) {
        // I-A' 00100-A 01210-PP 12421-N 23432
        I(w, 12, i_len); 
        PP(w, i_len - 200);
        P(w, i_len - 200 + 365, 3, 2.4625);
    }
}