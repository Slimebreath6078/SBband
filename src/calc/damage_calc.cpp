#include "calc/damage_calc.h"

/*!
 * @brief モンスターの使う呪文の威力を決定する /
 * @param dam 定数値
 * @param dice_num ダイス数
 * @param dice_side ダイス面
 * @param mult ダイス倍率
 * @param div ダイス倍率
 * @param TYPE  DAM_MAXで最大値を返し、DAM_MINで最小値を返す。DAM_ROLLはダイスを振って値を決定する。
 * @return 攻撃呪文のダメージを返す。攻撃呪文以外は-1を返す。
 */
HIT_POINT damage_roll(HIT_POINT dam, int dice_num, int dice_side, int mult, int div, damage_flag_type TYPE)
{
    switch (TYPE) {
    case damage_flag_type::DAM_MAX:
        dam += maxroll(dice_num, dice_side) * mult / div;
        break;
    case damage_flag_type::DAM_MIN:
        dam += dice_num * 1 * mult / div;
        break;
    case damage_flag_type::DAM_ROLL:
        dam += damroll(dice_num, dice_side) * mult / div;
        break;
    case damage_flag_type::DICE_NUM:
        return dice_num;
    case damage_flag_type::DICE_SIDE:
        return dice_side;
    case damage_flag_type::DICE_MULT:
        return mult;
    case damage_flag_type::DICE_DIV:
        return div;
    case damage_flag_type::BASE_DAM:
        return dam;
    }

    if (dam < 1)
        dam = 1;
    return dam;
}
