#include "mspell/mspell-curse.h"
#include "core/disturbance.h"
#include "effect/effect-processor.h"
#include "monster-race/race-ability-flags.h"
#include "monster/monster-info.h"
#include "monster/monster-list.h"
#include "mspell/mspell-attribute.h"
#include "mspell/mspell-checker.h"
#include "mspell/mspell-damage-calculator.h"
#include "mspell/mspell-util.h"
#include "mspell/mspell.h"
#include "system/floor-type-definition.h"
#include "system/player-type-definition.h"
#include "view/display-messages.h"
#include <map>

const std::map<MonsterAbilityType, cause_type> cause_data = {
    { MonsterAbilityType::CAUSE_1,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
            _("%^sがあなたを指さして呪った。", "%^s points at you and curses."),
            _("%^sは%sを指さして呪いをかけた。", "%^s points at %s and curses.")) } },
    { MonsterAbilityType::CAUSE_2,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
            _("%^sがあなたを指さして恐ろしげに呪った。", "%^s points at you and curses horribly."),
            _("%^sは%sを指さして恐ろしげに呪いをかけた。", "%^s points at %s and curses horribly.")) } },
    { MonsterAbilityType::CAUSE_3,
        { mspell_cast_msg_blind(_("%^sが何かを大声で叫んだ。", "%^s mumbles loudly."),
            _("%^sがあなたを指さして恐ろしげに呪文を唱えた！", "%^s points at you, incanting terribly!"),
            _("%^sは%sを指さし、恐ろしげに呪文を唱えた！", "%^s points at %s, incanting terribly!")) } },
    { MonsterAbilityType::CAUSE_4,
        { mspell_cast_msg_blind(_("%^sが「お前は既に死んでいる」と叫んだ。", "%^s screams the word 'DIE!'"),
            _("%^sがあなたの秘孔を突いて「お前は既に死んでいる」と叫んだ。", "%^s points at you, screaming the word DIE!"),
            _("%^sが%sの秘孔を突いて、「お前は既に死んでいる」と叫んだ。", "%^s points at %s, screaming the word, 'DIE!'")) } },
};

CAUSE_Projector::CAUSE_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE, MonsterAbilityType ms_type)
    : player_ptr(player_ptr)
    , m_idx(m_idx)
    , t_idx(t_idx)
    , ms_type(ms_type)
    , TARGET_TYPE(TARGET_TYPE)
{
}

/*!
 * @brief RF5_CAUSE_* の処理関数
 * @param dam 攻撃に使用するダメージ量
 * @param y 対象の地点のy座標
 * @param x 対象の地点のx座標
 */
MonsterSpellResult CAUSE_Projector::spell_RF5_CAUSE(HIT_POINT dam, POSITION y, POSITION x)
{
    auto res = MonsterSpellResult::make_valid(dam);
    res.learnable = TARGET_TYPE == MONSTER_TO_PLAYER;

    GAME_TEXT m_name[MAX_NLEN], t_name[MAX_NLEN];
    monster_name(player_ptr, m_idx, m_name);
    monster_name(player_ptr, t_idx, t_name);

    monspell_message(player_ptr, m_idx, t_idx, cause_data.at(ms_type).msg, TARGET_TYPE);

    breath(player_ptr, y, x, m_idx, get_ability_attribute(ms_type), dam, 0, false, TARGET_TYPE);

    return res;
}

MonsterSpellResult CAUSE_Projector::project(POSITION y, POSITION x)
{
    const auto dam = monspell_damage(player_ptr, ms_type, m_idx, damage_flag_type::DAM_ROLL);

    return this->spell_RF5_CAUSE(dam, y, x);
}
