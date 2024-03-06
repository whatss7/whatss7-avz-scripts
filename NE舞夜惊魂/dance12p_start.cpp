#include <avz.h>

int pos = 324;
ALogger<APvzGui> ingameLogger;

void AScript() {
    AConnect(ATime(1, -599), [](){
        AMaidCheats::Dancing();
    });
    AConnect('A', [](){
        pos -= 1;
        ingameLogger.Info("pos changed to #", pos);
    });
    AConnect('D', [](){
        pos += 1;
        ingameLogger.Info("pos changed to #", pos);
    });
    AConnect('S', [](){
        bool r1ok = false, r5ok = false;
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.Type() == AWW_8) {
                zombie.Abscissa() = 720;
            }
            if (zombie.Type() != ABW_9) continue;
            if (!r1ok && zombie.Row() == 0) {
                zombie.Abscissa() = pos;
                r1ok = true;
            } else if (!r5ok && zombie.Row() == 4) {
                zombie.Abscissa() = pos;
                r5ok = true;
            } else {
                zombie.Abscissa() = 720;
            }
        }
    });
}