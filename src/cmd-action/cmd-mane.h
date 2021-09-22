#pragma once

#include <functional>
#include "system/h-type.h"
#include "system/monster-race-definition.h"

struct player_type;

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
bool do_cmd_mane(player_type *player_ptr, bool baigaesi);
