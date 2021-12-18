#include "effect/effect-monster-curse.h"
#include "core/player-redraw-types.h"
#include "effect/effect-monster-util.h"
#include "hpmp/hp-mp-processor.h"
#include "monster-race/monster-race.h"
#include "monster-race/race-indice-types.h"
#include "system/floor-type-definition.h"
#include "system/monster-race-definition.h"
#include "system/monster-type-definition.h"
#include "system/player-type-definition.h"
#include "view/display-messages.h"

process_result effect_monster_curse_1(effect_monster_type *em_ptr)
{
    if (em_ptr->seen)
        em_ptr->obvious = true;
    if (!em_ptr->who)
        msg_format(_("%sを指差して呪いをかけた。", "You point at %s and curse."), em_ptr->m_name);
    if (randint0(100 + (em_ptr->caster_lev / 2)) < (em_ptr->r_ptr->level + 35)) {
        em_ptr->note = _("には効果がなかった。", " is unaffected.");
        em_ptr->dam = 0;
    }

    return PROCESS_CONTINUE;
}

process_result effect_monster_curse_2(effect_monster_type *em_ptr)
{
    if (em_ptr->seen)
        em_ptr->obvious = true;
    if (!em_ptr->who)
        msg_format(_("%sを指差して恐ろしげに呪いをかけた。", "You point at %s and curse horribly."), em_ptr->m_name);

    if (randint0(100 + (em_ptr->caster_lev / 2)) < (em_ptr->r_ptr->level + 35)) {
        em_ptr->note = _("には効果がなかった。", " is unaffected.");
        em_ptr->dam = 0;
    }

    return PROCESS_CONTINUE;
}

process_result effect_monster_curse_3(effect_monster_type *em_ptr)
{
    if (em_ptr->seen)
        em_ptr->obvious = true;
    if (!em_ptr->who)
        msg_format(_("%sを指差し、恐ろしげに呪文を唱えた！", "You point at %s, incanting terribly!"), em_ptr->m_name);

    if (randint0(100 + (em_ptr->caster_lev / 2)) < (em_ptr->r_ptr->level + 35)) {
        em_ptr->note = _("には効果がなかった。", " is unaffected.");
        em_ptr->dam = 0;
    }

    return PROCESS_CONTINUE;
}

process_result effect_monster_curse_4(effect_monster_type *em_ptr)
{
    if (em_ptr->seen)
        em_ptr->obvious = true;
    if (!em_ptr->who)
        msg_format(_("%sの秘孔を突いて、「お前は既に死んでいる」と叫んだ。",
                       "You point at %s, screaming the word, 'DIE!'."),
            em_ptr->m_name);

    if ((randint0(100 + (em_ptr->caster_lev / 2)) < (em_ptr->r_ptr->level + 35)) && ((em_ptr->who <= 0) || (em_ptr->m_caster_ptr->r_idx != MON_KENSHIROU))) {
        em_ptr->note = _("には効果がなかった。", " is unaffected.");
        em_ptr->dam = 0;
    }

    return PROCESS_CONTINUE;
}

process_result effect_monster_drain_life(PlayerType *player_ptr, effect_monster_type *em_ptr)
{
    if (em_ptr->seen)
        em_ptr->obvious = true;
    if (!em_ptr->who)
        msg_format(_("%sの生命力を吸収した。",
                       "You suck %s's life."),
            em_ptr->m_name);

    if (em_ptr->r_ptr->race_kind_flags.has_any_of({ MonraceKindType::DEMON, MonraceKindType::UNDEAD, MonraceKindType::NONLIVING }) ||
        em_ptr->r_ptr->resistance_flags.has(MonsterResistanceType::RESIST_ALL)) {
        em_ptr->note = _("には耐性がある！", " resists!");
        em_ptr->dam *= 8;
        em_ptr->dam /= randint1(12) + 6;
    } else {
        HIT_POINT dam = std::min(em_ptr->m_ptr->hp, em_ptr->dam);
        if (em_ptr->who == 0) {
            if (player_ptr->chp >= player_ptr->mhp)
                return PROCESS_CONTINUE;

            HIT_POINT heal = dam * 2 / 3 + damroll(1, dam / 3);
            hp_player(player_ptr, heal);
        } else {
            floor_type *floor_ptr = player_ptr->current_floor_ptr;
            monster_type *who_ptr = &floor_ptr->m_list[em_ptr->who];

            who_ptr->hp += dam * 2 / 3 + damroll(1, dam / 3);
            if (who_ptr->hp > who_ptr->maxhp)
                who_ptr->hp = who_ptr->maxhp;

            if (player_ptr->health_who == em_ptr->who)
                player_ptr->redraw |= (PR_HEALTH);

            if (player_ptr->riding == em_ptr->who)
                player_ptr->redraw |= (PR_UHEALTH);

            if (who_ptr->ml)
                msg_format(_("%sは体力を回復したようだ。", "%^s appears healthier."), em_ptr->killer);
        }
    }

    return PROCESS_CONTINUE;
}