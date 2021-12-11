/*!
 * @file blue-magic-breath.cpp
 * @brief 青魔法のブレス系呪文定義
 */

#include "blue-magic/blue-magic-breath.h"
#include "blue-magic/blue-magic-util.h"
#include "effect/attribute-types.h"
#include "mind/mind-blue-mage.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-damage-calculator.h"
#include "spell-kind/spells-launcher.h"
#include "system/player-type-definition.h"
#include "target/target-getter.h"
#include "view/display-messages.h"

breath_caster::breath_caster(PlayerType *player_ptr, bmc_type *bmc_ptr, concptr typ_name, MonsterAbilityType ms_type, AttributeType typ)
    : player_ptr(player_ptr)
    , bmc_ptr(bmc_ptr)
    , typ_name(typ_name)
    , ms_type(ms_type)
    , typ(typ)
{
}

bool breath_caster::project()
{
    if (!get_aim_dir(this->player_ptr, &this->bmc_ptr->dir))
        return false;

    msg_format(_("%sのブレスを吐いた。", "You breathe %s."), this->typ_name);
    this->bmc_ptr->damage = monspell_bluemage_damage(this->player_ptr, this->ms_type, this->bmc_ptr->plev, damage_flag_type::DAM_ROLL);
    fire_breath(this->player_ptr, this->typ, this->bmc_ptr->dir, this->bmc_ptr->damage, (this->bmc_ptr->plev > 40 ? 3 : 2));
    return true;
}

breath_acid_caster::breath_acid_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("酸", "acid"), MonsterAbilityType::BR_ACID, AttributeType::ACID)
{
}

breath_elec_caster::breath_elec_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("稲妻", "lightning"), MonsterAbilityType::BR_ELEC, AttributeType::ELEC)
{
}

breath_fire_caster::breath_fire_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("火炎", "fire"), MonsterAbilityType::BR_FIRE, AttributeType::FIRE)
{
}

breath_cold_caster::breath_cold_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("冷気", "frost"), MonsterAbilityType::BR_COLD, AttributeType::COLD)
{
}

breath_pois_caster::breath_pois_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("ガス", "gas"), MonsterAbilityType::BR_POIS, AttributeType::POIS)
{
}

breath_nether_caster::breath_nether_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("地獄", "nether"), MonsterAbilityType::BR_NETH, AttributeType::NETHER)
{
}

breath_lite_caster::breath_lite_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("閃光", "light"), MonsterAbilityType::BR_LITE, AttributeType::LITE)
{
}

breath_dark_caster::breath_dark_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("暗黒", "darkness"), MonsterAbilityType::BR_DARK, AttributeType::DARK)
{
}

breath_conf_caster::breath_conf_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("混乱", "confusion"), MonsterAbilityType::BR_CONF, AttributeType::CONFUSION)
{
}

breath_sound_caster::breath_sound_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("轟音", "sound"), MonsterAbilityType::BR_SOUN, AttributeType::SOUND)
{
}

breath_chaos_caster::breath_chaos_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("カオス", "chaos"), MonsterAbilityType::BR_CHAO, AttributeType::CHAOS)
{
}

breath_disenchant_caster::breath_disenchant_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("劣化", "disenchantment"), MonsterAbilityType::BR_DISE, AttributeType::DISENCHANT)
{
}

breath_nexus_caster::breath_nexus_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("因果混乱", "nexus"), MonsterAbilityType::BR_NEXU, AttributeType::NEXUS)
{
}

breath_time_caster::breath_time_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("時間逆転", "time"), MonsterAbilityType::BR_NEXU, AttributeType::NEXUS)
{
}

breath_inertia_caster::breath_inertia_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("遅鈍", "inertia"), MonsterAbilityType::BR_INER, AttributeType::INERTIAL)
{
}

breath_gravity_caster::breath_gravity_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("重力", "gravity"), MonsterAbilityType::BR_GRAV, AttributeType::GRAVITY)
{
}

breath_shards_caster::breath_shards_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("破片", "shards"), MonsterAbilityType::BR_SHAR, AttributeType::SHARDS)
{
}

breath_plasma_caster::breath_plasma_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("プラズマ", "plasma"), MonsterAbilityType::BR_PLAS, AttributeType::PLASMA)
{
}

breath_force_caster::breath_force_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("フォース", "force"), MonsterAbilityType::BR_FORC, AttributeType::FORCE)
{
}

breath_mana_caster::breath_mana_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("魔力", "mana"), MonsterAbilityType::BR_MANA, AttributeType::MANA)
{
}

breath_nuke_caster::breath_nuke_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("放射性廃棄物", "toxic waste"), MonsterAbilityType::BR_NUKE, AttributeType::NUKE)
{
}

breath_disintegration_caster::breath_disintegration_caster(PlayerType *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("分解", "disintegration"), MonsterAbilityType::BR_DISI, AttributeType::DISINTEGRATE)
{
}
