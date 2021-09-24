#pragma once

#include <functional>
#include "system/angband.h"
#include "object/object-broken.h"

#define DAMAGE_FORCE    1
#define DAMAGE_GENO     2
#define DAMAGE_LOSELIFE 3
#define DAMAGE_ATTACK   4
#define DAMAGE_NOESCAPE 5
#define DAMAGE_USELIFE  6

struct monster_type;
struct player_type;

struct damage_function{
    damage_function(std::function<PERCENTAGE(player_type *player_ptr)> calc_damage_rate, std::function<BIT_FLAGS(player_type *player_ptr)> has_resist,
            std::function<bool(player_type *player_ptr)> is_oppose);
    damage_function() = delete;
    ~damage_function() = default;
    damage_function operator =(damage_function) = delete;
    const std::function<PERCENTAGE(player_type *player_ptr)> calc_damage_rate;
    const std::function<BIT_FLAGS(player_type *player_ptr)> has_resist;
    const std::function<bool(player_type *player_ptr)> is_oppose;
};

class element_dam{
    protected:
        element_dam(player_type *player_ptr, concptr kb_str, HIT_POINT dam, bool aura, int stat, const ObjectBreaker &breaker, damage_function function);
        element_dam() = delete;
        player_type *player_ptr;
        concptr kb_str;
        HIT_POINT dam;
        bool aura;
        int stat;
        const ObjectBreaker &breaker;
        damage_function function;
        virtual void effect(bool double_resist);
    public:
        virtual ~element_dam() = default;
        HIT_POINT process();
        element_dam operator =(element_dam) = delete;
};
int take_hit(player_type *player_ptr, int damage_type, HIT_POINT damage, concptr kb_str);
HIT_POINT acid_dam(player_type *player_ptr, HIT_POINT dam, concptr kb_str, bool aura);
HIT_POINT elec_dam(player_type *player_ptr, HIT_POINT dam, concptr kb_str, bool aura);
HIT_POINT fire_dam(player_type *player_ptr, HIT_POINT dam, concptr kb_str, bool aura);
HIT_POINT cold_dam(player_type *player_ptr, HIT_POINT dam, concptr kb_str, bool aura);
void touch_zap_player(monster_type *m_ptr, player_type *player_ptr);
