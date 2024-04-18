#include "../walib.h"


void AScript() {
    Init({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN});
    aIceFiller.Start({{2, 3}, {4, 6}});
    for (int w: {1, 10}) {
        
    }
    for (int w: WaveList(3, 9) + WaveList(12, 19)) {
        I3(w, 11, 1800);
        RoofP(w, 410, 2, 2, 9);
        RoofP(w, 410, 7, 4, 9);
        RoofP(w, 630, 1, 2, 8.5);
        RoofP(w, 630, 6, 4, 8.5);
        TempC(w, 950, AFLOWER_POT, 2, 9, 1150);
        RoofP(w, 1140, 7, 4, 8.1);
        RoofP(w, 1600, 4, 2, 9);
        RoofP(w, 1600, 4, 4, 9);
    }
}