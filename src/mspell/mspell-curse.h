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

class CAUSE_1_Projector : public CAUSE_Projector{
    public:
        CAUSE_1_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
        CAUSE_1_Projector() = delete;
        virtual ~CAUSE_1_Projector() = default;
};

class CAUSE_2_Projector : public CAUSE_Projector{
    public:
        CAUSE_2_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
        CAUSE_2_Projector() = delete;
        virtual ~CAUSE_2_Projector() = default;
};

class CAUSE_3_Projector : public CAUSE_Projector{
    public:
        CAUSE_3_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
        CAUSE_3_Projector() = delete;
        virtual ~CAUSE_3_Projector() = default;
};

class CAUSE_4_Projector : public CAUSE_Projector{
    public:
        CAUSE_4_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
        CAUSE_4_Projector() = delete;
        virtual ~CAUSE_4_Projector() = default;
};

struct player_type;
