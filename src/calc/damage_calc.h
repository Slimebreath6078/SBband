#pragma once

#include "system/angband.h"

enum class damage_flag_type : int {
    DAM_ROLL = 1,
    DAM_MAX = 2,
    DAM_MIN = 3,
    DICE_NUM = 4,
    DICE_SIDE = 5,
    DICE_MULT = 6,
    DICE_DIV = 7,
    BASE_DAM = 8,
};

HIT_POINT damage_roll(HIT_POINT dam, int dice_num, int dice_side, int mult, int div, damage_flag_type TYPE);
