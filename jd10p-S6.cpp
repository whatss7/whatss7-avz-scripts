#include <avz.h>
#include "whatss7-avz2-lib/walib.h"

void AScript(){
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ACOFFEE_BEAN, ACHERRY_BOMB});
    WAAutoManageCob();
    aIceFiller.Start({{2, 7}});
    
    // S6: I-PP|PP|PP|PP|PP (12,6,6,6,6)
    // w1-w9: PP|PP|PP|PP|PP|I-PP|PP|PP|PP
    // w10-w19: PP|PP|PP|PP|I-PP|PP|PP|PP|PP|I-PP
    // w20: PP

    for (int w: { 1, 2, 3, 4, 5, 7, 8, 9, 11, 12, 13, 15, 16, 17, 18}) {
        AConnect(ATime(w, PCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
    }

    for (int w: { 10, 20 }) {
        AConnect(ATime(w, DPCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        // 炮炸珊瑚
        if (w == 20) {
            AConnect(ATime(w, 225 - CFT), [](){
                aCobManager.Fire({{4, 7.5}});
            });
        }
        // 炮炸蹦极
        AConnect(ATime(w, 400 - CFT), [](){
            aCobManager.Fire({{4, 7.5}});
        });
        // 消延迟
        if (w == 10) {
            AConnect(ATime(w, DPCP + CFT - ADT), [](){
                ACard(ACHERRY_BOMB, 2, 9);
            });
        }
    }

    for (int w: {6, 14, 19}) {
        if (w == 19) {
            AConnect(ATime(w - 1, -199 + 600 - MDT), [](){
                ACard(AM_ICE_SHROOM, 1, 1);
            });
            AConnect(ATime(w, -199), [](){
                ACard(ACOFFEE_BEAN, 1, 1);
            });
        } else {
            AConnect(ATime(w, -199), [](){
                ACard({AICE_SHROOM, ACOFFEE_BEAN}, 1, 1);
            });
        }
        AConnect(ATime(w, 1200 - 200 - CFT), [](){
            aCobManager.Fire({{2, 8.5}, {5, 8.5}});
        });
    }
}