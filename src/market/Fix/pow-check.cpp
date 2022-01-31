#include "market/Fix/pow-check.h"
#include "market/Fix/flag-checker.h"
#include "monster-race/monster-race.h"
#include "monster-race/race-flags1.h"
#include "monster-race/race-flags2.h"
#include "monster-race/race-flags3.h"
#include "object/object-flags.h"
#include "system/monster-race-definition.h"
#include "util/bit-flags-calculator.h"
#include <map>
#include <stdexcept>

static const std::vector<MonsterAbilityType> lite_ability_mask = {
    MonsterAbilityType::BO_LITE,
    MonsterAbilityType::BA_LITE,
    MonsterAbilityType::BR_LITE,
};

static const std::vector<MonsterAbilityType> fire_ability_mask = {
    MonsterAbilityType::BO_FIRE,
    MonsterAbilityType::BA_FIRE,
    MonsterAbilityType::BR_FIRE,
};

static const std::vector<MonsterAbilityType> cold_ability_mask = {
    MonsterAbilityType::BO_COLD,
    MonsterAbilityType::BA_COLD,
    MonsterAbilityType::BR_COLD,
};

static const std::vector<MonsterAbilityType> acid_ability_mask = {
    MonsterAbilityType::BO_ACID,
    MonsterAbilityType::BA_ACID,
    MonsterAbilityType::BR_ACID,
};

static const std::vector<MonsterAbilityType> elec_ability_mask = {
    MonsterAbilityType::BO_ELEC,
    MonsterAbilityType::BA_ELEC,
    MonsterAbilityType::BR_ELEC,
};

static const std::vector<MonsterAbilityType> poison_ability_mask = {
    MonsterAbilityType::BA_POIS,
    MonsterAbilityType::BR_POIS,
};

static const std::vector<MonsterAbilityType> summon_dragon_mask = {
    MonsterAbilityType::S_DRAGON,
    MonsterAbilityType::S_HI_DRAGON,
};

static const sb_std::unordered_map<tr_type, std::shared_ptr<monster_flag_checker_abstrct>> flag_pow_up = {
    { TR_SLAY_EVIL, make_general_flag_checker(MonraceKindType::GOOD) },
    { TR_SLAY_GOOD, make_general_flag_checker(MonraceKindType::EVIL) },
    { TR_SLAY_UNDEAD, make_general_flag_checker(lite_ability_mask) },
    { TR_SLAY_HUMAN, make_general_flag_checker(MonraceKindType::KAN_SEN) },
    { TR_SLAY_DRAGON, std::make_shared<monster_many_flag_checker>(std::vector<std::shared_ptr<monster_flag_checker_abstrct>>{ make_general_flag_checker(MonraceKindType::DRAGON), make_general_flag_checker(summon_dragon_mask) }) },
    { TR_KILL_EVIL, make_general_flag_checker(MonraceKindType::GOOD) },
    { TR_KILL_GOOD, make_general_flag_checker(MonraceKindType::EVIL) },
    { TR_KILL_UNDEAD, make_general_flag_checker(lite_ability_mask) },
    { TR_KILL_HUMAN, make_general_flag_checker(MonraceKindType::KAN_SEN) },
    { TR_KILL_DRAGON, std::make_shared<monster_many_flag_checker>(std::vector<std::shared_ptr<monster_flag_checker_abstrct>>{ make_general_flag_checker(MonraceKindType::DRAGON), make_general_flag_checker(summon_dragon_mask) }) },
    { TR_BRAND_FIRE, make_general_flag_checker(fire_ability_mask) },
    { TR_BRAND_COLD, make_general_flag_checker(cold_ability_mask) },
    { TR_BRAND_ELEC, make_general_flag_checker(acid_ability_mask) },
    { TR_BRAND_ACID, make_general_flag_checker(elec_ability_mask) },
    { TR_BRAND_POIS, make_general_flag_checker(poison_ability_mask) },
    { TR_FORCE_WEAPON, make_general_flag_checker(MonsterAbilityType::PSY_SPEAR) },
    { TR_BRAND_MAGIC, std::make_shared<monster_flag_checker_with_func>(can_cast_spell) }
};

static const sb_std::unordered_map<tr_type, std::shared_ptr<monster_flag_checker_abstrct>> flag_pow_down = {
    { TR_SLAY_EVIL, make_general_flag_checker(MonraceKindType::EVIL) },
    { TR_SLAY_GOOD, make_general_flag_checker(MonraceKindType::GOOD) },
    { TR_KILL_EVIL, make_general_flag_checker(MonraceKindType::EVIL) },
    { TR_KILL_GOOD, make_general_flag_checker(MonraceKindType::GOOD) },
};

template <typename T, typename M>
inline M contain_map(const std::map<T, M> &map_data, T key, M excp)
{
    try {
        return map_data.at(key);
    } catch (std::out_of_range &) {
        return excp;
    }
}

bool pow_check_str(monster_race *r_ptr)
{
    int d_num_total = 0, d_side_total = 0;
    for (auto &d : r_ptr->blow) {
        if (d.d_dice > 0)
            d_num_total = d.d_dice;
        if (d.d_side > 0)
            d_side_total = d.d_side;
    }

    return (damroll(d_num_total, d_side_total) > r_ptr->level * 2);
}

bool pow_check_int(monster_race *r_ptr)
{
    int prob = 0;

    if (any_bits(r_ptr->flags2, RF2_SMART))
        prob = 50;
    else if (any_bits(r_ptr->flags2, RF2_STUPID))
        prob = -25;

    return (prob + r_ptr->level > randint0(110));
}

bool pow_check_dex(monster_race *r_ptr)
{
    int blow_num = 0;
    for (auto &d : r_ptr->blow) {
        if (d.d_dice > 0 && d.d_side > 0)
            blow_num++;
    }
    return (r_ptr->level * blow_num / 2 > randint0(150));
}

bool pow_check_wis(monster_race *r_ptr)
{
    return (randint0(r_ptr->level + 60) > 50);
}

bool pow_check_con(monster_race *r_ptr)
{
    int hp;

    if (any_bits(r_ptr->flags1, RF1_FORCE_MAXHP))
        hp = r_ptr->hdice * r_ptr->hside;
    else
        hp = damroll(r_ptr->hdice, r_ptr->hside);

    return (hp > randint0(r_ptr->level * r_ptr->level));
}

bool pow_check_chr(monster_race *r_ptr)
{
    return (r_ptr->race_kind_flags.has(MonraceKindType::KAN_SEN) || one_in_(3));
}

bool pow_check_speed(monster_race *r_ptr)
{
    return (randint1(120) < r_ptr->speed - 110);
}

bool pow_check_stealth(monster_race *r_ptr)
{

    int pow = r_ptr->level;
    if (any_bits(r_ptr->flags2, RF2_INVISIBLE))
        pow *= 3;

    pow += 60;

    return (randint0(pow) > 60);
}

bool pow_check_search(monster_race *r_ptr)
{
    return (randint0(25) > r_ptr->sleep);
}

bool pow_check_tunnel(monster_race *r_ptr)
{
    int d_num_total = 0, d_side_total = 0;
    for (auto &d : r_ptr->blow) {
        if (d.d_dice > 0)
            d_num_total = d.d_dice;
        if (d.d_side > 0)
            d_side_total = d.d_side;
    }

    return (damroll(d_num_total, d_side_total) > 100);
}

bool pow_check_magic_mastery(monster_race *r_ptr)
{

    int pow = r_ptr->freq_spell;

    if (any_bits(r_ptr->flags2, RF2_SMART))
        pow *= 2;
    else if (any_bits(r_ptr->flags2, RF2_STUPID))
        pow /= 2;

    pow += 25;

    return (randint0(pow) > 25);
}

/* アイテムフラグでpowの初期値を決めて、一定条件でそれ2倍または半分にした後ダイス判定をする汎用的な関数 */
bool pow_check_common(monster_race *r_ptr, tr_type typ)
{
    int pow;

    switch (typ) {
    case TR_SLAY_EVIL:
    case TR_SLAY_GOOD:
    case TR_KILL_ANIMAL:
    case TR_KILL_DEMON:
    case TR_KILL_DRAGON:
    case TR_KILL_GIANT:
    case TR_KILL_HUMAN:
    case TR_KILL_ORC:
    case TR_KILL_TROLL:
    case TR_KILL_UNDEAD:
        pow = r_ptr->level / 4;
        break;

    case TR_KILL_GOOD:
    case TR_KILL_EVIL:
    case TR_VORPAL:
    case TR_BRAND_MAGIC:
        pow = r_ptr->level / 8;
        break;

    case TR_BRAND_ACID:
    case TR_BRAND_ELEC:
    case TR_BRAND_FIRE:
    case TR_BRAND_COLD:
    case TR_BRAND_POIS:
    case TR_FORCE_WEAPON:
        pow = r_ptr->level * r_ptr->freq_spell / 66;
        break;

    case TR_IMPACT:
        pow = r_ptr->level * r_ptr->ac / 750;
        break;

    default:
        pow = 40;
        break;
    }

    if (flag_pow_up.contains(typ) && flag_pow_up.at(typ)) {
        pow *= 2;
    } else if (flag_pow_down.contains(typ) && flag_pow_down.at(typ)) {
        pow /= 2;
    }

    pow += 50;

    if (randint0(pow) > 50)
        return true;

    return false;
}
