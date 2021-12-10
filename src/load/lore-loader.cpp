#include "load/lore-loader.h"
#include "game-option/runtime-arguments.h"
#include "load/angband-version-comparer.h"
#include "load/load-util.h"
#include "load/savedata-old-flag-types.h"
#include "monster-race/monster-race.h"
#include "system/angband.h"
#include "system/monster-race-definition.h"
#include "util/bit-flags-calculator.h"

/*!
 * @brief モンスターの思い出を読み込む / Read the monster lore
 * @param r_ptr 読み込み先モンスター種族情報へのポインタ
 * @param r_idx 読み込み先モンスターID(種族特定用)
 */
static void rd_lore(monster_race *r_ptr)
{
    r_ptr->r_sights = rd_s16b();
    r_ptr->r_deaths = rd_s16b();
    r_ptr->r_pkills = rd_s16b();

    r_ptr->r_akills = rd_s16b();

    r_ptr->r_tkills = rd_s16b();

    r_ptr->r_wake = rd_byte();
    r_ptr->r_ignore = rd_byte();

    r_ptr->r_can_evolve = rd_byte() > 0;

    r_ptr->r_drop_gold = rd_byte();
    r_ptr->r_drop_item = rd_byte();

    strip_bytes(1);
    r_ptr->r_cast_spell = rd_byte();

    r_ptr->r_blows[0] = rd_byte();
    r_ptr->r_blows[1] = rd_byte();
    r_ptr->r_blows[2] = rd_byte();
    r_ptr->r_blows[3] = rd_byte();

    r_ptr->r_flags1 = rd_u32b();
    r_ptr->r_flags2 = rd_u32b();
    r_ptr->r_flags3 = rd_u32b();
    rd_FlagGroup(r_ptr->r_resistance_flags, rd_byte);
    rd_FlagGroup(r_ptr->r_ability_flags, rd_byte);
    rd_FlagGroup(r_ptr->r_aura_flags, rd_byte);
    rd_FlagGroup(r_ptr->r_race_kind_flags, rd_byte);

    r_ptr->max_num = rd_byte();
    r_ptr->floor_id = rd_s16b();

    r_ptr->defeat_level = rd_s16b();
    r_ptr->defeat_time = rd_u32b();

    strip_bytes(1);

    r_ptr->r_flags1 &= r_ptr->flags1;
    r_ptr->r_flags2 &= r_ptr->flags2;
    r_ptr->r_flags3 &= r_ptr->flags3;
    r_ptr->r_resistance_flags &= r_ptr->resistance_flags;
    r_ptr->r_ability_flags &= r_ptr->ability_flags;
    r_ptr->r_aura_flags &= r_ptr->aura_flags;
    r_ptr->r_race_kind_flags &= r_ptr->r_race_kind_flags;
}

void load_lore(void)
{
    auto loading_max_r_idx = rd_u16b();
    monster_race dummy;
    for (auto i = 0U; i < loading_max_r_idx; i++) {
        auto *r_ptr = i < r_info.size() ? &r_info[i] : &dummy;
        rd_lore(r_ptr);
    }

    load_note(_("モンスターの思い出をロードしました", "Loaded Monster Memory"));
}
