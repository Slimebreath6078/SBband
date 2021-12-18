/*!
 * @brief ものまねの処理実装 / Imitation code
 * @date 2014/01/14
 * @author
 * Copyright (c) 1997 Ben Harrison, James E. Wilson, Robert A. Koeneke\n
 * This software may be copied and distributed for educational, research,\n
 * and not for profit purposes provided that this copyright and statement\n
 * are included in all such copies.  Other copyrights may also apply.\n
 * 2014 Deskull rearranged comment for Doxygen.\n
 */

#include "cmd-action/cmd-mane.h"
#include "action/action-limited.h"
#include "artifact/fixed-art-types.h"
#include "cmd-action/cmd-spell.h"
#include "core/asking-player.h"
#include "core/player-redraw-types.h"
#include "core/stuff-handler.h"
#include "core/window-redrawer.h"
#include "effect/attribute-types.h"
#include "floor/cave.h"
#include "floor/floor-object.h"
#include "game-option/disturbance-options.h"
#include "game-option/text-display-options.h"
#include "hpmp/hp-mp-processor.h"
#include "inventory/inventory-slot-types.h"
#include "main/sound-definitions-table.h"
#include "main/sound-of-music.h"
#include "mind/mind-mage.h"
#include "monster-floor/monster-summon.h"
#include "monster-floor/place-monster-types.h"
#include "monster-race/monster-race.h"
#include "monster-race/race-ability-flags.h"
#include "monster-race/race-flags-resistance.h"
#include "monster-race/race-flags1.h"
#include "monster-race/race-kind-flags.h"
#include "monster/monster-describer.h"
#include "monster/monster-info.h"
#include "monster/monster-processor.h"
#include "monster/monster-status.h"
#include "mspell/monster-power-table.h"
#include "player-base/player-class.h"
#include "player-info/mane-data-type.h"
#include "player-status/player-energy.h"
#include "player/player-status-table.h"
#include "spell-kind/spells-launcher.h"
#include "spell-kind/spells-lite.h"
#include "spell-kind/spells-neighbor.h"
#include "spell-kind/spells-sight.h"
#include "spell-kind/spells-teleport.h"
#include "spell-kind/spells-world.h"
#include "spell/spells-status.h"
#include "spell/spells-summon.h"
#include "spell/summon-types.h"
#include "status/bad-status-setter.h"
#include "status/body-improvement.h"
#include "status/buff-setter.h"
#include "system/floor-type-definition.h"
#include "system/grid-type-definition.h"
#include "system/monster-race-definition.h"
#include "system/monster-type-definition.h"
#include "system/object-type-definition.h"
#include "system/player-type-definition.h"
#include "target/projection-path-calculator.h"
#include "target/target-checker.h"
#include "target/target-getter.h"
#include "target/target-setter.h"
#include "target/target-types.h"
#include "term/screen-processor.h"
#include "timed-effect/player-stun.h"
#include "timed-effect/timed-effects.h"
#include "util/enum-converter.h"
#include "util/int-char-converter.h"
#include "view/display-messages.h"

#include <iterator>

static int damage;

summon_data::summon_data(summon_type type, BIT_FLAGS mode,
    std::function<bool(PlayerType *, MONSTER_IDX, POSITION, POSITION, DEPTH, summon_type, BIT_FLAGS)> summon)
    : type(type)
    , mode(mode)
    , summon(std::move(summon))
{
}

summon_data::summon_data(summon_type type, BIT_FLAGS mode,
    std::function<bool(PlayerType *, DEPTH, POSITION, POSITION, BIT_FLAGS)> summon)
    : type(type)
    , mode(mode)
    , summon([func = std::move(summon)](PlayerType *player_ptr, MONSTER_IDX, POSITION y, POSITION x, DEPTH lev, summon_type, BIT_FLAGS mode) { return func(player_ptr, lev, y, x, mode); })
{
}

mane_attack_spell::mane_attack_spell(PlayerType *player_ptr, concptr msg, AttributeType typ, POSITION rad,
    std::function<bool(PlayerType *, AttributeType, DIRECTION, HIT_POINT, POSITION)> func)
    : player_ptr(player_ptr)
    , msg(msg)
    , typ(typ)
    , rad(rad)
    , dam(damage)
    , func(func)
{
}

mane_attack_spell::mane_attack_spell(PlayerType *player_ptr, concptr msg, AttributeType typ, POSITION rad, HIT_POINT dam,
    std::function<bool(PlayerType *, AttributeType, DIRECTION, HIT_POINT, POSITION)> func)
    : player_ptr(player_ptr)
    , msg(msg)
    , typ(typ)
    , rad(rad)
    , dam(dam)
    , func(func)
{
}

mane_bolt::mane_bolt(PlayerType *player_ptr, concptr msg, AttributeType typ)
    : mane_attack_spell(player_ptr, msg, typ, 0,
          [func = fire_bolt](PlayerType *pl_ptr, AttributeType type, DIRECTION direct, HIT_POINT damag, POSITION) { return func(pl_ptr, type, direct, damag); })
{
}

mane_ball::mane_ball(PlayerType *player_ptr, concptr msg, AttributeType typ, POSITION rad)
    : mane_attack_spell(player_ptr, msg, typ, rad, fire_ball)
{
}

mane_beam::mane_beam(PlayerType *player_ptr, concptr msg, AttributeType typ)
    : mane_attack_spell(player_ptr, msg, typ, 0,
          [func = fire_beam](PlayerType *player_ptr, AttributeType typ, DIRECTION dir, HIT_POINT dam, POSITION) { return func(player_ptr, typ, dir, dam); })
{
}

mane_beam::mane_beam(PlayerType *player_ptr, concptr msg, AttributeType typ, HIT_POINT dam)
    : mane_attack_spell(player_ptr, msg, typ, 0, dam,
          [func = fire_beam](PlayerType *player_ptr, AttributeType typ, DIRECTION dir, HIT_POINT dam, POSITION) { return func(player_ptr, typ, dir, dam); })
{
}

mane_breath::mane_breath(PlayerType *player_ptr, concptr msg, char *buffer, AttributeType typ, POSITION rad)
    : mane_attack_spell(player_ptr, buffer, typ, rad, fire_breath)
{
    sprintf(buffer, _("%sのブレスを吐いた。", "You breathe %s."), msg);
}

mane_ball_hide::mane_ball_hide(PlayerType *player_ptr, concptr msg, AttributeType typ, POSITION rad)
    : mane_attack_spell(player_ptr, msg, typ, rad, fire_ball_hide)
{
}

mane_ball_hide::mane_ball_hide(PlayerType *player_ptr, concptr msg, AttributeType typ, POSITION rad, HIT_POINT dam)
    : mane_attack_spell(player_ptr, msg, typ, rad, dam, fire_ball_hide)
{
}

mane_bad_st::mane_bad_st(PlayerType *player_ptr, concptr msg, int power, std::function<bool(PlayerType *, DIRECTION, int)> func)
    : player_ptr(player_ptr)
    , msg(msg)
    , power(power)
    , func(func)
{
}

mane_summon::mane_summon(PlayerType *player_ptr, concptr msg, POSITION target_y, POSITION target_x, DEPTH plev, int num, std::vector<summon_data> summon_list)
    : player_ptr(player_ptr)
    , msg(msg)
    , target_y(target_y)
    , target_x(target_x)
    , plev(plev)
    , num(num)
    , summon_list(summon_list)
{
}

bool mane_attack_spell::fire()
{
    DIRECTION dir;
    if (!get_aim_dir(this->player_ptr, &dir))
        return false;
    else if (this->msg)
        msg_print(this->msg);
    func(this->player_ptr, this->typ, dir, dam, this->rad);
    return true;
}

bool mane_bad_st::fire()
{
    DIRECTION dir;
    if (!get_aim_dir(this->player_ptr, &dir))
        return false;
    else if (this->msg)
        msg_print(this->msg);

    func(this->player_ptr, dir, this->power);
    return true;
}

bool mane_summon::fire()
{
    int count = 0;
    if (!target_set(this->player_ptr, TARGET_KILL))
        return false;
    msg_print(this->msg);
    for (const auto &job : summon_list) {
        for (int k = count; k < this->num; k++) {
            if (job.summon(this->player_ptr, -1, this->target_y, this->target_x, this->plev, job.type, job.mode))
                count++;
        }
    }
    return true;
}

/*!
 * @brief 受け取ったパラメータに応じてものまねの効果情報をまとめたフォーマットを返す
 * @param p 情報を返す文字列参照ポインタ
 * @param power ものまねの効力の種類
 * @param dam ものまねの威力
 */
static void mane_info(PlayerType *player_ptr, char *p, MonsterAbilityType power, HIT_POINT dam)
{
    PLAYER_LEVEL plev = player_ptr->lev;

    strcpy(p, "");

    const auto power_int = enum2i(power);

    if ((power_int > 2 && power_int < 41) || (power_int > 41 && power_int < 59) || (power == MonsterAbilityType::PSY_SPEAR))
        sprintf(p, " %s%d", KWD_DAM, (int)dam);
    else {
        switch (power) {
        case MonsterAbilityType::DRAIN_MANA:
            sprintf(p, " %sd%d+%d", KWD_HEAL, plev * 3, plev);
            break;
        case MonsterAbilityType::HASTE:
            sprintf(p, " %sd%d+%d", KWD_DURATION, 20 + plev, plev);
            break;
        case MonsterAbilityType::HEAL:
            sprintf(p, " %s%d", KWD_HEAL, plev * 6);
            break;
        case MonsterAbilityType::INVULNER:
            sprintf(p, " %sd7+7", KWD_DURATION);
            break;
        case MonsterAbilityType::BLINK:
            sprintf(p, " %s10", KWD_SPHERE);
            break;
        case MonsterAbilityType::TPORT:
            sprintf(p, " %s%d", KWD_SPHERE, plev * 5);
            break;
        case MonsterAbilityType::RAISE_DEAD:
            sprintf(p, " %s5", KWD_SPHERE);
            break;
        default:
            break;
        }
    }
}

/*!
 * @brief どのものまねを発動するか選択する処理 /
 * Allow user to choose a imitation.
 * @param sn 実行したものまねのIDを返す参照ポインタ（キャンセルなどの場合-1を返す）
 * @param baigaesi TRUEならば倍返し上の処理として行う
 * @return 処理を実行したらTRUE、キャンセルした場合FALSEを返す。
 * @details
 * If a valid spell is chosen, saves it in '*sn' and returns TRUE
 * If the user hits escape, returns FALSE, and set '*sn' to -1
 * If there are no legal choices, returns FALSE, and sets '*sn' to -2
 *
 * The "prompt" should be "cast", "recite", or "study"
 * The "known" should be TRUE for cast/pray, FALSE for study
 *
 * nb: This function has a (trivial) display bug which will be obvious
 * when you run it. It's probably easy to fix but I haven't tried,
 * sorry.
 */
static int get_mane_power(PlayerType *player_ptr, int *sn, bool baigaesi)
{
    int i = 0;
    int num = 0;
    TERM_LEN y = 1;
    TERM_LEN x = 18;
    PERCENTAGE minfail = 0;
    PLAYER_LEVEL plev = player_ptr->lev;
    PERCENTAGE chance = 0;
    int ask;
    char choice;
    char out_val[MAX_MONSTER_NAME];
    char comment[80];
    concptr p = _("能力", "power");

    monster_power spell;
    bool flag, redraw;

    /* Assume cancelled */
    *sn = (-1);

    flag = false;
    redraw = false;

    auto mane_data = PlayerClass(player_ptr).get_specific_data<mane_data_type>();

    num = mane_data->mane_list.size();

    /* Build a prompt (accept all spells) */
    (void)strnfmt(out_val, 78, _("(%c-%c, '*'で一覧, ESC) どの%sをまねますか？", "(%c-%c, *=List, ESC=exit) Use which %s? "), I2A(0), I2A(num - 1), p);

    choice = always_show_list ? ESCAPE : 1;
    while (!flag) {
        if (choice == ESCAPE)
            choice = ' ';
        else if (!get_com(out_val, &choice, true))
            break;

        /* Request redraw */
        if ((choice == ' ') || (choice == '*') || (choice == '?')) {
            /* Show the list */
            if (!redraw) {
                char psi_desc[160];
                redraw = true;
                screen_save();

                /* Display a list of spells */
                prt("", y, x);
                put_str(_("名前", "Name"), y, x + 5);
                put_str(_("失率 効果", "Fail Info"), y, x + 36);

                /* Dump the spells */
                for (i = 0; i < num; i++) {
                    const auto &mane = mane_data->mane_list[i];
                    /* Access the spell */
                    spell = monster_powers.at(mane.spell);

                    chance = spell.manefail;

                    /* Reduce failure rate by "effective" level adjustment */
                    if (plev > spell.level)
                        chance -= 3 * (plev - spell.level);

                    /* Reduce failure rate by INT/WIS adjustment */
                    chance -= 3 * (adj_mag_stat[player_ptr->stat_index[spell.use_stat]] + adj_mag_stat[player_ptr->stat_index[A_DEX]] - 2) / 2;

                    if (spell.manedam)
                        chance = chance * (baigaesi ? mane.damage * 2 : mane.damage) / spell.manedam;

                    chance += player_ptr->to_m_chance;

                    if (player_ptr->inventory_list[INVEN_NECK].name1 == ART_GOGO_PENDANT) {
                        chance -= 10;
                    }

                    /* Extract the minimum failure rate */
                    minfail = adj_mag_fail[player_ptr->stat_index[spell.use_stat]];

                    /* Minimum failure rate */
                    if (chance < minfail)
                        chance = minfail;

                    auto player_stun = player_ptr->effects()->stun();
                    chance += player_stun->get_magic_chance_penalty();
                    if (chance > 95) {
                        chance = 95;
                    }

                    /* Get info */
                    mane_info(player_ptr, comment, mane.spell, (baigaesi ? mane.damage * 2 : mane.damage));

                    /* Dump the spell --(-- */
                    sprintf(psi_desc, "  %c) %-30s %3d%%%s", I2A(i), spell.name, chance, comment);
                    prt(psi_desc, y + i + 1, x);
                }

                /* Clear the bottom line */
                prt("", y + i + 1, x);
            }

            /* Hide the list */
            else {
                /* Hide list */
                redraw = false;
                screen_load();
            }

            /* Redo asking */
            continue;
        }

        /* Note verify */
        ask = isupper(choice);

        /* Lowercase */
        if (ask)
            choice = (char)tolower(choice);

        /* Extract request */
        i = (islower(choice) ? A2I(choice) : -1);

        /* Totally Illegal */
        if ((i < 0) || (i >= num)) {
            bell();
            continue;
        }

        /* Save the spell index */
        spell = monster_powers.at(mane_data->mane_list[i].spell);

        /* Verify it */
        if (ask) {
            char tmp_val[160];

            /* Prompt */
            (void)strnfmt(tmp_val, 78, _("%sをまねますか？", "Use %s? "), spell.name);

            /* Belay that order */
            if (!get_check(tmp_val))
                continue;
        }

        /* Stop the loop */
        flag = true;
    }
    if (redraw)
        screen_load();

    player_ptr->window_flags |= (PW_SPELL);
    handle_stuff(player_ptr);

    /* Abort if needed */
    if (!flag)
        return false;

    /* Save the choice */
    (*sn) = i;

    damage = (baigaesi ? mane_data->mane_list[i].damage * 2 : mane_data->mane_list[i].damage);

    /* Success */
    return true;
}

/*!
 * @brief ものまね処理の発動 /
 * do_cmd_cast calls this function if the player's class is 'imitator'.
 * @param player_ptr プレイヤーへの参照ポインタ
 * @param spell 発動するモンスター攻撃のID
 * @return 処理を実行したらTRUE、キャンセルした場合FALSEを返す。
 */
static bool use_mane(PlayerType *player_ptr, MonsterAbilityType spell)
{
    DIRECTION dir;
    PLAYER_LEVEL plev = player_ptr->lev;
    BIT_FLAGS mode = (PM_ALLOW_GROUP | PM_FORCE_PET);
    BIT_FLAGS u_mode = 0L;
    char p[80];

    if (randint1(50 + plev) < plev / 10)
        u_mode = PM_ALLOW_UNIQUE;

    /* spell code */
    switch (spell) {
    case MonsterAbilityType::SHRIEK:
        msg_print(_("かん高い金切り声をあげた。", "You make a high pitched shriek."));
        aggravate_monsters(player_ptr, 0);
        break;

    case MonsterAbilityType::XXX1:
        break;

    case MonsterAbilityType::DISPEL: {
        MONSTER_IDX m_idx;

        if (!target_set(player_ptr, TARGET_KILL))
            return false;
        m_idx = player_ptr->current_floor_ptr->grid_array[target_row][target_col].m_idx;
        if (!m_idx)
            break;
        if (!player_has_los_bold(player_ptr, target_row, target_col))
            break;
        if (!projectable(player_ptr, player_ptr->y, player_ptr->x, target_row, target_col))
            break;
        dispel_monster_status(player_ptr, m_idx);
        break;
    }

    case MonsterAbilityType::ROCKET:
        if (!get_aim_dir(player_ptr, &dir))
            return false;
        else
            msg_print(_("ロケットを発射した。", "You fire a rocket."));
        fire_rocket(player_ptr, AttributeType::ROCKET, dir, damage, 2);
        break;

    case MonsterAbilityType::SHOOT:
        if (!mane_bolt(player_ptr, _("矢を放った。", "You fire an arrow."), AttributeType::ARROW).fire())
            return false;
        break;

    case MonsterAbilityType::XXX2:
        break;

    case MonsterAbilityType::XXX3:
        break;

    case MonsterAbilityType::XXX4:
        break;

    case MonsterAbilityType::BR_ACID:
        if (!mane_breath(player_ptr, _("酸", "acid"), p, AttributeType::ACID, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_ELEC:
        if (!mane_breath(player_ptr, _("稲妻", "lightning"), p, AttributeType::ELEC, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_FIRE:
        if (!mane_breath(player_ptr, _("火炎", "fire"), p, AttributeType::FIRE, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_COLD:
        if (!mane_breath(player_ptr, _("冷気", "frost"), p, AttributeType::COLD, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_POIS:
        if (!mane_breath(player_ptr, _("ガス", "gas"), p, AttributeType::POIS, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_NETH:
        if (!mane_breath(player_ptr, _("地獄", "nether"), p, AttributeType::NETHER, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_LITE:
        if (!mane_breath(player_ptr, _("閃光", "light"), p, AttributeType::LITE, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_DARK:
        if (!mane_breath(player_ptr, _("暗黒", "darkness"), p, AttributeType::DARK, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_CONF:
        if (!mane_breath(player_ptr, _("混乱", "confusion"), p, AttributeType::CONFUSION, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_SOUN:
        if (!mane_breath(player_ptr, _("轟音", "sound"), p, AttributeType::SOUND, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_CHAO:
        if (!mane_breath(player_ptr, _("カオス", "chaos"), p, AttributeType::CHAOS, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_DISE:
        if (!mane_breath(player_ptr, _("劣化", "disenchantment"), p, AttributeType::DISENCHANT, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_NEXU:
        if (!mane_breath(player_ptr, _("因果混乱", "nexus"), p, AttributeType::NEXUS, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_TIME:
        if (!mane_breath(player_ptr, _("時間逆転", "time"), p, AttributeType::TIME, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_INER:
        if (!mane_breath(player_ptr, _("遅鈍", "inertia"), p, AttributeType::INERTIAL, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_GRAV:
        if (!mane_breath(player_ptr, _("重力", "gravity"), p, AttributeType::GRAVITY, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_SHAR:
        if (!mane_breath(player_ptr, _("破片", "shards"), p, AttributeType::SHARDS, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_PLAS:
        if (!mane_breath(player_ptr, _("プラズマ", "plasma"), p, AttributeType::PLASMA, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_FORC:
        if (!mane_breath(player_ptr, _("フォース", "force"), p, AttributeType::FORCE, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BR_MANA:
        if (!mane_breath(player_ptr, _("魔力", "mana"), p, AttributeType::MANA, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BA_NUKE:
        if (!mane_ball(player_ptr, _("放射能球を放った。", "You cast a ball of radiation."), AttributeType::NUKE, 2).fire())
            return false;
        break;

    case MonsterAbilityType::BR_NUKE:
        if (!mane_breath(player_ptr, _("放射性廃棄物", "toxic waste"), p, AttributeType::NUKE, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BA_CHAO:
        if (!mane_ball(player_ptr, _("純ログルスを放った。", "You invoke a raw Logrus."), AttributeType::CHAOS, 4).fire())
            return false;
        break;
    case MonsterAbilityType::BR_DISI:
        if (!mane_breath(player_ptr, _("分解", "disintegration"), p, AttributeType::DISINTEGRATE, (plev > 35 ? 3 : 2)).fire())
            return false;
        break;

    case MonsterAbilityType::BA_ACID:
        if (!mane_ball(player_ptr, _("アシッド・ボールの呪文を唱えた。", "You cast an acid ball."), AttributeType::ACID, 2).fire())
            return false;
        break;
    case MonsterAbilityType::BA_ELEC:
        if (!mane_ball(player_ptr, _("サンダー・ボールの呪文を唱えた。", "You cast a lightning ball."), AttributeType::ELEC, 2).fire())
            return false;
        break;
    case MonsterAbilityType::BA_FIRE:
        if (!mane_ball(player_ptr, _("ファイア・ボールの呪文を唱えた。", "You cast a fire ball."), AttributeType::FIRE, 2).fire())
            return false;
        break;
    case MonsterAbilityType::BA_COLD:
        if (!mane_ball(player_ptr, _("アイス・ボールの呪文を唱えた。", "You cast a frost ball."), AttributeType::COLD, 2).fire())
            return false;
        break;
    case MonsterAbilityType::BA_POIS:
        if (!mane_ball(player_ptr, _("悪臭雲の呪文を唱えた。", "You cast a stinking cloud."), AttributeType::POIS, 2).fire())
            return false;
        break;
    case MonsterAbilityType::BA_NETH:
        if (!mane_ball(player_ptr, _("地獄球の呪文を唱えた。", "You cast a nether ball."), AttributeType::NETHER, 2).fire())
            return false;
        break;
    case MonsterAbilityType::BA_WATE:
        if (!mane_ball(player_ptr, _("流れるような身振りをした。", "You gesture fluidly."), AttributeType::WATER, 4).fire())
            return false;
        break;
    case MonsterAbilityType::BA_MANA:
        if (!mane_ball(player_ptr, _("魔力の嵐の呪文を念じた。", "You invoke a mana storm."), AttributeType::MANA, 4).fire())
            return false;
        break;
    case MonsterAbilityType::BA_DARK:
        if (!mane_ball(player_ptr, _("暗黒の嵐の呪文を念じた。", "You invoke a darkness storm."), AttributeType::DARK, 4).fire())
            return false;
        break;
    case MonsterAbilityType::DRAIN_MANA:
        if (!mane_ball_hide(player_ptr, nullptr, AttributeType::DRAIN_MANA, randint1(plev * 3) + plev, 0).fire())
            return false;
        break;
    case MonsterAbilityType::MIND_BLAST:
        if (!mane_ball_hide(player_ptr, nullptr, AttributeType::MIND_BLAST, 0).fire())
            return false;
        break;
    case MonsterAbilityType::BRAIN_SMASH:
        if (!mane_ball_hide(player_ptr, nullptr, AttributeType::BRAIN_SMASH, 0).fire())
            return false;
        break;
    case MonsterAbilityType::CAUSE_1:
        if (!mane_ball_hide(player_ptr, nullptr, AttributeType::CAUSE_1, 0).fire())
            return false;
        break;
    case MonsterAbilityType::CAUSE_2:
        if (!mane_ball_hide(player_ptr, nullptr, AttributeType::CAUSE_2, 0).fire())
            return false;
        break;
    case MonsterAbilityType::CAUSE_3:
        if (!mane_ball_hide(player_ptr, nullptr, AttributeType::CAUSE_3, 0).fire())
            return false;
        break;
    case MonsterAbilityType::CAUSE_4:
        if (!mane_ball_hide(player_ptr, nullptr, AttributeType::CAUSE_4, 0).fire())
            return false;
        break;
    case MonsterAbilityType::BO_ACID:
        if (!mane_bolt(player_ptr, _("アシッド・ボルトの呪文を唱えた。", "You cast an acid bolt."), AttributeType::ACID).fire())
            return false;
        break;
    case MonsterAbilityType::BO_ELEC:
        if (!mane_bolt(player_ptr, _("サンダー・ボルトの呪文を唱えた。", "You cast a lightning bolt."), AttributeType::ELEC).fire())
            return false;
        break;
    case MonsterAbilityType::BO_FIRE:
        if (!mane_bolt(player_ptr, _("ファイア・ボルトの呪文を唱えた。", "You cast a fire bolt."), AttributeType::FIRE).fire())
            return false;
        break;
    case MonsterAbilityType::BO_COLD:
        if (!mane_bolt(player_ptr, _("アイス・ボルトの呪文を唱えた。", "You cast a frost bolt."), AttributeType::COLD).fire())
            return false;
        break;
    case MonsterAbilityType::BA_LITE:
        if (!mane_ball(player_ptr, _("スターバーストの呪文を念じた。", "You invoke a starburst."), AttributeType::LITE, 4).fire())
            return false;
        break;
    case MonsterAbilityType::BO_NETH:
        if (!mane_bolt(player_ptr, _("地獄の矢の呪文を唱えた。", "You cast a nether bolt."), AttributeType::NETHER).fire())
            return false;
        break;
    case MonsterAbilityType::BO_WATE:
        if (!mane_bolt(player_ptr, _("ウォーター・ボルトの呪文を唱えた。", "You cast a water bolt."), AttributeType::WATER).fire())
            return false;
        break;
    case MonsterAbilityType::BO_MANA:
        if (!mane_bolt(player_ptr, _("魔力の矢の呪文を唱えた。", "You cast a mana bolt."), AttributeType::MANA).fire())
            return false;
        break;
    case MonsterAbilityType::BO_PLAS:
        if (!mane_bolt(player_ptr, _("プラズマ・ボルトの呪文を唱えた。", "You cast a plasma bolt."), AttributeType::PLASMA).fire())
            return false;
        break;
    case MonsterAbilityType::BO_ICEE:
        if (!mane_bolt(player_ptr, _("極寒の矢の呪文を唱えた。", "You cast a ice bolt."), AttributeType::ICE).fire())
            return false;
        break;
    case MonsterAbilityType::MISSILE:
        if (!mane_bolt(player_ptr, _("マジック・ミサイルの呪文を唱えた。", "You cast a magic missile."), AttributeType::MISSILE).fire())
            return false;
        break;
    case MonsterAbilityType::SCARE:
        if (!mane_bad_st(player_ptr, _("恐ろしげな幻覚を作り出した。", "You cast a fearful illusion."), plev + 10, fear_monster).fire())
            return false;
        break;
    case MonsterAbilityType::BLIND:
        if (!mane_bad_st(player_ptr, nullptr, plev * 2, confuse_monster).fire())
            return false;
        break;
    case MonsterAbilityType::CONF:
        if (!mane_bad_st(player_ptr, _("誘惑的な幻覚をつくり出した。", "You cast a mesmerizing illusion."), plev * 2, confuse_monster).fire())

            return false;
        break;
    case MonsterAbilityType::SLOW:
        if (!mane_bad_st(player_ptr, nullptr, plev, slow_monster).fire())

            return false;
        break;
    case MonsterAbilityType::HOLD:
        if (!mane_bad_st(player_ptr, nullptr, plev, sleep_monster).fire())

            return false;
        break;
    case MonsterAbilityType::HASTE:
        (void)set_fast(player_ptr, randint1(20 + plev) + plev, false);
        break;
    case MonsterAbilityType::HAND_DOOM: {
        if (!mane_ball_hide(player_ptr, _("<破滅の手>を放った！", "You invoke the Hand of Doom!"), AttributeType::HAND_DOOM, 200, 0).fire())
            return false;
        break;
    }
    case MonsterAbilityType::HEAL: {
        msg_print(_("自分の傷に念を集中した。", "You concentrate on your wounds!"));
        (void)hp_player(player_ptr, plev * 6);
        BadStatusSetter bss(player_ptr);
        (void)bss.stun(0);
        (void)bss.cut(0);
        break;
    }
    case MonsterAbilityType::INVULNER:
        msg_print(_("無傷の球の呪文を唱えた。", "You cast a Globe of Invulnerability."));
        (void)set_invuln(player_ptr, randint1(7) + 7, false);
        break;
    case MonsterAbilityType::BLINK:
        teleport_player(player_ptr, 10, TELEPORT_SPONTANEOUS);
        break;
    case MonsterAbilityType::TPORT:
        teleport_player(player_ptr, plev * 5, TELEPORT_SPONTANEOUS);
        break;
    case MonsterAbilityType::WORLD:
        (void)time_walk(player_ptr);
        break;
    case MonsterAbilityType::SPECIAL:
        break;
    case MonsterAbilityType::TELE_TO: {
        monster_type *m_ptr;
        monster_race *r_ptr;
        GAME_TEXT m_name[MAX_NLEN];

        if (!target_set(player_ptr, TARGET_KILL))
            return false;
        if (!player_ptr->current_floor_ptr->grid_array[target_row][target_col].m_idx)
            break;
        if (!player_has_los_bold(player_ptr, target_row, target_col))
            break;
        if (!projectable(player_ptr, player_ptr->y, player_ptr->x, target_row, target_col))
            break;
        m_ptr = &player_ptr->current_floor_ptr->m_list[player_ptr->current_floor_ptr->grid_array[target_row][target_col].m_idx];
        r_ptr = &r_info[m_ptr->r_idx];
        monster_desc(player_ptr, m_name, m_ptr, 0);
        if (r_ptr->resistance_flags.has(MonsterResistanceType::RESIST_TELEPORT)) {
            if ((r_ptr->race_kind_flags.has(MonraceKindType::UNIQUE)) || (r_ptr->resistance_flags.has(MonsterResistanceType::RESIST_ALL))) {
                if (is_original_ap_and_seen(player_ptr, m_ptr))
                    r_ptr->r_resistance_flags.set(MonsterResistanceType::RESIST_TELEPORT);
                msg_format(_("%sには効果がなかった！", "%s is unaffected!"), m_name);

                break;
            } else if (r_ptr->level > randint1(100)) {
                if (is_original_ap_and_seen(player_ptr, m_ptr))
                    r_ptr->r_resistance_flags.set(MonsterResistanceType::RESIST_TELEPORT);
                msg_format(_("%sには耐性がある！", "%s resists!"), m_name);

                break;
            }
        }
        msg_format(_("%sを引き戻した。", "You command %s to return."), m_name);

        teleport_monster_to(
            player_ptr, player_ptr->current_floor_ptr->grid_array[target_row][target_col].m_idx, player_ptr->y, player_ptr->x, 100, TELEPORT_PASSIVE);
        break;
    }
    case MonsterAbilityType::TELE_AWAY:
        if (!mane_beam(player_ptr, nullptr, AttributeType::AWAY_ALL, plev).fire())
            return false;
        break;

    case MonsterAbilityType::TELE_LEVEL:
        return teleport_level_other(player_ptr);
        break;

    case MonsterAbilityType::PSY_SPEAR:
        if (!mane_beam(player_ptr, _("光の剣を放った。", "You throw a psycho-spear."), AttributeType::PSY_SPEAR).fire())
            return false;
        break;

    case MonsterAbilityType::DARKNESS:
        msg_print(_("暗闇の中で手を振った。", "You gesture in shadow."));
        (void)unlite_area(player_ptr, 10, 3);
        break;

    case MonsterAbilityType::TRAPS:
        if (!target_set(player_ptr, TARGET_KILL))
            return false;
        msg_print(_("呪文を唱えて邪悪に微笑んだ。", "You cast a spell and cackle evilly."));
        trap_creation(player_ptr, target_row, target_col);
        break;
    case MonsterAbilityType::FORGET:
        msg_print(_("しかし何も起きなかった。", "Nothing happens."));
        break;
    case MonsterAbilityType::RAISE_DEAD:
        msg_print(_("死者復活の呪文を唱えた。", "You animate the dead."));
        (void)animate_dead(player_ptr, 0, player_ptr->y, player_ptr->x);
        break;
    case MonsterAbilityType::S_KIN: {
        if (!mane_summon(player_ptr, _("援軍を召喚した。", "You summon minions."), target_row, target_col, plev, 4,
                { summon_data(SUMMON_NONE, (PM_FORCE_PET | PM_ALLOW_GROUP), summon_kin_player) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::S_CYBER: {
        int max_cyber = (player_ptr->current_floor_ptr->dun_level / 50) + randint1(3);
        if (max_cyber > 4)
            max_cyber = 4;
        if (!mane_summon(player_ptr, _("サイバーデーモンを召喚した！", "You summon Cyberdemons!"), target_row, target_col, plev, max_cyber,
                { summon_data(SUMMON_CYBER, mode, summon_specific) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::S_MONSTER: {
        if (!mane_summon(player_ptr, _("仲間を召喚した。", "You summon help."), target_row, target_col, plev, 1,
                { summon_data(SUMMON_NONE, (mode | u_mode), summon_specific) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::S_MONSTERS: {
        if (!mane_summon(player_ptr, _("モンスターを召喚した！", "You summon monsters!"), target_row, target_col, plev, 6,
                { summon_data(SUMMON_NONE, (mode | u_mode), summon_specific) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::S_ANT: {
        if (!mane_summon(player_ptr, _("アリを召喚した。", "You summon ants."), target_row, target_col, plev, 6,
                { summon_data(SUMMON_ANT, mode, summon_specific) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::S_SPIDER: {
        if (!mane_summon(player_ptr, _("蜘蛛を召喚した。", "You summon spiders."), target_row, target_col, plev, 6,
                { summon_data(SUMMON_SPIDER, mode, summon_specific) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::S_HOUND: {
        if (!mane_summon(player_ptr, _("ハウンドを召喚した。", "You summon hounds."), target_row, target_col, plev, 4,
                { summon_data(SUMMON_HOUND, mode, summon_specific) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::S_HYDRA: {
        if (!mane_summon(player_ptr, _("ヒドラを召喚した。", "You summon hydras."), target_row, target_col, plev, 4,
                { summon_data(SUMMON_HYDRA, mode, summon_specific) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::S_ANGEL: {
        if (!mane_summon(player_ptr, _("天使を召喚した！", "You summon an angel!"), target_row, target_col, plev, 1,
                { summon_data(SUMMON_ANGEL, mode, summon_specific) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::S_DEMON: {
        if (!mane_summon(player_ptr, _("混沌の宮廷から悪魔を召喚した！", "You summon a demon from the Courts of Chaos!"), target_row, target_col, plev, 1,
                { summon_data(SUMMON_DEMON, (mode | u_mode), summon_specific) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::S_UNDEAD: {
        if (!mane_summon(player_ptr, _("アンデッドの強敵を召喚した！", "You summon an undead adversary!"), target_row, target_col, plev, 1,
                { summon_data(SUMMON_UNDEAD, (mode | u_mode), summon_specific) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::S_DRAGON: {
        if (!mane_summon(player_ptr, _("ドラゴンを召喚した！", "You summon a dragon!"), target_row, target_col, plev, 1,
                { summon_data(SUMMON_DRAGON, (mode | u_mode), summon_specific) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::S_HI_UNDEAD: {
        if (!mane_summon(player_ptr, _("強力なアンデッドを召喚した！", "You summon greater undead!"), target_row, target_col, plev, 6,
                { summon_data(SUMMON_HI_UNDEAD, (mode | u_mode), summon_specific) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::S_HI_DRAGON: {
        if (!mane_summon(player_ptr, _("古代ドラゴンを召喚した！", "You summon ancient dragons!"), target_row, target_col, plev, 4,
                { summon_data(SUMMON_HI_DRAGON, (mode | u_mode), summon_specific) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::S_AMBERITES: {
        if (!mane_summon(player_ptr, _("アンバーの王族を召喚した！", "You summon Lords of Amber!"), target_row, target_col, plev, 4,
                { summon_data(SUMMON_AMBERITES, (mode | PM_ALLOW_UNIQUE), summon_specific) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::S_UNIQUE: {
        if (!mane_summon(player_ptr, _("特別な強敵を召喚した！", "You summon special opponents!"), target_row, target_col, plev, 4,
                { summon_data(SUMMON_UNIQUE, (mode | PM_ALLOW_UNIQUE), summon_specific),
                    summon_data(SUMMON_HI_UNDEAD, (mode | u_mode), summon_specific) })
                 .fire())
            return false;
        break;
    }
    case MonsterAbilityType::BO_LITE:
        if (!mane_bolt(player_ptr, _("スターライトアローを放った。", "You fire a starlight arrow."), AttributeType::LITE).fire())
            return false;
        break;
    case MonsterAbilityType::BO_DARK:
        if (!mane_bolt(player_ptr, _("暗黒の矢の呪文を唱えた。", "You cast a dark bolt."), AttributeType::DARK).fire())
            return false;
        break;
    case MonsterAbilityType::DRAIN_LIFE:
        if (!mane_ball_hide(player_ptr, nullptr, AttributeType::DRAIN_LIFE, 0).fire())
            return false;
        break;
    default:
        msg_print("hoge?");
    }

    return true;
}

/*!
 * @brief ものまねコマンドのメインルーチン /
 * do_cmd_cast calls this function if the player's class is 'imitator'.
 * @param baigaesi TRUEならば倍返し上の処理として行う
 * @return 処理を実行したらTRUE、キャンセルした場合FALSEを返す。
 * @details
 * If a valid spell is chosen, saves it in '*sn' and returns TRUE
 * If the user hits escape, returns FALSE, and set '*sn' to -1
 * If there are no legal choices, returns FALSE, and sets '*sn' to -2
 *
 * The "prompt" should be "cast", "recite", or "study"
 * The "known" should be TRUE for cast/pray, FALSE for study
 *
 * nb: This function has a (trivial) display bug which will be obvious
 * when you run it. It's probably easy to fix but I haven't tried,
 * sorry.
 */
bool do_cmd_mane(PlayerType *player_ptr, bool baigaesi)
{
    int n = 0;
    PERCENTAGE chance;
    PERCENTAGE minfail = 0;
    PLAYER_LEVEL plev = player_ptr->lev;
    monster_power spell;
    bool cast;

    if (cmd_limit_confused(player_ptr))
        return false;

    auto mane_data = PlayerClass(player_ptr).get_specific_data<mane_data_type>();

    if (mane_data->mane_list.empty()) {
        msg_print(_("まねられるものが何もない！", "You don't remember any action!"));
        return false;
    }

    if (!get_mane_power(player_ptr, &n, baigaesi))
        return false;

    spell = monster_powers.at(mane_data->mane_list[n].spell);

    /* Spell failure chance */
    chance = spell.manefail;

    /* Reduce failure rate by "effective" level adjustment */
    if (plev > spell.level)
        chance -= 3 * (plev - spell.level);

    /* Reduce failure rate by 1 stat and DEX adjustment */
    chance -= 3 * (adj_mag_stat[player_ptr->stat_index[spell.use_stat]] + adj_mag_stat[player_ptr->stat_index[A_DEX]] - 2) / 2;

    if (spell.manedam)
        chance = chance * damage / spell.manedam;

    chance += player_ptr->to_m_chance;

    /* Extract the minimum failure rate */
    minfail = adj_mag_fail[player_ptr->stat_index[spell.use_stat]];

    /* Minimum failure rate */
    if (chance < minfail)
        chance = minfail;

    auto player_stun = player_ptr->effects()->stun();
    chance += player_stun->get_magic_chance_penalty();
    if (chance > 95) {
        chance = 95;
    }

    /* Failed spell */
    if (randint0(100) < chance) {
        if (flush_failure)
            flush();
        msg_print(_("ものまねに失敗した！", "You failed to concentrate hard enough!"));
        sound(SOUND_FAIL);
    } else {
        sound(SOUND_ZAP);
        cast = use_mane(player_ptr, mane_data->mane_list[n].spell);
        if (!cast)
            return false;
    }

    mane_data->mane_list.erase(std::next(mane_data->mane_list.begin(), n));

    PlayerEnergy(player_ptr).set_player_turn_energy(100);

    player_ptr->redraw |= (PR_IMITATION);
    player_ptr->window_flags |= (PW_PLAYER);
    player_ptr->window_flags |= (PW_SPELL);

    return true;
}
