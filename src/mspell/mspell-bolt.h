#pragma once

#include "main/sound-definitions-table.h"
#include "mind/drs-types.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-util.h"
#include "system/angband.h"
#include "system/h-type.h"

struct MonsterSpellResult;

struct bolt_type {
    mspell_cast_msg_blind msg;
    sound_type sound;
    std::vector<drs_type> drs;
};

class PlayerType;

class BoltProjector {
public:
    BoltProjector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE, MonsterAbilityType ms_type);
    BoltProjector() = delete;
    virtual ~BoltProjector() = default;
    MonsterSpellResult project(POSITION y, POSITION x);

private:
    PlayerType *player_ptr;
    MONSTER_IDX m_idx;
    MONSTER_IDX t_idx;
    int TARGET_TYPE;
    MonsterAbilityType ms_type;
    bool view_message(mspell_cast_msg_blind msg);
    bool view_message();
    void play_sound();
    void smart_learn();
};
