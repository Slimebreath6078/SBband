#pragma once

#include "market/Fix/flag-checker.h"
#include "system/angband.h"
#include "system/monster-race-definition.h"
#include "system/object-type-definition.h"

struct blow_dice_list {
    int dice_num;
    int dice_side;
};

enum class weapon_fix_result_type {
    DONE = 0,
    NOT_MATCH = 1,
    DUPLICATE = 2,
    FAILED = 3,
};

class tr_flag_getter_abstrct {
public:
    tr_flag_getter_abstrct(bool single);
    virtual ~tr_flag_getter_abstrct() = default;
    tr_flag_getter_abstrct(const tr_flag_getter_abstrct &) = delete;
    void operator=(tr_flag_getter_abstrct &) = delete;
    virtual tr_type get_flag() = 0;
    const bool single;
};

class tr_flag_getter : public tr_flag_getter_abstrct {
public:
    tr_flag_getter(tr_type flag);
    tr_flag_getter() = delete;
    ~tr_flag_getter() = default;
    tr_flag_getter(const tr_flag_getter &) = delete;
    tr_flag_getter operator=(tr_flag_getter &) = delete;
    tr_type get_flag();

private:
    tr_type flag;
};

/* 装備のフラグを複数の候補からランダムに取り出す関数的クラス */
class tr_flag_random_getter : public tr_flag_getter_abstrct {
public:
    tr_flag_random_getter(std::initializer_list<tr_type> flag);
    tr_flag_random_getter() = delete;
    ~tr_flag_random_getter() = default;
    tr_flag_random_getter(const tr_flag_random_getter &) = delete;
    tr_flag_random_getter operator=(tr_flag_random_getter &) = delete;
    tr_type get_flag();

private:
    std::vector<tr_type> flag;
};

/* 装備のフラグを複数の候補からランダムに取り出す関数的クラス */
class tr_flag_getter_one_in : public tr_flag_getter_abstrct {
public:
    tr_flag_getter_one_in(int range, tr_type one, tr_type other);
    tr_flag_getter_one_in() = delete;
    ~tr_flag_getter_one_in() = default;
    tr_flag_getter_one_in(const tr_flag_getter_one_in &) = delete;
    tr_flag_getter_one_in operator=(tr_flag_getter_one_in &) = delete;
    tr_type get_flag();

private:
    int range;
    tr_type one;
    tr_type other;
};

class add_hook_abstrct {
public:
    add_hook_abstrct() = default;
    virtual ~add_hook_abstrct() = default;
    add_hook_abstrct(const add_hook_abstrct &) = delete;
    void operator=(add_hook_abstrct &) = delete;
    virtual weapon_fix_result_type proc(object_type *o_ptr, monster_race *r_ptr) = 0;

protected:
    weapon_fix_result_type set_flag(object_type *o_ptr, tr_flag_getter_abstrct *tr_getter);

private:
    bool is_duplicate_flag(object_type *o_ptr, tr_type typ);
};

class add_simple_hook : public add_hook_abstrct {
public:
    add_simple_hook(tr_type tr_flag);
    add_simple_hook(std::unique_ptr<tr_flag_getter_abstrct> tr_flag);
    add_simple_hook() = delete;
    ~add_simple_hook() = default;
    add_simple_hook(const add_simple_hook &) = delete;
    add_simple_hook operator=(add_simple_hook &) = delete;
    weapon_fix_result_type proc(object_type *o_ptr, monster_race *r_ptr);

private:
    std::unique_ptr<tr_flag_getter_abstrct> tr_flag;
};

class add_check_hook : public add_hook_abstrct {
public:
    add_check_hook(std::unique_ptr<tr_flag_getter_abstrct> tr_flag, std::shared_ptr<monster_flag_checker_abstrct> flag, std::function<bool(monster_race *)> pow_check);
    add_check_hook(std::unique_ptr<tr_flag_getter_abstrct> tr_flag, std::shared_ptr<monster_flag_checker_abstrct> flag, std::function<bool(monster_race *, tr_type)> pow_check);
    add_check_hook() = delete;
    ~add_check_hook() = default;
    add_check_hook(const add_check_hook &) = delete;
    add_check_hook operator=(add_check_hook &) = delete;
    weapon_fix_result_type proc(object_type *o_ptr, monster_race *r_ptr);

private:
    std::unique_ptr<tr_flag_getter_abstrct> tr_flag;
    std::shared_ptr<monster_flag_checker_abstrct> flag;
    std::function<bool(monster_race *, tr_type)> pow_check;
};

class add_other_hook : public add_hook_abstrct {
public:
    add_other_hook(tr_type tr_other);
    add_other_hook(std::unique_ptr<tr_flag_getter_abstrct> tr_other);
    add_other_hook() = delete;
    ~add_other_hook() = default;
    add_other_hook(const add_other_hook &) = delete;
    add_other_hook operator=(add_other_hook &) = delete;
    weapon_fix_result_type proc(object_type *o_ptr, monster_race *r_ptr);

private:
    std::unique_ptr<tr_flag_getter_abstrct> tr_other;
};

void grab_flags_from_monrace(object_type *o_ptr, monster_race *r_ptr, int min, int max);
void grab_one_flag_from_monrace(object_type *o_ptr, monster_race *r_ptr);
