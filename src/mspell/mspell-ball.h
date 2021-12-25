#pragma once

#include "main/sound-definitions-table.h"
#include "mind/drs-types.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-util.h"
#include "system/angband.h"
#include "system/h-type.h"

struct ball_type {
    mspell_cast_msg_blind msg;
    sound_type sound;
    std::vector<drs_type> drs;
};

struct MonsterSpellResult;
class BallProjector {
protected:
public:
    BallProjector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE, byte rad, MonsterAbilityType ms_type);
    BallProjector() = delete;
    virtual ~BallProjector() = default;
    MonsterSpellResult project(POSITION y, POSITION x);

private:
    PlayerType *player_ptr;
    MONSTER_IDX m_idx;
    MONSTER_IDX t_idx;
    int TARGET_TYPE;
    byte rad;
    MonsterAbilityType ms_type;
    bool view_message(mspell_cast_msg_blind msg);
    bool view_message();
    void smart_learn();
    void play_sound();
};

class PlayerType;
