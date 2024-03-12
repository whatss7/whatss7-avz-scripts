#include "../walib.h"

void AScript() {
    WAInit({
        AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ALILY_PAD, ACHERRY_BOMB, 
        AJALAPENO, ASQUASH, ASPIKEWEED, AGARLIC, APUMPKIN
    });
    WAFixNuts();
    // C6u: IC-PA|N|Ia-PA'|PP (19, 6, 19, 6)
    // w1-w9: PP|ICC-PA|N|IaC-PA'|PP|ICC-PA|N|IaC-PA'|PP
    // w10-w19: PP|ICC-PA|N|IaC-PA'|PP|ICC-PA|N|IaC-PA'|PP|ICC-PA
    // w20: PP

    // 目前先只考虑慢速关
    for (int w: {1, 5, 9, 10, 14, 18, 20}) {
        PP(w);
    }
    for (int w: {3, 7, 12, 16}) {
        N(w, PCP, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
    }
    for (int w: {2, 6, 11, 15, 19}) {
        ManualI(w, 1, 1, 6, 601);
        AConnect(ATime(w, 400), [](){
            if (WAExistZombie(ABC_12, {2})) {
                ACard(ASPIKEWEED, 2, 9);
            }
        });
        AConnect(ATime(w, 1200), [](){
            if (WAExistZombie(ABC_12, {5})) {
                ACard(ASPIKEWEED, 5, 7);
            }
        });
        if (WAExistZombie(ABC_12, {5})) C(w, 1200, ASPIKEWEED, 5, 7);
        A(w, 1900 - 200, 2, 9);
        P(w, 1900 - 200, 5, 8.5);
    }
    for (int w: {4, 8, 13, 17}) {
        ManualI(w, 1, 1, 6, 601);
        C(w, 400, ASQUASH, {{2, 9}, {2, 8}, {2, 7}});
        AConnect(ATime(w, 700), [](){
            if (WAExistZombie(AXC_15, {2})) {
                ACard(AGARLIC, 2, 9);
            }
        });
        AConnect(ATime(w, 1200), [](){
            if (WAExistZombie(ABC_12, {5})) {
                ACard(ASPIKEWEED, 5, 7);
            }
        });
        J(w, 1900 - 200, 1, 6);
        P(w, 1900 - 200, 5, 8.5);
    }
}