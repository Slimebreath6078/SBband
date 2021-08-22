#pragma once

#include "system/angband.h"
#include "object-enchant/tr-types.h"

typedef struct object_type object_type;
typedef struct player_type player_type;

bool potion_smash_effect(player_type *owner_ptr, MONSTER_IDX who, POSITION y, POSITION x, KIND_OBJECT_IDX k_idx);
PERCENTAGE breakage_chance(player_type *owner_ptr, object_type *o_ptr, bool has_archer_bonus, SPELL_IDX snipe_type);

class ObjectBreaker {
protected:
    ObjectBreaker(tr_type ignore_flg, player_type *player_ptr);
    ObjectBreaker() = delete;
    virtual ~ObjectBreaker() = default;

public:
    void inventory_damage(int perc);
    int can_destroy(object_type *o_ptr) const;
    virtual bool hates(object_type *o_ptr) const = 0;

private:
    tr_type ignore_flg;
    player_type *player_ptr;
};

class BreakerAcid : public ObjectBreaker {
public:
    BreakerAcid(player_type *player_ptr);
    virtual ~BreakerAcid() = default;
    bool hates(object_type *o_ptr) const;
};

class BreakerElec : public ObjectBreaker {
public:
    BreakerElec(player_type *player_ptr);
    virtual ~BreakerElec() = default;
    bool hates(object_type *o_ptr) const;
};

class BreakerFire : public ObjectBreaker {
public:
    BreakerFire(player_type *player_ptr);
    virtual ~BreakerFire() = default;
    bool hates(object_type *o_ptr) const;
};

class BreakerCold : public ObjectBreaker {
public:
    BreakerCold(player_type *player_ptr);
    virtual ~BreakerCold() = default;
    bool hates(object_type *o_ptr) const;
};
