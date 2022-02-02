#include "market/Fix/flag-checker.h"
#include "util/bit-flags-calculator.h"

template std::shared_ptr<monster_flag_checker<MonsterResistanceType>> make_general_flag_checker(MonsterResistanceType flag);
template std::shared_ptr<monster_flag_checker<MonsterAbilityType>> make_general_flag_checker(MonsterAbilityType flag);
template std::shared_ptr<monster_flag_checker<MonraceKindType>> make_general_flag_checker(MonraceKindType flag);
template std::shared_ptr<monster_flag_checker<MonsterAuraType>> make_general_flag_checker(MonsterAuraType flag);
template std::shared_ptr<monster_flag_checker<MonsterAbilityType>> make_general_flag_checker(std::vector<MonsterAbilityType> flag);

template <typename T>
std::shared_ptr<monster_flag_checker<T>> make_general_flag_checker(T flag)
{
    return std::make_shared<monster_flag_checker<T>>(flag);
}

template <typename T>
std::shared_ptr<monster_flag_checker<T>> make_general_flag_checker(std::vector<T> flag)
{
    return std::make_shared<monster_flag_checker<T>>(flag);
}

std::unique_ptr<monster_flag_checker<BIT_FLAGS>> make_general_flag_checker(BIT_FLAGS flag, int num)
{
    return std::make_unique<monster_flag_checker<BIT_FLAGS>>(flag, num);
}

template <typename T>
monster_flag_checker<T>::monster_flag_checker(T flag)
    : flag({ flag })
    , num(0)
{
}

template <typename T>
monster_flag_checker<T>::monster_flag_checker(T flag, int num)
    : flag({ flag })
    , num(num)
{
}

template <typename T>
monster_flag_checker<T>::monster_flag_checker(std::vector<T> flag)
    : flag(flag)
    , num(0)
{
}

template <typename T>
bool monster_flag_checker<T>::flag_check(monster_race * /* Unused */)
{
    return false;
}

template <>
bool monster_flag_checker<MonsterResistanceType>::flag_check(monster_race *r_ptr)
{
    return r_ptr->resistance_flags.has_any_of(this->flag.begin(), this->flag.end());
}

template <>
bool monster_flag_checker<MonsterAuraType>::flag_check(monster_race *r_ptr)
{
    return r_ptr->aura_flags.has_any_of(this->flag.begin(), this->flag.end());
}

template <>
bool monster_flag_checker<MonsterAbilityType>::flag_check(monster_race *r_ptr)
{
    return r_ptr->ability_flags.has_any_of(this->flag.begin(), this->flag.end());
}

template <>
bool monster_flag_checker<MonraceKindType>::flag_check(monster_race *r_ptr)
{
    return r_ptr->race_kind_flags.has_any_of(this->flag.begin(), this->flag.end());
}

template <>
bool monster_flag_checker<MonraceDropType>::flag_check(monster_race *r_ptr)
{
    return r_ptr->drop_flags.has_any_of(this->flag.begin(), this->flag.end());
}

template <>
bool monster_flag_checker<BIT_FLAGS>::flag_check(monster_race *r_ptr)
{
    BIT_FLAGS *flag_ptr;

    switch (this->num) {
    case 1:
        flag_ptr = &r_ptr->flags1;
        break;
    case 2:
        flag_ptr = &r_ptr->flags2;
        break;
    case 3:
        flag_ptr = &r_ptr->flags3;
        break;
    case 7:
        flag_ptr = &r_ptr->flags7;
        break;
    case 8:
        flag_ptr = &r_ptr->flags8;
        break;
    case 9:
        flag_ptr = &r_ptr->flags9;
        break;
    default:
        return false;
    }

    for (auto f : this->flag) {
        if (any_bits(*flag_ptr, f))
            return true;
    }
    return false;
}

monster_many_flag_checker::monster_many_flag_checker(std::vector<std::shared_ptr<monster_flag_checker_abstrct>> flag)
{
    for (auto &f : flag) {
        this->flag.push_back(std::move(f));
    }
}

bool monster_many_flag_checker::flag_check(monster_race *r_ptr)
{
    for (auto &f : this->flag)
        if (!f->flag_check(r_ptr))
            return false;
    return true;
}

monster_flag_checker_with_func::monster_flag_checker_with_func(std::function<bool(monster_race *)> func)
    : func(func)
{
}

bool monster_flag_checker_with_func::flag_check(monster_race *r_ptr)
{
    return func(r_ptr);
}

bool can_cast_spell(monster_race *r_ptr)
{
    return r_ptr->freq_spell != 0;
}

bool can_not_cast_spell(monster_race *r_ptr)
{
    return !can_cast_spell(r_ptr);
}

bool has_speed(monster_race *r_ptr)
{
    return r_ptr->speed >= 110;
}

bool can_search(monster_race *r_ptr)
{
    return 25 >= r_ptr->sleep;
}
