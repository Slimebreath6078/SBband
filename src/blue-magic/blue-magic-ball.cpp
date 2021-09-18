/*!
 * @file blue-magic-ball.cpp
 * @brief 青魔法のボール系呪文定義
 */

#include "blue-magic/blue-magic-ball.h"
#include "blue-magic/blue-magic-util.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-damage-calculator.h"
#include "spell-kind/spells-launcher.h"
#include "spell/spell-types.h"
#include "system/player-type-definition.h"
#include "target/target-getter.h"
#include "view/display-messages.h"

ball_caster::ball_caster(player_type *player_ptr, bmc_type *bmc_ptr, concptr msg, RF_ABILITY ms_type, EFFECT_ID typ, POSITION rad)
    : player_ptr(player_ptr)
    , bmc_ptr(bmc_ptr)
    , msg(msg)
    , ms_type(ms_type)
    , typ(typ)
    , rad(rad)
{}

bool ball_caster::project(){
    if (!get_aim_dir(this->player_ptr, &this->bmc_ptr->dir))
        return false;

    msg_print(this->msg);
    this->bmc_ptr->damage = monspell_bluemage_damage(this->player_ptr, this->ms_type, this->bmc_ptr->plev, DAM_ROLL);
    fire_ball(this->player_ptr, this->typ, this->bmc_ptr->dir, bmc_ptr->damage, rad);
    return true;
}

ball_acid_caster::ball_acid_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("アシッド・ボールの呪文を唱えた。", "You cast an acid ball."), RF_ABILITY::BA_ACID, GF_ACID, 2)
{}

ball_elec_caster::ball_elec_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("サンダー・ボールの呪文を唱えた。", "You cast a lightning ball."), RF_ABILITY::BA_ELEC, GF_ELEC, 2)
{}

ball_fire_caster::ball_fire_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("ファイア・ボールの呪文を唱えた。", "You cast a fire ball."), RF_ABILITY::BA_FIRE, GF_FIRE, 2)
{}

ball_cold_caster::ball_cold_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("アイス・ボールの呪文を唱えた。", "You cast a frost ball."), RF_ABILITY::BA_COLD, GF_COLD, 2)
{}

ball_pois_caster::ball_pois_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("悪臭雲の呪文を唱えた。", "You cast a stinking cloud."), RF_ABILITY::BA_POIS, GF_POIS, 2)
{}

ball_nuke_caster::ball_nuke_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("放射能球を放った。", "You cast a ball of radiation."), RF_ABILITY::BA_NUKE, GF_NUKE, 2)
{}

ball_nether_caster::ball_nether_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("地獄球の呪文を唱えた。", "You cast a nether ball."), RF_ABILITY::BA_NETH, GF_NETHER, 2)
{}

ball_chaos_caster::ball_chaos_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("純ログルスを放った。", "You invoke a raw Logrus."), RF_ABILITY::BA_CHAO, GF_CHAOS, 4)
{}

ball_water_caster::ball_water_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("流れるような身振りをした。", "You gesture fluidly."), RF_ABILITY::BA_WATE, GF_WATER, 4)
{}

ball_star_burst_caster::ball_star_burst_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("スターバーストの呪文を念じた。", "You invoke a starburst."), RF_ABILITY::BA_LITE, GF_LITE, 4)
{}

ball_dark_storm_caster::ball_dark_storm_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("暗黒の嵐の呪文を念じた。", "You invoke a darkness storm."), RF_ABILITY::BA_DARK, GF_DARK, 4)
{}

ball_mana_storm_caster::ball_mana_storm_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("暗黒の嵐の呪文を念じた。", "You invoke a darkness storm."), RF_ABILITY::BA_MANA, GF_MANA, 4)
{}
