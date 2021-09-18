#pragma once
/*!
 * @file blue-magic-spirit-curse.h
 * @brief 青魔法の呪い系処理ヘッダ
 */

#include "monster-race/race-ability-flags.h"
#include "system/h-type.h"

struct bmc_type;
struct player_type;

class curse_caster{
    protected:
        curse_caster(player_type *player_ptr, bmc_type *bmc_ptr, RF_ABILITY ms_type, EFFECT_ID typ);
    public:
        ~curse_caster() = default;
        bool project();
    private:
        player_type *player_ptr;
        bmc_type *bmc_ptr;
        RF_ABILITY ms_type;
        EFFECT_ID typ;
};
bool cast_blue_drain_mana(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_mind_blast(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_brain_smash(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_curse_1(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_curse_2(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_curse_3(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_curse_4(player_type *player_ptr, bmc_type *bmc_ptr);
