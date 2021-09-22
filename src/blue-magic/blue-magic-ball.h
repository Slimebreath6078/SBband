#pragma once

/*!
 * @file blue-magic-ball.h
 * @brief 青魔法のボール系呪文ヘッダ
 */

#include "monster-race/race-ability-flags.h"
#include "system/h-type.h"

struct bmc_type;
struct player_type;

class ball_caster{
    protected:
        ball_caster(player_type *player_ptr, bmc_type *bmc_ptr, concptr msg, RF_ABILITY ms_type, EFFECT_ID typ, POSITION rad);
    public:
        ~ball_caster() = default;
        bool project();
    private:
        player_type *player_ptr;
        bmc_type *bmc_ptr;
        concptr msg;
        RF_ABILITY ms_type;
        EFFECT_ID typ;
        POSITION rad;
};

class ball_acid_caster : public ball_caster{
    public:
        ball_acid_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        ~ball_acid_caster() = default;
};

class ball_elec_caster : public ball_caster{
    public:
        ball_elec_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        ~ball_elec_caster() = default;
};

class ball_fire_caster : public ball_caster{
    public:
        ball_fire_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        ~ball_fire_caster() = default;
};

class ball_cold_caster : public ball_caster{
    public:
        ball_cold_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        ~ball_cold_caster() = default;
};

class ball_pois_caster : public ball_caster{
    public:
        ball_pois_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        ~ball_pois_caster() = default;
};

class ball_nuke_caster : public ball_caster{
    public:
        ball_nuke_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        ~ball_nuke_caster() = default;
};

class ball_nether_caster : public ball_caster{
    public:
        ball_nether_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        ~ball_nether_caster() = default;
};

class ball_chaos_caster : public ball_caster{
    public:
        ball_chaos_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        ~ball_chaos_caster() = default;
};

class ball_water_caster : public ball_caster{
    public:
        ball_water_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        ~ball_water_caster() = default;
};

class ball_star_burst_caster : public ball_caster{
    public:
        ball_star_burst_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        ~ball_star_burst_caster() = default;
};

class ball_dark_storm_caster : public ball_caster{
    public:
        ball_dark_storm_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        ~ball_dark_storm_caster() = default;
};

class ball_mana_storm_caster : public ball_caster{
    public:
        ball_mana_storm_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        ~ball_mana_storm_caster() = default;
};