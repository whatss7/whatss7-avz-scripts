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
#define DEBUG_LOG(x) waDebugLogger.Info(x)
#else
#define DEBUG_LOG(x)
#endif
ALogger<AMsgBox> waLogger;
ATickRunner waRecoverEndRunner;
ATickRunner waCheckRunner;
std::vector<APlantType> waCheckPlants = { ACOB_CANNON, AGLOOM_SHROOM, AWINTER_MELON };

// 获得当前所处的场地。
std::string WAGetCurrentScene() {
    std::string scenes[] = { "DE", "NE", "PE", "FE", "RE", "ME" };
    int scene_id = AGetMainObject()->Scene();
    if (scene_id < 0 || scene_id > 5) { waLogger.Error("未知的场地"); return ""; }
    else return scenes[scene_id];
}

bool WAHasZombie(std::vector<AZombieType> types) {
    for (auto &&zombie: aAliveZombieFilter) {
        if (std::find(types.begin(), types.end(), zombie.Type()) != types.end()) return true;
    }
    return false;
}

bool WAHasZombie(AZombieType type) {   
    return WAHasZombie(std::vector<AZombieType>({type}));
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

// 启动测试模式：10倍速，当忧郁菇、冰瓜投手或玉米加农炮受损时弹窗提示。
// 检测受损的植物类型可通过修改向量 waCheckPlants 进行设置。
void WACheck() {
    ASetGameSpeed(10);
    waCheckRunner.Start([](){
        for (auto &&plant: aAlivePlantFilter) {
            if (std::find(waCheckPlants.begin(), waCheckPlants.end(), plant.Type()) != waCheckPlants.end()) {
                if (plant.Hp() != plant.HpMax()) {
                    waLogger.Error("第" + std::to_string(plant.Row() + 1) + "行第" + std::to_string(plant.Col() + 1) + "列植物受损");
                    waCheckRunner.Stop();
                    break;
                }
            }
        }
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

// WAEndCobber 会在收尾波使用已恢复的炮清理剩余的僵尸。
// 默认提供 waEndCobber 直接使用，但每个对象只能用于一种收尾方式，若需要更多收尾方式需定义新的全局变量。
// 默认炸9列，为血量最高的巨人僵尸留下600血。
// 用于收尾的最后一炮会在所有僵尸都走进范围后再开炮，默认考虑除伴舞外所有僵尸。
// 毫无 IO 又有前置植物需要保护时，请使用 `IncludeBackupDancer()` 同时考虑伴舞。
// IO 较强的阵可以无视一般僵尸时，请使用  `Bucket()`, `Football()` 和 `Giga()` 选择能处理的僵尸等级。
// 其他情况，可以使用 `setIgnoreList()` 和 `setDangerList()` 进行的手动处理。
// 注意调用其中一个会覆盖之前这两个函数进行的所有设置，且水路和陆路需要分开设置。
// 请在最后一个运算量生效后再调用，例如：
// `AConnect(ATime(20, DPCP + CFT + 1), WAEndCobber());`
class WAEndCobber {
public:
    WAEndCobber() {
        column = 9;
        ioDamage = 600;
        Default();
    }
    void setColumn(float col) {
        column = col;
    }
    void setIODamage(int io) {
        ioDamage = io;
    }
    void setIgnoreList(const std::vector<AZombieType> &ignore) {
        list_is_ignore = true;
        list = ignore;
    }
    void setDangerList(const std::vector<AZombieType> &danger) {
        list_is_ignore = false;
        list = danger;
    }
    void setWaterIgnoreList(const std::vector<AZombieType> &ignore) {
        list_is_ignore = true;
        list = ignore;
    }
    void setWaterDangerList(const std::vector<AZombieType> &danger) {
        list_is_ignore = false;
        list = danger;
    }
    // 无视除白眼、红眼外的所有僵尸
    void Giga() {
        setDangerList({ABY_23, AHY_32});
    }
    // 无视除橄榄、白眼、红眼外的所有僵尸
    void Football() {
        setDangerList({AGL_7, ABY_23, AHY_32});
    }
    // 无视除铁桶、橄榄、白眼、红眼外的所有僵尸
    void Bucket() {
        setDangerList({ATT_4, AGL_7, ABY_23, AHY_32});
    }
    // 还原为默认行为
    void Default() {
        setWaterIgnoreList({});
        setIgnoreList({ABW_9});
    }
    // 考虑所有僵尸
    void IncludeBackupDancer() {
        setIgnoreList({});
    }
    void operator()() {
        ATime time = ANowTime();
        if (time.wave != 9 && time.wave != 19 && time.wave != 20) {
            waLogger.Error("当前波次不是收尾波，不能使用 WAEndCobber");
        }
        DoRecoverFire();
    }
private:
    static bool isIncluded(AZombie &zombie, 
                           const std::vector<AZombieType> &list, bool list_is_ignore, 
                           const std::vector<AZombieType> &water_list, bool water_list_is_ignore) {
        std::string scene = WAGetCurrentScene();
        if ((scene == "PE" || scene == "FE") && (zombie.Row() == 2 || zombie.Row() == 3)) {
            if (water_list_is_ignore && std::find(water_list.begin(), water_list.end(), zombie.Type()) != water_list.end()) return false;
            if (!water_list_is_ignore && std::find(water_list.begin(), water_list.end(), zombie.Type()) == water_list.end()) return false;
            return true;
        } else {
            if (list_is_ignore && std::find(list.begin(), list.end(), zombie.Type()) != list.end()) return false;
            if (!list_is_ignore && std::find(list.begin(), list.end(), zombie.Type()) == list.end()) return false;
            return true;
        }
    }
    static void Fire(float column) {
        std::string scene = WAGetCurrentScene();
        if (scene == "PE" || scene == "FE") {
            aCobManager.RecoverFire({{2, column}, {5, column}});
        } else {
            aCobManager.RecoverFire({{2, column}, {4, column}});
        }
    }
    static void ScheduleFire(float column, 
                             std::vector<AZombieType> list, bool list_is_ignore, 
                             std::vector<AZombieType> water_list, bool water_list_is_ignore) {
        waRecoverEndRunner.Start([column, list, list_is_ignore, water_list, water_list_is_ignore](){
            ATime now = ANowTime();
            // 如果此波已过，立即停止
            if (now.wave != 9 && now.wave != 19 && now.wave != 20) {
                waRecoverEndRunner.Stop();
            }
            if (now.time < 0) {
                waRecoverEndRunner.Stop();
            }
            // 检查僵尸位置
            float max_x = 0;
            for (auto &zombie: aAliveZombieFilter) {
                if (!isIncluded(zombie, list, list_is_ignore, water_list, water_list_is_ignore)) continue;
                max_x = std::max(max_x, zombie.Abscissa() + zombie.BulletAbscissa());
            }
            // 如果僵尸全灭（或者已经进家）则立即停止
            if (max_x == 0) {
                waRecoverEndRunner.Stop();
            }
            // 所有僵尸进入范围开炮
            if (max_x <= 800 - (9 - column) * 80) {
                waRecoverEndRunner.Stop();
                Fire(column);
            }
        });
    }
    void DoRecoverFire() {
        int maxHp = 0;
        for (auto &&zombie: aAliveZombieFilter) {
            if (!isIncluded(zombie, list, list_is_ignore, water_list, water_list_is_ignore)) continue;
            if (zombie.Type() == ABY_23 || zombie.Type() == AHY_32) {
                // 记录巨人最高血量
                maxHp = std::max(maxHp, zombie.Hp());
            } else {
                // 所有未被忽略的非巨人僵尸都需要一炮
                maxHp = std::max(maxHp, 1800);
            } 
        }
        if (maxHp > ioDamage) {
            // 其中一炮等所有僵尸走进画面再打（对于炸9列来说）
            ScheduleFire(column, list, list_is_ignore, water_list, water_list_is_ignore);
        }
        for (int i = ioDamage + 1800; i < maxHp; i += 1800) {
            // 其他的立即打
            Fire(column);
        }
    }
    std::vector<AZombieType> list;
    bool list_is_ignore;
    std::vector<AZombieType> water_list;
    bool water_list_is_ignore;
    float column;
    int ioDamage;
} waEndCobber;

#endif // WHATSS7_WALIB_H