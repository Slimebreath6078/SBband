#pragma once
/*!
 * @file blue-magic-spirit-curse.h
 * @brief 青魔法の呪い系処理ヘッダ
 */

#include "effect/attribute-types.h"
#include "monster-race/race-ability-flags.h"
#include "system/h-type.h"

struct bmc_type;
class PlayerType;

class curse_caster {
protected:
    curse_caster(PlayerType *player_ptr, bmc_type *bmc_ptr, MonsterAbilityType ms_type, AttributeType typ);

public:
    ~curse_caster() = default;
    bool project();

private:
    PlayerType *player_ptr;
    bmc_type *bmc_ptr;
    MonsterAbilityType ms_type;
    AttributeType typ;
};

class drain_mana_caster : public curse_caster {
public:
    drain_mana_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    drain_mana_caster() = delete;
    ~drain_mana_caster() = default;
};

class mind_blast_caster : public curse_caster {
public:
    mind_blast_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    mind_blast_caster() = delete;
    ~mind_blast_caster() = default;
};

class brain_smash_caster : public curse_caster {
public:
    brain_smash_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    brain_smash_caster() = delete;
    ~brain_smash_caster() = default;
};

class curse_1_caster : public curse_caster {
public:
    curse_1_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    curse_1_caster() = delete;
    ~curse_1_caster() = default;
};

class curse_2_caster : public curse_caster {
public:
    curse_2_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    curse_2_caster() = delete;
    ~curse_2_caster() = default;
};

class curse_3_caster : public curse_caster {
public:
    curse_3_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    curse_3_caster() = delete;
    ~curse_3_caster() = default;
};

class curse_4_caster : public curse_caster {
public:
    curse_4_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    curse_4_caster() = delete;
    ~curse_4_caster() = default;
};
