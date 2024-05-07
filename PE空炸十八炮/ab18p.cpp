#include "../walib.h"

void AScript() {
    Init({ACHERRY_BOMB});
    for (int w: WaveList(1, 20)) {
        PP(w);
        if (AGetZombieTypeList()[ABY_23] || AGetZombieTypeList()[AHY_32]) {
            P(w, PCP + 110, 1, 8);
        } else {
            P(w, PCP + 110, 2, 9);
        }
        if (w == 10) {
            if (AGetZombieTypeList()[AHY_32]) {
                SmartA(w, PCP);
            } else {
                SmartA(w);
            }
        }
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