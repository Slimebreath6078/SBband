#pragma once

#include "effect/attribute-types.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-util.h"
#include "system/angband.h"
#include "system/h-type.h"

struct MonsterSpellResult;
class BallProjector {
protected:
    BallProjector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, const mspell_cast_msg_blind &msgs, int TARGET_TYPE, byte rad, MonsterAbilityType ms_type, AttributeType typ, int SOUND);
    BallProjector() = delete;
    PlayerType *player_ptr;
    MONSTER_IDX m_idx;
    MONSTER_IDX t_idx;
    mspell_cast_msg_blind const msgs;
    int TARGET_TYPE;
    bool view_message(mspell_cast_msg_blind msg);
    bool virtual view_message();
    void virtual smart_learn();

public:
    virtual ~BallProjector() = default;
    MonsterSpellResult project(POSITION y, POSITION x);

private:
    byte rad;
    MonsterAbilityType ms_type;
    AttributeType typ;
    int SOUND;
    void play_sound();
};

class BA_NUKE_Projector : public BallProjector {
public:
    BA_NUKE_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
    BA_NUKE_Projector() = delete;
    virtual ~BA_NUKE_Projector() = default;

private:
    void smart_learn();
};

class BA_CHAO_Projector : public BallProjector {
public:
    BA_CHAO_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
    BA_CHAO_Projector() = delete;
    virtual ~BA_CHAO_Projector() = default;

private:
    void smart_learn();
};

class BA_ACID_Projector : public BallProjector {
public:
    BA_ACID_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
    BA_ACID_Projector() = delete;
    virtual ~BA_ACID_Projector() = default;

private:
    void smart_learn();
};

class BA_ELEC_Projector : public BallProjector {
public:
    BA_ELEC_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
    BA_ELEC_Projector() = delete;
    virtual ~BA_ELEC_Projector() = default;

private:
    void smart_learn();
};

class BA_FIRE_Projector : public BallProjector {
public:
    BA_FIRE_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
    BA_FIRE_Projector() = delete;
    virtual ~BA_FIRE_Projector() = default;

private:
    bool view_message();
    void smart_learn();
};

class BA_COLD_Projector : public BallProjector {
public:
    BA_COLD_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
    BA_COLD_Projector() = delete;
    virtual ~BA_COLD_Projector() = default;

private:
    void smart_learn();
};

class BA_POIS_Projector : public BallProjector {
public:
    BA_POIS_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
    BA_POIS_Projector() = delete;
    virtual ~BA_POIS_Projector() = default;

private:
    void smart_learn();
};

class BA_NETH_Projector : public BallProjector {
public:
    BA_NETH_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
    BA_NETH_Projector() = delete;
    virtual ~BA_NETH_Projector() = default;

private:
    void smart_learn();
};

class BA_WATE_Projector : public BallProjector {
public:
    BA_WATE_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
    BA_WATE_Projector() = delete;
    virtual ~BA_WATE_Projector() = default;

private:
    bool view_message();
};

class BA_MANA_Projector : public BallProjector {
public:
    BA_MANA_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
    BA_MANA_Projector() = delete;
    virtual ~BA_MANA_Projector() = default;
};

class BA_DARK_Projector : public BallProjector {
public:
    BA_DARK_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
    BA_DARK_Projector() = delete;
    virtual ~BA_DARK_Projector() = default;

private:
    void smart_learn();
};

class BA_LITE_Projector : public BallProjector {
public:
    BA_LITE_Projector(PlayerType *player_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
    BA_LITE_Projector() = delete;
    virtual ~BA_LITE_Projector() = default;

private:
    void smart_learn();
};

class PlayerType;
