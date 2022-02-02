#pragma once

#include "system/angband.h"
#include "object/object-flags.h"
#include "system/monster-race-definition.h"

bool pow_check_str(monster_race *r_ptr);
bool pow_check_int(monster_race *r_ptr);
bool pow_check_dex(monster_race *r_ptr);
bool pow_check_wis(monster_race *r_ptr);
bool pow_check_con(monster_race *r_ptr);
bool pow_check_chr(monster_race *r_ptr);
bool pow_check_speed(monster_race *r_ptr);
bool pow_check_stealth(monster_race *r_ptr);
bool pow_check_search(monster_race *r_ptr);
bool pow_check_tunnel(monster_race *r_ptr);
bool pow_check_magic_mastery(monster_race *r_ptr);
bool pow_check_common(monster_race *r_ptr, tr_type typ);
