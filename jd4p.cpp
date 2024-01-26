#include <avz.h>
#include "whatss7-avz2-lib/walib.h"

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB, ADOOM_SHROOM, ALILY_PAD, APUFF_SHROOM, ASUN_SHROOM, APUMPKIN});    
    WAAutoManageCob();
    aPlantFixer.Start(APUMPKIN);
    aPlantFixer.SetHp(4000 / 3 * 2);

    WASkipTo(9, 100);

    // ch4 I-PP|I-PP (18, 18)

    aIceFiller.Start({{3, 5}, {1, 4}, {6, 4}});

    // w1 N
    for (int w: {1}) {
        AConnect(ATime(w, PCP + CFT - ADT - CBT), [](){
            ACard({ALILY_PAD, ADOOM_SHROOM, ACOFFEE_BEAN}, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
        });
    }

    // w2 PP
    for (int w: {2}) {
        AConnect(ATime(w, PCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
    }

    // w10 PPA 樱桃消延迟
    for (int w: {10}) {
        AConnect(ATime(w, DPCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        AConnect(ATime(w, DPCP + CFT - ADT), [](){
            ACard(ACHERRY_BOMB, 2, 9);
        });
    }

    // w11 I-PP 点冰要在刷新前，冰杀w10蹦极
    for (int w: {11}) {
        AConnect(ATime(w - 1, 650 - CBT - ADT), [](){
            aIceFiller.Coffee();
        });
        AConnect(ATime(w, 1800 - 200 - CFT), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
    }

    // w20 I-PP 但冰杀蹦极
    for (int w: {20}) {
        AConnect(ATime(w, 400 - CBT - ADT), [](){
            aIceFiller.Coffee();
        });
        AConnect(ATime(w, 1800 - 200 - CFT), [](){
            aCobManager.Fire({{2, 8}, {5, 8}});
        });
    }

    // 常规 I-PP
    for (int w: WaveList(3, 9) + WaveList(12, 19)) {
        AConnect(ATime(w, -199), [](){
            aIceFiller.Coffee();
        });
        AConnect(ATime(w, 1800 - 200 - CFT), [](){
            aCobManager.Fire({{2, 8}, {5, 8}});
        });
        if (w == 9 || w == 19) {
            AConnect(ATime(w, 1800 - 200 - CBT - ADT), [w](){
                ACard({ALILY_PAD, ADOOM_SHROOM, ACOFFEE_BEAN}, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
            });
        }
    }

}