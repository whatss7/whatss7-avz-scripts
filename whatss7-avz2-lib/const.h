#ifndef WALIB_CONST_H
#define WALIB_CONST_H

// 常见预判炸时间点（有8列炮情况下最晚舞王不召唤时间点）
const int PRE_COB_POINT = 316;
// 玉米加农炮发射到生效用时
const int COB_FLYING_TIME = 373;
// 泳池修正玉米加农炮发射到生效用时
const int POOL_COB_FLYING_TIME = 378;
// 屋顶修正玉米加农炮发射到生效用时
const int ROOF_COB_FLYING_TIME = 387;
// 灰烬植物和寒冰菇种下到生效用时
const int ASH_DELAY_TIME = 100;
// 咖啡豆生效时间198cs或199cs（此处取198cs）
const int COFFEE_BEAN_TIME = 198;
// 模仿者种下至生效时间319cs或320cs（此处取319cs）
const int IMITATOT_DELAY_TIME = 319;
// 窝瓜种下至生效时间182cs
const int SQUASH_DELAY_TIME = 182;

// 常见预判炸时间点（有8列炮情况下最晚舞王不召唤时间点）
const int PCP = PRE_COB_POINT;
// 玉米加农炮发射到生效用时
const int CFT = COB_FLYING_TIME;
// 泳池修正玉米加农炮发射到生效用时
const int PCFT = POOL_COB_FLYING_TIME;
// 屋顶修正玉米加农炮发射到生效用时
const int RCFT = ROOF_COB_FLYING_TIME;
// 灰烬植物和寒冰菇种下到生效用时
const int ADT = ASH_DELAY_TIME;
// 咖啡豆生效时间198cs或199cs（此处取198cs）
const int CBT = COFFEE_BEAN_TIME;
// 模仿者种下至生效时间319cs或320cs（此处取319cs）
const int MDT = IMITATOT_DELAY_TIME;
// 窝瓜种下至生效时间182cs
const int SDT = SQUASH_DELAY_TIME;

#endif // WALIB_CONST_H