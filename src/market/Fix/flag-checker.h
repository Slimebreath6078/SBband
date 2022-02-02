/**
 * @file flag-checker.h
 * @author 火炎の飛竜
 * @brief フラグ条件の構文木作成用のクラスをまとめたファイル
 * 構文木を作成するものとしては汎用性があるかもしれないが、
 * 無論速度もメモリもラムダ式とかよりはるかに効率が悪い
 *
 * できる構文木のイメージ
 *
 *       AND
 *     /     \
 *   OR       AND
 *  /  \     /   \
 * Ch   Ch  Ch   OR
 *              /  \
 *             Ch  Ch
 *
 * @version 0.1
 * @date 2022-02-07
 *
 *
 */
#pragma once

#include "system/angband.h"
#include "system/monster-race-definition.h"
#include <deque>
#include <functional>
#include <queue>
#include <stdexcept>
#include <tuple>

namespace flgchk_std {

/**
 * @brief トークンの種類
 * @details 優先度は昇順となっていて、
 * 現状の仕様だと同優先度は不可能。
 */
enum class token_kind {
    OR = 0,
    XOR,
    AND,
    NOT,
    CHECKER,
    MAX,
};

/**
 * @brief トークンの抽象クラス
 * @note 他でも使うならテンプレートで幅を持たせてもいいかもしれない。
 */
class token_abstrct {
public:
    token_abstrct(token_kind kind, int priority)
        : kind(kind)
        , priority(priority)
    {
    }
    token_abstrct() = delete;
    virtual ~token_abstrct() = default;
    virtual bool proc(monster_race *r_ptr) = 0;
    virtual void push(const std::shared_ptr<token_abstrct> checker) = 0;
    virtual std::shared_ptr<token_abstrct> &right() = 0;
    virtual const std::deque<std::shared_ptr<token_abstrct>> get_list()
    {
        return std::deque<std::shared_ptr<token_abstrct>>{ nullptr };
    };
    virtual void sort(){};

    const token_kind kind;
    const int priority;
};

/**
 * @brief 条件演算子の抽象クラス
 * @note 他でも使うならテンプレートで幅を持たせてもいいかもしれない。
 */
class checker_abstrct : public token_abstrct {
public:
    checker_abstrct(int priority)
        : token_abstrct(token_kind::CHECKER, priority)
    {
    }
    checker_abstrct() = delete;
    virtual ~checker_abstrct() = default;
    virtual bool proc(monster_race *r_ptr) = 0;
    void push(const std::shared_ptr<token_abstrct>) final {}
    std::shared_ptr<token_abstrct> &right() final
    {
        return dummy;
    }
    const std::deque<std::shared_ptr<token_abstrct>> get_list() final
    {
        return std::deque<std::shared_ptr<token_abstrct>>{ nullptr };
    }
    void sort() final
    {
    }

private:
    std::shared_ptr<token_abstrct> dummy;
};

/**
 * @brief 一つのフラグを判定する具象クラス
 * 基本的にこれを使っていく
 *
 * @tparam T 判定する enum class の型
 */
template <typename T>
class single : public checker_abstrct {
public:
    single(int priority, T typ)
        : checker_abstrct(priority)
        , typ(typ)
    {
    }
    single() = delete;
    bool proc(monster_race *r_ptr) override
    {
        return r_ptr->get_flag<T>().has(typ);
    }

private:
    T typ;
};

class chk_func : public checker_abstrct {
public:
    chk_func(int priority, std::function<bool(monster_race *)> method)
        : checker_abstrct(priority)
        , method(method)
    {
    }
    chk_func() = delete;
    bool proc(monster_race *r_ptr) override;

private:
    std::function<bool(monster_race *)> method;
};

/**
 * @brief BIT_FLAGS で管理されているフラグの一つを判定する具象クラス
 * @details リファクタリング終わったら消す
 */
class bit_flags : public checker_abstrct {
public:
    bit_flags(int priority, int num, BIT_FLAGS flag)
        : checker_abstrct(priority)
        , num(num)
        , flag(flag)
    {
    }
    bit_flags() = delete;
    bool proc(monster_race *r_ptr) override;

private:
    const int num;
    const BIT_FLAGS flag;
};

/**
 * @brief 演算子の基礎クラス（ NOT を除く）
 * @details NOT はいろいろ特殊なのでここからは継承しない
 */
class op_abstrct : public token_abstrct {
public:
    op_abstrct(token_kind kind, int priority, bool first_result, std::function<bool(bool, bool)> calc_func)
        : token_abstrct(kind, priority)
        , first_result(first_result)
        , calc_func(calc_func)
    {
    }
    op_abstrct() = delete;
    virtual ~op_abstrct() = default;

    virtual bool proc(monster_race *r_ptr) override;
    void push(const std::shared_ptr<token_abstrct> checker) override
    {
        this->checker.push_back(checker);
    }
    std::shared_ptr<token_abstrct> &right() override
    {
        if (checker.size() < 2) {
            return dummy;
        }
        return checker.back();
    }
    const std::deque<std::shared_ptr<token_abstrct>> get_list() override
    {
        return checker;
    }
    void sort() override;

protected:
    std::deque<std::shared_ptr<token_abstrct>> checker;
    const bool first_result;
    std::function<bool(bool, bool)> calc_func;
    std::shared_ptr<token_abstrct> dummy;
};

/**
 * @brief AND トークン
 * @details 二つ以上の条件トークンの間に入れ、それらの全てが true の場合に true を返す
 * 使い方は概ねビット演算子の AND と同じ
 */
class op_and : public op_abstrct {
public:
    op_and(int priority)
        : op_abstrct(token_kind::AND, priority, true, [](bool result, bool result2) { return result && result2; })
    {
    }
    op_and() = delete;
    ~op_and() = default;
};

/**
 * @brief OR トークン
 * @details 二つ以上の条件トークンの間に入れ、それらの一つ以上が true の場合に true を返す
 * 使い方は概ねビット演算子の OR と同じ
 */
class op_or : public op_abstrct {
public:
    op_or(int priority)
        : op_abstrct(token_kind::OR, priority, false, [](bool result, bool result2) { return result || result2; })
    {
    }
    op_or() = delete;
    ~op_or() = default;
};

/**
 * @brief XOR トークン('^')
 *
 * @details 二つの条件トークンの間に入れ、どちらかのみが true の場合に true を返す
 * 例えば
 * (A ^ B)
 * は A または B のどちらかのみ true の場合に true を返す
 *
 * (A ^ B ^ C)
 * の場合は A, B, C のどれか一つか全て（奇数個）がtrueの時のみ true を返す
 */
class op_xor : public op_abstrct {
public:
    op_xor(int priority)
        : op_abstrct(token_kind::XOR, priority, false, [](bool result, bool result2) { return result != result2; })
    {
    }
    op_xor() = delete;
    ~op_xor() = default;
};

class op_not : public token_abstrct {
public:
    op_not(int priority)
        : token_abstrct(token_kind::NOT, priority){};
    op_not() = delete;
    ~op_not() = default;
    bool proc(monster_race *r_ptr) override;
    void push(const std::shared_ptr<token_abstrct> checker) override
    {
        if (!checker)
            this->checker = checker;
    }
    std::shared_ptr<token_abstrct> &right() override
    {
        return this->checker;
    }
    const std::deque<std::shared_ptr<token_abstrct>> get_list() override
    {
        return std::deque<std::shared_ptr<token_abstrct>>{ checker };
    }
    void sort() override
    {
        if (checker->kind == this->kind)
            throw std::runtime_error("No allowable double-nots!");
    }

private:
    std::shared_ptr<token_abstrct> checker;
};

/**
 * @brief 合致するフラグの数で判定するトークン
 *
 * @details 便宜上演算子で定義しているが、実際は判定ノードに近い
 */
class op_count : public op_abstrct {
public:
    op_count(int priority, int count, std::function<bool(int, int)> compare)
        : op_abstrct(token_kind::CHECKER, priority, true, [](bool, bool) { return false; })
        , count(count)
        , compare(compare)
    {
    }
    op_count() = delete;
    ~op_count() = default;
    bool proc(monster_race *r_ptr) override;

private:
    int count;
    std::function<bool(int, int)> compare;
};

/**
 * @brief 複数のフラグの条件をまとめたマニピュレータクラス
 * streamに左シフトして使う
 *
 * @tparam T 判定する enum class の型
 * @tparam MAX enum class の末端( get_back() の終端として使う)
 */
template <typename T, T MAX = T::MAX>
class multi_chk {
public:
    multi_chk(token_kind kind, std::queue<T> typs)
        : kind(kind)
        , typs(typs)
    {
        assert(typs.size() >= 2);
    }
    multi_chk() = delete;
    T get_back()
    {
        T v = typs.front();
        typs.pop();
        return v;
    }

    bool is_empty()
    {
        return typs.empty();
    }

    const token_kind kind;

private:
    std::queue<T> typs;
};

/**
 * @brief counter_chkのトークンクラス
 * @details 抽象クラスを作成してそれを継承することにより
 * 本体のテンプレート型を逐一書かずとも複数の種類のトークンを保持できる
 */
class counter_chk_abstrct {
public:
    counter_chk_abstrct() = default;
    virtual ~counter_chk_abstrct() = default;
    virtual std::shared_ptr<checker_abstrct> get_token(int priority) = 0;
};
template <typename T>
class counter_chk_symbol : public counter_chk_abstrct {
public:
    counter_chk_symbol(T flag)
        : flag(flag)
    {
    }
    counter_chk_symbol() = delete;
    ~counter_chk_symbol() = default;
    std::shared_ptr<checker_abstrct> get_token(int priority)
    {
        return std::make_shared<single<T>>(priority, this->flag);
    }

private:
    T flag;
};

/**
 * @brief 合致するフラグの数で判定をするトークンを作成するマニピュレータ
 *
 * @tparam Arg 判定をするフラグ
 */
template <typename... Arg>
class count_chk {
public:
    count_chk(int num, std::function<bool(int, int)> compare, Arg... args)
        : num(num)
        , compare(compare)
    {
        make_token(args...);
    }

    count_chk(int num, Arg... args)
        : num(num)
        , compare([](int count, int num) { return count == num; })
    {
        make_token(args...);
    }

    std::shared_ptr<checker_abstrct> get_token(int priority)
    {
        auto ptr = checker.front()->get_token(priority);
        checker.pop();
        return ptr;
    }

    bool is_end()
    {
        return checker.empty();
    }

    template <typename T, typename... Args>
    void make_token(T typ, Args... args)
    {
        checker.push(std::make_shared<counter_chk_symbol<T>>(typ));
        make_token(std::forward<Args>(args)...);
    }

    void make_token()
    {
    }

    count_chk() = delete;

    const int num;
    const std::function<bool(int, int)> compare;

private:
    std::queue<std::shared_ptr<counter_chk_abstrct>> checker;
};

/**
 * @brief BIT_FLAGS判定用のマニピュレータクラス
 * streamに左シフトして使う
 *
 */
class bit_stream {
public:
    bit_stream(BIT_FLAGS flag, int num)
        : flag(flag)
        , num(num)
    {
    }
    bit_stream() = delete;
    const BIT_FLAGS flag;
    const int num;
};

/**
 * @brief 末端用のマニピュレータクラス
 * streamに左シフトして使うと構文木を最適化（省メモリ化）する
 * その分速度は落ちるので定数向け
 */
class stream_end {
public:
    stream_end() = default;
    ~stream_end() = default;
    void operator=(const stream_end &) = delete;
};

/**
 * @brief streamクラス
 * 左シフトでフラグや専用トークンなどを入れれば
 * それに合った判定トークンや演算子トークンを作ってくれる。
 * 要するにostreamの真似事
 */
class stream {
public:
    stream()
        : priority(0){};
    ~stream() = default;
    void operator=(stream &) = delete;

    template <typename T>
    stream &operator<<(const multi_chk<T> &check)
    {
        multi_chk<T> data = check;

        this->priority++;

        push_checker_token(std::make_shared<single<T>>(this->priority, data.get_back()));
        do {
            add_op(data.kind, this->checker);
            push_checker_token(std::make_shared<single<T>>(this->priority, data.get_back()));
        } while (!data.is_empty());

        this->priority--;

        return *this;
    }

    template <typename... Arg>
    stream &operator<<(count_chk<Arg...> &&check)
    {
        std::deque<std::shared_ptr<token_abstrct>> list;
        auto ptr = std::make_shared<op_count>(this->priority, check.num, check.compare);

        while (!check.is_end()) {
            ptr->push(check.get_token(this->priority));
        }

        push_checker_token(ptr);

        return *this;
    }

    stream &operator<<(const stream_end &)
    {
        if (checker)
            checker->sort();

        return *this;
    }

    stream &operator<<(const bit_stream &stream)
    {
        push_checker_token(std::make_shared<bit_flags>(this->priority, stream.num, stream.flag));
        return *this;
    }

    stream &operator<<(const std::function<bool(monster_race *)> &func)
    {
        push_checker_token(std::make_shared<chk_func>(this->priority, func));
        return *this;
    }

    stream &operator<<(const MonsterAbilityType &typ)
    {
        push_checker_token(std::make_shared<single<MonsterAbilityType>>(this->priority, typ));
        return *this;
    }

    stream &operator<<(const MonraceKindType &typ)
    {
        push_checker_token(std::make_shared<single<MonraceKindType>>(this->priority, typ));
        return *this;
    }

    stream &operator<<(const MonsterAuraType &typ)
    {
        push_checker_token(std::make_shared<single<MonsterAuraType>>(this->priority, typ));
        return *this;
    }

    stream &operator<<(const MonsterResistanceType &typ)
    {
        push_checker_token(std::make_shared<single<MonsterResistanceType>>(this->priority, typ));
        return *this;
    }

    stream &operator<<(const MonraceDropType &typ)
    {
        push_checker_token(std::make_shared<single<MonraceDropType>>(this->priority, typ));
        return *this;
    }

    stream &operator<<(const char &symbol)
    {
        this->check_symbol(symbol);
        return *this;
    }

    stream &operator<<(const char *symbols)
    {
        for (auto &c : std::string(symbols)) {
            this->check_symbol(c);
        }
        return *this;
    }

    void check_symbol(const char &symbol);
    void push_checker_token(std::shared_ptr<token_abstrct> checker);
    std::shared_ptr<token_abstrct> make_op_token(token_kind kind);
    void add_op(token_kind kind, std::shared_ptr<token_abstrct> &ptr);
    std::deque<std::shared_ptr<token_abstrct>> optimize(token_kind kind, std::shared_ptr<token_abstrct> &ptr);
    bool proc(monster_race *r_ptr) const
    {
        if (!checker)
            return true;

        return this->checker->proc(r_ptr);
    }

private:
    std::shared_ptr<token_abstrct> checker;
    int priority;
};

template <typename T>
multi_chk<T> make_multi(token_kind kind, std::vector<T> list)
{
    std::queue<T> queue;

    for (auto &l : list)
        queue.push(l);
    return multi_chk<T>(kind, std::move(queue));
}

template <typename... Arg>
count_chk<Arg...> count_of(std::function<bool(int, int)> compare, int num, Arg... args)
{
    return count_chk<Arg...>(num, compare, args...);
}

template <typename... Arg>
count_chk<Arg...> count_of(int num, Arg... args)
{
    return count_chk<Arg...>(num, args...);
}

extern const stream null_stream;
extern const stream_end end;
}

bool can_cast_spell(monster_race *r_ptr);
bool can_not_cast_spell(monster_race *r_ptr);
bool has_speed(monster_race *r_ptr);
bool can_search(monster_race *r_ptr);
