#pragma once

#include "system/angband.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-util.h"
#include "system/h-type.h"

struct MonsterSpellResult;

class BallProjector{
    protected:
        BallProjector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, const SpellMsg_blind &msgs, byte rad, int TARGET_TYPE, RF_ABILITY ms_type, EFFECT_ID typ);
        BallProjector() = delete;
        player_type *player_ptr;
        MONSTER_IDX m_idx;
        MONSTER_IDX t_idx;
        int TARGET_TYPE;
        bool virtual view_message();
        void virtual smart_learn();
    public:
        virtual ~BallProjector() = default;
        MonsterSpellResult project(POSITION y, POSITION x);
    private :
        byte rad;
        SpellMsg_blind msgs;
        RF_ABILITY ms_type;
        EFFECT_ID typ;
};

struct player_type;
MonsterSpellResult spell_RF4_BA_NUKE(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF4_BA_CHAO(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_BA_ACID(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_BA_ELEC(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_BA_FIRE(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_BA_COLD(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_BA_POIS(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_BA_NETH(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_BA_WATE(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_BA_MANA(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_BA_DARK(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_BA_LITE(player_type *player_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
