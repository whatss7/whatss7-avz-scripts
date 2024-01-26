#ifndef WHATSS7_WALIB_H
#define WHATSS7_WALIB_H

#include "avz.h"
#include <algorithm>

#if __AVZ_VERSION__ <= 221001
#error "walib is designed for AvZ 2, which is incompatible with AvZ 1."
#elif __AVZ_VERSION__ < 240113
#warning "walib is designed for AvZ 2 version 240113. You're using an older version, which might cause issues."
#elif __AVZ_VERSION__ > 240113
#warning "walib is designed for AvZ 2 version 240113. You're using an newer version, which might cause issues."
#endif

// 玉米加农炮发射到生效用时
const int COB_FLYING_TIME = 373;
// 灰烬植物和寒冰菇种下到生效用时
const int ASH_DELAY_TIME = 100;
// 6秒加速波预判炸时间点
const int PRE_COB_POINT = -95;
// 旗帜波6秒加速波预判炸时间点
const int DELAYED_PRE_COB_POINT = -55;
// 咖啡豆生效时间198cs或199cs（此处取198cs）
const int COFFEE_BEAN_TIME = 198;
// 模仿者种下至生效时间319cd或320cs（此处取320cs）
const int IMITATOT_DELAY_TIME = 320;

// 玉米加农炮发射到生效用时
const int CFT = COB_FLYING_TIME;
// 灰烬植物和寒冰菇种下到生效用时
const int ADT = ASH_DELAY_TIME;
// 6秒加速波预判炸时间点
const int PCP = PRE_COB_POINT;
// 旗帜波6秒加速波预判炸时间点
const int DPCP = DELAYED_PRE_COB_POINT;
// 旗帜波6秒加速波预判炸时间点
const int W10PCP = DPCP, W20PCP = DPCP;
// 咖啡豆生效时间198cs或199cs（此处取198cs）
const int CBT = COFFEE_BEAN_TIME;
// 模仿者种下至生效时间319cd或320cs（此处取319cs）
const int MDT = IMITATOT_DELAY_TIME;

#ifdef WALIB_DEBUG
ALogger<AConsole> waDebugLogger;
#endif
ALogger<AMsgBox> waLogger;
ATickRunner waRecoverEndRunner;

// 获得当前所处的场地。
std::string WAGetCurrentScene() {
    std::string scenes[] = { "DE", "NE", "PE", "FE", "RE", "ME" };
    int scene_id = AGetMainObject()->Scene();
    if (scene_id < 0 || scene_id > 5) { waLogger.Error("未知的场地"); return ""; }
    else return scenes[scene_id];
}

// 初始化选卡并指定僵尸。传入空数组不指定僵尸，使用自然生成的僵尸。
// 选卡剩下的格子会用一些常用的植物填充防止漏选。
void WAInit(const std::vector<APlantType> &plants, const std::vector<AZombieType> &zombies, bool cycle = false) {
    if (!zombies.empty()) ASetZombies(std::vector<int>(zombies.begin(), zombies.end()));
    if(cycle) ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    // 使用常用植物填充植物格防止漏带
    std::vector<APlantType> extra_plants = {
        AICE_SHROOM,        // 寒冰菇
        ACOFFEE_BEAN,       // 咖啡豆
        ACHERRY_BOMB,       // 樱桃炸弹
        ADOOM_SHROOM,       // 毁灭菇
        ABLOVER,            // 三叶草
        APUFF_SHROOM,       // 垫材四人组：小喷菇
        ASUN_SHROOM,        // 垫材四人组：阳光菇
        ASCAREDY_SHROOM,    // 垫材四人组：胆小菇
        AFLOWER_POT,        // 垫材四人组：花盆
        AM_ICE_SHROOM       // 模仿者寒冰菇
    };
    std::vector<int> plant_ids(plants.begin(), plants.end());
    for (APlantType plant: extra_plants) {
        if (plant_ids.size() >= 10) break;
        // 检查植物是否已在列表中，若不在则用此植物填充
        if (std::find(plants.begin(), plants.end(), plant) == plants.end())  {
            plant_ids.push_back(plant);
        }
    }
    ASelectCards(plant_ids);
}

// 初始化选卡，并根据场地选择合理的僵尸。
// 选卡剩下的格子会用一些常用的植物填充防止漏选。
// 场地支持传入的参数：
// `"Manual"`: 或其他任意下方未提到的参数: 不进行僵尸选择，使用自然出怪
// `"Cycle"`: 不进行僵尸选择，使用自然出怪，并开启脚本挂机循环
// `"Auto"` 或不传入参数: 自动根据场地选择下面的组合
// `"DE"`: 路障 撑杆 橄榄 舞王 冰车 小丑 气球 矿工 蹦极 白眼 红眼
// `"NE"`: 路障 撑杆 橄榄 舞王 小丑 气球 矿工 跳跳 蹦极 白眼 红眼
// `"PE"` 或 `"FE"`: 撑杆 橄榄 舞王 冰车 海豚 小丑 气球 矿工 蹦极 白眼 红眼
// `"RE"` 或 `"ME"`: 路障 撑杆 橄榄 冰车 小丑 气球 跳跳 蹦极 扶梯 白眼 红眼
void WAInit(const std::vector<APlantType> &plants, std::string scene="Auto") {
    // 为各场地选择常见的出怪组合
    for (int i = 0; i < scene.length(); i++) {
        scene[i] = toupper(scene[i]);
    }
    if (scene == "AUTO") {
        scene = WAGetCurrentScene();
    }
    std::vector<AZombieType> zombies;
    bool cycle = false;
    if (scene == "PE" || scene == "FE") {
        zombies = { ACG_3, AGL_7, AWW_8, ABC_12, AHT_14, AXC_15, AQQ_16, AKG_17, ABJ_20, ABY_23, AHY_32 };
    } else if (scene == "DE") {
        // DE没有水路僵尸
        zombies = { ALZ_2, ACG_3, AGL_7, AWW_8, ABC_12, AXC_15, AQQ_16, AKG_17, ABJ_20, ABY_23, AHY_32 };
    } else if (scene == "NE") {
        // NE没有水路僵尸和冰车
        zombies = { ALZ_2, ACG_3, AGL_7, AWW_8, AXC_15, AQQ_16, AKG_17, ATT_18, ABJ_20, ABY_23, AHY_32 };
    } else if (scene == "RE" || scene == "ME") {
        // RE和FE没有水路僵尸、舞王和矿工
        zombies = { ALZ_2, ACG_3, AGL_7, ABC_12, AXC_15, AQQ_16, ATT_18, ABJ_20, AFT_21, ABY_23, AHY_32 };
    } else if (scene == "CYCLE") {
        // 不设置，并循环执行脚本
        cycle = true;
    }
    WAInit(plants, zombies, cycle);
}

void WAAutoManageCob() {
    AConnect(ATime(1, -599), [] {
        aCobManager.AutoSetList();
    });
}

void WASkipTo(int wave, int time = -199) {
    AConnect(ATime(1, -590), [wave, time](){
        ASkipTick(wave, time);
    });
}

class WaveList {
public:
    using iterator = std::vector<int>::iterator;
    WaveList(int _start, int _end) {
        if (_start > _end) std::swap(_start, _end);
        for (int i = _start; i <= _end; i++) {
            l.push_back(i);
        }
    }
    WaveList operator+(const WaveList &other) {
        WaveList new_list = *this;
        for (int i : other.l) {
            new_list.l.push_back(i);
        }
        sort(new_list.begin(), new_list.end());
        new_list.l.resize(unique(new_list.begin(), new_list.end()) - new_list.begin());
        return new_list;
    }
    iterator begin() { return l.begin(); }
    iterator end() { return l.end(); }
private:
    std::vector<int> l;
};

// WARecoverEnd 会在收尾波使用已恢复的炮清理剩余的僵尸。
// 默认炸9列，为血量最高的巨人僵尸留下600血。
// 用于收尾的最后一炮会在所有僵尸都走进范围后再开炮（x-757），默认伴舞除外，需要同时考虑伴舞的请使用 `IncludeBackupDancer()`.
// 请在最后一个运算量生效后再调用，例如：
// `AConnect(ATime(20, DPCP + CFT + 1), WARecoverEnd());`
struct WARecoverEnd {
    WARecoverEnd(float column = 9, int ioDamage = 600): column(column), ioDamage(ioDamage) {
        CM = &aCobManager;
        includeBD = false;
    }
    WARecoverEnd &setCobManager(ACobManager &cobManager) {
        CM = &cobManager;
        return *this;
    }
    void operator()() {
        ATime time = ANowTime();
        if (time.wave != 9 && time.wave != 19 && time.wave != 20) {
            waLogger.Error("当前波次不是收尾波，不能使用 WARecoverEnd");
        }
        DoRecoverFire();
    }
    WARecoverEnd &IncludeBackupDancer() {
        includeBD = true;
        return *this;
    }
private:
    void Fire() {
        std::string scene = WAGetCurrentScene();
        if (scene == "PE" || scene == "FE") {
            CM->RecoverFire({{2, column}, {5, column}});
        } else {
            CM->RecoverFire({{2, column}, {4, column}});
        }
    }
    void ScheduleFire() {
        waRecoverEndRunner.Start([this](){
            ATime now = ANowTime();
            if (now.wave != 9 && now.wave != 19 && now.wave != 20) {
                waRecoverEndRunner.Stop();
            }
            if (now.time < 0) {
                waRecoverEndRunner.Stop();
            }
            float max_x = 0;
            for (auto &&zombie: aAliveZombieFilter) {
                if (zombie.Type() == ABW_9 && !includeBD) continue;
                max_x = std::max(max_x, zombie.Abscissa() + zombie.BulletAbscissa());
            }
            #ifdef WALIB_DEBUG
            waDebugLogger.Info("max_x = " + std::to_string(max_x));
            #endif
            if (max_x == 0) {
                waRecoverEndRunner.Stop();
            }
            if (max_x <= 757) {
                waRecoverEndRunner.Stop();
                Fire();
            }
        });
    }
    void DoRecoverFire() {
        int maxHp = 0;
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.Type() == ABY_23 || zombie.Type() == AHY_32) {
                maxHp = std::max(maxHp, zombie.Hp());
            } else {
                maxHp = std::max(maxHp, 1800);
            }
        }
        if (maxHp > ioDamage) {
            ScheduleFire();
        }
        for (int i = ioDamage + 1800; i < maxHp; i += 1800) {
            Fire();
        }
    }
    bool includeBD;
    float column;
    int ioDamage;
    ACobManager *CM;
};

/*
// WAWaitEnd 会尽量自动拖住一波收尾。
// 默认场上存在持续减速，2垫拖巨人
// WAWaitEnd 假定所有其他僵尸已被清理，可能留下的有巨人、撑杆或伴舞。
// 对于留下巨人的情况，使用垫材拖住其中一路；
// 对于留下撑杆的情况，使用高坚果拦住。
struct WAEndWaiter {
    WAEndWaiter(int wave, int start_time, int column = 9, bool slow=true): column(column), slow(slow) {
        CM = &aCobManager;
    }
    void SetCobManager(ACobManager &cobManager) {
        CM = &cobManager;
    }
    void Start() {
        // 先尝试巨人拖收尾
        bool hasGiga[6], hasGiga2[6], hasGiga3[6], hasPole[6];
        memset(hasGiga, 0, sizeof(hasGiga));
        memset(hasGiga2, 0, sizeof(hasGiga2));
        memset(hasGiga3, 0, sizeof(hasGiga3));
        memset(hasPole, 0, sizeof(hasPole));
        for (auto &&zombie: aAliveZombieFilter) {
            if (zombie.Type() == ABY_23 || zombie.Type() == AHY_32) {
                hasGiga[zombie.Row()] = true;
                if (zombie.Hp() > 1800) hasGiga2[zombie.Row()] = true;
                if (zombie.Hp() > 3600) hasGiga3[zombie.Row()] = true;
            }
            if (zombie.Type() == ACG_3) hasPole[zombie.Row()] = true;
        }
        // 模式一：一列有巨人无撑杆
        if (hasGiga[1]) {
            if (hasGiga[2]) {
                if (hasGiga2[1]) CM->Fire(2, column);
            }
        }
    }
    bool slow;
    int wave;
    int column;
    ACobManager *CM;
};
*/

#endif // WHATSS7_WALIB_H