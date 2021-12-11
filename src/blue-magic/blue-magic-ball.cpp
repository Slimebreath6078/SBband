/*!
 * @file blue-magic-ball.cpp
 * @brief 青魔法のボール系呪文定義
 */

#include "blue-magic/blue-magic-ball.h"
#include "blue-magic/blue-magic-util.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-damage-calculator.h"
#include "spell-kind/spells-launcher.h"
#include "system/player-type-definition.h"
#include "target/target-getter.h"
#include "view/display-messages.h"

ball_caster::ball_caster(PlayerType *player_ptr, bmc_type *bmc_ptr, concptr msg, MonsterAbilityType ms_type, AttributeType typ, POSITION rad)
    : player_ptr(player_ptr)
    , bmc_ptr(bmc_ptr)
    , msg(msg)
    , ms_type(ms_type)
    , typ(typ)
    , rad(rad)
{
}

bool ball_caster::project()
{
    if (!get_aim_dir(this->player_ptr, &this->bmc_ptr->dir))
        return false;

    msg_print(this->msg);
    this->bmc_ptr->damage = monspell_bluemage_damage(this->player_ptr, this->ms_type, this->bmc_ptr->plev, damage_flag_type::DAM_ROLL);
    fire_ball(this->player_ptr, this->typ, this->bmc_ptr->dir, bmc_ptr->damage, rad);
    return true;
}

ball_acid_caster::ball_acid_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("アシッド・ボールの呪文を唱えた。", "You cast an acid ball."), MonsterAbilityType::BA_ACID, AttributeType::ACID, 2)
{
}

ball_elec_caster::ball_elec_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("サンダー・ボールの呪文を唱えた。", "You cast a lightning ball."), MonsterAbilityType::BA_ELEC, AttributeType::ELEC, 2)
{
}

ball_fire_caster::ball_fire_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("ファイア・ボールの呪文を唱えた。", "You cast a fire ball."), MonsterAbilityType::BA_FIRE, AttributeType::FIRE, 2)
{
}

ball_cold_caster::ball_cold_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("アイス・ボールの呪文を唱えた。", "You cast a frost ball."), MonsterAbilityType::BA_COLD, AttributeType::COLD, 2)
{
}

ball_pois_caster::ball_pois_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("悪臭雲の呪文を唱えた。", "You cast a stinking cloud."), MonsterAbilityType::BA_POIS, AttributeType::POIS, 2)
{
}

ball_nuke_caster::ball_nuke_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("放射能球を放った。", "You cast a ball of radiation."), MonsterAbilityType::BA_NUKE, AttributeType::NUKE, 2)
{
}

ball_nether_caster::ball_nether_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("地獄球の呪文を唱えた。", "You cast a nether ball."), MonsterAbilityType::BA_NETH, AttributeType::NETHER, 2)
{
}

ball_chaos_caster::ball_chaos_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("純ログルスを放った。", "You invoke a raw Logrus."), MonsterAbilityType::BA_CHAO, AttributeType::CHAOS, 4)
{
}

ball_water_caster::ball_water_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("流れるような身振りをした。", "You gesture fluidly."), MonsterAbilityType::BA_WATE, AttributeType::WATER, 4)
{
}

ball_star_burst_caster::ball_star_burst_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("スターバーストの呪文を念じた。", "You invoke a starburst."), MonsterAbilityType::BA_LITE, AttributeType::LITE, 4)
{
}

ball_dark_storm_caster::ball_dark_storm_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("暗黒の嵐の呪文を念じた。", "You invoke a darkness storm."), MonsterAbilityType::BA_DARK, AttributeType::DARK, 4)
{
}

ball_mana_storm_caster::ball_mana_storm_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : ball_caster(player_ptr, bmc_ptr, _("暗黒の嵐の呪文を念じた。", "You invoke a darkness storm."), MonsterAbilityType::BA_MANA, AttributeType::MANA, 4)
{
}
