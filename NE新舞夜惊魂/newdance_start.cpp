#include <avz.h>

ALogger<APvzGui> logger;

void AScript() {
    AConnect('S', [](){
        bool w9ok = false, w19ok = false;
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.Type() == AFT_21) {
                if (zombie.Row() + 1 == 2) {
                    zombie.AtWave() = 8;
                    w9ok = true;
                } else {
                    zombie.AtWave() = 18;
                    w19ok = true;
                }
            }
        }
        logger.Info("wave 9 #; wave 19 #.", w9ok ? "yes" : "no", w19ok ? "yes" : "no");
    });
}