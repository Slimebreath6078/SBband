#pragma once

#include "calc/damage_calc.h"
#include "system/angband.h"

enum class MonsterAbilityType;
class PlayerType;
HIT_POINT monspell_damage(PlayerType *player_ptr, MonsterAbilityType ms_type, MONSTER_IDX m_idx, damage_flag_type TYPE);
HIT_POINT monspell_race_damage(PlayerType *player_ptr, MonsterAbilityType ms_type, MONRACE_IDX r_idx, damage_flag_type TYPE);
HIT_POINT monspell_bluemage_damage(PlayerType *player_ptr, MonsterAbilityType ms_type, PLAYER_LEVEL plev, damage_flag_type TYPE);
