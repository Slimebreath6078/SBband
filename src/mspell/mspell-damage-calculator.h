#pragma once

#include "system/angband.h"

enum class MonsterAbilityType;
class PlayerType;
HIT_POINT monspell_damage(PlayerType *player_ptr, MonsterAbilityType ms_type, MONSTER_IDX m_idx, int TYPE);
HIT_POINT monspell_race_damage(PlayerType *player_ptr, MonsterAbilityType ms_type, MONRACE_IDX r_idx, int TYPE);
HIT_POINT monspell_bluemage_damage(PlayerType *player_ptr, MonsterAbilityType ms_type, PLAYER_LEVEL plev, int TYPE);
