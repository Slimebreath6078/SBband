#pragma once

#include "system/angband.h"
#include "system/monster-race-definition.h"
#include <functional>

class monster_flag_checker_abstrct {
public:
    monster_flag_checker_abstrct() = default;
    virtual ~monster_flag_checker_abstrct() = default;
    void operator=(monster_flag_checker_abstrct &) = delete;
    virtual bool flag_check(monster_race *r_ptr) = 0;
};

template <typename T>
class monster_flag_checker : public monster_flag_checker_abstrct {
public:
    monster_flag_checker(T flag);
    monster_flag_checker(T flag, int num);
    monster_flag_checker(std::vector<T> flag);
    monster_flag_checker() = delete;
    ~monster_flag_checker() = default;
    monster_flag_checker<T> operator=(monster_flag_checker<T> &) = delete;
    bool flag_check(monster_race *r_ptr);

private:
    std::vector<T> flag;
    int num; /*フラグの番号。enum class化が終わったら消す*/
};

class monster_many_flag_checker : public monster_flag_checker_abstrct {
public:
    monster_many_flag_checker(std::vector<std::shared_ptr<monster_flag_checker_abstrct>> flag);
    monster_many_flag_checker() = delete;
    ~monster_many_flag_checker() = default;
    monster_many_flag_checker operator=(monster_many_flag_checker &) = delete;
    bool flag_check(monster_race *r_ptr);

private:
    std::vector<std::shared_ptr<monster_flag_checker_abstrct>> flag;
};

class monster_flag_checker_with_func : public monster_flag_checker_abstrct {
public:
    monster_flag_checker_with_func(std::function<bool(monster_race *)> func);
    monster_flag_checker_with_func() = delete;
    ~monster_flag_checker_with_func() = default;
    monster_flag_checker_with_func operator=(monster_flag_checker_with_func &) = delete;
    bool flag_check(monster_race *r_ptr);

private:
    std::function<bool(monster_race *)> func;
};

template <typename T>
std::shared_ptr<monster_flag_checker<T>> make_general_flag_checker(T flag);
template <typename T>
std::shared_ptr<monster_flag_checker<T>> make_general_flag_checker(std::vector<T> flag);
std::unique_ptr<monster_flag_checker<BIT_FLAGS>> make_general_flag_checker(BIT_FLAGS flag, int num);

bool can_cast_spell(monster_race *r_ptr);
bool can_not_cast_spell(monster_race *r_ptr);
bool has_speed(monster_race *r_ptr);
bool can_search(monster_race *r_ptr);
