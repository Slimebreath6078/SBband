#pragma once
/*!
 * @file blue-magic-breath.h
 * @brief 青魔法のブレス系呪文ヘッダ
 */

#include "monster-race/race-ability-flags.h"
#include "system/h-type.h"

struct bmc_type;
struct player_type;

class breath_caster{
    protected:
        breath_caster(player_type *player_ptr, bmc_type *bmc_ptr, concptr typ_name, RF_ABILITY ms_type, EFFECT_ID typ);
    public:
        ~breath_caster() = default;
        bool project();
    private:
        player_type *player_ptr;
        bmc_type *bmc_ptr;
        concptr typ_name;
        RF_ABILITY ms_type;
        EFFECT_ID typ;
};
bool cast_blue_breath_acid(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_elec(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_fire(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_cold(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_pois(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_nether(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_lite(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_dark(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_conf(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_sound(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_chaos(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_disenchant(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_nexus(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_time(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_inertia(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_gravity(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_shards(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_plasma(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_force(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_mana(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_nuke(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_breath_disintegration(player_type *player_ptr, bmc_type *bmc_ptr);
