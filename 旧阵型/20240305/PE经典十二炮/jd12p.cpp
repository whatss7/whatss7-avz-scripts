#include <avz.h>
#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB});
    WAAutoManageCob();
    for (int w: WaveList(1, 20)) {
        PP(w);
        if (w == 9 || w == 19 || w == 20) {
            PPForEnd(w, 1200 - 200);
            PPForEnd(w, 1800 - 200);
        }
        if (w == 10) SmartA();
        if (w == 20) ManualI(w, -50, 1, 1);
    }
}