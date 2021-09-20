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
bool cast_blue_summon_kin(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_summon_cyber(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_summon_monster(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_summon_monsters(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_summon_ant(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_summon_spider(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_summon_hound(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_summon_hydra(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_summon_angel(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_summon_demon(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_summon_undead(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_summon_dragon(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_summon_high_undead(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_summon_high_dragon(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_summon_amberite(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_summon_unique(player_type *player_ptr, bmc_type *bmc_ptr);
