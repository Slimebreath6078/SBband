#include "market/Fix/flag-checker.h"
#include "util/bit-flags-calculator.h"
#include <numeric>

const flgchk_std::stream flgchk_std::null_stream = flgchk_std::stream();
const flgchk_std::stream_end flgchk_std::end = flgchk_std::stream_end();

void flgchk_std::stream::check_symbol(const char &symbol)
{
    switch (symbol) {
    case '(':
        this->priority++;
        break;
    case ')':
        this->priority--;
        break;
    case '&':
        add_op(token_kind::AND, this->checker);
        break;
    case '|':
        add_op(token_kind::OR, this->checker);
        break;
    case '^':
        add_op(token_kind::XOR, this->checker);
        break;
    case '~':
        add_op(token_kind::NOT, this->checker);
        break;
    default:
        throw std::runtime_error("Unknown symbol in flag_checker.");
    }

    if (this->priority < 0)
        throw std::runtime_error("Priority is minus in flag_checker.");
}

bool flgchk_std::chk_func::proc(monster_race *r_ptr)
{
    return method(r_ptr);
}

bool flgchk_std::bit_flags::proc(monster_race *r_ptr)
{
    BIT_FLAGS *r_flag;
    switch (num) {
    case 1:
        r_flag = &r_ptr->flags1;
        break;
    case 2:
        r_flag = &r_ptr->flags2;
        break;
    case 3:
        r_flag = &r_ptr->flags3;
        break;
    case 7:
        r_flag = &r_ptr->flags7;
        break;
    case 8:
        r_flag = &r_ptr->flags8;
        break;
    case 9:
        r_flag = &r_ptr->flags9;
        break;
    default:
        throw std::runtime_error("Invalid number of r_flags.");
    };

    return any_bits(*r_flag, flag);
}

void flgchk_std::op_abstrct::sort()
{
    const auto func = [kind = this->kind](std::shared_ptr<token_abstrct> checker, auto pop, auto push) {
        checker->sort();
        if (checker->kind == kind) {
            const auto lis = checker->get_list();

            pop();
            for (const auto &l : lis) {
                push(l);
            }
        }
    };

    func(
        checker.front(), [&checker = this->checker]() { checker.pop_front(); }, [&checker = this->checker](std::shared_ptr<token_abstrct> ptr) { checker.push_front(ptr); });
    func(
        checker.back(), [&checker = this->checker]() { checker.pop_back(); }, [&checker = this->checker](std::shared_ptr<token_abstrct> ptr) { checker.push_back(ptr); });
}

bool flgchk_std::op_abstrct::proc(monster_race *r_ptr)
{
    return std::transform_reduce(
        this->checker.begin(), this->checker.end(), this->first_result, [calc_func = this->calc_func](bool first, bool second) { return calc_func(first, second); }, [r_ptr](auto &c) { return c->proc(r_ptr); });
}

bool flgchk_std::op_not::proc(monster_race *r_ptr)
{
    return !checker->proc(r_ptr);
}

bool flgchk_std::op_count::proc(monster_race *r_ptr)
{
    auto result = std::transform_reduce(
        this->checker.begin(), this->checker.end(), 0, [](int first, int second) { return first + second; }, [r_ptr](auto &c) { 
            if(c->proc(r_ptr)){
                return 1;
                } else {
                    return 0;
                    } });

    return this->compare(this->count, result);
}

void flgchk_std::stream::add_op(token_kind kind, std::shared_ptr<token_abstrct> &ptr)
{
    if (!ptr)
        throw std::runtime_error("The flag operator has no right.");

    if (this->priority * enum2i(token_kind::MAX) + enum2i(kind) < ptr->priority * enum2i(token_kind::MAX) + enum2i(ptr->kind)) {
        std::shared_ptr<token_abstrct> token = make_op_token(kind);

        assert(token);

        token->push(std::move(ptr));
        ptr = std::move(token);
    } else {
        add_op(kind, ptr->right());
    }
}

void flgchk_std::stream::push_checker_token(std::shared_ptr<token_abstrct> checker)
{
    auto *ptr = &this->checker;

    if (!(*ptr)) {
        this->checker = checker;
        return;
    }

    while (true) {
        if (!(*ptr)->right())
            break;
        ptr = &(*ptr)->right();
    }
    (*ptr)->push(checker);
}

std::shared_ptr<flgchk_std::token_abstrct> flgchk_std::stream::make_op_token(token_kind kind)
{
    switch (kind) {
    case token_kind::AND:
        return std::make_unique<op_and>(this->priority);
    case token_kind::OR:
        return std::make_unique<op_or>(this->priority);
    case token_kind::XOR:
        return std::make_unique<op_xor>(this->priority);
    case token_kind::NOT:
        return std::make_unique<op_not>(this->priority);
    default:
        return nullptr;
    }
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
