/*!
 * @file blue-magic-summon.cpp
 * @brief 青魔法の召喚系スペル定義
 */

#include "blue-magic/blue-magic-summon.h"
#include "blue-magic/blue-magic-util.h"
#include "monster-floor/monster-summon.h"
#include "monster-floor/place-monster-types.h"
#include "spell/spells-summon.h"
#include "spell/summon-types.h"
#include "system/player-type-definition.h"
#include "view/display-messages.h"

summon_list::summon_list(concptr msg_angry, summon_type type, BIT_FLAGS mode, 
    std::function<bool(player_type *, MONSTER_IDX, POSITION, POSITION, DEPTH, summon_type, BIT_FLAGS)> summon)
    : msg_angry(msg_angry)
    , type(type)
    , mode(mode)
    , summon(std::move(summon))
{}

summon_list::summon_list(concptr msg_angry, summon_type type, BIT_FLAGS mode, 
    std::function<bool(player_type *, DEPTH, POSITION, POSITION, BIT_FLAGS)> summon)
    : msg_angry(msg_angry)
    , type(type)
    , mode(mode)
    , summon([func = std::move(summon)]
        (player_type *player_ptr, MONSTER_IDX, POSITION y, POSITION x, DEPTH lev, summon_type, BIT_FLAGS mode)
        {return func(player_ptr, lev, y, x, mode);})
{}

summon_caster::summon_caster(player_type *player_ptr, bmc_type *bmc_ptr, concptr msg, std::vector<summon_list> summons, int num)
    : player_ptr(player_ptr)
    , bmc_ptr(bmc_ptr)
    , msg(msg)
    , summons(std::move(summons))
    , num(num)
{}

bool summon_caster::project(){
    int count = 0;

    msg_print(this->msg);
    for(const auto& job : summons){
        for (int k = count; k < num; k++){
            if(job.summon(this->player_ptr, (bmc_ptr->pet ? -1 : 0), this->player_ptr->y, this->player_ptr->x,
                this->bmc_ptr->summon_lev, job.type, job.mode)){
                    count++;
                    if(!this->bmc_ptr->pet)
                        msg_print(job.msg_angry);
            }
        }
    }

    if(count == 0)
        bmc_ptr->no_trump = true;

    return true;
}

summon_kin_caster::summon_kin_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("援軍を召喚した。", "You summon one of your kin."),
        {summon_list(_("召喚された仲間は怒っている！", "The summoned companion is angry!"), SUMMON_NONE, (bmc_ptr->pet ? PM_FORCE_PET : PM_NONE), summon_kin_player)},
        1)
{}

summon_cyber_caster::summon_cyber_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("サイバーデーモンを召喚した！", "You summon a Cyberdemon!"),
        {summon_list(_("召喚されたサイバーデーモンは怒っている！", "The summoned Cyberdemon is angry!"), SUMMON_CYBER, bmc_ptr->p_mode, summon_specific)},
        1)
{}

summon_monster_caster::summon_monster_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("仲間を召喚した。", "You summon help."),
        {summon_list(_("召喚されたモンスターは怒っている！", "The summoned monster is angry!"), SUMMON_NONE, bmc_ptr->p_mode, summon_specific)},
        1)
{}

summon_monsters_caster::summon_monsters_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("モンスターを召喚した！", "You summon monsters!"),
        {summon_list(_("召喚されたモンスターは怒っている！", "The summoned monster is angry!"), SUMMON_NONE, (bmc_ptr->p_mode | bmc_ptr->u_mode), summon_specific)},
        bmc_ptr->plev / 15 + 2)
{}

summon_ant_caster::summon_ant_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("アリを召喚した。", "You summon ants."),
        {summon_list(_("召喚されたアリは怒っている！", "The summoned ants are angry!"), SUMMON_ANT, (PM_ALLOW_GROUP | bmc_ptr->p_mode), summon_specific)},
        1)
{}

summon_spider_caster::summon_spider_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("蜘蛛を召喚した。", "You summon spiders."),
        {summon_list(_("召喚された蜘蛛は怒っている！", "The summoned spiders are angry!"), SUMMON_SPIDER, (PM_ALLOW_GROUP | bmc_ptr->p_mode), summon_specific)},
        1)
{}

summon_hound_caster::summon_hound_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("ハウンドを召喚した。", "You summon hounds."),
        {summon_list(_("召喚されたハウンドは怒っている！", "The summoned hounds are angry!"), SUMMON_HOUND, (PM_ALLOW_GROUP | bmc_ptr->p_mode), summon_specific)},
        1)
{}

summon_hydra_caster::summon_hydra_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("ヒドラを召喚した。", "You summon a hydras."),
        {summon_list(_("召喚されたヒドラは怒っている！", "The summoned hydras are angry!"), SUMMON_HYDRA, (bmc_ptr->g_mode | bmc_ptr->p_mode), summon_specific)},
        1)
{}

summon_angel_caster::summon_angel_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("天使を召喚した！", "You summon an angel!"),
        {summon_list(_("召喚された天使は怒っている！", "The summoned angel is angry!"), SUMMON_ANGEL, (bmc_ptr->g_mode | bmc_ptr->p_mode), summon_specific)},
        1)
{}

summon_demon_caster::summon_demon_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("混沌の宮廷から悪魔を召喚した！", "You summon a demon from the Courts of Chaos!"),
        {summon_list(_("召喚されたデーモンは怒っている！", "The summoned demon is angry!"), SUMMON_DEMON, (bmc_ptr->g_mode | bmc_ptr->p_mode), summon_specific)},
        1)
{}

summon_undead_caster::summon_undead_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("アンデッドの強敵を召喚した！", "You summon an undead adversary!"),
        {summon_list(_("召喚されたアンデッドは怒っている！", "The summoned undead is angry!"), SUMMON_UNDEAD, (bmc_ptr->g_mode | bmc_ptr->p_mode), summon_specific)},
        1)
{}

summon_dragon_caster::summon_dragon_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("ドラゴンを召喚した！", "You summon a dragon!"),
        {summon_list(_("召喚されたドラゴンは怒っている！", "The summoned dragon is angry!"), SUMMON_UNDEAD, (bmc_ptr->g_mode | bmc_ptr->p_mode), summon_specific)},
        1)
{}

summon_high_undead_caster::summon_high_undead_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("強力なアンデッドを召喚した！", "You summon a greater undead!"),
        {summon_list(_("召喚された上級アンデッドは怒っている！", "The summoned greater undead is angry!"), SUMMON_HI_UNDEAD, 
            (bmc_ptr->g_mode | bmc_ptr->p_mode | bmc_ptr->u_mode), summon_specific)},
        1)
{}

summon_high_dragon_caster::summon_high_dragon_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("古代ドラゴンを召喚した！", "You summon an ancient dragon!"),
        {summon_list(_("召喚された古代ドラゴンは怒っている！", "The summoned ancient dragon is angry!"), SUMMON_HI_DRAGON, 
            (bmc_ptr->g_mode | bmc_ptr->p_mode | bmc_ptr->u_mode), summon_specific)},
        1)
{}

summon_amberite_caster::summon_amberite_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("アンバーの王族を召喚した！", "You summon a Lord of Amber!"),
        {summon_list(_("召喚されたアンバーの王族は怒っている！", "The summoned Lord of Amber is angry!"), SUMMON_AMBERITES, 
            (bmc_ptr->g_mode | bmc_ptr->p_mode | bmc_ptr->u_mode), summon_specific)},
        1)
{}

summon_unique_caster::summon_unique_caster(player_type *player_ptr, bmc_type *bmc_ptr)
    : summon_caster(player_ptr, bmc_ptr, _("特別な強敵を召喚した！", "You summon a special opponent!"),
        {summon_list(_("召喚されたユニーク・モンスターは怒っている！", "The summoned special opponent is angry!"), SUMMON_UNIQUE, 
            (bmc_ptr->g_mode | bmc_ptr->p_mode | PM_ALLOW_UNIQUE), summon_specific),
         summon_list(_("召喚された上級アンデッドは怒っている！", "The summoned greater undead is angry!"), SUMMON_HI_UNDEAD, 
            (bmc_ptr->g_mode | bmc_ptr->p_mode | PM_ALLOW_UNIQUE), summon_specific)},
        1)
{}

