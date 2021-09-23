#pragma once

#include <functional>
#include <vector>
#include "spell/summon-types.h"
#include "system/h-type.h"
#include "system/monster-race-definition.h"
#include "spell/spell-types.h"

struct player_type;

struct summon_data{
    summon_data(summon_type type, BIT_FLAGS mode, std::function<bool(player_type *, MONSTER_IDX, POSITION, POSITION, DEPTH, summon_type, BIT_FLAGS)> summon);
    summon_data(summon_type type, BIT_FLAGS mode, std::function<bool(player_type *, DEPTH, POSITION, POSITION, BIT_FLAGS)> summon);
    summon_data operator =(summon_data) = delete;
    const summon_type type;
    const BIT_FLAGS mode;
    const std::function<bool(player_type *, MONSTER_IDX, POSITION, POSITION, DEPTH, summon_type, BIT_FLAGS)> summon;
};
class mane_attack_spell{
    protected:
        mane_attack_spell(player_type *player_ptr, concptr msg, EFFECT_ID typ, POSITION rad,
            std::function<bool(player_type *, EFFECT_ID, DIRECTION, HIT_POINT, POSITION)> func);
        mane_attack_spell(player_type *player_ptr, concptr msg, EFFECT_ID typ, POSITION rad, HIT_POINT dam,
            std::function<bool(player_type *, EFFECT_ID, DIRECTION, HIT_POINT, POSITION)> func);
        mane_attack_spell() = delete;
    public:
        ~mane_attack_spell() = default;
        bool fire();
    private:
        player_type *player_ptr;
        concptr msg;
        EFFECT_ID typ;
        POSITION rad;
        HIT_POINT dam;
        std::function<bool(player_type *, EFFECT_ID, DIRECTION, HIT_POINT, POSITION)> func;
};

class mane_bolt : public mane_attack_spell{
    public:
        mane_bolt(player_type *player_ptr, concptr msg, EFFECT_ID typ);
        mane_bolt() = delete;
        ~mane_bolt() = default;
};

class mane_beam : public mane_attack_spell{
    public:
        mane_beam(player_type *player_ptr, concptr msg, EFFECT_ID typ);
        mane_beam(player_type *player_ptr, concptr msg, EFFECT_ID typ, HIT_POINT dam);
        mane_beam() = delete;
        ~mane_beam() = default;
};

class mane_ball : public mane_attack_spell{
    public:
        mane_ball(player_type *player_ptr, concptr msg, EFFECT_ID typ, POSITION rad);
        mane_ball() = delete;
        ~mane_ball() = default;
};

class mane_breath : public mane_attack_spell{
    public:
        mane_breath(player_type *player_ptr, concptr msg, char* buffer, EFFECT_ID typ, POSITION rad);
        mane_breath() = delete;
        ~mane_breath() = default;
};

class mane_ball_hide : public mane_attack_spell{
    public:
        mane_ball_hide(player_type *player_ptr, concptr msg, EFFECT_ID typ, POSITION rad);
        mane_ball_hide(player_type *player_ptr, concptr msg, EFFECT_ID typ, POSITION rad, HIT_POINT dam);
        mane_ball_hide() = delete;
        ~mane_ball_hide() = default;
};

class mane_bad_st{
    public:
        mane_bad_st(player_type *player_ptr, concptr msg, int power, std::function<bool(player_type *, DIRECTION, int)> func);
        mane_bad_st() = delete;
        ~mane_bad_st() = default;
        bool fire();
    private:
        player_type *player_ptr;
        concptr msg;
        int power;
        std::function<bool(player_type *, DIRECTION, int)> func;
};

class mane_summon{
    public:
        mane_summon(player_type *player_ptr, concptr msg, POSITION target_y, POSITION target_x, DEPTH plev, int num, std::vector<summon_data> summon_list);
        mane_summon() = delete;
        ~mane_summon() = default;
        bool fire();
    private:
        player_type *player_ptr;
        concptr msg;
        POSITION target_y;
        POSITION target_x;
        DEPTH plev;
        int num;
        std::vector<summon_data> summon_list;
};
bool do_cmd_mane(player_type *player_ptr, bool baigaesi);
