#include "market/Fix/weapon-kansen.h"
#include "artifact/artifact-info.h"
#include "artifact/fixed-art-types.h"
#include "artifact/random-art-effects.h"
#include "core/asking-player.h"
#include "core/player-update-types.h"
#include "core/stuff-handler.h"
#include "flavor/flavor-describer.h"
#include "flavor/object-flavor-types.h"
#include "floor/floor-object.h"
#include "inventory/inventory-object.h"
#include "market/Fix/building-craft-fix.h"
#include "market/Fix/pow-check.h"
#include "market/building-util.h"
#include "monster-race/monster-race.h"
#include "monster-race/race-flags1.h"
#include "monster-race/race-flags2.h"
#include "monster-race/race-flags3.h"
#include "object-enchant/object-boost.h"
#include "object-enchant/special-object-flags.h"
#include "object-enchant/tr-types.h"
#include "object-hook/hook-weapon.h"
#include "object/item-tester-hooker.h"
#include "object/item-use-flags.h"
#include "object/object-flags.h"
#include "object/object-kind-hook.h"
#include "object/object-kind.h"
#include "object/object-value.h"
#include "racial/racial-android.h"
#include "spell-realm/spells-hex.h"
#include "sv-definition/sv-other-types.h"
#include "sv-definition/sv-weapon-types.h"
#include "system/monster-race-definition.h"
#include "system/object-type-definition.h"
#include "system/player-type-definition.h"
#include "term/screen-processor.h"
#include "util/bit-flags-calculator.h"
#include "view/display-messages.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <stdexcept>

auto no_powcheck = [](monster_race *, tr_type) { return !one_in_(2); };

static const auto all_resistance = {
    TR_RES_ACID,
    TR_IM_ACID,
    TR_RES_ELEC,
    TR_IM_ELEC,
    TR_RES_FIRE,
    TR_IM_FIRE,
    TR_RES_COLD,
    TR_IM_COLD,
    TR_RES_POIS,
    TR_RES_POIS,
    TR_RES_CHAOS,
    TR_RES_DARK,
    TR_RES_LITE,
    TR_RES_SHARDS,
    TR_RES_WATER,
    TR_RES_TIME,
    TR_RES_NETHER,
    TR_RES_NEXUS,
    TR_RES_SOUND,
    TR_RES_DISEN,
    TR_RES_CURSE,
    TR_RES_FEAR,
    TR_RES_CONF,
    TR_RES_BLIND
};

static const sb_std::unordered_map<tr_type, std::vector<tr_type>> duplicate_list = {
    { TR_SLAY_ANIMAL, { TR_KILL_ANIMAL } },
    { TR_SLAY_DEMON, { TR_KILL_DEMON } },
    { TR_SLAY_DRAGON, { TR_KILL_DRAGON } },
    { TR_SLAY_EVIL, { TR_KILL_EVIL } },
    { TR_SLAY_GIANT, { TR_KILL_GIANT } },
    { TR_SLAY_GOOD, { TR_KILL_GOOD } },
    { TR_SLAY_HUMAN, { TR_KILL_HUMAN } },
    { TR_SLAY_ORC, { TR_KILL_ORC } },
    { TR_SLAY_TROLL, { TR_KILL_TROLL } },
    { TR_SLAY_UNDEAD, { TR_KILL_UNDEAD } },
    { TR_KILL_ANIMAL, { TR_SLAY_ANIMAL } },
    { TR_KILL_DEMON, { TR_SLAY_DEMON } },
    { TR_KILL_DRAGON, { TR_SLAY_DRAGON } },
    { TR_KILL_EVIL, { TR_SLAY_EVIL } },
    { TR_KILL_GIANT, { TR_SLAY_GIANT } },
    { TR_KILL_GOOD, { TR_SLAY_GOOD } },
    { TR_KILL_HUMAN, { TR_SLAY_HUMAN } },
    { TR_KILL_ORC, { TR_SLAY_ORC } },
    { TR_KILL_TROLL, { TR_SLAY_TROLL } },
    { TR_KILL_UNDEAD, { TR_SLAY_UNDEAD } },
    { TR_RES_ACID, { TR_IM_ACID } },
    { TR_RES_ELEC, { TR_IM_ELEC } },
    { TR_RES_FIRE, { TR_IM_FIRE } },
    { TR_RES_COLD, { TR_IM_COLD } },
};

static const std::vector<std::shared_ptr<add_hook_abstrct>> resistance_table = {
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter_one_in>(6, TR_RES_FIRE, TR_IM_FIRE), flgchk_std::stream() << MonsterResistanceType::IMMUNE_FIRE, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter_one_in>(6, TR_RES_COLD, TR_IM_COLD), flgchk_std::stream() << MonsterResistanceType::IMMUNE_COLD, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter_one_in>(6, TR_RES_ELEC, TR_IM_ELEC), flgchk_std::stream() << MonsterResistanceType::IMMUNE_ELEC, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter_one_in>(6, TR_RES_ACID, TR_IM_ACID), flgchk_std::stream() << MonsterResistanceType::IMMUNE_ACID, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_RES_POIS), flgchk_std::stream() << MonsterResistanceType::IMMUNE_POISON, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_RES_CHAOS), flgchk_std::stream() << MonsterResistanceType::RESIST_CHAOS, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_RES_DARK), flgchk_std::stream() << MonsterResistanceType::RESIST_DARK, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_RES_LITE), flgchk_std::stream() << MonsterResistanceType::RESIST_LITE, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_RES_SHARDS), flgchk_std::stream() << MonsterResistanceType::RESIST_SHARDS, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_RES_WATER), flgchk_std::stream() << MonsterResistanceType::RESIST_WATER, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_RES_TIME), flgchk_std::stream() << MonsterResistanceType::RESIST_TIME, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_RES_NETHER), flgchk_std::stream() << MonsterResistanceType::RESIST_NETHER, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_RES_NEXUS), flgchk_std::stream() << MonsterResistanceType::RESIST_NEXUS, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_RES_SOUND), flgchk_std::stream() << MonsterResistanceType::RESIST_SOUND, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_RES_DISEN), flgchk_std::stream() << MonsterResistanceType::RESIST_DISENCHANT, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_RES_FEAR), flgchk_std::stream() << flgchk_std::bit_stream(static_cast<BIT_FLAGS>(RF3_NO_FEAR), 3), no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_RES_CONF), flgchk_std::stream() << flgchk_std::bit_stream(static_cast<BIT_FLAGS>(RF3_NO_CONF), 3), no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_RES_BLIND), flgchk_std::stream() << flgchk_std::bit_stream(static_cast<BIT_FLAGS>(RF3_NO_SLEEP), 3), no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_RES_SOUND), flgchk_std::stream() << flgchk_std::bit_stream(static_cast<BIT_FLAGS>(RF3_NO_STUN), 3), no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_random_getter>(all_resistance), flgchk_std::stream() << MonsterResistanceType::RESIST_ALL, no_powcheck)
};

static const std::vector<std::shared_ptr<add_hook_abstrct>> slay_table = {
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_SLAY_EVIL), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_SLAY_GOOD), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_SLAY_GIANT), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_SLAY_ORC), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_SLAY_TROLL), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_SLAY_UNDEAD), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_SLAY_HUMAN), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_SLAY_DRAGON), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_SLAY_DEMON), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_SLAY_ANIMAL), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_KILL_EVIL), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_KILL_GOOD), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_KILL_GIANT), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_KILL_ORC), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_KILL_TROLL), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_KILL_UNDEAD), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_KILL_HUMAN), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_KILL_DRAGON), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_KILL_DEMON), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_KILL_ANIMAL), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_BRAND_FIRE), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_BRAND_COLD), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_BRAND_ELEC), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_BRAND_ACID), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_BRAND_POIS), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_FORCE_WEAPON), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_VORPAL), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_IMPACT), flgchk_std::null_stream, pow_check_common),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_BRAND_MAGIC), flgchk_std::null_stream, pow_check_common)
};

static const std::vector<std::shared_ptr<add_hook_abstrct>> pval_table = {
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_STR), flgchk_std::null_stream, pow_check_str),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_INT), flgchk_std::null_stream, pow_check_int),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_DEX), flgchk_std::null_stream, pow_check_dex),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_WIS), flgchk_std::null_stream, pow_check_wis),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_CON), flgchk_std::null_stream, pow_check_con),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_CHR), flgchk_std::null_stream, pow_check_chr),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_SPEED), flgchk_std::stream() << has_speed, pow_check_speed),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_STEALTH), flgchk_std::null_stream, pow_check_stealth),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_SEARCH), flgchk_std::stream() << can_search, pow_check_search),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_TUNNEL), flgchk_std::null_stream, pow_check_tunnel),
    std::make_shared<add_simple_hook>(std::make_unique<tr_flag_getter>(TR_INFRA)),
    std::make_shared<add_other_hook>(std::make_unique<tr_flag_getter>(TR_BLOWS)),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_MAGIC_MASTERY), flgchk_std::null_stream, pow_check_magic_mastery)
};

static const std::vector<std::shared_ptr<add_hook_abstrct>> other_table = {
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_FREE_ACT), flgchk_std::stream() << flgchk_std::bit_stream(static_cast<BIT_FLAGS>(RF3_NO_SLEEP), 3), no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_SH_FIRE), flgchk_std::stream() << MonsterAuraType::FIRE, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_SH_COLD), flgchk_std::stream() << MonsterAuraType::COLD, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_SH_ELEC), flgchk_std::stream() << MonsterAuraType::ELEC, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_HOLD_EXP), flgchk_std::stream() << MonraceKindType::NONLIVING, no_powcheck),
    std::make_shared<add_check_hook>(std::make_unique<tr_flag_getter>(TR_REFLECT), flgchk_std::stream() << flgchk_std::bit_stream(static_cast<BIT_FLAGS>(RF2_REFLECTING), 2), no_powcheck),
    std::make_shared<add_simple_hook>(std::make_unique<tr_flag_getter>(TR_SUST_STR)),
    std::make_shared<add_simple_hook>(std::make_unique<tr_flag_getter>(TR_SUST_INT)),
    std::make_shared<add_simple_hook>(std::make_unique<tr_flag_getter>(TR_SUST_DEX)),
    std::make_shared<add_simple_hook>(std::make_unique<tr_flag_getter>(TR_SUST_WIS)),
    std::make_shared<add_simple_hook>(std::make_unique<tr_flag_getter>(TR_SUST_CON)),
    std::make_shared<add_simple_hook>(std::make_unique<tr_flag_getter>(TR_SUST_CHR))
};

static const std::vector<std::vector<std::shared_ptr<add_hook_abstrct>>> grab_flag_table = {
    resistance_table,
    slay_table,
    pval_table,
    other_table
};

tr_flag_getter_abstrct::tr_flag_getter_abstrct(bool single)
    : single(single)
{
}

tr_flag_getter::tr_flag_getter(tr_type flag)
    : tr_flag_getter_abstrct(true)
    , flag(flag)
{
}

tr_type tr_flag_getter::get_flag()
{
    return flag;
}

tr_flag_random_getter::tr_flag_random_getter(std::initializer_list<tr_type> flag)
    : tr_flag_getter_abstrct(false)
    , flag(flag)
{
}

tr_type tr_flag_random_getter::get_flag()
{
    return flag[randint0(flag.size())];
}

tr_flag_getter_one_in::tr_flag_getter_one_in(int range, tr_type one, tr_type other)
    : tr_flag_getter_abstrct(false)
    , range(range)
    , one(one)
    , other(other)
{
}

tr_type tr_flag_getter_one_in::get_flag()
{
    return one_in_(range) ? one : other;
}

weapon_fix_result_type add_hook_abstrct::set_flag(object_type *o_ptr, tr_flag_getter_abstrct *tr_getter)
{
    auto o_flag = object_flags(o_ptr);
    auto flag = tr_getter->get_flag();

    if (o_flag.has_not(flag) && !is_duplicate_flag(o_ptr, flag)) {
        o_ptr->art_flags.set(flag);
        return weapon_fix_result_type::DONE;
    }
    return tr_getter->single ? weapon_fix_result_type::DUPLICATE : weapon_fix_result_type::FAILED;
}

bool add_hook_abstrct::is_duplicate_flag(object_type *o_ptr, tr_type typ)
{
    if (!duplicate_list.contains(typ))
        return false;

    return o_ptr->art_flags.has_any_of(duplicate_list.at(typ).begin(), duplicate_list.at(typ).end());
}

add_simple_hook::add_simple_hook(tr_type tr_flag)
    : tr_flag(std::make_unique<tr_flag_getter>(tr_flag))
{
}

add_simple_hook::add_simple_hook(std::unique_ptr<tr_flag_getter_abstrct> tr_flag)
    : tr_flag(std::move(tr_flag))
{
}

weapon_fix_result_type add_simple_hook::proc(object_type *o_ptr, monster_race * /*未使用*/)
{
    if (!one_in_(2))
        return weapon_fix_result_type::FAILED;

    return set_flag(o_ptr, tr_flag.get());
}

add_check_hook::add_check_hook(std::unique_ptr<tr_flag_getter_abstrct> tr_flag, flgchk_std::stream flag, std::function<bool(monster_race *)> pow_check)
    : tr_flag(std::move(tr_flag))
    , flag(flag)
    , pow_check([func = std::move(pow_check)](monster_race *r_ptr, tr_type) { return func(r_ptr); })
{
}

add_check_hook::add_check_hook(std::unique_ptr<tr_flag_getter_abstrct> tr_flag, flgchk_std::stream flag, std::function<bool(monster_race *, tr_type)> pow_check)
    : tr_flag(std::move(tr_flag))
    , flag(flag)
    , pow_check(std::move(pow_check))
{
}

weapon_fix_result_type add_check_hook::proc(object_type *o_ptr, monster_race *r_ptr)
{
    auto typ = tr_flag->get_flag();
    std::unique_ptr<tr_flag_getter_abstrct> getter = std::make_unique<tr_flag_getter>(typ);

    if (!flag.proc(r_ptr))
        return weapon_fix_result_type::NOT_MATCH;

    if (!pow_check(r_ptr, typ))
        return weapon_fix_result_type::FAILED;

    return set_flag(o_ptr, getter.get());
}

add_other_hook::add_other_hook(tr_type tr_other)
    : tr_other(std::make_unique<tr_flag_getter>(tr_other))
{
}

add_other_hook::add_other_hook(std::unique_ptr<tr_flag_getter_abstrct> tr_other)
    : tr_other(std::move(tr_other))
{
}

weapon_fix_result_type add_other_hook::proc(object_type *o_ptr, monster_race *r_ptr)
{
    auto flag = tr_other->get_flag();
    switch (flag) {
    case TR_BLOWS: {
        int blow_num = 0, pow;
        for (auto &d : r_ptr->blow) {
            if (d.d_dice > 0 && d.d_side > 0)
                blow_num++;
        }
        pow = (r_ptr->level + (r_ptr->speed - 110) * 4) * blow_num + 300;

        if (pow < 300)
            return weapon_fix_result_type::NOT_MATCH;
        if (randint0(pow) > 300)
            return set_flag(o_ptr, tr_other.get());
    }
        return weapon_fix_result_type::FAILED;

    default:
        return weapon_fix_result_type::NOT_MATCH;
    }
}

void grab_flags_from_monrace(object_type *o_ptr, monster_race *r_ptr, int min, int max)
{
    auto table = grab_flag_table;
    int count = 0;
    auto tr_flags = o_ptr->art_flags; /* 追加前のアイテムフラグ（追加されたフラグによってpvalなどを変えるために使う） */

    while (count < max) {
        auto ability = table.begin() + randint0(table.size());
        auto flag = (*ability).begin() + randint0((*ability).size());

        auto result = (*flag)->proc(o_ptr, r_ptr);

        if (result == weapon_fix_result_type::NOT_MATCH || result == weapon_fix_result_type::DUPLICATE)
            (*ability).erase(flag); /* 計算数削減のため、対応する特性を持っていないモンスターの場合や重複しているアイテムフラグは候補から消す */
        else if (result == weapon_fix_result_type::DONE) {
            (*ability).erase(flag); /* 計算数削減で既に追加したフラグは候補から消す */
            count++;
            if (count >= min && !one_in_(4))
                break;
        }
        if ((*ability).size() == 0)
            table.erase(ability); /* 候補がない種類の配列は消す */
    }

    if (tr_flags.has_none_of(TR_PVAL_FLAG_MASK) && o_ptr->art_flags.has_any_of(TR_PVAL_FLAG_MASK))
        o_ptr->pval = std::max<short>(o_ptr->pval, 1);
    else {
        if (tr_flags.has_not(TR_BLOWS) && o_ptr->art_flags.has(TR_BLOWS)) {
            auto bmax = std::min<short>(3, std::max<short>(1, 40 / (o_ptr->dd * o_ptr->ds)));
            o_ptr->pval = std::min<short>(o_ptr->pval, bmax);
        }
        if (tr_flags.has_not(TR_SPEED) && o_ptr->art_flags.has(TR_SPEED))
            o_ptr->pval = std::min<short>(o_ptr->pval, 4);
    }
}

void grab_one_flag_from_monrace(object_type *o_ptr, monster_race *r_ptr)
{
    grab_flags_from_monrace(o_ptr, r_ptr, 1, 1);
}
