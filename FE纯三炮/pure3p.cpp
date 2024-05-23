#include "../walib.h"
#include "mod/mod.h"

void AScript() {
    UnlimitedSun(ModState::SCOPED_ON);
    // 4-9核炸不到1列474巨人；3-9核炸不到6列409巨人
    Init({ADOOM_SHROOM, ACHERRY_BOMB, AJALAPENO, ALILY_PAD, ATALL_NUT, AGARLIC});
    for (int w: { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 }) {
        ManualI(w, 1, 4, 3, 2501);
        P(w, 1234, 3, 8.1125);
        N(w, 2301, {{3, 9}, {4, 9}, {3, 8}, {4, 8}});
        P(w, 2301 + 196, 5, 5);
    }
    for (int w: { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 }) {
        ManualI(w, 1, 4, 3, 2501);
        P(w, 1234, 3, 8.1125);
        P(w, 2301, 5, 7.6375);
        A(w, 2301 + 196, 5, 5);
        J(w, 2301, 1, 2);
    }
}
