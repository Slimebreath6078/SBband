#pragma once

#include "main/sound-definitions-table.h"
#include "mind/drs-types.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-util.h"
#include "system/angband.h"
#include "system/h-type.h"
#include "system/player-type-definition.h"

struct cause_type {
    mspell_cast_msg_blind msg;
};

struct MonsterSpellResult;

class CAUSE_Projector {
public:
    CAUSE_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE, MonsterAbilityType ms_type);
    CAUSE_Projector() = delete;
    virtual ~CAUSE_Projector() = default;
    MonsterSpellResult project(POSITION y, POSITION x);

private:
    PlayerType *player_ptr;
    MONSTER_IDX m_idx;
    MONSTER_IDX t_idx;
    MonsterAbilityType ms_type;
    int TARGET_TYPE;
    MonsterSpellResult spell_RF5_CAUSE(HIT_POINT dam, POSITION y, POSITION x);
};

class PlayerType;
