#pragma once

#include "spell/summon-types.h"
#include "system/h-type.h"
#include "system/monster-race-definition.h"
#include <functional>
#include <vector>

class PlayerType;

struct summon_data {
    summon_data(summon_type type, BIT_FLAGS mode, std::function<bool(PlayerType *, MONSTER_IDX, POSITION, POSITION, DEPTH, summon_type, BIT_FLAGS)> summon);
    summon_data(summon_type type, BIT_FLAGS mode, std::function<bool(PlayerType *, DEPTH, POSITION, POSITION, BIT_FLAGS)> summon);
    summon_data operator=(summon_data) = delete;
    const summon_type type;
    const BIT_FLAGS mode;
    const std::function<bool(PlayerType *, MONSTER_IDX, POSITION, POSITION, DEPTH, summon_type, BIT_FLAGS)> summon;
};
class mane_attack_spell {
protected:
    mane_attack_spell(PlayerType *player_ptr, concptr msg, AttributeType typ, POSITION rad,
        std::function<bool(PlayerType *, AttributeType, DIRECTION, HIT_POINT, POSITION)> func);
    mane_attack_spell(PlayerType *player_ptr, concptr msg, AttributeType typ, POSITION rad, HIT_POINT dam,
        std::function<bool(PlayerType *, AttributeType, DIRECTION, HIT_POINT, POSITION)> func);
    mane_attack_spell() = delete;

public:
    ~mane_attack_spell() = default;
    bool fire();

private:
    PlayerType *player_ptr;
    concptr msg;
    AttributeType typ;
    POSITION rad;
    HIT_POINT dam;
    std::function<bool(PlayerType *, AttributeType, DIRECTION, HIT_POINT, POSITION)> func;
};

class mane_bolt : public mane_attack_spell {
public:
    mane_bolt(PlayerType *player_ptr, concptr msg, AttributeType typ);
    mane_bolt() = delete;
    ~mane_bolt() = default;
};

class mane_beam : public mane_attack_spell {
public:
    mane_beam(PlayerType *player_ptr, concptr msg, AttributeType typ);
    mane_beam(PlayerType *player_ptr, concptr msg, AttributeType typ, HIT_POINT dam);
    mane_beam() = delete;
    ~mane_beam() = default;
};

class mane_ball : public mane_attack_spell {
public:
    mane_ball(PlayerType *player_ptr, concptr msg, AttributeType typ, POSITION rad);
    mane_ball() = delete;
    ~mane_ball() = default;
};

class mane_breath : public mane_attack_spell {
public:
    mane_breath(PlayerType *player_ptr, concptr msg, char *buffer, AttributeType typ, POSITION rad);
    mane_breath() = delete;
    ~mane_breath() = default;
};

class mane_ball_hide : public mane_attack_spell {
public:
    mane_ball_hide(PlayerType *player_ptr, concptr msg, AttributeType typ, POSITION rad);
    mane_ball_hide(PlayerType *player_ptr, concptr msg, AttributeType typ, POSITION rad, HIT_POINT dam);
    mane_ball_hide() = delete;
    ~mane_ball_hide() = default;
};

class mane_bad_st {
public:
    mane_bad_st(PlayerType *player_ptr, concptr msg, int power, std::function<bool(PlayerType *, DIRECTION, int)> func);
    mane_bad_st() = delete;
    ~mane_bad_st() = default;
    bool fire();

private:
    PlayerType *player_ptr;
    concptr msg;
    int power;
    std::function<bool(PlayerType *, DIRECTION, int)> func;
};

class mane_summon {
public:
    mane_summon(PlayerType *player_ptr, concptr msg, POSITION target_y, POSITION target_x, DEPTH plev, int num, std::vector<summon_data> summon_list);
    mane_summon() = delete;
    ~mane_summon() = default;
    bool fire();

private:
    PlayerType *player_ptr;
    concptr msg;
    POSITION target_y;
    POSITION target_x;
    DEPTH plev;
    int num;
    std::vector<summon_data> summon_list;
};

bool do_cmd_mane(PlayerType *player_ptr, bool baigaesi);
