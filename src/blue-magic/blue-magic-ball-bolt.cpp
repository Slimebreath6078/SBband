/*!
 * @file blue-magic-ball-bolt.cpp
 * @brief 青魔法のボール/ボルト系呪文定義
 */

#include "blue-magic/blue-magic-ball-bolt.h"
#include "blue-magic/blue-magic-util.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-damage-calculator.h"
#include "spell-kind/spells-launcher.h"
#include "spell/spell-types.h"
#include "system/player-type-definition.h"
#include "target/target-getter.h"
#include "view/display-messages.h"

bool cast_blue_bolt_acid(player_type *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("アシッド・ボルトの呪文を唱えた。", "You cast an acid bolt."));
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, RF_ABILITY::BO_ACID, bmc_ptr->plev, DAM_ROLL);
    fire_bolt(player_ptr, GF_ACID, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}

bool cast_blue_bolt_elec(player_type *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("サンダー・ボルトの呪文を唱えた。", "You cast a lightning bolt."));
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, RF_ABILITY::BO_ELEC, bmc_ptr->plev, DAM_ROLL);
    fire_bolt(player_ptr, GF_ELEC, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}

bool cast_blue_bolt_fire(player_type *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("ファイア・ボルトの呪文を唱えた。", "You cast a fire bolt."));
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, RF_ABILITY::BO_FIRE, bmc_ptr->plev, DAM_ROLL);
    fire_bolt(player_ptr, GF_FIRE, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}

bool cast_blue_bolt_cold(player_type *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("アイス・ボルトの呪文を唱えた。", "You cast a frost bolt."));
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, RF_ABILITY::BO_COLD, bmc_ptr->plev, DAM_ROLL);
    fire_bolt(player_ptr, GF_COLD, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}

bool cast_blue_bolt_nether(player_type *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("地獄の矢の呪文を唱えた。", "You cast a nether bolt."));
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, RF_ABILITY::BO_NETH, bmc_ptr->plev, DAM_ROLL);
    fire_bolt(player_ptr, GF_NETHER, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}

bool cast_blue_bolt_water(player_type *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("ウォーター・ボルトの呪文を唱えた。", "You cast a water bolt."));
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, RF_ABILITY::BO_WATE, bmc_ptr->plev, DAM_ROLL);
    fire_bolt(player_ptr, GF_WATER, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}

bool cast_blue_bolt_mana(player_type *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("魔力の矢の呪文を唱えた。", "You cast a mana bolt."));
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, RF_ABILITY::BO_MANA, bmc_ptr->plev, DAM_ROLL);
    fire_bolt(player_ptr, GF_MANA, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}

bool cast_blue_bolt_plasma(player_type *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("プラズマ・ボルトの呪文を唱えた。", "You cast a plasma bolt."));
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, RF_ABILITY::BO_PLAS, bmc_ptr->plev, DAM_ROLL);
    fire_bolt(player_ptr, GF_PLASMA, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}

bool cast_blue_bolt_icee(player_type *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("極寒の矢の呪文を唱えた。", "You cast a ice bolt."));
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, RF_ABILITY::BO_ICEE, bmc_ptr->plev, DAM_ROLL);
    fire_bolt(player_ptr, GF_ICE, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}

bool cast_blue_bolt_missile(player_type *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("マジック・ミサイルの呪文を唱えた。", "You cast a magic missile."));
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, RF_ABILITY::MISSILE, bmc_ptr->plev, DAM_ROLL);
    fire_bolt(player_ptr, GF_MISSILE, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}

bool cast_blue_bolt_lite(player_type *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("スターライトアローを放った。", "You fire a starlight arrow."));
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, RF_ABILITY::BO_LITE, bmc_ptr->plev, DAM_ROLL);
    fire_bolt(player_ptr, GF_ICE, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}

bool cast_blue_bolt_dark(player_type *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("暗黒の矢の呪文を唱えた。", "You cast a dark bolt."));
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, RF_ABILITY::BO_DARK, bmc_ptr->plev, DAM_ROLL);
    fire_bolt(player_ptr, GF_ICE, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}
