/*!
 * @file blue-magic-spirit-curse.cpp
 * @brief 青魔法の呪い系処理定義
 */


#include "blue-magic/blue-magic-spirit-curse.h"
#include "blue-magic/blue-magic-util.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-damage-calculator.h"
#include "spell-kind/spells-launcher.h"
#include "spell/spell-types.h"
#include "system/player-type-definition.h"
#include "target/target-getter.h"
#include "view/display-messages.h"

curse_caster::curse_caster(player_type *player_ptr, bmc_type *bmc_ptr, RF_ABILITY ms_type, EFFECT_ID typ)
    : player_ptr(player_ptr)
    , bmc_ptr(bmc_ptr)
    , ms_type(ms_type)
    , typ(typ)
{}

bool curse_caster::project(){
    if (!get_aim_dir(this->player_ptr, &this->bmc_ptr->dir))
        return false;

    this->bmc_ptr->damage = monspell_bluemage_damage(this->player_ptr, this->ms_type, this->bmc_ptr->plev, DAM_ROLL);
    fire_ball_hide(this->player_ptr, this->typ, this->bmc_ptr->dir, this->bmc_ptr->damage, 0);
    return true;
}

drain_mana_caster::drain_mana_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : curse_caster(player_ptr, bmc_ptr, RF_ABILITY::DRAIN_MANA, GF_DRAIN_MANA)
{}

mind_blast_caster::mind_blast_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : curse_caster(player_ptr, bmc_ptr, RF_ABILITY::MIND_BLAST, GF_MIND_BLAST)
{}

brain_smash_caster::brain_smash_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : curse_caster(player_ptr, bmc_ptr, RF_ABILITY::BRAIN_SMASH, GF_BRAIN_SMASH)
{}

curse_1_caster::curse_1_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : curse_caster(player_ptr, bmc_ptr, RF_ABILITY::CAUSE_1, GF_CAUSE_1)
{}

curse_2_caster::curse_2_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : curse_caster(player_ptr, bmc_ptr, RF_ABILITY::CAUSE_2, GF_CAUSE_2)
{}

curse_3_caster::curse_3_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : curse_caster(player_ptr, bmc_ptr, RF_ABILITY::CAUSE_3, GF_CAUSE_3)
{}

curse_4_caster::curse_4_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : curse_caster(player_ptr, bmc_ptr, RF_ABILITY::CAUSE_4, GF_CAUSE_4)
{}
