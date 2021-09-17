#pragma once

#include "system/angband.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-util.h"
#include "system/h-type.h"
#include "system/player-type-definition.h"

struct MonsterSpellResult;

class CAUSE_Projector{
    protected:
        CAUSE_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, const SpellMsg_blind &msgs, RF_ABILITY ms_type, EFFECT_ID typ, int TARGET_TYPE);
        CAUSE_Projector() = delete;
        player_type *player_ptr;
        MONSTER_IDX m_idx;
        MONSTER_IDX t_idx;
        RF_ABILITY ms_type;
        EFFECT_ID typ;
        int TARGET_TYPE;
        MonsterSpellResult spell_RF5_CAUSE(HIT_POINT dam, POSITION y, POSITION x);
    public:
        virtual ~CAUSE_Projector() = default;
        MonsterSpellResult project(POSITION y, POSITION x);
    private:
        SpellMsg_blind msgs;
};

struct player_type;
MonsterSpellResult spell_RF5_CAUSE_1(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_CAUSE_2(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_CAUSE_3(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_CAUSE_4(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
