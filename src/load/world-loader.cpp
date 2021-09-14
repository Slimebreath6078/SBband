#include "load/world-loader.h"
#include "cmd-building/cmd-building.h"
#include "dungeon/dungeon.h"
#include "floor/wild.h"
#include "load/angband-version-comparer.h"
#include "load/load-util.h"
#include "load/load-zangband.h"
#include "market/bounty.h"
#include "system/building-type-definition.h"
#include "system/floor-type-definition.h"
#include "system/player-type-definition.h"
#include "world/world.h"

static void rd_hengband_dungeons(void)
{
    byte max = (byte)current_world_ptr->max_d_idx;
    rd_byte(&max);
    int16_t tmp16s;
    for (int i = 0; i < max; i++) {
        rd_s16b(&tmp16s);
        max_dlv[i] = tmp16s;
        if (max_dlv[i] > d_info[i].maxdepth)
            max_dlv[i] = d_info[i].maxdepth;
    }
}

void rd_dungeons(player_type *player_ptr)
{
    rd_hengband_dungeons();

    if (player_ptr->max_plv < player_ptr->lev)
        player_ptr->max_plv = player_ptr->lev;
}

/*!
 * @brief 現実変容処理の有無及びその残りターン数を読み込む
 * @param player_ptr プレイヤーへの参照ポインタ
 */
void rd_alter_reality(player_type *player_ptr)
{
    int16_t tmp16s;
    rd_s16b(&tmp16s);
    player_ptr->recall_dungeon = (byte)tmp16s;

    rd_s16b(&player_ptr->alter_reality);
}

void set_gambling_monsters(void)
{
    const int max_gambling_monsters = 4;
    for (int i = 0; i < max_gambling_monsters; i++) {
        rd_s16b(&battle_mon[i]);
        rd_u32b(&mon_odds[i]);
    }
}

/*!
 * @details 自動拾い関係はこれしかないのでworldに突っ込むことにする。必要があれば再分割する
 */
void rd_autopick(player_type *player_ptr)
{
    byte tmp8u;
    rd_byte(&tmp8u);
    player_ptr->autopick_autoregister = tmp8u != 0;
}

static void set_undead_turn_limit(player_type *player_ptr)
{
    switch (player_ptr->start_race) {
    case player_race_type::VAMPIRE:
    case player_race_type::SKELETON:
    case player_race_type::ZOMBIE:
    case player_race_type::SPECTRE:
        current_world_ptr->game_turn_limit = TURNS_PER_TICK * TOWN_DAWN * MAX_DAYS + TURNS_PER_TICK * TOWN_DAWN * 3 / 4;
        break;
    default:
        current_world_ptr->game_turn_limit = TURNS_PER_TICK * TOWN_DAWN * (MAX_DAYS - 1) + TURNS_PER_TICK * TOWN_DAWN * 3 / 4;
        break;
    }
}

static void rd_world_info(player_type *player_ptr)
{
    set_undead_turn_limit(player_ptr);
    current_world_ptr->dungeon_turn_limit = TURNS_PER_TICK * TOWN_DAWN * (MAX_DAYS - 1) + TURNS_PER_TICK * TOWN_DAWN * 3 / 4;
    rd_s32b(&player_ptr->current_floor_ptr->generated_turn);
    rd_s32b(&player_ptr->feeling_turn);

    rd_s32b(&current_world_ptr->game_turn);
    rd_s32b(&current_world_ptr->dungeon_turn);

    rd_s32b(&current_world_ptr->arena_start_turn);

    rd_s16b(&current_world_ptr->today_mon);
    rd_s16b(&player_ptr->today_mon);
}

void rd_visited_towns(player_type *player_ptr)
{
    int32_t tmp32s;
    rd_s32b(&tmp32s);
    player_ptr->visit = (BIT_FLAGS)tmp32s;
}

void rd_global_configurations(player_type *player_ptr)
{
    rd_u32b(&current_world_ptr->seed_flavor);
    rd_u32b(&current_world_ptr->seed_town);

    rd_u16b(&player_ptr->panic_save);
    rd_u16b(&current_world_ptr->total_winner);
    rd_u16b(&current_world_ptr->noscore);

    byte tmp8u;
    rd_byte(&tmp8u);
    player_ptr->is_dead = (bool)tmp8u;

    rd_byte(&player_ptr->feeling);
    rd_world_info(player_ptr);
}

void load_wilderness_info(player_type *player_ptr)
{
    rd_s32b(&player_ptr->wilderness_x);
    rd_s32b(&player_ptr->wilderness_y);
    
    rd_byte((byte *)&player_ptr->wild_mode);

    rd_byte((byte *)&player_ptr->ambush_flag);
}

errr analyze_wilderness(void)
{
    int32_t wild_x_size;
    int32_t wild_y_size;
    rd_s32b(&wild_x_size);
    rd_s32b(&wild_y_size);

    if ((wild_x_size > current_world_ptr->max_wild_x) || (wild_y_size > current_world_ptr->max_wild_y)) {
        load_note(format(_("荒野が大きすぎる(%u/%u)！", "Wilderness is too big (%u/%u)!"), wild_x_size, wild_y_size));
        return (23);
    }

    for (int i = 0; i < wild_x_size; i++)
        for (int j = 0; j < wild_y_size; j++)
            rd_u32b(&wilderness[j][i].seed);

    return 0;
}
