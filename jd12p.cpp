#include <avz.h>
#include "whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit("PE", {AICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB});
    WAAutoManageCob();
    // regular waves: PP
    for (int w: WaveList(1, 9) + WaveList(11, 19)) {
        AConnect(ATime(w, PCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
    }
    // w9, w19: (PP-)PP-PP
    for (int w: { 9, 19 }) {
        AConnect(ATime(w, PCP), [](){
            aCobManager.RecoverFire({{2, 9}, {5, 9}, {2, 9}, {5, 9}});
        });
    }
    // w10: PPA
    // cherry de-delay
    AConnect(ATime(10, DPCP + CFT - ADT), [](){
        ACard(ACHERRY_BOMB, 2, 9);
    });
    AConnect(ATime(10, DPCP), [](){
        aCobManager.Fire({{2, 9}, {5, 9}});
    });
    // w20: I-PP-PP-PP
    // ice de-coral, 12s slow wave
    AConnect(ATime(20, 100 - 299), [](){
        ACard(AICE_SHROOM, 1, 1);
        ACard(ACOFFEE_BEAN, 1, 1);
    });
    AConnect(ATime(20, 1200 - 200 - CFT), [](){
        aCobManager.Fire({{2, 9}, {5, 9}});
    });
    AConnect(ATime(20, 1800 - 200 - CFT), [](){
        aCobManager.RecoverFire({{2, 9}, {5, 9}, {2, 9}, {5, 9}});
    });
}