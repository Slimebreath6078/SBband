﻿#include "system/angband.h"
#include "effect/effect-monster-util.h"
#include "effect/effect-monster-domination.h"
#include "player/player-effects.h"
#include "spell/spells-diceroll.h"
#include "monster/monster-status.h"
#include "effect/spells-effect-util.h"
#include "cmd/cmd-pet.h" // 暫定、後で消すかも.
#include "dungeon/quest.h"
#include "monster/monster-race-hook.h"

static void effect_monster_domination_corrupted_addition(player_type *caster_ptr, effect_monster_type *em_ptr)
{
	switch (randint1(4))
	{
	case 1:
		set_stun(caster_ptr, caster_ptr->stun + em_ptr->dam / 2);
		break;
	case 2:
		set_confused(caster_ptr, caster_ptr->confused + em_ptr->dam / 2);
		break;
	default:
	{
		if (em_ptr->r_ptr->flags3 & RF3_NO_FEAR)
			em_ptr->note = _("には効果がなかった。", " is unaffected.");
		else
			set_afraid(caster_ptr, caster_ptr->afraid + em_ptr->dam);
	}
	}
}


// Powerful demons & undead can turn a mindcrafter's attacks back on them.
static void effect_monster_domination_corrupted(player_type *caster_ptr, effect_monster_type *em_ptr)
{
	bool is_corrupted = ((em_ptr->r_ptr->flags3 & (RF3_UNDEAD | RF3_DEMON)) != 0) &&
		(em_ptr->r_ptr->level > caster_ptr->lev / 2) &&
		(one_in_(2));
	if (!is_corrupted)
	{
		em_ptr->note = _("には効果がなかった。", " is unaffected.");
		em_ptr->obvious = FALSE;
		return;
	}

	em_ptr->note = NULL;
	msg_format(_("%^sの堕落した精神は攻撃を跳ね返した！",
		(em_ptr->seen ? "%^s's corrupted mind backlashes your attack!" :
			"%^ss corrupted mind backlashes your attack!")), em_ptr->m_name);
	if (randint0(100 + em_ptr->r_ptr->level / 2) < caster_ptr->skill_sav)
	{
		msg_print(_("しかし効力を跳ね返した！", "You resist the effects!"));
		return;
	}

	effect_monster_domination_corrupted_addition(caster_ptr, em_ptr);
}


static void effect_monster_domination_addition(effect_monster_type *em_ptr)
{
	switch (randint1(4))
	{
	case 1:
		em_ptr->do_stun = em_ptr->dam / 2;
		break;
	case 2:
		em_ptr->do_conf = em_ptr->dam / 2;
		break;
	default:
		em_ptr->do_fear = em_ptr->dam;
	}
}


gf_switch_result effect_monster_domination(player_type *caster_ptr, effect_monster_type *em_ptr)
{
	if (!is_hostile(em_ptr->m_ptr)) return GF_SWITCH_CONTINUE;

	if (em_ptr->seen) em_ptr->obvious = TRUE;

	if ((em_ptr->r_ptr->flags1 & (RF1_UNIQUE | RF1_QUESTOR)) ||
		(em_ptr->r_ptr->flags3 & RF3_NO_CONF) ||
		(em_ptr->r_ptr->level > randint1((em_ptr->dam - 10) < 1 ? 1 : (em_ptr->dam - 10)) + 10))
	{
		if (((em_ptr->r_ptr->flags3 & RF3_NO_CONF) != 0) && is_original_ap_and_seen(caster_ptr, em_ptr->m_ptr))
			em_ptr->r_ptr->r_flags3 |= (RF3_NO_CONF);

		em_ptr->do_conf = 0;
		effect_monster_domination_corrupted(caster_ptr, em_ptr);
		em_ptr->dam = 0;
		return GF_SWITCH_CONTINUE;
	}

	if (!common_saving_throw_charm(caster_ptr, em_ptr->dam, em_ptr->m_ptr))
	{
		em_ptr->note = _("があなたに隷属した。", " is in your thrall!");
		set_pet(caster_ptr, em_ptr->m_ptr);
		em_ptr->dam = 0;
		return GF_SWITCH_CONTINUE;
	}

	effect_monster_domination_addition(em_ptr);
	em_ptr->dam = 0;
	return GF_SWITCH_CONTINUE;
}


static bool effect_monster_crusade_domination(player_type *caster_ptr, effect_monster_type *em_ptr)
{
	if (((em_ptr->r_ptr->flags3 & RF3_GOOD) == 0) || caster_ptr->current_floor_ptr->inside_arena)
		return FALSE;

	if (em_ptr->r_ptr->flags3 & RF3_NO_CONF) em_ptr->dam -= 50;
	if (em_ptr->dam < 1) em_ptr->dam = 1;

	if (is_pet(em_ptr->m_ptr))
	{
		em_ptr->note = _("の動きが速くなった。", " starts moving faster.");
		(void)set_monster_fast(caster_ptr, em_ptr->g_ptr->m_idx, MON_FAST(em_ptr->m_ptr) + 100);
		return TRUE;
	}

	if ((em_ptr->r_ptr->flags1 & RF1_QUESTOR) ||
		(em_ptr->r_ptr->flags1 & RF1_UNIQUE) ||
		(em_ptr->m_ptr->mflag2 & MFLAG2_NOPET) ||
		(caster_ptr->cursed & TRC_AGGRAVATE) ||
		((em_ptr->r_ptr->level + 10) > randint1(em_ptr->dam)))
	{
		if (one_in_(4))
			em_ptr->m_ptr->mflag2 |= MFLAG2_NOPET;

		return FALSE;
	}

	em_ptr->note = _("を支配した。", " is tamed!");
	set_pet(caster_ptr, em_ptr->m_ptr);
	(void)set_monster_fast(caster_ptr, em_ptr->g_ptr->m_idx, MON_FAST(em_ptr->m_ptr) + 100);
	if (is_original_ap_and_seen(caster_ptr, em_ptr->m_ptr))
		em_ptr->r_ptr->r_flags3 |= RF3_GOOD;

	return TRUE;
}


gf_switch_result effect_monster_crusade(player_type *caster_ptr, effect_monster_type *em_ptr)
{
	if (em_ptr->seen) em_ptr->obvious = TRUE;
	bool success = effect_monster_crusade_domination(caster_ptr, em_ptr);
	if (success)
	{
		em_ptr->dam = 0;
		return GF_SWITCH_CONTINUE;
	}

	if ((em_ptr->r_ptr->flags3 & RF3_NO_FEAR) == 0)
		em_ptr->do_fear = randint1(90) + 10;
	else if (is_original_ap_and_seen(caster_ptr, em_ptr->m_ptr))
		em_ptr->r_ptr->r_flags3 |= RF3_NO_FEAR;

	em_ptr->dam = 0;
	return GF_SWITCH_CONTINUE;
}


static bool effect_monster_capture_attemption(player_type *caster_ptr, effect_monster_type *em_ptr, int capturable_hp)
{
	if (em_ptr->m_ptr->hp >= randint0(capturable_hp)) return FALSE;

	if (em_ptr->m_ptr->mflag2 & MFLAG2_CHAMELEON)
		choose_new_monster(caster_ptr, em_ptr->g_ptr->m_idx, FALSE, MON_CHAMELEON);

	msg_format(_("%sを捕えた！", "You capture %^s!"), em_ptr->m_name);
	cap_mon = em_ptr->m_ptr->r_idx;
	cap_mspeed = em_ptr->m_ptr->mspeed;
	cap_hp = em_ptr->m_ptr->hp;
	cap_maxhp = em_ptr->m_ptr->max_maxhp;
	cap_nickname = em_ptr->m_ptr->nickname;
	if ((em_ptr->g_ptr->m_idx == caster_ptr->riding) && rakuba(caster_ptr, -1, FALSE))
		msg_format(_("地面に落とされた。", "You have fallen from %s."), em_ptr->m_name);

	delete_monster_idx(caster_ptr, em_ptr->g_ptr->m_idx);
	return TRUE;
}


gf_switch_result effect_monster_capture(player_type *caster_ptr, effect_monster_type *em_ptr)
{
	floor_type *floor_ptr = caster_ptr->current_floor_ptr;
	int capturable_hp;
	if ((floor_ptr->inside_quest && (quest[floor_ptr->inside_quest].type == QUEST_TYPE_KILL_ALL) && !is_pet(em_ptr->m_ptr)) ||
		(em_ptr->r_ptr->flags1 & (RF1_UNIQUE)) || (em_ptr->r_ptr->flags7 & (RF7_NAZGUL)) || (em_ptr->r_ptr->flags7 & (RF7_UNIQUE2)) || (em_ptr->r_ptr->flags1 & RF1_QUESTOR) || em_ptr->m_ptr->parent_m_idx)
	{
		msg_format(_("%sには効果がなかった。", "%s is unaffected."), em_ptr->m_name);
		em_ptr->skipped = TRUE;
		return GF_SWITCH_CONTINUE;
	}

	if (is_pet(em_ptr->m_ptr)) capturable_hp = em_ptr->m_ptr->maxhp * 4L;
	else if ((caster_ptr->pclass == CLASS_BEASTMASTER) && monster_living(em_ptr->m_ptr->r_idx))
		capturable_hp = em_ptr->m_ptr->maxhp * 3 / 10;
	else
		capturable_hp = em_ptr->m_ptr->maxhp * 3 / 20;

	if (em_ptr->m_ptr->hp >= capturable_hp)
	{
		msg_format(_("もっと弱らせないと。", "You need to weaken %s more."), em_ptr->m_name);
		em_ptr->skipped = TRUE;
		return GF_SWITCH_CONTINUE;
	}

	if (effect_monster_capture_attemption(caster_ptr, em_ptr, capturable_hp))
		return GF_SWITCH_TRUE;

	msg_format(_("うまく捕まえられなかった。", "You failed to capture %s."), em_ptr->m_name);
	em_ptr->skipped = TRUE;
	return GF_SWITCH_CONTINUE;
}
