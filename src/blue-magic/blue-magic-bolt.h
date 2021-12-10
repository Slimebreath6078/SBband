#pragma once
/*!
 * @file blue-magic-ball-bolt.h
 * @brief 青魔法のボール/ボルト系呪文ヘッダ
 */

#include "effect/attribute-types.h"
#include "monster-race/race-ability-flags.h"
#include "system/h-type.h"

struct bmc_type;
class PlayerType;

class bolt_caster {
protected:
    bolt_caster(PlayerType *player_ptr, bmc_type *bmc_ptr, concptr msg, MonsterAbilityType ms_type, AttributeType typ);

public:
    ~bolt_caster() = default;
    bool project();

private:
    PlayerType *player_ptr;
    bmc_type *bmc_ptr;
    concptr msg;
    MonsterAbilityType ms_type;
    AttributeType typ;
};

class bolt_acid_caster : public bolt_caster {
public:
    bolt_acid_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    bolt_acid_caster() = delete;
    ~bolt_acid_caster() = default;
};

class bolt_elec_caster : public bolt_caster {
public:
    bolt_elec_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    bolt_elec_caster() = delete;
    ~bolt_elec_caster() = default;
};

class bolt_fire_caster : public bolt_caster {
public:
    bolt_fire_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    bolt_fire_caster() = delete;
    ~bolt_fire_caster() = default;
};

class bolt_cold_caster : public bolt_caster {
public:
    bolt_cold_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    bolt_cold_caster() = delete;
    ~bolt_cold_caster() = default;
};

class bolt_nether_caster : public bolt_caster {
public:
    bolt_nether_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    bolt_nether_caster() = delete;
    ~bolt_nether_caster() = default;
};

class bolt_water_caster : public bolt_caster {
public:
    bolt_water_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    bolt_water_caster() = delete;
    ~bolt_water_caster() = default;
};

class bolt_mana_caster : public bolt_caster {
public:
    bolt_mana_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    bolt_mana_caster() = delete;
    ~bolt_mana_caster() = default;
};

class bolt_plasma_caster : public bolt_caster {
public:
    bolt_plasma_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    bolt_plasma_caster() = delete;
    ~bolt_plasma_caster() = default;
};

class bolt_icee_caster : public bolt_caster {
public:
    bolt_icee_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    bolt_icee_caster() = delete;
    ~bolt_icee_caster() = default;
};

class bolt_missile_caster : public bolt_caster {
public:
    bolt_missile_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    bolt_missile_caster() = delete;
    ~bolt_missile_caster() = default;
};

class bolt_lite_caster : public bolt_caster {
public:
    bolt_lite_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    bolt_lite_caster() = delete;
    ~bolt_lite_caster() = default;
};

class bolt_dark_caster : public bolt_caster {
public:
    bolt_dark_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    bolt_dark_caster() = delete;
    ~bolt_dark_caster() = default;
};
