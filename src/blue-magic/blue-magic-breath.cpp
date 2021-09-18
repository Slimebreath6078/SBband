/*!
 * @file blue-magic-breath.cpp
 * @brief 青魔法のブレス系呪文定義
 */

#include "blue-magic/blue-magic-breath.h"
#include "blue-magic/blue-magic-util.h"
#include "mind/mind-blue-mage.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-damage-calculator.h"
#include "spell-kind/spells-launcher.h"
#include "spell/spell-types.h"
#include "system/player-type-definition.h"
#include "target/target-getter.h"
#include "view/display-messages.h"

breath_caster::breath_caster(player_type *player_ptr, bmc_type *bmc_ptr, concptr typ_name, RF_ABILITY ms_type, EFFECT_ID typ)
    : player_ptr(player_ptr)
    , bmc_ptr(bmc_ptr)
    , typ_name(typ_name)
    , ms_type(ms_type)
    , typ(typ)
{}

bool breath_caster::project(){
    if (!get_aim_dir(this->player_ptr, &this->bmc_ptr->dir))
        return false;

    msg_format(_("%sのブレスを吐いた。", "You breathe %s."), this->typ_name);
    this->bmc_ptr->damage = monspell_bluemage_damage(this->player_ptr, this->ms_type, this->bmc_ptr->plev, DAM_ROLL);
    fire_breath(this->player_ptr, this->typ, this->bmc_ptr->dir, this->bmc_ptr->damage, (this->bmc_ptr->plev > 40 ? 3 : 2));
    return true;
}

breath_acid_caster::breath_acid_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("酸", "acid"), RF_ABILITY::BR_ACID, GF_ACID)
{}

breath_elec_caster::breath_elec_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("稲妻", "lightning"), RF_ABILITY::BR_ELEC, GF_ELEC)
{}

breath_fire_caster::breath_fire_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("火炎", "fire"), RF_ABILITY::BR_FIRE, GF_FIRE)
{}

breath_cold_caster::breath_cold_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("冷気", "frost"), RF_ABILITY::BR_COLD, GF_COLD)
{}

breath_pois_caster::breath_pois_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("ガス", "gas"), RF_ABILITY::BR_POIS, GF_POIS)
{}

breath_nether_caster::breath_nether_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("地獄", "nether"), RF_ABILITY::BR_NETH, GF_NETHER)
{}

breath_lite_caster::breath_lite_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("閃光", "light"), RF_ABILITY::BR_LITE, GF_LITE)
{}

breath_dark_caster::breath_dark_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("暗黒", "darkness"), RF_ABILITY::BR_DARK, GF_DARK)
{}

breath_conf_caster::breath_conf_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("混乱", "confusion"), RF_ABILITY::BR_CONF, GF_CONFUSION)
{}

breath_sound_caster::breath_sound_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("轟音", "sound"), RF_ABILITY::BR_SOUN, GF_SOUND)
{}

breath_chaos_caster::breath_chaos_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("カオス", "chaos"), RF_ABILITY::BR_CHAO, GF_CHAOS)
{}

breath_disenchant_caster::breath_disenchant_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("劣化", "disenchantment"), RF_ABILITY::BR_DISE, GF_DISENCHANT)
{}

breath_nexus_caster::breath_nexus_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("因果混乱", "nexus"), RF_ABILITY::BR_NEXU, GF_NEXUS)
{}

breath_time_caster::breath_time_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("時間逆転", "time"), RF_ABILITY::BR_NEXU, GF_NEXUS)
{}

breath_inertia_caster::breath_inertia_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("遅鈍", "inertia"), RF_ABILITY::BR_INER, GF_INERTIAL)
{}

breath_gravity_caster::breath_gravity_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("重力", "gravity"), RF_ABILITY::BR_GRAV, GF_GRAVITY)
{}

breath_shards_caster::breath_shards_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("破片", "shards"), RF_ABILITY::BR_SHAR, GF_SHARDS)
{}

breath_plasma_caster::breath_plasma_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("プラズマ", "plasma"), RF_ABILITY::BR_PLAS, GF_PLASMA)
{}

breath_force_caster::breath_force_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("フォース", "force"), RF_ABILITY::BR_FORC, GF_FORCE)
{}

breath_mana_caster::breath_mana_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("魔力", "mana"), RF_ABILITY::BR_MANA, GF_MANA)
{}

breath_nuke_caster::breath_nuke_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("放射性廃棄物", "toxic waste"), RF_ABILITY::BR_NUKE, GF_NUKE)
{}

breath_disintegration_caster::breath_disintegration_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : breath_caster(player_ptr, bmc_ptr, _("分解", "disintegration"), RF_ABILITY::BR_DISI, GF_DISINTEGRATE)
{}

