#pragma once
/*!
 * @file blue-magic-ball-bolt.h
 * @brief 青魔法のボール/ボルト系呪文ヘッダ
 */

#include "monster-race/race-ability-flags.h"
#include "system/h-type.h"

struct bmc_type;
struct player_type;

class bolt_caster{
    protected:
        bolt_caster(player_type *player_ptr, bmc_type *bmc_ptr, concptr msg, RF_ABILITY ms_type, EFFECT_ID typ);
    public:
        ~bolt_caster() = default;
        bool project();
    private:
        player_type *player_ptr;
        bmc_type *bmc_ptr;
        concptr msg;
        RF_ABILITY ms_type;
        EFFECT_ID typ;
};

class bolt_acid_caster : public bolt_caster{
    public:
        bolt_acid_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        bolt_acid_caster() = delete;
        ~bolt_acid_caster() = default;
};

class bolt_elec_caster : public bolt_caster{
    public:
        bolt_elec_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        bolt_elec_caster() = delete;
        ~bolt_elec_caster() = default;
};

class bolt_fire_caster : public bolt_caster{
    public:
        bolt_fire_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        bolt_fire_caster() = delete;
        ~bolt_fire_caster() = default;
};

class bolt_cold_caster : public bolt_caster{
    public:
        bolt_cold_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        bolt_cold_caster() = delete;
        ~bolt_cold_caster() = default;
};

class bolt_nether_caster : public bolt_caster{
    public:
        bolt_nether_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        bolt_nether_caster() = delete;
        ~bolt_nether_caster() = default;
};

class bolt_water_caster : public bolt_caster{
    public:
        bolt_water_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        bolt_water_caster() = delete;
        ~bolt_water_caster() = default;
};

class bolt_mana_caster : public bolt_caster{
    public:
        bolt_mana_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        bolt_mana_caster() = delete;
        ~bolt_mana_caster() = default;
};

class bolt_plasma_caster : public bolt_caster{
    public:
        bolt_plasma_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        bolt_plasma_caster() = delete;
        ~bolt_plasma_caster() = default;
};

class bolt_icee_caster : public bolt_caster{
    public:
        bolt_icee_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        bolt_icee_caster() = delete;
        ~bolt_icee_caster() = default;
};

class bolt_missile_caster : public bolt_caster{
    public:
        bolt_missile_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        bolt_missile_caster() = delete;
        ~bolt_missile_caster() = default;
};

class bolt_lite_caster : public bolt_caster{
    public:
        bolt_lite_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        bolt_lite_caster() = delete;
        ~bolt_lite_caster() = default;
};

class bolt_dark_caster : public bolt_caster{
    public:
        bolt_dark_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        bolt_dark_caster() = delete;
        ~bolt_dark_caster() = default;
};
