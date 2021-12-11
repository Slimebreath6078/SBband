#pragma once

#include "calc/damage_calc.h"
#include "object/object-broken.h"
#include "player/player-status-resist.h"
#include "system/angband.h"
#include <functional>
#include <memory>

#define DAMAGE_FORCE 1
#define DAMAGE_GENO 2
#define DAMAGE_LOSELIFE 3
#define DAMAGE_ATTACK 4
#define DAMAGE_NOESCAPE 5
#define DAMAGE_USELIFE 6

struct monster_type;

class PlayerType;

class attribute_dam {
protected:
    attribute_dam(PlayerType *player_ptr, concptr kb_str, HIT_POINT dam, bool aura, std::function<PERCENTAGE(PlayerType *player_ptr, rate_calc_type_mode mode)> calc_damage_rate);
    attribute_dam(PlayerType *player_ptr, concptr kb_str, HIT_POINT dam, bool aura, std::function<PERCENTAGE(PlayerType *player_ptr)> calc_damage_rate);
    attribute_dam() = delete;
    PlayerType *player_ptr;
    concptr kb_str;
    HIT_POINT dam;
    bool aura;
    const std::function<PERCENTAGE(PlayerType *player_ptr, rate_calc_type_mode mode)> calc_damage_rate;
    virtual void effect(HIT_POINT &damage) = 0;

public:
    virtual ~attribute_dam() = default;
    virtual HIT_POINT process();
    void operator=(const attribute_dam &) = delete;
};

class acid_dam : public attribute_dam {
public:
    acid_dam(PlayerType *player_ptr, HIT_POINT dam, concptr kb_str, bool aura);
    acid_dam() = delete;
    virtual ~acid_dam() = default;

private:
    void effect(HIT_POINT &damage);
    virtual bool minus_ac();
    acid_dam operator=(acid_dam) = delete;
};

class elec_dam : public attribute_dam {
public:
    elec_dam(PlayerType *player_ptr, HIT_POINT dam, concptr kb_str, bool aura);
    elec_dam() = delete;
    virtual ~elec_dam() = default;

private:
    void effect(HIT_POINT &damage);
    elec_dam operator=(elec_dam) = delete;
};

class fire_dam : public attribute_dam {
public:
    fire_dam(PlayerType *player_ptr, HIT_POINT dam, concptr kb_str, bool aura);
    fire_dam() = delete;
    virtual ~fire_dam() = default;

private:
    void effect(HIT_POINT &damage);
    fire_dam operator=(fire_dam) = delete;
};

class cold_dam : public attribute_dam {
public:
    cold_dam(PlayerType *player_ptr, HIT_POINT dam, concptr kb_str, bool aura);
    cold_dam() = delete;
    virtual ~cold_dam() = default;

private:
    void effect(HIT_POINT &damage);
    cold_dam operator=(cold_dam) = delete;
};

class shards_dam : public attribute_dam {
public:
    shards_dam(PlayerType *player_ptr, HIT_POINT dam, concptr kb_str, bool aura);
    shards_dam() = delete;
    virtual ~shards_dam() = default;

private:
    void effect(HIT_POINT &damage);
    shards_dam operator=(shards_dam) = delete;
};

int take_hit(PlayerType *player_ptr, int damage_type, HIT_POINT damage, concptr kb_str);
void touch_zap_player(monster_type *m_ptr, PlayerType *player_ptr);
HIT_POINT calc_aura_damage(MONRACE_IDX r_idx, DEPTH level, damage_flag_type TYPE);
