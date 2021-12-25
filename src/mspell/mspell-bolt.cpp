#include "mspell/mspell-bolt.h"
#include "effect/attribute-types.h"
#include "effect/effect-processor.h"
#include "main/sound-definitions-table.h"
#include "main/sound-of-music.h"
#include "mind/drs-types.h"
#include "monster-race/monster-race.h"
#include "monster-race/race-ability-flags.h"
#include "monster-race/race-flags3.h"
#include "monster-race/race-kind-flags.h"
#include "monster/monster-info.h"
#include "monster/monster-update.h"
#include "mspell/mspell-attribute.h"
#include "mspell/mspell-checker.h"
#include "mspell/mspell-damage-calculator.h"
#include "mspell/mspell-util.h"
#include "mspell/mspell.h"
#include "system/floor-type-definition.h"
#include "system/monster-race-definition.h"
#include "system/monster-type-definition.h"
#include "system/player-type-definition.h"
#include "util/bit-flags-calculator.h"
#include <map>

const std::map<MonsterAbilityType, bolt_type> bolt_data = {
    { MonsterAbilityType::SHOOT,
        { mspell_cast_msg_blind(_("%^sが奇妙な音を発した。", "%^s makes a strange noise."), _("%^sが矢を放った。", "%^s fires an arrow."),
              _("%^sが%sに矢を放った。", "%^s fires an arrow at %s.")),
            SOUND_SHOOT, { DRS_NONE } } },
    { MonsterAbilityType::BO_ACID,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがアシッド・ボルトの呪文を唱えた。", "%^s casts an acid bolt."),
              _("%sが%sに向かってアシッド・ボルトの呪文を唱えた。", "%^s casts an acid bolt at %s.")),
            SOUND_ACID, { DRS_ACID, DRS_REFLECT } } },
    { MonsterAbilityType::BO_ELEC,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがサンダー・ボルトの呪文を唱えた。", "%^s casts a lightning bolt."),
              _("%^sが%sに向かってサンダー・ボルトの呪文を唱えた。", "%^s casts a lightning bolt at %s.")),
            SOUND_ELEC, { DRS_ELEC, DRS_REFLECT } } },
    { MonsterAbilityType::BO_FIRE,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがファイア・ボルトの呪文を唱えた。", "%^s casts a fire bolt."),
              _("%^sが%sに向かってファイア・ボルトの呪文を唱えた。", "%^s casts a fire bolt at %s.")),
            SOUND_FIRE, { DRS_FIRE, DRS_REFLECT } } },
    { MonsterAbilityType::BO_COLD,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがアイス・ボルトの呪文を唱えた。", "%^s casts a frost bolt."),
              _("%^sが%sに向かってアイス・ボルトの呪文を唱えた。", "%^s casts a frost bolt at %s.")),
            SOUND_COLD, { DRS_COLD, DRS_REFLECT } } },
    { MonsterAbilityType::BO_NETH,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."), _("%^sが地獄の矢の呪文を唱えた。", "%^s casts a nether bolt."),
              _("%^sが%sに向かって地獄の矢の呪文を唱えた。", "%^s casts a nether bolt at %s.")),
            SOUND_MAX, { DRS_NETH, DRS_REFLECT } } },
    { MonsterAbilityType::BO_WATE,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがウォーター・ボルトの呪文を唱えた。", "%^s casts a water bolt."),
              _("%^sが%sに向かってウォーター・ボルトの呪文を唱えた。", "%^s casts a water bolt at %s.")),
            SOUND_MAX, { DRS_REFLECT } } },
    { MonsterAbilityType::BO_MANA,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."), _("%^sが魔力の矢の呪文を唱えた。", "%^s casts a mana bolt."),
              _("%^sが%sに向かって魔力の矢の呪文を唱えた。", "%^s casts a mana bolt at %s.")),
            SOUND_MAX, { DRS_REFLECT } } },
    { MonsterAbilityType::BO_PLAS,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがプラズマ・ボルトの呪文を唱えた。", "%^s casts a plasma bolt."),
              _("%^sが%sに向かってプラズマ・ボルトの呪文を唱えた。", "%^s casts a plasma bolt at %s.")),
            SOUND_MAX, { DRS_REFLECT } } },
    { MonsterAbilityType::BO_ICEE,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."), _("%^sが極寒の矢の呪文を唱えた。", "%^s casts an ice bolt."),
              _("%^sが%sに向かって極寒の矢の呪文を唱えた。", "%^s casts an ice bolt at %s.")),
            SOUND_COLD, { DRS_REFLECT } } },
    { MonsterAbilityType::MISSILE,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがマジック・ミサイルの呪文を唱えた。", "%^s casts a magic missile."),
              _("%^sが%sに向かってマジック・ミサイルの呪文を唱えた。", "%^s casts a magic missile at %s.")),
            SOUND_MAX, { DRS_REFLECT } } },
    { MonsterAbilityType::BO_LITE,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sがスターライトアローを放った。", "%^s fires a starlight arrow."),
              _("%^sが%sに向かってスターライトアローを放った。", "%^s fires a starlight arrow at %s.")),
            SOUND_MAX, { DRS_LITE, DRS_REFLECT } } },
    { MonsterAbilityType::BO_DARK,
        { mspell_cast_msg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
              _("%^sが暗黒の矢の呪文を唱えた。。", "%^s casts a dark bolt."),
              _("%^sが%sに向かって暗黒の矢の呪文を唱えた。", "%^s casts a dark bolt at %s.")),
            SOUND_MAX, { DRS_DARK, DRS_REFLECT } } },
};

BoltProjector::BoltProjector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE, MonsterAbilityType ms_type)
    : player_ptr(player_ptr)
    , m_idx(m_idx)
    , t_idx(t_idx)
    , TARGET_TYPE(TARGET_TYPE)
    , ms_type(ms_type)
{
}

MonsterSpellResult BoltProjector::project(POSITION y, POSITION x)
{
    if (view_message())
        play_sound();

    const auto dam = monspell_damage(player_ptr, ms_type, m_idx, damage_flag_type::DAM_ROLL);
    const auto proj_res = bolt(player_ptr, m_idx, y, x, get_ability_attribute(ms_type), dam, TARGET_TYPE);
    if (TARGET_TYPE == MONSTER_TO_PLAYER)
        smart_learn();

    auto res = MonsterSpellResult::make_valid(dam);
    res.learnable = proj_res.affected_player;

    return res;
}

bool BoltProjector::view_message(mspell_cast_msg_blind msg)
{
    return monspell_message(player_ptr, m_idx, t_idx, msg, TARGET_TYPE);
}

bool BoltProjector::view_message()
{
    if (ms_type == MonsterAbilityType::SHOOT) {
        monster_type *m_ptr = &player_ptr->current_floor_ptr->m_list[m_idx];
        monster_race *r_ptr = &r_info[m_ptr->r_idx];

        if (r_ptr->race_kind_flags.has(MonraceKindType::KAN_SEN)) {
            mspell_cast_msg_blind msg(_("%^sが奇妙な音を発した。", "%^s makes a strange noise."), _("%^sが艦砲射撃をした。", "%^s bombards."),
                _("%^sが%sに艦砲射撃をした。", "%^s bombards %s."));

            return view_message(msg);
        }
    }

    return view_message(bolt_data.at(ms_type).msg);
}

void BoltProjector::play_sound()
{
    sound(bolt_data.at(ms_type).sound);
}

void BoltProjector::smart_learn()
{
    for (auto &drs : bolt_data.at(ms_type).drs)
        update_smart_learn(player_ptr, m_idx, drs);
}
