#include "mspell/mspell-bolt.h"
#include "effect/effect-processor.h"
#include "main/sound-definitions-table.h"
#include "main/sound-of-music.h"
#include "mind/drs-types.h"
#include "monster-race/monster-race.h"
#include "monster-race/race-flags3.h"
#include "monster-race/race-ability-flags.h"
#include "monster/monster-info.h"
#include "monster/monster-update.h"
#include "mspell/mspell-checker.h"
#include "mspell/mspell-damage-calculator.h"
#include "mspell/mspell-util.h"
#include "mspell/mspell.h"
#include "spell/spell-types.h"
#include "system/floor-type-definition.h"
#include "system/monster-race-definition.h"
#include "system/monster-type-definition.h"
#include "system/player-type-definition.h"
#include "util/bit-flags-calculator.h"

BoltProjector::BoltProjector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, const SpellMsg_blind &msgs, int TARGET_TYPE, RF_ABILITY ms_type, EFFECT_ID typ, int SOUND)
    :   player_ptr(player_ptr)
    ,   m_idx(m_idx)
    ,   t_idx(t_idx)
    ,   TARGET_TYPE(TARGET_TYPE)
    ,   msgs(msgs)
    ,   ms_type(ms_type)
    ,   typ(typ)
    ,   SOUND(SOUND)
{}

SHOOT_Projector::SHOOT_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    :   BoltProjector(player_ptr,m_idx,t_idx,
            SpellMsg_blind(_("%^sが奇妙な音を発した。", "%^s makes a strange noise."), _("%^sが矢を放った。", "%^s fires an arrow."),
            _("%^sが%sに矢を放った。", "%^s fires an arrow at %s.")), TARGET_TYPE, RF_ABILITY::SHOOT, GF_ARROW, SOUND_SHOOT)
{}

BO_ACID_Projector::BO_ACID_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    :   BoltProjector(player_ptr,m_idx,t_idx,
            SpellMsg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
            _("%^sがアシッド・ボルトの呪文を唱えた。", "%^s casts an acid bolt."),
            _("%sが%sに向かってアシッド・ボルトの呪文を唱えた。", "%^s casts an acid bolt at %s.")), TARGET_TYPE, RF_ABILITY::BO_ACID, GF_ACID, SOUND_ACID)
{}

BO_ELEC_Projector::BO_ELEC_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    :   BoltProjector(player_ptr,m_idx,t_idx,
            SpellMsg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
            _("%^sがサンダー・ボルトの呪文を唱えた。", "%^s casts a lightning bolt."),
            _("%^sが%sに向かってサンダー・ボルトの呪文を唱えた。", "%^s casts a lightning bolt at %s.")), TARGET_TYPE, RF_ABILITY::BO_ELEC, GF_ELEC, SOUND_ELEC)
{}

BO_FIRE_Projector::BO_FIRE_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    :   BoltProjector(player_ptr,m_idx,t_idx,
            SpellMsg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
            _("%^sがファイア・ボルトの呪文を唱えた。", "%^s casts a fire bolt."),
            _("%^sが%sに向かってファイア・ボルトの呪文を唱えた。", "%^s casts a fire bolt at %s.")), TARGET_TYPE, RF_ABILITY::BO_FIRE, GF_FIRE, SOUND_FIRE)
{}

BO_COLD_Projector::BO_COLD_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    :   BoltProjector(player_ptr,m_idx,t_idx,
            SpellMsg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
            _("%^sがアイス・ボルトの呪文を唱えた。", "%^s casts a frost bolt."),
            _("%^sが%sに向かってアイス・ボルトの呪文を唱えた。", "%^s casts a frost bolt at %s.")), TARGET_TYPE, RF_ABILITY::BO_COLD, GF_COLD, SOUND_COLD)
{}

BO_NETH_Projector::BO_NETH_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    :   BoltProjector(player_ptr,m_idx,t_idx,
            SpellMsg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."), _("%^sが地獄の矢の呪文を唱えた。", "%^s casts a nether bolt."),
             _("%^sが%sに向かって地獄の矢の呪文を唱えた。", "%^s casts a nether bolt at %s.")), TARGET_TYPE, RF_ABILITY::BO_NETH, GF_NETHER, SOUND_MAX)
{}

BO_WATE_Projector::BO_WATE_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    :   BoltProjector(player_ptr,m_idx,t_idx,
            SpellMsg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
            _("%^sがウォーター・ボルトの呪文を唱えた。", "%^s casts a water bolt."),
            _("%^sが%sに向かってウォーター・ボルトの呪文を唱えた。", "%^s casts a water bolt at %s.")), TARGET_TYPE, RF_ABILITY::BO_WATE, GF_WATER, SOUND_MAX)
{}

BO_MANA_Projector::BO_MANA_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    :   BoltProjector(player_ptr,m_idx,t_idx,
            SpellMsg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."), _("%^sが魔力の矢の呪文を唱えた。", "%^s casts a mana bolt."),
            _("%^sが%sに向かって魔力の矢の呪文を唱えた。", "%^s casts a mana bolt at %s.")), TARGET_TYPE, RF_ABILITY::BO_MANA, GF_MANA,  SOUND_MAX)
{}

BO_PLAS_Projector::BO_PLAS_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    :   BoltProjector(player_ptr,m_idx,t_idx,
            SpellMsg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
            _("%^sがプラズマ・ボルトの呪文を唱えた。", "%^s casts a plasma bolt."),
            _("%^sが%sに向かってプラズマ・ボルトの呪文を唱えた。", "%^s casts a plasma bolt at %s.")), TARGET_TYPE, RF_ABILITY::BO_PLAS, GF_PLASMA, SOUND_MAX)
{}

BO_ICEE_Projector::BO_ICEE_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    :   BoltProjector(player_ptr,m_idx,t_idx,
            SpellMsg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."), _("%^sが極寒の矢の呪文を唱えた。", "%^s casts an ice bolt."),
            _("%^sが%sに向かって極寒の矢の呪文を唱えた。", "%^s casts an ice bolt at %s.")), TARGET_TYPE, RF_ABILITY::BO_ICEE, GF_ICE, SOUND_MAX)
{}

MISSILE_Projector::MISSILE_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE)
    :   BoltProjector(player_ptr,m_idx,t_idx,
            SpellMsg_blind(_("%^sが何かをつぶやいた。", "%^s mumbles."),
            _("%^sがマジック・ミサイルの呪文を唱えた。", "%^s casts a magic missile."),
            _("%^sが%sに向かってマジック・ミサイルの呪文を唱えた。", "%^s casts a magic missile at %s.")), TARGET_TYPE, RF_ABILITY::MISSILE, GF_MISSILE, SOUND_MAX)
{}

MonsterSpellResult BoltProjector::project(POSITION y, POSITION x){
    if (view_message())
        play_sound();
    
    const auto dam = monspell_damage(player_ptr, ms_type, m_idx, DAM_ROLL);
    const auto proj_res = bolt(player_ptr, m_idx, y, x, typ, dam, TARGET_TYPE);
    if (TARGET_TYPE == MONSTER_TO_PLAYER) 
        smart_learn();

    auto res = MonsterSpellResult::make_valid(dam);
    res.learnable = proj_res.affected_player;

    return res;
}

void BoltProjector::play_sound(){
    sound(SOUND);
}

bool BoltProjector::view_message(){
    return monspell_message(player_ptr, m_idx, t_idx, msgs, TARGET_TYPE);
}

void BoltProjector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_REFLECT);
}

bool SHOOT_Projector::view_message(){
    monster_type *m_ptr = &player_ptr->current_floor_ptr->m_list[m_idx];
    monster_race *r_ptr = &r_info[m_ptr->r_idx];
    if (any_bits(r_ptr->flags3, RF3_KAN_SEN)) {
        return monspell_message(player_ptr, m_idx, t_idx, 
            SpellMsg_blind(_("%^sが奇妙な音を発した。", "%^s makes a strange noise."), _("%^sが艦砲射撃をした。", "%^s bombards."),
            _("%^sが%sに艦砲射撃をした。", "%^s bombards %s.")), TARGET_TYPE);
    } else {
        return BoltProjector::view_message();
    }
}

void SHOOT_Projector::smart_learn()
{}

void BO_ACID_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_ACID);
    BoltProjector::smart_learn();
}

void BO_ELEC_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_ELEC);
    BoltProjector::smart_learn();
}

void BO_FIRE_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_FIRE);
    BoltProjector::smart_learn();
}

void BO_COLD_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_COLD);
    BoltProjector::smart_learn();
}

void BO_NETH_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_NETH);
    BoltProjector::smart_learn();
}

void BO_WATE_Projector::smart_learn()
{
    BoltProjector::smart_learn();
}

void BO_MANA_Projector::smart_learn()
{
    BoltProjector::smart_learn();
}

void BO_PLAS_Projector::smart_learn()
{
    BoltProjector::smart_learn();
}

void BO_ICEE_Projector::smart_learn()
{
    update_smart_learn(player_ptr, m_idx, DRS_COLD);
    BoltProjector::smart_learn();
}

void MISSILE_Projector::smart_learn()
{
    BoltProjector::smart_learn();
}