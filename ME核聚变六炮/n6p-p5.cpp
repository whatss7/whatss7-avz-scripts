#include "../walib.h"

void AScript() {
    Init({
        ADOOM_SHROOM, AM_DOOM_SHROOM, AICE_SHROOM, AUMBRELLA_LEAF, ACHERRY_BOMB,
        AJALAPENO, ASQUASH, AFLOWER_POT, AKERNEL_PULT, ACOB_CANNON
    });
    for (int w: {1, 2, 3, 6, 7, 8, 11, 12, 13, 16, 17, 18}) {
        PP(w, 500);
    }
    for (int w: {4, 14}) {
        WhiteN(w, 500, w == 4 ? 2 : 3, 8);
    }
    for (int w: {5, 15}) {
        ZomboniN(w, 500, w == 5 ? 2 : 3, 9);
    }
    for (int w: {9, 19}) {
        // AA'a 花盆转不过来...
    }
    for (int w: {10}) {
        RoofP(w, 500, 2, 9, 1);
        ZomboniA(w, 500, 4, 9);
        waRoofCobManager[1].FixLatest();
        TempC(w, 300, AUMBRELLA_LEAF, 4, 2, 399);
        ManualI(w, 500, 4, 2);
    }
}