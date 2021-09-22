#pragma once
/*!
 * @file blue-magic-breath.h
 * @brief 青魔法のブレス系呪文ヘッダ
 */

#include "monster-race/race-ability-flags.h"
#include "system/h-type.h"

struct bmc_type;
struct player_type;

class breath_caster{
    protected:
        breath_caster(player_type *player_ptr, bmc_type *bmc_ptr, concptr typ_name, RF_ABILITY ms_type, EFFECT_ID typ);
    public:
        ~breath_caster() = default;
        bool project();
    private:
        player_type *player_ptr;
        bmc_type *bmc_ptr;
        concptr typ_name;
        RF_ABILITY ms_type;
        EFFECT_ID typ;
};

class breath_acid_caster : public breath_caster{
    public:
        breath_acid_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_acid_caster() = delete;
        ~breath_acid_caster() = default;
};

class breath_elec_caster : public breath_caster{
    public:
        breath_elec_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_elec_caster() = delete;
        ~breath_elec_caster() = default;
};

class breath_fire_caster : public breath_caster{
    public:
        breath_fire_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_fire_caster() = delete;
        ~breath_fire_caster() = default;
};

class breath_cold_caster : public breath_caster{
    public:
        breath_cold_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_cold_caster() = delete;
        ~breath_cold_caster() = default;
};

class breath_pois_caster : public breath_caster{
    public:
        breath_pois_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_pois_caster() = delete;
        ~breath_pois_caster() = default;
};

class breath_nether_caster : public breath_caster{
    public:
        breath_nether_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_nether_caster() = delete;
        ~breath_nether_caster() = default;
};

class breath_lite_caster : public breath_caster{
    public:
        breath_lite_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_lite_caster() = delete;
        ~breath_lite_caster() = default;
};

class breath_dark_caster : public breath_caster{
    public:
        breath_dark_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_dark_caster() = delete;
        ~breath_dark_caster() = default;
};

class breath_conf_caster : public breath_caster{
    public:
        breath_conf_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_conf_caster() = delete;
        ~breath_conf_caster() = default;
};

class breath_sound_caster : public breath_caster{
    public:
        breath_sound_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_sound_caster() = delete;
        ~breath_sound_caster() = default;
};

class breath_chaos_caster : public breath_caster{
    public:
        breath_chaos_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_chaos_caster() = delete;
        ~breath_chaos_caster() = default;
};

class breath_disenchant_caster : public breath_caster{
    public:
        breath_disenchant_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_disenchant_caster() = delete;
        ~breath_disenchant_caster() = default;
};

class breath_nexus_caster : public breath_caster{
    public:
        breath_nexus_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_nexus_caster() = delete;
        ~breath_nexus_caster() = default;
};

class breath_time_caster : public breath_caster{
    public:
        breath_time_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_time_caster() = delete;
        ~breath_time_caster() = default;
};

class breath_inertia_caster : public breath_caster{
    public:
        breath_inertia_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_inertia_caster() = delete;
        ~breath_inertia_caster() = default;
};

class breath_gravity_caster : public breath_caster{
    public:
        breath_gravity_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_gravity_caster() = delete;
        ~breath_gravity_caster() = default;
};

class breath_shards_caster : public breath_caster{
    public:
        breath_shards_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_shards_caster() = delete;
        ~breath_shards_caster() = default;
};

class breath_plasma_caster : public breath_caster{
    public:
        breath_plasma_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_plasma_caster() = delete;
        ~breath_plasma_caster() = default;
};

class breath_force_caster : public breath_caster{
    public:
        breath_force_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_force_caster() = delete;
        ~breath_force_caster() = default;
};

class breath_mana_caster : public breath_caster{
    public:
        breath_mana_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_mana_caster() = delete;
        ~breath_mana_caster() = default;
};

class breath_nuke_caster : public breath_caster{
    public:
        breath_nuke_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_nuke_caster() = delete;
        ~breath_nuke_caster() = default;
};

class breath_disintegration_caster : public breath_caster{
    public:
        breath_disintegration_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        breath_disintegration_caster() = delete;
        ~breath_disintegration_caster() = default;
};

