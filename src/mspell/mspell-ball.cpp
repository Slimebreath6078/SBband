#include "mspell/mspell-ball.h"
#include "effect/attribute-types.h"
#include "effect/effect-processor.h"
#include "main/sound-definitions-table.h"
#include "main/sound-of-music.h"
#include "mind/drs-types.h"
#include "monster-race/race-ability-flags.h"
#include "monster-race/race-indice-types.h"
#include "monster/monster-info.h"
#include "monster/monster-status.h"
#include "monster/monster-update.h"
#include "mspell/mspell-attribute.h"
#include "mspell/mspell-checker.h"
#include "mspell/mspell-damage-calculator.h"
#include "mspell/mspell-util.h"
#include "mspell/mspell.h"
#include "system/floor-type-definition.h"
#include "system/monster-type-definition.h"
#include "system/player-type-definition.h"
#include "view/display-messages.h"
#include <map>

const std::map<MonsterAbilityType, ball_type> ball_data = {
    { MonsterAbilityType::BA_NUKE,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sが放射能球を放った。", "%^s casts a ball of radiation."),
              _("%^sが%sに放射能球を放った。", "%^s casts a ball of radiation at %s.")),
            SOUND_MAX, { DRS_POIS } } },
    { MonsterAbilityType::BA_ACID,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがアシッド・ボールの呪文を唱えた。", "%^s casts an acid ball."),
              _("%^sが%sに向かってアシッド・ボールの呪文を唱えた。", "%^s casts an acid ball at %s.")),
            SOUND_ACID, { DRS_POIS } } },
    { MonsterAbilityType::BA_ELEC,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがサンダー・ボールの呪文を唱えた。", "%^s casts a lightning ball."),
              _("%^sが%sに向かってサンダー・ボールの呪文を唱えた。", "%^s casts a lightning ball at %s.")),
            SOUND_ELEC, { DRS_ELEC } } },
    { MonsterAbilityType::BA_FIRE,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがファイア・ボールの呪文を唱えた。", "%^s casts a fire ball."),
              _("%^sが%sに向かってファイア・ボールの呪文を唱えた。", "%^s casts a fire ball at %s.")),
            SOUND_FIRE, { DRS_FIRE } } },
    { MonsterAbilityType::BA_COLD,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがアイス・ボールの呪文を唱えた。", "%^s casts a frost ball."),
              _("%^sが%sに向かってアイス・ボールの呪文を唱えた。", "%^s casts a frost ball at %s.")),
            SOUND_COLD, { DRS_COLD } } },
    { MonsterAbilityType::BA_POIS,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sが悪臭雲の呪文を唱えた。", "%^s casts a stinking cloud."),
              _("%^sが%sに向かって悪臭雲の呪文を唱えた。", "%^s casts a stinking cloud at %s.")),
            SOUND_MAX, { DRS_POIS } } },
    { MonsterAbilityType::BA_NETH,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sが地獄球の呪文を唱えた。", "%^s casts a nether ball."),
              _("%^sが%sに向かって地獄球の呪文を唱えた。", "%^s casts a nether ball at %s.")),
            SOUND_MAX, { DRS_NETH } } },
    { MonsterAbilityType::BA_WATE,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sが流れるような身振りをした。", "%^s gestures fluidly."),
              _("%^sが%sに対して流れるような身振りをした。", "%^s gestures fluidly at %s.")),
            SOUND_MAX, { DRS_NONE } } },
    { MonsterAbilityType::BA_MANA,
        { mspell_cast_msg_blind(_("%^sが何かを力強くつぶやいた。", "%^s mumbles powerfully."),
              _("%^sが魔力の嵐の呪文を念じた。", "%^s invokes a mana storm."),
              _("%^sが%sに対して魔力の嵐の呪文を念じた。", "%^s invokes a mana storm upon %s.")),
            SOUND_MAX, { DRS_NONE } } },
    { MonsterAbilityType::BA_DARK,
        { mspell_cast_msg_blind(_("%^sが何かを力強くつぶやいた。", "%^s mumbles powerfully."),
              _("%^sが暗黒の嵐の呪文を念じた。", "%^s invokes a darkness storm."),
              _("%^sが%sに対して暗黒の嵐の呪文を念じた。", "%^s invokes a darkness storm upon %s.")),
            SOUND_MAX, { DRS_DARK } } },
    { MonsterAbilityType::BA_LITE,
        { mspell_cast_msg_blind(_("%^sが何かを力強くつぶやいた。", "%^s mumbles powerfully."),
              _("%^sがスターバーストの呪文を念じた。", "%^s invokes a starburst."),
              _("%^sが%sに対してスターバーストの呪文を念じた。", "%^s invokes a starburst upon %s.")),
            SOUND_MAX, { DRS_LITE } } },
};

BallProjector::BallProjector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE, byte rad, MonsterAbilityType ms_type)
    : player_ptr(player_ptr)
    , m_idx(m_idx)
    , t_idx(t_idx)
    , TARGET_TYPE(TARGET_TYPE)
    , rad(rad)
    , ms_type(ms_type)
{
}

MonsterSpellResult BallProjector::project(POSITION y, POSITION x)
{
    if (view_message())
        play_sound();

    const auto dam = monspell_damage(player_ptr, ms_type, m_idx, damage_flag_type::DAM_ROLL);
    const auto proj_res = breath(player_ptr, y, x, m_idx, get_ability_attribute(ms_type), dam, rad, false, TARGET_TYPE);
    if (TARGET_TYPE == MONSTER_TO_PLAYER)
        smart_learn();

    auto res = MonsterSpellResult::make_valid(dam);
    res.learnable = proj_res.affected_player;

    return res;
}

void BallProjector::play_sound()
{
    sound(ball_data.at(this->ms_type).sound);
}

bool BallProjector::view_message(mspell_cast_msg_blind msg)
{
    return monspell_message(player_ptr, m_idx, t_idx, msg, TARGET_TYPE);
}

bool BallProjector::view_message()
{
    if (this->ms_type == MonsterAbilityType::BA_FIRE) {
        monster_type *m_ptr = &player_ptr->current_floor_ptr->m_list[m_idx];
        if (m_ptr->r_idx == MON_ROLENTO || m_ptr->r_idx == MON_NANAHA) {
            mspell_cast_msg_blind msg;

            msg.blind = _("%sが何かを投げた。", "%^s throws something.");
            msg.to_player = _("%sは手榴弾を投げた。", "%^s throws a hand grenade.");
            msg.to_mons = _("%^sが%^sに向かって手榴弾を投げた。", "%^s throws a hand grenade.");

            return this->view_message(msg);
        }
    } else if (this->ms_type == MonsterAbilityType::BA_WATE) {
        bool known = monster_near_player(player_ptr->current_floor_ptr, m_idx, t_idx);
        bool see_either = see_monster(player_ptr, m_idx) || see_monster(player_ptr, t_idx);
        bool mon_to_mon = (TARGET_TYPE == MONSTER_TO_MONSTER);
        bool mon_to_player = (TARGET_TYPE == MONSTER_TO_PLAYER);
        GAME_TEXT t_name[MAX_NLEN];
        monster_name(player_ptr, t_idx, t_name);

        bool notice = this->view_message(ball_data.at(this->ms_type).msg);

        if (mon_to_player) {
            msg_format(_("あなたは渦巻きに飲み込まれた。", "You are engulfed in a whirlpool."));
        } else if (mon_to_mon && known && see_either && !player_ptr->blind) {
            msg_format(_("%^sは渦巻に飲み込まれた。", "%^s is engulfed in a whirlpool."), t_name);
        }

        return notice;
    }

    return this->view_message(ball_data.at(this->ms_type).msg);
}

void BallProjector::smart_learn()
{
    for (auto &drs : ball_data.at(this->ms_type).drs)
        update_smart_learn(player_ptr, m_idx, drs);
}
