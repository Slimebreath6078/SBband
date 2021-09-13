#pragma once

#include "system/angband.h"

/* Spell Type flag */
#define MONSTER_TO_PLAYER 0x01
#define MONSTER_TO_MONSTER 0x02

/* monster spell number */
#define RF4_SPELL_START 32 * 3
#define RF5_SPELL_START 32 * 4
#define RF6_SPELL_START 32 * 5

struct floor_type;
struct player_type;

struct SpellMsg_blind{
    SpellMsg_blind(concptr msg_blind, concptr msg_mons_to_player, concptr msg_mons_to_mons);
    concptr msg_blind;
    concptr msg_mons_to_player;
    concptr msg_mons_to_mons;
};

bool see_monster(player_type *player_ptr, MONSTER_IDX m_idx);
bool monster_near_player(floor_type* floor_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx);
bool monspell_message_base(player_type* target_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, concptr msg1, concptr msg2, concptr msg3, concptr msg4, bool msg_flag_aux, int TARGET_TYPE);
bool monspell_message(player_type* target_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, const SpellMsg_blind &msgs, int TARGET_TYPE);
void simple_monspell_message(player_type* target_ptr, MONSTER_IDX m_idx, MONSTER_IDX t_idx, concptr msg1, concptr msg2, int TARGET_TYPE);
