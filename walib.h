#ifndef WHATSS7_WALIB_H
#define WHATSS7_WALIB_H

#include "avz.h"

#if __AVZ_VERSION__ <= 221001
#error "walib is designed for AvZ 2, which is incompatible with AvZ 1."
#elif __AVZ_VERSION__ < 240113
#warning "walib is designed for AvZ 2 version 240113. You're using an older version, which might cause issues."
#elif __AVZ_VERSION__ > 240113
#warning "walib is designed for AvZ 2 version 240113. You're using a newer version, which might cause issues."
#endif

#include "whatss7-avz2-lib/ash.h"
#include "whatss7-avz2-lib/card.h"
#include "whatss7-avz2-lib/cob.h"
#include "whatss7-avz2-lib/const.h"
#include "whatss7-avz2-lib/info.h"
#include "whatss7-avz2-lib/init.h"

#endif // WHATSS7_WALIB_H

