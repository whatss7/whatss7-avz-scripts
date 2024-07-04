#ifndef WALIB_INFO_H
#define WALIB_INFO_H

#include "avz.h"

#ifdef WALIB_DEBUG
ALogger<AConsole> waDebugLogger;
#define DEBUG_LOG(x) waDebugLogger.Info(x)
#else
#define DEBUG_LOG(x)
#endif
ALogger<AMsgBox> waLogger;
ALogger<APvzGui> waIngameLogger;

#pragma region 辅助类

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

#pragma endregion

#pragma region 场上信息获取

// 获得当前所处的场地。
std::string GetCurrentScene() {
    std::string scenes[] = { "DE", "NE", "PE", "FE", "RE", "ME" };
    int scene_id = AGetMainObject()->Scene();
    if (scene_id < 0 || scene_id > 5) { waLogger.Error("未知的场地"); return ""; }
    else return scenes[scene_id];
}

bool IsDayScene() {
    int scene_id = AGetMainObject()->Scene();
    if (scene_id < 0 || scene_id > 5) { waLogger.Error("未知的场地"); return false; }
    return scene_id == 0 || scene_id == 2 || scene_id == 4;
}

bool IsNightScene() {
    int scene_id = AGetMainObject()->Scene();
    if (scene_id < 0 || scene_id > 5) { waLogger.Error("未知的场地"); return false; }
    return scene_id == 1 || scene_id == 3 || scene_id == 5;
}

bool IsFrontyardScene() {
    int scene_id = AGetMainObject()->Scene();
    if (scene_id < 0 || scene_id > 5) { waLogger.Error("未知的场地"); return false; }
    return scene_id == 0 || scene_id == 1;
}

bool IsBackyardScene() {
    int scene_id = AGetMainObject()->Scene();
    if (scene_id < 0 || scene_id > 5) { waLogger.Error("未知的场地"); return false; }
    return scene_id == 2 || scene_id == 3;
}

bool IsRoofScene() {
    int scene_id = AGetMainObject()->Scene();
    if (scene_id < 0 || scene_id > 5) { waLogger.Error("未知的场地"); return false; }
    return scene_id == 4 || scene_id == 5;
}

// 获取当前场景最大可能的炮飞行时间。
int GetCFT() {
    if (IsFrontyardScene()) return CFT;
    else if (IsBackyardScene()) return PCFT;
    else if (IsRoofScene()) return RCFT;
    return -1;
}

// 判断场上某行是否有指定类型的僵尸。此处行从 1 开始编号。
bool ExistZombie(std::vector<AZombieType> types, std::vector<int> rows = {1, 2, 3, 4, 5, 6}) {
    for (auto &&zombie: aAliveZombieFilter) {
        if (std::find(types.begin(), types.end(), zombie.Type()) != types.end()) {
            if (std::find(rows.begin(), rows.end(), zombie.Row() + 1) != rows.end()) {
                return true;
            }
        }
    }
    return false;
}

// 判断场上某行是否有指定类型的僵尸。此处行从 1 开始编号。
bool ExistZombie(AZombieType type, std::vector<int> rows = {1, 2, 3, 4, 5, 6}) {   
    return ExistZombie(std::vector<AZombieType>({type}), rows);
}

// 判断指定位置是否有指定的植物。
bool ExistPlant(int row, int col) {
    for (auto &&plant: aAlivePlantFilter) {
        if (plant.Col() + 1 == col && plant.Row() + 1 == row) {
            return true;
        }
    }
    return false;
}


// 判断指定位置是否有指定的植物。
bool ExistPlant(APlantType type, int row, int col) {
    for (auto &&plant: aAlivePlantFilter) {
        if (plant.Type() == type && plant.Col() + 1 == col && plant.Row() + 1 == row) {
            return true;
        }
    }
    return false;
}

// 判断指定位置是否有指定的植物。
bool ExistPlant(const std::vector<APlantType> &types, int row, int col) {
    for (auto &&plant: aAlivePlantFilter) {
        if (std::find(types.begin(), types.end(), APlantType(plant.Type())) != types.end() &&
            plant.Col() + 1 == col && plant.Row() + 1 == row) {
            return true;
        }
    }
    return false;
}

// 判断是否为有效的时间。普通波次小于 -200 的时间无效。
bool IsValidTime(int wave, int time) {
    if (wave == 1) return time >= -599;
    else if (wave == 10 || wave == 20) return time >= -945;
    else return time >= -200;
}
#pragma endregion


// 控制 `ForEnd()` 和 `PPForEnd()` 函数所无视的僵尸类型。
std::vector<AZombieType> waForEndIgnore = { AKG_17, AXG_24 };

// 控制 `ForEnd()` 和 `PPForEnd()` 函数所无视的水路僵尸类型。若为空，则沿用 `waForEndIgnore` 的设置。
// 在其中插入一个不会在水路生成的僵尸以禁用上述行为。
std::vector<AZombieType> waForEndIgnoreInWater = {};

// 判断当前是否符合 `ForEnd()` 的条件。
bool ForEndJudge(int wave) {
    std::string scene = GetCurrentScene();
    // 若为后院且水路无视未设置，则使用陆路设置
    if (IsBackyardScene() && waForEndIgnoreInWater.empty()) {
        waForEndIgnoreInWater = waForEndIgnore;
    }
    ATime now = ANowTime();
    // 已经不是当前波次则不执行
    if (now.wave != wave) return false;
    bool hasZombie = false;
    // 场上只有被忽略的僵尸时不执行
    for (auto &&zombie: aAliveZombieFilter) {
        if (IsBackyardScene() && (zombie.Row() == 2 || zombie.Row() == 3)) {
            if (std::find(waForEndIgnoreInWater.begin(), waForEndIgnoreInWater.end(), zombie.Type()) != waForEndIgnoreInWater.end()) {
                continue;
            }
        } else {
            if (std::find(waForEndIgnore.begin(), waForEndIgnore.end(), zombie.Type()) != waForEndIgnore.end()) {
                continue;
            }
        }
        if ((zombie.Type() != ABW_9 && zombie.AtWave() + 1 == wave) || (wave != 9 && wave != 19)) {
            hasZombie = true;
            break;
        }
    }
    if (!hasZombie) return false;
    return true;
}

// 用于收尾的函数。在指定时间是对应波次（处于刷新倒计时也算）且场上有僵尸才执行对应的操作。
// 此函数w9/w19不计非本波僵尸与伴舞，且所有波次默认不计矿工和小鬼。
void ForEnd(int wave, int time, std::function<void()> action) {
    AConnect(ATime(wave, time), [wave, action](){
        if (ForEndJudge(wave)) action();
    });
}

AZombie *GetLastZombie() {
    AZombie *last_zombie = nullptr;
    for (auto &&zombie: aAliveZombieFilter) {
        if (zombie.Hp() < 0) continue;
        last_zombie = &zombie;
        if (zombie.Type() != ABW_9) break;
    }
    return last_zombie;
}

ATickRunner untilOneLeftRunner;
// 在只剩零或一个僵尸时执行指定操作。可以用于收尾时处理多余的僵尸。
void UntilOneLeft(int wave, int start_time, 
                  std::function<void()> oneAtStartAction, 
                  std::function<void()> multiAtStartAction,
                  std::function<void()> oneLeftAction) {
    AConnect(ATime(wave, start_time), [=](){
        int cnt = 0;
        for (auto &&zombie: aAliveZombieFilter) {
            (void)zombie;
            cnt++;
        }
        if (cnt <= 1) {
            if(oneAtStartAction) oneAtStartAction();
        } else {
            if (multiAtStartAction) multiAtStartAction();
            untilOneLeftRunner.Start([=](){
                int cnt = 0;
                for (auto &&zombie: aAliveZombieFilter) {
                    (void)zombie;
                    cnt++;
                }
                if (cnt <= 1) {
                    if (oneLeftAction) oneLeftAction();
                    untilOneLeftRunner.Stop();
                }
            });
        }
    });
}

#pragma endregion

#endif // WALIB_INFO_H