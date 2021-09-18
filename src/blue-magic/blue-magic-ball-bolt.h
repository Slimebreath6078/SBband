#pragma once
/*!
 * @file blue-magic-ball-bolt.h
 * @brief 青魔法のボール/ボルト系呪文ヘッダ
 */

#include "monster-race/race-ability-flags.h"
#include "system/h-type.h"

struct bmc_type;
struct player_type;

class ball_caster{
    protected:
        ball_caster(player_type *player_ptr, bmc_type *bmc_ptr, concptr msg, RF_ABILITY ms_type, EFFECT_ID typ, POSITION rad);
    public:
        ~ball_caster() = default;
        bool project();
    private:
        player_type *player_ptr;
        bmc_type *bmc_ptr;
        concptr msg;
        RF_ABILITY ms_type;
        EFFECT_ID typ;
        POSITION rad;
};
bool cast_blue_ball_acid(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_ball_elec(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_ball_fire(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_ball_cold(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_ball_pois(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_ball_nuke(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_ball_nether(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_ball_chaos(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_ball_water(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_ball_star_burst(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_ball_dark_storm(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_ball_mana_storm(player_type *player_ptr, bmc_type *bmc_ptr);

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
