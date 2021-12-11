/*!
 * @file blue-magic-ball-bolt.cpp
 * @brief 青魔法のボール/ボルト系呪文定義
 */

#include "blue-magic/blue-magic-bolt.h"
#include "blue-magic/blue-magic-util.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-damage-calculator.h"
#include "spell-kind/spells-launcher.h"
#include "system/player-type-definition.h"
#include "target/target-getter.h"
#include "view/display-messages.h"

bolt_caster::bolt_caster(PlayerType *player_ptr, bmc_type *bmc_ptr, concptr msg, MonsterAbilityType ms_type, AttributeType typ)
    : player_ptr(player_ptr)
    , bmc_ptr(bmc_ptr)
    , msg(msg)
    , ms_type(ms_type)
    , typ(typ)
{
}

bool bolt_caster::project()
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(msg);
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, ms_type, bmc_ptr->plev, damage_flag_type::DAM_ROLL);
    fire_bolt(player_ptr, typ, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}

bolt_acid_caster::bolt_acid_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("アシッド・ボルトの呪文を唱えた。", "You cast an acid bolt."), MonsterAbilityType::BO_ACID, AttributeType::ACID)
{
}

bolt_elec_caster::bolt_elec_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("サンダー・ボルトの呪文を唱えた。", "You cast a lightning bolt."), MonsterAbilityType::BO_ELEC, AttributeType::ELEC)
{
}

bolt_fire_caster::bolt_fire_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("ファイア・ボルトの呪文を唱えた。", "You cast a fire bolt."), MonsterAbilityType::BO_FIRE, AttributeType::FIRE)
{
}

bolt_cold_caster::bolt_cold_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("アイス・ボルトの呪文を唱えた。", "You cast a frost bolt."), MonsterAbilityType::BO_COLD, AttributeType::COLD)
{
}

bolt_nether_caster::bolt_nether_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("地獄の矢の呪文を唱えた。", "You cast a nether bolt."), MonsterAbilityType::BO_NETH, AttributeType::NETHER)
{
}

bolt_water_caster::bolt_water_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("ウォーター・ボルトの呪文を唱えた。", "You cast a water bolt."), MonsterAbilityType::BO_WATE, AttributeType::WATER)
{
}

bolt_mana_caster::bolt_mana_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("魔力の矢の呪文を唱えた。", "You cast a mana bolt."), MonsterAbilityType::BO_MANA, AttributeType::MANA)
{
}

bolt_plasma_caster::bolt_plasma_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("プラズマ・ボルトの呪文を唱えた。", "You cast a plasma bolt."), MonsterAbilityType::BO_PLAS, AttributeType::PLASMA)
{
}

bolt_icee_caster::bolt_icee_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("極寒の矢の呪文を唱えた。", "You cast a ice bolt."), MonsterAbilityType::BO_ICEE, AttributeType::ICE)
{
}

bolt_missile_caster::bolt_missile_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("マジック・ミサイルの呪文を唱えた。", "You cast a magic missile."), MonsterAbilityType::MISSILE, AttributeType::MISSILE)
{
}

bolt_lite_caster::bolt_lite_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("スターライトアローを放った。", "You fire a starlight arrow."), MonsterAbilityType::BO_LITE, AttributeType::LITE)
{
}

bolt_dark_caster::bolt_dark_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("暗黒の矢の呪文を唱えた。", "You cast a dark bolt."), MonsterAbilityType::BO_DARK, AttributeType::DARK)
{
}
