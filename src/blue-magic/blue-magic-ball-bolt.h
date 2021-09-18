#pragma once
/*!
 * @file blue-magic-ball-bolt.h
 * @brief 青魔法のボール/ボルト系呪文ヘッダ
 */

#include "monster-race/race-ability-flags.h"
#include "system/h-type.h"

struct bmc_type;
struct player_type;

bool cast_blue_bolt_acid(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_bolt_elec(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_bolt_fire(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_bolt_cold(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_bolt_nether(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_bolt_water(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_bolt_mana(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_bolt_plasma(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_bolt_icee(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_bolt_missile(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_bolt_lite(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_bolt_dark(player_type *player_ptr, bmc_type *bmc_ptr);
