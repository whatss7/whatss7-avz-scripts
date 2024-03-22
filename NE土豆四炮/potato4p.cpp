#include "../walib.h"

ATickRunner potatoRunner;

void AScript() {
    Init({
        APOTATO_MINE, AUMBRELLA_LEAF, AICE_SHROOM, AM_ICE_SHROOM, ADOOM_SHROOM, 
        ACHERRY_BOMB, AJALAPENO, ASQUASH, ABLOVER, AGRAVE_BUSTER
    });
    AutoBlover(2, 1);
    StartReloadMode();

    const int short_len = 1600, long_len = 1900, n_len = 690;

    for (int w: {1, 6, 11, 16}) {
        // 此处使用智能脚本，引入底线炮伤，防止短冰波矿工啃食土豆雷
        // 矿工到达159时，不会再啃食土豆雷
        // 根据时空数据，最早914，最晚1001矿工不会再啃食土豆雷
        // 根据-650种土豆雷的时间，若要波长至少为1600，最早950可种，过450炮生效，过651冰生效
        ManualI(w, 1, 4, 1, 601);
        AConnect(ATime(w, 950), [w](){
            ARemovePlant(3, 3, APOTATO_MINE);
            potatoRunner.Start([w](){
                float slow = 0;
                for (auto &&zombie: aAliveZombieFilter) {
                    if (zombie.Row() + 1 == 3 && zombie.Type() == AKG_17) {
                        slow = std::max(slow, zombie.Abscissa());
                    }
                }
                if (slow < 159) {
                    ACard(APOTATO_MINE, 3, 3);
                    PP(w, ANowTime().time + 450, 8.45);
                    ManualI(w, ANowTime().time + 651, 4, 1);
                    potatoRunner.Stop();
                }
            });
        });
    }
    for (int w: {2, 7, 12, 17}) {
        // I(); 已在上波处理
        PP(w, long_len - 200, 8.3);
    }
    for (int w: {3, 8, 13, 18}) {
        // AA'a波，希望窝瓜不演戏
        A(w, PCP, 4, 9);
        J(w, PCP, 1, 9);
        C(w, 136, ASQUASH, 2, 9);
    }
    for (int w: {4, 9, 14, 19}) {
        // N波，延长到690
        N(w, n_len - 200, {{3, 9}, {3, 8}, {2, 8}, {4, 8}});
        if (w == 9 || w == 19) {
            PP(w, n_len + PCP);
            ManualI(w, n_len + 601 + 1, 4, 1);
            AConnect(ATime(w, n_len + 601 + short_len - 200 - CFT), [w](){
                PP(w, n_len + 601 + short_len - 200, 8.3);
            });
        }
    }
    for (int w: {5, 10, 15, 20}) {
        if (w == 10 || w == 20) {
            TempC(w, -500, AUMBRELLA_LEAF, 3, 3, 400);
            TempC(w, 300, AUMBRELLA_LEAF, 2, 7, 400);
        }
        PP(w);
        if (w == 20) {
            RemoveGraves(w, 3901);
            C(w, 2001, APOTATO_MINE, 3, 3);
            ManualI(w, 601 + 1, 4, 1);
            PP(w, 601 + short_len - 200, 8.5);
            ManualI(w, 601 + short_len + 1, 4, 1);
            PP(w, 601 + short_len + long_len - 200, 8.5);
        }
    }
}