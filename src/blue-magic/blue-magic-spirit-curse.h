#pragma once
/*!
 * @file blue-magic-spirit-curse.h
 * @brief 青魔法の呪い系処理ヘッダ
 */

#include "monster-race/race-ability-flags.h"
#include "system/h-type.h"

struct bmc_type;
struct player_type;

class curse_caster{
    protected:
        curse_caster(player_type *player_ptr, bmc_type *bmc_ptr, RF_ABILITY ms_type, EFFECT_ID typ);
    public:
        ~curse_caster() = default;
        bool project();
    private:
        player_type *player_ptr;
        bmc_type *bmc_ptr;
        RF_ABILITY ms_type;
        EFFECT_ID typ;
};

class drain_mana_caster : public curse_caster{
    public:
        drain_mana_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        drain_mana_caster() = delete;
        ~drain_mana_caster() = default;
};

class mind_blast_caster : public curse_caster{
    public:
        mind_blast_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        mind_blast_caster() = delete;
        ~mind_blast_caster() = default;
};

class brain_smash_caster : public curse_caster{
    public:
        brain_smash_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        brain_smash_caster() = delete;
        ~brain_smash_caster() = default;
};

class curse_1_caster : public curse_caster{
    public:
        curse_1_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        curse_1_caster() = delete;
        ~curse_1_caster() = default;
};

class curse_2_caster : public curse_caster{
    public:
        curse_2_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        curse_2_caster() = delete;
        ~curse_2_caster() = default;
};

class curse_3_caster : public curse_caster{
    public:
        curse_3_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        curse_3_caster() = delete;
        ~curse_3_caster() = default;
};

class curse_4_caster : public curse_caster{
    public:
        curse_4_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        curse_4_caster() = delete;
        ~curse_4_caster() = default;
};
