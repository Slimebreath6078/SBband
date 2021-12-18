#pragma once

#include "system/angband.h"
#include "system/player-type-definition.h"

struct effect_monster_type;
process_result effect_monster_curse_1(effect_monster_type *em_ptr);
process_result effect_monster_curse_2(effect_monster_type *em_ptr);
process_result effect_monster_curse_3(effect_monster_type *em_ptr);
process_result effect_monster_curse_4(effect_monster_type *em_ptr);
process_result effect_monster_drain_life(PlayerType *player_ptr, effect_monster_type *em_ptr);
