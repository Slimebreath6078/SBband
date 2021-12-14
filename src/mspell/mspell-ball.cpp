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
#include "mspell/mspell-checker.h"
#include "mspell/mspell-damage-calculator.h"
#include "mspell/mspell-util.h"
#include "mspell/mspell.h"
#include "system/floor-type-definition.h"
#include "system/monster-type-definition.h"
#include "system/player-type-definition.h"
#include "view/display-messages.h"

BallProjector::BallProjector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, const mspell_cast_msg_blind &msgs, int TARGET_TYPE, byte rad, MonsterAbilityType ms_type, AttributeType typ, int SOUND)
    : player_ptr(player_ptr)
    , m_idx(m_idx)
    , t_idx(t_idx)
    , msgs(msgs)
    , TARGET_TYPE(TARGET_TYPE)
    , rad(rad)
    , ms_type(ms_type)
    , typ(typ)
    , SOUND(SOUND)
{
}

MonsterSpellResult BallProjector::project(POSITION y, POSITION x)
{
    if (view_message())
        play_sound();

    const auto dam = monspell_damage(player_ptr, ms_type, m_idx, damage_flag_type::DAM_ROLL);
    const auto proj_res = breath(player_ptr, y, x, m_idx, typ, dam, rad, false, TARGET_TYPE);
    if (TARGET_TYPE == MONSTER_TO_PLAYER)
        smart_learn();

    auto res = MonsterSpellResult::make_valid(dam);
    res.learnable = proj_res.affected_player;

    return res;
}

void BallProjector::play_sound()
{
    sound(SOUND);
}

BA_NUKE_Projector::BA_NUKE_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    : BallProjector(player_ptr, m_idx, t_idx,
          mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."), _("%^sが放射能球を放った。", "%^s casts a ball of radiation."),
              _("%^sが%sに放射能球を放った。", "%^s casts a ball of radiation at %s.")),
          2, TARGET_TYPE, MonsterAbilityType::BA_NUKE, AttributeType::NUKE, SOUND_MAX)
{
}

BA_CHAO_Projector::BA_CHAO_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    : BallProjector(player_ptr, m_idx, t_idx,
          mspell_cast_msg_blind(_("%^sが恐ろしげにつぶやいた。", "%^s mumbles frighteningly."), _("%^sが純ログルスを放った。", "%^s invokes a raw Logrus."),
              _("%^sが%sに純ログルスを放った。", "%^s invokes raw Logrus upon %s.")),
          4, TARGET_TYPE, MonsterAbilityType::BA_CHAO, AttributeType::CHAOS, SOUND_MAX)
{
}

BA_ACID_Projector::BA_ACID_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    : BallProjector(player_ptr, m_idx, t_idx,
          mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがアシッド・ボールの呪文を唱えた。", "%^s casts an acid ball."),
              _("%^sが%sに向かってアシッド・ボールの呪文を唱えた。", "%^s casts an acid ball at %s.")),
          monster_is_powerful(player_ptr->current_floor_ptr, m_idx) ? 4 : 2, TARGET_TYPE, MonsterAbilityType::BA_ACID, AttributeType::ACID, SOUND_ACID)
{
}

BA_ELEC_Projector::BA_ELEC_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    : BallProjector(player_ptr, m_idx, t_idx,
          mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがサンダー・ボールの呪文を唱えた。", "%^s casts a lightning ball."),
              _("%^sが%sに向かってサンダー・ボールの呪文を唱えた。", "%^s casts a lightning ball at %s.")),
          monster_is_powerful(player_ptr->current_floor_ptr, m_idx) ? 4 : 2, TARGET_TYPE, MonsterAbilityType::BA_ELEC, AttributeType::ELEC, SOUND_ELEC)
{
}

BA_FIRE_Projector::BA_FIRE_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    : BallProjector(player_ptr, m_idx, t_idx,
          mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがファイア・ボールの呪文を唱えた。", "%^s casts a fire ball."),
              _("%^sが%sに向かってファイア・ボールの呪文を唱えた。", "%^s casts a fire ball at %s.")),
          monster_is_powerful(player_ptr->current_floor_ptr, m_idx) ? 4 : 2, TARGET_TYPE, MonsterAbilityType::BA_FIRE, AttributeType::FIRE, SOUND_FIRE)
{
}

BA_COLD_Projector::BA_COLD_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    : BallProjector(player_ptr, m_idx, t_idx,
          mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがアイス・ボールの呪文を唱えた。", "%^s casts a frost ball."),
              _("%^sが%sに向かってアイス・ボールの呪文を唱えた。", "%^s casts a frost ball at %s.")),
          monster_is_powerful(player_ptr->current_floor_ptr, m_idx) ? 4 : 2, TARGET_TYPE, MonsterAbilityType::BA_COLD, AttributeType::COLD, SOUND_COLD)
{
}

BA_POIS_Projector::BA_POIS_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    : BallProjector(player_ptr, m_idx, t_idx,
          mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."), _("%^sが悪臭雲の呪文を唱えた。", "%^s casts a stinking cloud."),
              _("%^sが%sに向かって悪臭雲の呪文を唱えた。", "%^s casts a stinking cloud at %s.")),
          2, TARGET_TYPE, MonsterAbilityType::BA_POIS, AttributeType::POIS, SOUND_MAX)
{
}

BA_NETH_Projector::BA_NETH_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    : BallProjector(player_ptr, m_idx, t_idx,
          mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."), _("%^sが地獄球の呪文を唱えた。", "%^s casts a nether ball."),
              _("%^sが%sに向かって地獄球の呪文を唱えた。", "%^s casts a nether ball at %s.")),
          2, TARGET_TYPE, MonsterAbilityType::BA_NETH, AttributeType::NETHER, SOUND_MAX)
{
}

BA_WATE_Projector::BA_WATE_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    : BallProjector(player_ptr, m_idx, t_idx,
          mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."), _("%^sが流れるような身振りをした。", "%^s gestures fluidly."),
              _("%^sが%sに対して流れるような身振りをした。", "%^s gestures fluidly at %s.")),
          4, TARGET_TYPE, MonsterAbilityType::BA_WATE, AttributeType::WATER, SOUND_MAX)
{
}

BA_MANA_Projector::BA_MANA_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    : BallProjector(player_ptr, m_idx, t_idx,
          mspell_cast_msg_blind(_("%^sが何かを力強くつぶやいた。", "%^s mumbles powerfully."),
              _("%^sが魔力の嵐の呪文を念じた。", "%^s invokes a mana storm."), _("%^sが%sに対して魔力の嵐の呪文を念じた。", "%^s invokes a mana storm upon %s.")),
          4, TARGET_TYPE, MonsterAbilityType::BA_MANA, AttributeType::MANA, SOUND_MAX)
{
}

BA_DARK_Projector::BA_DARK_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    : BallProjector(player_ptr, m_idx, t_idx,
          mspell_cast_msg_blind(_("%^sが何かを力強くつぶやいた。", "%^s mumbles powerfully."),
              _("%^sが暗黒の嵐の呪文を念じた。", "%^s invokes a darkness storm."),
              _("%^sが%sに対して暗黒の嵐の呪文を念じた。", "%^s invokes a darkness storm upon %s.")),
          4, TARGET_TYPE, MonsterAbilityType::BA_DARK, AttributeType::DARK, SOUND_MAX)
{
}

BA_LITE_Projector::BA_LITE_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    : BallProjector(player_ptr, m_idx, t_idx,
          mspell_cast_msg_blind(_("%^sが何かを力強くつぶやいた。", "%^s mumbles powerfully."),
              _("%^sがスターバーストの呪文を念じた。", "%^s invokes a starburst."),
              _("%^sが%sに対してスターバーストの呪文を念じた。", "%^s invokes a starburst upon %s.")),
          4, TARGET_TYPE, MonsterAbilityType::BA_LITE, AttributeType::LITE, SOUND_MAX)
{
}

bool BA_FIRE_Projector::view_message()
{
    monster_type *m_ptr = &player_ptr->current_floor_ptr->m_list[m_idx];
    mspell_cast_msg_blind msg;

    //else以外では特殊メッセージを表示する
    if (m_ptr->r_idx == MON_ROLENTO || m_ptr->r_idx == MON_NANAHA) {
        msg.blind = _("%sが何かを投げた。", "%^s throws something.");
        msg.to_player = _("%sは手榴弾を投げた。", "%^s throws a hand grenade.");
        msg.to_mons = _("%^sが%^sに向かって手榴弾を投げた。", "%^s throws a hand grenade.");
    } else {
        msg.blind = this->msgs.blind;
        msg.to_player = this->msgs.to_player;
        msg.to_mons = this->msgs.to_mons;
    }

    return BallProjector::view_message(msg);
}

bool BallProjector::view_message(mspell_cast_msg_blind msg)
{
    return monspell_message(player_ptr, m_idx, t_idx, msg, TARGET_TYPE);
}

bool BallProjector::view_message()
{
    return this->view_message(msgs);
}

bool BA_WATE_Projector::view_message()
{
    bool known = monster_near_player(player_ptr->current_floor_ptr, m_idx, t_idx);
    bool see_either = see_monster(player_ptr, m_idx) || see_monster(player_ptr, t_idx);
    bool mon_to_mon = (TARGET_TYPE == MONSTER_TO_MONSTER);
    bool mon_to_player = (TARGET_TYPE == MONSTER_TO_PLAYER);
    GAME_TEXT t_name[MAX_NLEN];
    monster_name(player_ptr, t_idx, t_name);

    bool notice = BallProjector::view_message();

    if (mon_to_player) {
        msg_format(_("あなたは渦巻きに飲み込まれた。", "You are engulfed in a whirlpool."));
    } else if (mon_to_mon && known && see_either && !player_ptr->blind) {
        msg_format(_("%^sは渦巻に飲み込まれた。", "%^s is engulfed in a whirlpool."), t_name);
    }

    return notice;
}

void BallProjector::smart_learn() {}

void BA_NUKE_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_POIS);
}

void BA_CHAO_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_CHAOS);
}

void BA_ACID_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_ACID);
}

void BA_ELEC_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_ELEC);
}
void BA_FIRE_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_FIRE);
}

void BA_COLD_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_COLD);
}

void BA_POIS_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_POIS);
}

void BA_NETH_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_NETH);
}

void BA_DARK_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_DARK);
}

void BA_LITE_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_LITE);
}
