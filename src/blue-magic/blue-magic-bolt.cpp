/*!
 * @file blue-magic-ball-bolt.cpp
 * @brief 青魔法のボール/ボルト系呪文定義
 */

#include "blue-magic/blue-magic-bolt.h"
#include "blue-magic/blue-magic-util.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-damage-calculator.h"
#include "spell-kind/spells-launcher.h"
#include "spell/spell-types.h"
#include "system/player-type-definition.h"
#include "target/target-getter.h"
#include "view/display-messages.h"

bolt_caster::bolt_caster(player_type *player_ptr, bmc_type *bmc_ptr, concptr msg, RF_ABILITY ms_type, EFFECT_ID typ)
    : player_ptr(player_ptr)
    , bmc_ptr(bmc_ptr)
    , msg(msg)
    , ms_type(ms_type)
    , typ(typ)
{}

bool bolt_caster::project(){
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(msg);
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, ms_type, bmc_ptr->plev, DAM_ROLL);
    fire_bolt(player_ptr, typ, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}

bolt_acid_caster::bolt_acid_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("アシッド・ボルトの呪文を唱えた。", "You cast an acid bolt."), RF_ABILITY::BO_ACID, GF_ACID)
{}

bolt_elec_caster::bolt_elec_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("サンダー・ボルトの呪文を唱えた。", "You cast a lightning bolt."), RF_ABILITY::BO_ELEC, GF_ELEC)
{}

bolt_fire_caster::bolt_fire_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("ファイア・ボルトの呪文を唱えた。", "You cast a fire bolt."), RF_ABILITY::BO_FIRE, GF_FIRE)
{}

bolt_cold_caster::bolt_cold_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("アイス・ボルトの呪文を唱えた。", "You cast a frost bolt."), RF_ABILITY::BO_COLD, GF_COLD)
{}

bolt_nether_caster::bolt_nether_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("地獄の矢の呪文を唱えた。", "You cast a nether bolt."), RF_ABILITY::BO_NETH, GF_NETHER)
{}

bolt_water_caster::bolt_water_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("ウォーター・ボルトの呪文を唱えた。", "You cast a water bolt."), RF_ABILITY::BO_WATE, GF_WATER)
{}

bolt_mana_caster::bolt_mana_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("魔力の矢の呪文を唱えた。", "You cast a mana bolt."), RF_ABILITY::BO_MANA, GF_MANA)
{}

bolt_plasma_caster::bolt_plasma_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("プラズマ・ボルトの呪文を唱えた。", "You cast a plasma bolt."), RF_ABILITY::BO_PLAS, GF_PLASMA)
{}

bolt_icee_caster::bolt_icee_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("極寒の矢の呪文を唱えた。", "You cast a ice bolt."), RF_ABILITY::BO_ICEE, GF_ICE)
{}

bolt_missile_caster::bolt_missile_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("マジック・ミサイルの呪文を唱えた。", "You cast a magic missile."), RF_ABILITY::MISSILE, GF_MISSILE)
{}

bolt_lite_caster::bolt_lite_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("スターライトアローを放った。", "You fire a starlight arrow."), RF_ABILITY::BO_LITE, GF_LITE)
{}

bolt_dark_caster::bolt_dark_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : bolt_caster(player_ptr, bmc_ptr, _("暗黒の矢の呪文を唱えた。", "You cast a dark bolt."), RF_ABILITY::BO_DARK, GF_DARK)
{}
