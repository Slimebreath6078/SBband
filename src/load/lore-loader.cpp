#include "load/lore-loader.h"
#include "game-option/runtime-arguments.h"
#include "load/angband-version-comparer.h"
#include "load/load-util.h"
#include "load/old/load-v1-5-0.h"
#include "load/savedata-old-flag-types.h"
#include "system/angband.h"
#include "system/monster-race-info.h"
#include "system/system-variables.h"
#include "util/bit-flags-calculator.h"
#include "util/enum-converter.h"

/*!
 * @brief モンスターの思い出を読み込む / Read the monster lore
 * @param r_ptr 読み込み先モンスター種族情報へのポインタ
 * @param r_idx 読み込み先モンスターID(種族特定用)
 */
static void rd_lore(MonsterRaceInfo *r_ptr)
{
    r_ptr->r_sights = rd_s16b();
    r_ptr->r_deaths = rd_s16b();
    r_ptr->r_pkills = rd_s16b();

    if (h_older_than(1, 7, 0, 5)) {
        r_ptr->r_akills = r_ptr->r_pkills;
    } else {
        r_ptr->r_akills = rd_s16b();
    }

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

    rd_FlagGroup(r_ptr->r_resistance_flags, rd_byte);
    rd_FlagGroup(r_ptr->r_ability_flags, rd_byte);
    rd_FlagGroup(r_ptr->r_aura_flags, rd_byte);
    rd_FlagGroup(r_ptr->r_behavior_flags, rd_byte);
    rd_FlagGroup(r_ptr->r_kind_flags, rd_byte);
    rd_FlagGroup(r_ptr->r_drop_flags, rd_byte);
    rd_FlagGroup(r_ptr->r_feature_flags, rd_byte);
    rd_FlagGroup(r_ptr->r_special_flags, rd_byte);
    rd_FlagGroup(r_ptr->r_misc_flags, rd_byte);

    r_ptr->max_num = rd_byte();
    r_ptr->floor_id = rd_s16b();

    r_ptr->defeat_level = rd_s16b();
    r_ptr->defeat_time = rd_u32b();

    strip_bytes(1);

    r_ptr->r_resistance_flags &= r_ptr->resistance_flags;
    r_ptr->r_ability_flags &= r_ptr->ability_flags;
    r_ptr->r_aura_flags &= r_ptr->aura_flags;
    r_ptr->r_behavior_flags &= r_ptr->behavior_flags;
    r_ptr->r_drop_flags &= r_ptr->drop_flags;
    r_ptr->r_kind_flags &= r_ptr->kind_flags;
    r_ptr->r_feature_flags &= r_ptr->feature_flags;
    r_ptr->r_special_flags &= r_ptr->special_flags;
    r_ptr->r_misc_flags &= r_ptr->misc_flags;
}

void load_lore(void)
{
    auto loading_max_r_idx = rd_u16b();
    MonsterRaceInfo dummy;
    for (auto i = 0U; i < loading_max_r_idx; i++) {
        auto r_idx = static_cast<MonsterRaceId>(i);
        auto *r_ptr = i < monraces_info.size() ? &monraces_info[r_idx] : &dummy;
        rd_lore(r_ptr);
    }

    for (size_t i = loading_max_r_idx; i < monraces_info.size(); i++) {
        auto monrace_id = i2enum<MonsterRaceId>(i);
        auto &monrace = monraces_info[monrace_id];
        auto max_num = MAX_MONSTER_NUM;
        if (monrace.kind_flags.has(MonsterKindType::UNIQUE) || monrace.population_flags.has(MonsterPopulationType::ONLY_ONE)) {
            max_num = MAX_UNIQUE_NUM;
        } else if (monrace.population_flags.has(MonsterPopulationType::NAZGUL)) {
            max_num = MAX_NAZGUL_NUM;
        } else if (monrace.population_flags.has(MonsterPopulationType::BUNBUN_STRIKER)) {
            max_num = MAX_BUNBUN_NUM;
        }

        monrace.max_num = max_num;
    }

    load_note(_("モンスターの思い出をロードしました", "Loaded Monster Memory"));
}
