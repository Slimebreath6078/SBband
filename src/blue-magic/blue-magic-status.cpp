/*!
 * @file blue-magic-status.cpp
 * @brief 青魔法の状態異常系スペル定義
 */

#include "blue-magic/blue-magic-status.h"
#include "blue-magic/blue-magic-util.h"
#include "spell/spells-status.h"
#include "system/player-type-definition.h"
#include "target/target-getter.h"
#include "view/display-messages.h"

status_caster::status_caster(player_type *player_ptr, bmc_type *bmc_ptr, concptr msg, std::function<bool(player_type *, DIRECTION, PLAYER_LEVEL)> func,
    PLAYER_LEVEL level)
    : player_ptr(player_ptr)
    , bmc_ptr(bmc_ptr)
    , msg(msg)
    , func(std::move(func))
    , level(level)
{}

bool status_caster::project(){
    if (!get_aim_dir(this->player_ptr, &this->bmc_ptr->dir))
        return false;

    if(this->msg != nullptr)
        msg_print(this->msg);

    this->func(this->player_ptr, this->bmc_ptr->dir, this->level);
    return true;
}

scare_caster::scare_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : status_caster(player_ptr, bmc_ptr, _("恐ろしげな幻覚を作り出した。", "You cast a fearful illusion."), fear_monster, bmc_ptr->plev + 10)
{}

blind_caster::blind_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : status_caster(player_ptr, bmc_ptr, nullptr, confuse_monster, bmc_ptr->plev * 2)
{}

confusion_caster::confusion_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : status_caster(player_ptr, bmc_ptr, _("誘惑的な幻覚をつくり出した。", "You cast a mesmerizing illusion."), confuse_monster, bmc_ptr->plev * 2)
{}

slow_caster::slow_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : status_caster(player_ptr, bmc_ptr, nullptr, slow_monster, bmc_ptr->plev)
{}

sleep_caster::sleep_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : status_caster(player_ptr, bmc_ptr, nullptr, sleep_monster, bmc_ptr->plev)
{}
