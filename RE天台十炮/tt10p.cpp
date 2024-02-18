#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, AFLOWER_POT, ACOB_CANNON});
    WAAutoManageCob();
    for (int w: WaveList(1, 20)) {
        PP(w, 700 - 200);
        if (w == 20) ManualI(w, -50, {{1, 8}});
        if (w == 9 || w == 19 || w == 20) {
            PPForEnd(w, 1400 - 200);
            PPForEnd(w, 2100 - 200);
            PPForEnd(w, 2800 - 200);
        }
    }
}
