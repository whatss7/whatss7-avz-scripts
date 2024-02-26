#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({ACHERRY_BOMB});
    for (int w: WaveList(1, 20)) {
        PP(w);
        P(w, PCP + 110, 1, 8);
        if (w == 10) SmartA(w, PCP);
        if (w == 20) P(w, 225, 4, 7.5875);
        if (w == 9 || w == 19 || w == 20) {
            ForEnd(w, PCP + 601 - CFT, [w](){
                PP(w, PCP + 601);
                P(w, PCP + 601 + 110, 1, 8);
            });
            ForEnd(w, PCP + 601 * 2 - CFT, [w](){
                PP(w, PCP + 601 * 2);
            });
            ForEnd(w, PCP + 601 * 3 - CFT, [w](){
                PP(w, PCP + 601 * 3);
            });
        }
    }
}