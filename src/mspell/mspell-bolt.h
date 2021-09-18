#pragma once

#include "system/angband.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-util.h"
#include "system/h-type.h"

struct MonsterSpellResult;

struct player_type;

class BoltProjector{
    protected:
        BoltProjector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, const SpellMsg_blind &msgs, int TARGET_TYPE, RF_ABILITY ms_type, EFFECT_ID typ, int SOUND);
        BoltProjector() = delete;
        player_type *player_ptr;
        MONSTER_IDX m_idx;
        MONSTER_IDX t_idx;
        int TARGET_TYPE;
        bool virtual view_message();
        void virtual smart_learn();
    public:
        virtual ~BoltProjector() = default;
        MonsterSpellResult project(POSITION y, POSITION x);
    private :
        SpellMsg_blind msgs;
        RF_ABILITY ms_type;
        EFFECT_ID typ;
        int SOUND;
        void play_sound();
};

class SHOOT_Projector : public BoltProjector{
    public:
        SHOOT_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
        SHOOT_Projector() = delete;
        virtual ~SHOOT_Projector() = default;
    private:
        void smart_learn();
        bool view_message();
};

class BO_ACID_Projector : public BoltProjector{
    public:
        BO_ACID_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
        BO_ACID_Projector() = delete;
        virtual ~BO_ACID_Projector() = default;
    private:
        void smart_learn();
};

class BO_ELEC_Projector : public BoltProjector{
    public:
        BO_ELEC_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
        BO_ELEC_Projector() = delete;
        virtual ~BO_ELEC_Projector() = default;
    private:
        void smart_learn();
};

class BO_FIRE_Projector : public BoltProjector{
    public:
        BO_FIRE_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
        BO_FIRE_Projector() = delete;
        virtual ~BO_FIRE_Projector() = default;
    private:
        void smart_learn();
};

class BO_COLD_Projector : public BoltProjector{
    public:
        BO_COLD_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
        BO_COLD_Projector() = delete;
        virtual ~BO_COLD_Projector() = default;
    private:
        void smart_learn();
};

class BO_NETH_Projector : public BoltProjector{
    public:
        BO_NETH_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
        BO_NETH_Projector() = delete;
        virtual ~BO_NETH_Projector() = default;
    private:
        void smart_learn();
};

class BO_WATE_Projector : public BoltProjector{
    public:
        BO_WATE_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
        BO_WATE_Projector() = delete;
        virtual ~BO_WATE_Projector() = default;
    private:
        void smart_learn();
};

class BO_MANA_Projector : public BoltProjector{
    public:
        BO_MANA_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
        BO_MANA_Projector() = delete;
        virtual ~BO_MANA_Projector() = default;
    private:
        void smart_learn();
};

class BO_PLAS_Projector : public BoltProjector{
    public:
        BO_PLAS_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
        BO_PLAS_Projector() = delete;
        virtual ~BO_PLAS_Projector() = default;
    private:
        void smart_learn();
};

class BO_ICEE_Projector : public BoltProjector{
    public:
        BO_ICEE_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
        BO_ICEE_Projector() = delete;
        virtual ~BO_ICEE_Projector() = default;
    private:
        void smart_learn();
};

class MISSILE_Projector : public BoltProjector{
    public:
        MISSILE_Projector(player_type *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
        MISSILE_Projector() = delete;
        virtual ~MISSILE_Projector() = default;
    private:
        void smart_learn();
};
