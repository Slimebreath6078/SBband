#pragma once

#include "object/object-broken.h"
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
struct player_type;

struct damage_function {
    damage_function(std::function<PERCENTAGE(player_type *player_ptr)> calc_damage_rate, std::function<BIT_FLAGS(player_type *player_ptr)> has_resist,
        std::function<bool(player_type *player_ptr)> is_oppose);
    damage_function() = delete;
    ~damage_function() = default;
    damage_function operator=(damage_function) = delete;
    const std::function<PERCENTAGE(player_type *player_ptr)> calc_damage_rate;
    const std::function<BIT_FLAGS(player_type *player_ptr)> has_resist;
    const std::function<bool(player_type *player_ptr)> is_oppose;
};

class element_dam {
protected:
    element_dam(player_type *player_ptr, concptr kb_str, HIT_POINT dam, bool aura, int stat, std::unique_ptr<ObjectBreaker> breaker, damage_function function);
    element_dam() = delete;
    player_type *player_ptr;
    concptr kb_str;
    HIT_POINT dam;
    bool aura;
    int stat;
    std::unique_ptr<ObjectBreaker> breaker;
    damage_function function;
    virtual void effect(bool double_resist);

public:
    virtual ~element_dam() = default;
    HIT_POINT process();
    element_dam operator=(element_dam) = delete;
};

class acid_dam : public element_dam {
public:
    acid_dam(player_type *player_ptr, HIT_POINT dam, concptr kb_str);
    acid_dam() = delete;
    virtual ~acid_dam() = default;

private:
    void effect(bool double_resist);
    virtual bool minus_ac();
    acid_dam operator=(acid_dam) = delete;
};

class elec_dam : public element_dam {
public:
    elec_dam(player_type *player_ptr, HIT_POINT dam, concptr kb_str, bool aura);
    elec_dam() = delete;
    virtual ~elec_dam() = default;

private:
    void effect(bool double_resist);
    elec_dam operator=(elec_dam) = delete;
};

class fire_dam : public element_dam {
public:
    fire_dam(player_type *player_ptr, HIT_POINT dam, concptr kb_str, bool aura);
    fire_dam() = delete;
    virtual ~fire_dam() = default;

private:
    void effect(bool double_resist);
    fire_dam operator=(fire_dam) = delete;
};

class cold_dam : public element_dam {
public:
    cold_dam(player_type *player_ptr, HIT_POINT dam, concptr kb_str, bool aura);
    cold_dam() = delete;
    virtual ~cold_dam() = default;

private:
    void effect(bool double_resist);
    cold_dam operator=(cold_dam) = delete;
};
int take_hit(player_type *player_ptr, int damage_type, HIT_POINT damage, concptr kb_str);
void touch_zap_player(monster_type *m_ptr, player_type *player_ptr);
