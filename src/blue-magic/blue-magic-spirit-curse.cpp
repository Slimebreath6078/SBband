/*!
 * @file blue-magic-spirit-curse.cpp
 * @brief 青魔法の呪い系処理定義
 */

#include "blue-magic/blue-magic-spirit-curse.h"
#include "blue-magic/blue-magic-util.h"
#include "effect/attribute-types.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-damage-calculator.h"
#include "spell-kind/spells-launcher.h"
#include "system/player-type-definition.h"
#include "target/target-getter.h"
#include "view/display-messages.h"

curse_caster::curse_caster(PlayerType *player_ptr, bmc_type *bmc_ptr, MonsterAbilityType ms_type, AttributeType typ)
    : player_ptr(player_ptr)
    , bmc_ptr(bmc_ptr)
    , ms_type(ms_type)
    , typ(typ)
{
}

bool curse_caster::project()
{
    if (!get_aim_dir(this->player_ptr, &this->bmc_ptr->dir))
        return false;

    this->bmc_ptr->damage = monspell_bluemage_damage(this->player_ptr, this->ms_type, this->bmc_ptr->plev, damage_flag_type::DAM_ROLL);
    fire_ball_hide(this->player_ptr, this->typ, this->bmc_ptr->dir, this->bmc_ptr->damage, 0);
    return true;
}

drain_mana_caster::drain_mana_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : curse_caster(player_ptr, bmc_ptr, MonsterAbilityType::DRAIN_MANA, AttributeType::DRAIN_MANA)
{
}

mind_blast_caster::mind_blast_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : curse_caster(player_ptr, bmc_ptr, MonsterAbilityType::MIND_BLAST, AttributeType::MIND_BLAST)
{
}

brain_smash_caster::brain_smash_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : curse_caster(player_ptr, bmc_ptr, MonsterAbilityType::BRAIN_SMASH, AttributeType::BRAIN_SMASH)
{
}

curse_1_caster::curse_1_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : curse_caster(player_ptr, bmc_ptr, MonsterAbilityType::CAUSE_1, AttributeType::CAUSE_1)
{
}

curse_2_caster::curse_2_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : curse_caster(player_ptr, bmc_ptr, MonsterAbilityType::CAUSE_2, AttributeType::CAUSE_2)
{
}

curse_3_caster::curse_3_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : curse_caster(player_ptr, bmc_ptr, MonsterAbilityType::CAUSE_3, AttributeType::CAUSE_3)
{
}

curse_4_caster::curse_4_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : curse_caster(player_ptr, bmc_ptr, MonsterAbilityType::CAUSE_4, AttributeType::CAUSE_4)
{
}
