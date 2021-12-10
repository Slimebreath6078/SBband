/*!
 * @file blue-magic-caster.cpp
 * @brief 青魔法のその他系統の呪文定義と詠唱時分岐処理
 */

#include "blue-magic/blue-magic-caster.h"
#include "blue-magic/blue-magic-ball.h"
#include "blue-magic/blue-magic-bolt.h"
#include "blue-magic/blue-magic-breath.h"
#include "blue-magic/blue-magic-spirit-curse.h"
#include "blue-magic/blue-magic-status.h"
#include "blue-magic/blue-magic-summon.h"
#include "blue-magic/blue-magic-util.h"
#include "blue-magic/learnt-info.h"
#include "effect/attribute-types.h"
#include "floor/cave.h"
#include "hpmp/hp-mp-processor.h"
#include "monster-race/monster-race.h"
#include "monster-race/race-ability-flags.h"
#include "monster-race/race-flags-resistance.h"
#include "monster-race/race-flags1.h"
#include "monster-race/race-kind-flags.h"
#include "monster/monster-describer.h"
#include "monster/monster-info.h"
#include "monster/monster-status.h"
#include "mspell/mspell-damage-calculator.h"
#include "spell-kind/spells-launcher.h"
#include "spell-kind/spells-lite.h"
#include "spell-kind/spells-neighbor.h"
#include "spell-kind/spells-sight.h"
#include "spell-kind/spells-teleport.h"
#include "spell-kind/spells-world.h"
#include "spell/spells-status.h"
#include "status/bad-status-setter.h"
#include "status/body-improvement.h"
#include "status/buff-setter.h"
#include "system/floor-type-definition.h"
#include "system/grid-type-definition.h"
#include "system/monster-race-definition.h"
#include "system/monster-type-definition.h"
#include "system/player-type-definition.h"
#include "target/projection-path-calculator.h"
#include "target/target-checker.h"
#include "target/target-getter.h"
#include "target/target-setter.h"
#include "target/target-types.h"
#include "view/display-messages.h"

static bool cast_blue_dispel(PlayerType *player_ptr)
{
    if (!target_set(player_ptr, TARGET_KILL))
        return false;

    MONSTER_IDX m_idx = player_ptr->current_floor_ptr->grid_array[target_row][target_col].m_idx;
    if ((m_idx == 0) || !player_has_los_bold(player_ptr, target_row, target_col) || !projectable(player_ptr, player_ptr->y, player_ptr->x, target_row, target_col))
        return true;

    dispel_monster_status(player_ptr, m_idx);
    return true;
}

static bool cast_blue_rocket(PlayerType *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("ロケットを発射した。", "You fire a rocket."));
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, MonsterAbilityType::ROCKET, bmc_ptr->plev, DAM_ROLL);
    fire_rocket(player_ptr, AttributeType::ROCKET, bmc_ptr->dir, bmc_ptr->damage, 2);
    return true;
}

static bool cast_blue_shoot(PlayerType *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("矢を放った。", "You fire an arrow."));
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, MonsterAbilityType::SHOOT, bmc_ptr->plev, DAM_ROLL);
    fire_bolt(player_ptr, AttributeType::ARROW, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}

static bool cast_blue_hand_doom(PlayerType *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("<破滅の手>を放った！", "You invoke the Hand of Doom!"));
    fire_ball_hide(player_ptr, AttributeType::HAND_DOOM, bmc_ptr->dir, bmc_ptr->plev * 3, 0);
    return true;
}

static bool exe_blue_teleport_back(PlayerType *player_ptr, GAME_TEXT *m_name)
{
    monster_type *m_ptr;
    monster_race *r_ptr;
    floor_type *floor_ptr = player_ptr->current_floor_ptr;
    if ((floor_ptr->grid_array[target_row][target_col].m_idx == 0) || !player_has_los_bold(player_ptr, target_row, target_col) || !projectable(player_ptr, player_ptr->y, player_ptr->x, target_row, target_col))
        return true;

    m_ptr = &floor_ptr->m_list[floor_ptr->grid_array[target_row][target_col].m_idx];
    r_ptr = &r_info[m_ptr->r_idx];
    monster_desc(player_ptr, m_name, m_ptr, 0);
    if (r_ptr->resistance_flags.has(MonsterResistanceType::RESIST_TELEPORT))
        return false;

    if (r_ptr->race_kind_flags.has(MonraceKindType::UNIQUE) || r_ptr->resistance_flags.has(MonsterResistanceType::RESIST_ALL)) {
        if (is_original_ap_and_seen(player_ptr, m_ptr))
            r_ptr->r_resistance_flags.set(MonsterResistanceType::RESIST_TELEPORT);

        msg_format(_("%sには効果がなかった！", "%s is unaffected!"), m_name);
        return true;
    }

    if (r_ptr->level <= randint1(100))
        return false;

    if (is_original_ap_and_seen(player_ptr, m_ptr))
        r_ptr->r_resistance_flags.set(MonsterResistanceType::RESIST_TELEPORT);

    msg_format(_("%sには耐性がある！", "%s resists!"), m_name);
    return true;
}

static bool cast_blue_teleport_back(PlayerType *player_ptr)
{
    if (!target_set(player_ptr, TARGET_KILL))
        return false;

    GAME_TEXT m_name[MAX_NLEN];
    if (exe_blue_teleport_back(player_ptr, m_name))
        return true;

    msg_format(_("%sを引き戻した。", "You command %s to return."), m_name);
    teleport_monster_to(
        player_ptr, player_ptr->current_floor_ptr->grid_array[target_row][target_col].m_idx, player_ptr->y, player_ptr->x, 100, TELEPORT_PASSIVE);
    return true;
}

static bool cast_blue_teleport_away(PlayerType *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    (void)fire_beam(player_ptr, AttributeType::AWAY_ALL, bmc_ptr->dir, 100);
    return true;
}

static bool cast_blue_psy_spear(PlayerType *player_ptr, bmc_type *bmc_ptr)
{
    if (!get_aim_dir(player_ptr, &bmc_ptr->dir))
        return false;

    msg_print(_("光の剣を放った。", "You throw a psycho-spear."));
    bmc_ptr->damage = monspell_bluemage_damage(player_ptr, MonsterAbilityType::PSY_SPEAR, bmc_ptr->plev, DAM_ROLL);
    (void)fire_beam(player_ptr, AttributeType::PSY_SPEAR, bmc_ptr->dir, bmc_ptr->damage);
    return true;
}

static bool cast_blue_make_trap(PlayerType *player_ptr)
{
    if (!target_set(player_ptr, TARGET_KILL))
        return false;

    msg_print(_("呪文を唱えて邪悪に微笑んだ。", "You cast a spell and cackle evilly."));
    trap_creation(player_ptr, target_row, target_col);
    return true;
}

static bool switch_cast_blue_magic(PlayerType *player_ptr, bmc_type *bmc_ptr, MonsterAbilityType spell)
{
    switch (spell) {
    case MonsterAbilityType::SHRIEK:
        msg_print(_("かん高い金切り声をあげた。", "You make a high pitched shriek."));
        aggravate_monsters(player_ptr, 0);
        return true;
    case MonsterAbilityType::XXX1:
    case MonsterAbilityType::XXX2:
    case MonsterAbilityType::XXX3:
    case MonsterAbilityType::XXX4:
        return true;
    case MonsterAbilityType::DISPEL:
        return cast_blue_dispel(player_ptr);
    case MonsterAbilityType::ROCKET:
        return cast_blue_rocket(player_ptr, bmc_ptr);
    case MonsterAbilityType::SHOOT:
        return cast_blue_shoot(player_ptr, bmc_ptr);
    case MonsterAbilityType::BR_ACID:
        return breath_acid_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_ELEC:
        return breath_elec_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_FIRE:
        return breath_fire_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_COLD:
        return breath_cold_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_POIS:
        return breath_pois_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_NETH:
        return breath_nether_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_LITE:
        return breath_lite_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_DARK:
        return breath_dark_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_CONF:
        return breath_conf_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_SOUN:
        return breath_sound_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_CHAO:
        return breath_chaos_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_DISE:
        return breath_disenchant_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_NEXU:
        return breath_nexus_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_TIME:
        return breath_time_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_INER:
        return breath_inertia_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_GRAV:
        return breath_gravity_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_SHAR:
        return breath_shards_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_PLAS:
        return breath_plasma_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_FORC:
        return breath_force_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_MANA:
        return breath_mana_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_NUKE:
        return breath_nuke_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BR_DISI:
        return breath_disintegration_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BA_ACID:
        return ball_acid_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BA_ELEC:
        return ball_elec_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BA_FIRE:
        return ball_fire_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BA_COLD:
        return ball_cold_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BA_POIS:
        return ball_pois_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BA_NUKE:
        return ball_nuke_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BA_NETH:
        return ball_nether_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BA_CHAO:
        return ball_chaos_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BA_WATE:
        return ball_water_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BA_LITE:
        return ball_star_burst_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BA_DARK:
        return ball_dark_storm_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BA_MANA:
        return ball_mana_storm_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::DRAIN_MANA:
        return drain_mana_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::MIND_BLAST:
        return mind_blast_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BRAIN_SMASH:
        return brain_smash_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::CAUSE_1:
        return curse_1_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::CAUSE_2:
        return curse_2_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::CAUSE_3:
        return curse_3_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::CAUSE_4:
        return curse_4_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BO_ACID:
        return bolt_acid_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BO_ELEC:
        return bolt_elec_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BO_FIRE:
        return bolt_fire_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BO_COLD:
        return bolt_cold_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BO_NETH:
        return bolt_nether_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BO_WATE:
        return bolt_water_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BO_MANA:
        return bolt_mana_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BO_PLAS:
        return bolt_plasma_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BO_ICEE:
        return bolt_icee_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::MISSILE:
        return bolt_missile_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::SCARE:
        return scare_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BLIND:
        return blind_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::CONF:
        return confusion_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::SLOW:
        return slow_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::HOLD:
        return sleep_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::HASTE:
        (void)set_fast(player_ptr, randint1(20 + bmc_ptr->plev) + bmc_ptr->plev, false);
        return true;
    case MonsterAbilityType::HAND_DOOM:
        return cast_blue_hand_doom(player_ptr, bmc_ptr);
    case MonsterAbilityType::HEAL: {
        msg_print(_("自分の傷に念を集中した。", "You concentrate on your wounds!"));
        (void)hp_player(player_ptr, bmc_ptr->plev * 4);
        BadStatusSetter bss(player_ptr);
        (void)bss.stun(0);
        (void)bss.cut(0);
        return true;
    }
    case MonsterAbilityType::INVULNER:
        msg_print(_("無傷の球の呪文を唱えた。", "You cast a Globe of Invulnerability."));
        (void)set_invuln(player_ptr, randint1(4) + 4, false);
        return true;
    case MonsterAbilityType::BLINK:
        teleport_player(player_ptr, 10, TELEPORT_SPONTANEOUS);
        return true;
    case MonsterAbilityType::TPORT:
        teleport_player(player_ptr, bmc_ptr->plev * 5, TELEPORT_SPONTANEOUS);
        return true;
    case MonsterAbilityType::WORLD:
        (void)time_walk(player_ptr);
        return true;
    case MonsterAbilityType::SPECIAL:
        return true;
    case MonsterAbilityType::TELE_TO:
        return cast_blue_teleport_back(player_ptr);
    case MonsterAbilityType::TELE_AWAY:
        return cast_blue_teleport_away(player_ptr, bmc_ptr);
    case MonsterAbilityType::TELE_LEVEL:
        return teleport_level_other(player_ptr);
    case MonsterAbilityType::PSY_SPEAR:
        return cast_blue_psy_spear(player_ptr, bmc_ptr);
    case MonsterAbilityType::DARKNESS:
        msg_print(_("暗闇の中で手を振った。", "You gesture in shadow."));
        (void)unlite_area(player_ptr, 10, 3);
        return true;
    case MonsterAbilityType::TRAPS:
        return cast_blue_make_trap(player_ptr);
    case MonsterAbilityType::FORGET:
        msg_print(_("しかし何も起きなかった。", "Nothing happens."));
        return true;
    case MonsterAbilityType::RAISE_DEAD:
        msg_print(_("死者復活の呪文を唱えた。", "You animate the dead."));
        (void)animate_dead(player_ptr, 0, player_ptr->y, player_ptr->x);
        return true;
    case MonsterAbilityType::S_KIN:
        return summon_kin_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::S_CYBER:
        return summon_cyber_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::S_MONSTER:
        return summon_monster_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::S_MONSTERS:
        return summon_monsters_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::S_ANT:
        return summon_ant_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::S_SPIDER:
        return summon_spider_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::S_HOUND:
        return summon_hound_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::S_HYDRA:
        return summon_hydra_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::S_ANGEL:
        return summon_angel_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::S_DEMON:
        return summon_demon_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::S_UNDEAD:
        return summon_undead_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::S_DRAGON:
        return summon_dragon_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::S_HI_UNDEAD:
        return summon_high_undead_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::S_HI_DRAGON:
        return summon_high_dragon_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::S_AMBERITES:
        return summon_amberite_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::S_UNIQUE:
        return summon_unique_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BO_LITE:
        return bolt_lite_caster(player_ptr, bmc_ptr).project();
    case MonsterAbilityType::BO_DARK:
        return bolt_dark_caster(player_ptr, bmc_ptr).project();
    default:
        msg_print("hoge?");
        return true;
    }
}

/*!
 * @brief 青魔法の発動 /
 * do_cmd_cast calls this function if the player's class is 'blue-mage'.
 * @param spell 発動するモンスター攻撃のID
 * @param success TRUEは成功時、FALSEは失敗時の処理を行う
 * @return 処理を実行したらTRUE、キャンセルした場合FALSEを返す。
 */
bool cast_learned_spell(PlayerType *player_ptr, MonsterAbilityType spell, const bool success)
{
    bmc_type tmp_bm;
    bmc_type *bmc_ptr = initialize_blue_magic_type(player_ptr, &tmp_bm, success, get_pseudo_monstetr_level);
    if (!switch_cast_blue_magic(player_ptr, bmc_ptr, spell))
        return false;

    if (bmc_ptr->no_trump)
        msg_print(_("何も現れなかった。", "No one appeared."));

    return true;
}
