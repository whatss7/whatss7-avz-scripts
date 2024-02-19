#include "../whatss7-avz2-lib/walib.h"

void DelayRemovingAJ(int wave, int time) {
    AConnect(ATime(wave, time - ADT), [wave, time](){
        int uby = 0, uhy = 0, dby = 0, dhy = 0;
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.Type() == ABY_23) {
                if (zombie.Row() < 3) uby++;
                else dby++;
            } else if (zombie.Type() == AHY_32) {
                if (zombie.Row() < 3) uhy++;
                else dhy++;
            }
        }
        if (uby * 2 + uhy * 3 > dby * 2 + dhy * 3) {
            A(wave, time, 2, 9);
            J(wave, time, 6, 4);
        } else {
            A(wave, time, 5, 9);
            J(wave, time, 1, 4);
        }
    });
}

void AScript() {
    WAInit({AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, ALILY_PAD, ACOFFEE_BEAN, AJALAPENO}, "None", true);
    WACheck();
    WAAutoManageCob();
    // 存在红眼时，使用S6节奏；否则，使用P6节奏。
    if (AGetZombieTypeList()[AHY_32]) {
        AAssumeWavelength({
            ATime(1, 601), ATime(2, 601), ATime(3, 601), ATime(4, 601), ATime(5, 1200), 
            ATime(6, 601), ATime(7, 601), ATime(8, 601),
            ATime(10, 601), ATime(11, 601), ATime(12, 601), ATime(13, 601), ATime(14, 1200), 
            ATime(15, 601), ATime(16, 601), ATime(17, 601), ATime(18, 601)
        });
        // S6: I-PP|PP|PP|PPSS|PP
        // w1红眼到w4 100cs被冻，存活2678cs，最早命中100+400冻结+800*2减速+(1997-800)=3297cs
        // w2红眼到w4 存活1478cs，最早命中1997cs
        // w3红眼到w5 存活1478cs，最早命中1997cs
        // w4红眼到w6 1300cs被冻，存活2200cs，最早命中1300+400冻结+(1997-1300)*2减速=2397cs
        // w5红眼到w8 700cs被冻，存活2678cs，最早命中700+400冻结+800*2减速+(1997-1500)=3197cs
        // 由此，此循环全收红眼守6列炮
        // w1-w9: PP|PP|PPDD|PP|IC-PP|PP|PP|PPDD|IC-PP-PP-PP-PP
        // w10-w19: PPAdd|PP|NDD|PP|IC-PP|PP|PP|PPDD|PP|IC-PP-PP-PP-PP
        // w20: Idd-PP-PP-PP-PP
        // 加速波：PP或PPSS
        for (int w: WaveList(1, 18)) {
            if (w == 5 || w == 9 || w == 12 || w == 14) continue;
            PP(w);
            // PPDD波
            if (w == 3 || w == 8 || w == 17) PP(w, PCAP + 110);
            // w10 炸蹦极，消延迟
            if (w == 10){
                PP(w, 400, 2);
                DelayRemovingA(w, 400);
            }
        }
        for (int w: {12}) {
            N(w, PCAP, 3, 9);
            PP(w, PCAP + 110);
        }
        // 冰波：IC-PP，w20顺便冰消珊瑚，放置地刺保证w10放樱桃消延迟
        for (int w: {5, 9, 14, 19, 20}) {
            ManualI(w, 100, 1, 4);
            PP(w, 1200 - 200, 9);
            // C(w, 400, ASPIKEWEED, 2, 9);
            // 收尾波
            if (w == 9 || w == 19 || w == 20) {
                PPForEnd(w, 1800 - 200);
                PPForEnd(w, 2400 - 200);
                PPForEnd(w, 3000 - 200);
            }
            // w20 炸蹦极
            if (w == 20) PP(w, 400, 2);
        }
    } else {
        // P6: PP|PP|PP|PP|PP|PP
        // w1-w9: PP|PP|PP|PP|PP|PP|PP|PP|PP
        // w10-w19: PPdd|I-PP|PP|PP|PP|PP|PP|PP|PP|PP
        // w20: Idd-PP

        AAssumeWavelength({
            ATime(1, 601), ATime(2, 601), ATime(3, 601), ATime(4, 601), ATime(5, 601), 
            ATime(6, 601), ATime(7, 601), ATime(8, 601),
            ATime(10, 601), ATime(11, 1200), ATime(12, 601), ATime(13, 601), ATime(14, 601), 
            ATime(15, 601), ATime(16, 601), ATime(17, 601), ATime(18, 601)
        });
        for (int w: WaveList(1, 10) + WaveList(12, 19)) {
            PP(w);
            if (w == 9 || w == 19) {
                PPForEnd(w, 1200 - 200);
                PPForEnd(w, 1800 - 200);
            }
            // w10 炸蹦极，消延迟
            if (w == 10){
                PP(w, 400, 2);
                DelayRemovingA(w, 400);
            } 
        }
        for (int w: {11, 20}) {
            ManualI(w, 100, 1, 4);
            // C(w, 400, ASPIKEWEED, 2, 9);
            PP(w, 1200 - 200); 
            // w20 炸蹦极
            if (w == 20) {
                PP(w, 400, 2);
                PPForEnd(w, 1800 - 200);
                PPForEnd(w, 2400 - 200);
            }
        }
    }
}