#include <avz.h>
#include "whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit("PE", {AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, ADOOM_SHROOM, APUFF_SHROOM, ASUN_SHROOM, ABLOVER});    
    WAAutoManageCob();

    // ch4 18+18 I-PP|I-PP
    // start N|PP|I-PP|... (try later)

    aIceFiller.Start({{3, 5}, {1, 4}, {6, 4}});

    // w1/w10/w20 PP
    for (int w: {1, 10, 20}) {
        AConnect(ATime(w, 318 - CFT), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
    }

    // w2/w11 I-PP
    for (int w: {2, 11}) {
        AConnect(ATime(w - 1, 600 - 200), [](){
            aIceFiller.Coffee();
        });
        AConnect(ATime(w, 1800 - 200 - CFT), [](){
            aCobManager.Fire({{2, 8}, {5, 8}});
        });
    }

    // w9/w19 I-PP-PP
    for (int w: {9, 19}) {
        AConnect(ATime(w - 1, 1800 - 200), [](){
            aIceFiller.Coffee();
        });
        AConnect(ATime(w, 1800 - 200 - CFT), [](){
            aCobManager.Fire({{2, 8}, {5, 8}});
        });
        AConnect(ATime(w, 1800 - 200 - CFT), [](){
            aCobManager.RecoverFire({{2, 8}, {5, 8}});
        });
    }


    // regular I-PP
    for (int w: WaveList(3, 8) + WaveList(12, 18)) {
        AConnect(ATime(w - 1, 1800 - 200), [](){
            aIceFiller.Coffee();
        });
        AConnect(ATime(w, 1800 - 200 - CFT), [](){
            aCobManager.Fire({{2, 8}, {5, 8}});
        });
    }

}