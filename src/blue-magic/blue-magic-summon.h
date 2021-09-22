#pragma once
/*!
 * @file blue-magic-summon.h
 * @brief 青魔法の召喚系スペルヘッダ
 */

#include <functional>
#include <vector>
#include "spell/summon-types.h"
#include "system/h-type.h"

struct bmc_type;
struct player_type;

struct summon_list{
    summon_list(concptr msg_angry, summon_type type, BIT_FLAGS mode, std::function<bool(player_type *, MONSTER_IDX, POSITION, POSITION, DEPTH, summon_type, BIT_FLAGS)> summon);
    summon_list(concptr msg_angry, summon_type type, BIT_FLAGS mode, std::function<bool(player_type *, DEPTH, POSITION, POSITION, BIT_FLAGS)> summon);
    summon_list operator =(summon_list) = delete;
    const concptr msg_angry;
    const summon_type type;
    const BIT_FLAGS mode;
    const std::function<bool(player_type *, MONSTER_IDX, POSITION, POSITION, DEPTH, summon_type, BIT_FLAGS)> summon;
};

class summon_caster{
    protected:
        summon_caster(player_type *player_ptr, bmc_type *bmc_ptr, concptr msg, std::vector<summon_list> summons, int num);
        summon_caster() = delete;
    public:
        ~summon_caster() = default;
        bool project();
    private:
        player_type *player_ptr;
        bmc_type *bmc_ptr;
        concptr msg;
        std::vector<summon_list> summons;
        int num;
};

class summon_kin_caster : public summon_caster{
    public:
        summon_kin_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_kin_caster() = delete;
        ~summon_kin_caster() = default;
};

class summon_cyber_caster : public summon_caster{
    public:
        summon_cyber_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_cyber_caster() = delete;
        ~summon_cyber_caster() = default;
};

class summon_monster_caster : public summon_caster{
    public:
        summon_monster_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_monster_caster() = delete;
        ~summon_monster_caster() = default;
};

class summon_monsters_caster : public summon_caster{
    public:
        summon_monsters_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_monsters_caster() = delete;
        ~summon_monsters_caster() = default;
};

class summon_ant_caster : public summon_caster{
    public:
        summon_ant_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_ant_caster() = delete;
        ~summon_ant_caster() = default;
};

class summon_spider_caster : public summon_caster{
    public:
        summon_spider_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_spider_caster() = delete;
        ~summon_spider_caster() = default;
};

class summon_hound_caster : public summon_caster{
    public:
        summon_hound_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_hound_caster() = delete;
        ~summon_hound_caster() = default;
};

class summon_hydra_caster : public summon_caster{
    public:
        summon_hydra_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_hydra_caster() = delete;
        ~summon_hydra_caster() = default;
};

class summon_angel_caster : public summon_caster{
    public:
        summon_angel_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_angel_caster() = delete;
        ~summon_angel_caster() = default;
};

class summon_demon_caster : public summon_caster{
    public:
        summon_demon_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_demon_caster() = delete;
        ~summon_demon_caster() = default;
};

class summon_undead_caster : public summon_caster{
    public:
        summon_undead_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_undead_caster() = delete;
        ~summon_undead_caster() = default;
};

class summon_dragon_caster : public summon_caster{
    public:
        summon_dragon_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_dragon_caster() = delete;
        ~summon_dragon_caster() = default;
};

class summon_high_undead_caster : public summon_caster{
    public:
        summon_high_undead_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_high_undead_caster() = delete;
        ~summon_high_undead_caster() = default;
};

class summon_high_dragon_caster : public summon_caster{
    public:
        summon_high_dragon_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_high_dragon_caster() = delete;
        ~summon_high_dragon_caster() = default;
};

class summon_amberite_caster : public summon_caster{
    public:
        summon_amberite_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_amberite_caster() = delete;
        ~summon_amberite_caster() = default;
};

class summon_unique_caster : public summon_caster{
    public:
        summon_unique_caster(player_type *player_ptr, bmc_type *bmc_ptr);
        summon_unique_caster() = delete;
        ~summon_unique_caster() = default;
};
