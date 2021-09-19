#pragma once
/*!
 * @file blue-magic-status.h
 * @brief 青魔法の状態異常系スペルヘッダ
 */

#include <functional>
#include "monster-race/race-ability-flags.h"
#include "system/h-type.h"

struct bmc_type;
struct player_type;

class status_caster{
    protected:
        status_caster(player_type *player_ptr, bmc_type *bmc_ptr, concptr msg, std::function<bool(player_type *, DIRECTION, PLAYER_LEVEL)> func, PLAYER_LEVEL level);
        status_caster() = delete;
    public:
        ~status_caster() = default;
        bool project();
    private:
        player_type *player_ptr;
        bmc_type *bmc_ptr;
        concptr msg;
        std::function<bool(player_type *, DIRECTION, PLAYER_LEVEL)> func;
        PLAYER_LEVEL level;
};
bool cast_blue_scare(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_blind(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_confusion(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_slow(player_type *player_ptr, bmc_type *bmc_ptr);
bool cast_blue_sleep(player_type *player_ptr, bmc_type *bmc_ptr);
