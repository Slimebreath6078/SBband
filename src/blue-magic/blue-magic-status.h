#pragma once
/*!
 * @file blue-magic-status.h
 * @brief 青魔法の状態異常系スペルヘッダ
 */

#include "monster-race/race-ability-flags.h"
#include "system/h-type.h"
#include <functional>

struct bmc_type;
class PlayerType;

class status_caster {
protected:
    status_caster(PlayerType *player_ptr, bmc_type *bmc_ptr, concptr msg, std::function<bool(PlayerType *, DIRECTION, PLAYER_LEVEL)> func, PLAYER_LEVEL level);
    status_caster() = delete;

public:
    ~status_caster() = default;
    bool project();

private:
    PlayerType *player_ptr;
    bmc_type *bmc_ptr;
    concptr msg;
    std::function<bool(PlayerType *, DIRECTION, PLAYER_LEVEL)> func;
    PLAYER_LEVEL level;
};

class scare_caster : public status_caster {
public:
    scare_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    scare_caster() = delete;
    ~scare_caster() = default;
};

class blind_caster : public status_caster {
public:
    blind_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    blind_caster() = delete;
    ~blind_caster() = default;
};

class confusion_caster : public status_caster {
public:
    confusion_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    confusion_caster() = delete;
    ~confusion_caster() = default;
};

class slow_caster : public status_caster {
public:
    slow_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    slow_caster() = delete;
    virtual ~slow_caster() = default;
};

class sleep_caster : public status_caster {
public:
    sleep_caster(PlayerType *player_ptr, bmc_type *bmc_ptr);
    sleep_caster() = delete;
    virtual ~sleep_caster() = default;
};
