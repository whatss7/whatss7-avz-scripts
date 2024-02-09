#include "../whatss7-avz2-lib/walib.h"

void AScript() {
    // 因为潜水有啃核威胁，所以特别加上
    WAInit({ADOOM_SHROOM, AM_DOOM_SHROOM, AICE_SHROOM, ALILY_PAD, ACOFFEE_BEAN, ACHERRY_BOMB, APUMPKIN},
           std::vector<AZombieType>({ACG_3, AGL_7, AWW_8, AQS_11, ABC_12, AHT_14, AXC_15, AKG_17, ABJ_20, ABY_23, AHY_32}));
    WAAutoManageCob();
    aIceFiller.Start({{2, 7}});

    // S6: I-N|PP|PP|PP|PP (12, 6, 6, 6, 6)
    // w1-w9: PP|PP|PP|PP|I-N|PP|PP|PP|PPN'
    // w10-w19: PP|PP|PP|PP|I-N|PP|PP|PP|PP|I-N'
    // w20: PPDD

    // 加速波 PP
    for (int w: WaveList(1, 9) + WaveList(11, 19)) {
        if (w == 5 || w == 14 || w == 19) continue;
        // PP
        AConnect(ATime(w, PCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
    } 
    // w9 N' 炸撑杆
    for (int w: {9}) {
        AConnect(ATime(w - 1, 400 - CBT - ADT - MDT + 600), [](){
            ACard({ALILY_PAD, AM_DOOM_SHROOM}, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
        });
        AConnect(ATime(w, 400 - CBT - ADT), [](){
            ACard(ACOFFEE_BEAN, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
        });
    }
    // 冰波 w5/w14 I-N
    for (int w: {5, 14}) {
        // I
        AConnect(ATime(w, -199), [](){ aIceFiller.Coffee(); });
        // N
        AConnect(ATime(w, 1200 - 200 - CBT - ADT), [](){
            ACard({ALILY_PAD, APUMPKIN, ADOOM_SHROOM, ACOFFEE_BEAN}, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
        });
    }
    // 冰波 w19 I-N'
    for (int w: {19}) {
        // I
        AConnect(ATime(w, -199), [](){ aIceFiller.Coffee(); });
        // N'
        AConnect(ATime(w, 1200 - 200 - CBT - ADT - MDT), [](){
            ACard({ALILY_PAD, APUMPKIN, AM_DOOM_SHROOM}, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
        });
        AConnect(ATime(w, 1200 - 200 - CBT - ADT), [](){
            ACard(ACOFFEE_BEAN, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
        });
    }
    // 旗帜波 w10 消延迟 w20 炸撑杆
    for (int w: {10, 20}) {
        AConnect(ATime(w, DPCP), [](){
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        // 消延迟
        if (w == 10) {
            AConnect(ATime(w, 400 - ADT), [](){
                ACard(ACHERRY_BOMB, 2, 9);
            });
        }
        // 炸撑杆
        if (w == 20) {
            AConnect(ATime(w, 400 - CFT), [](){
                aCobManager.Fire({{2, 9}, {5, 9}});
            });
        }
    }
}