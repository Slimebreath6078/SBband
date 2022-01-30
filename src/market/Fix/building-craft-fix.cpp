#include "market/Fix/building-craft-fix.h"
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
#include "market/Fix/weapon-kansen.h"
#include "market/building-util.h"
#include "monster-race/monster-race.h"
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
#include "sv-definition/sv-corpse-types.h"
#include "sv-definition/sv-other-types.h"
#include "sv-definition/sv-weapon-types.h"
#include "system/monster-race-definition.h"
#include "system/object-type-definition.h"
#include "system/player-type-definition.h"
#include "term/screen-processor.h"
#include "util/bit-flags-calculator.h"
#include "view/display-messages.h"
#include <algorithm>
#include <random>

/*!
 * @brief 修復材料のオブジェクトから修復対象に特性を移植する。
 * @param to_ptr 修復対象オブジェクトの構造体の参照ポインタ。
 * @param from_ptr 修復材料オブジェクトの構造体の参照ポインタ。
 * @return 修復対象になるならTRUEを返す。
 */
static void give_one_ability_of_object(object_type *to_ptr, object_type *from_ptr)
{
    auto to_flgs = object_flags(to_ptr);
    auto from_flgs = object_flags(from_ptr);

    int n = 0;
    tr_type cand[TR_FLAG_MAX];
    for (int i = 0; i < TR_FLAG_MAX; i++) {
        switch (i) {
        case TR_IGNORE_ACID:
        case TR_IGNORE_ELEC:
        case TR_IGNORE_FIRE:
        case TR_IGNORE_COLD:
        case TR_ACTIVATE:
        case TR_RIDING:
        case TR_THROW:
        case TR_SHOW_MODS:
        case TR_HIDE_TYPE:
        case TR_XXX_93:
        case TR_XXX_94:
        case TR_FULL_NAME:
        case TR_FIXED_FLAVOR:
            break;
        default:
            auto tr_flag = i2enum<tr_type>(i);
            if (from_flgs.has(tr_flag) && to_flgs.has_not(tr_flag)) {
                if (!(TR_PVAL_FLAG_MASK.has(tr_flag) && (from_ptr->pval < 1)))
                    cand[n++] = tr_flag;
            }
        }
    }

    if (n <= 0)
        return;

    auto tr_idx = cand[randint0(n)];
    to_ptr->art_flags.set(tr_idx);
    if (TR_PVAL_FLAG_MASK.has(tr_idx))
        to_ptr->pval = std::max<short>(to_ptr->pval, 1);
    auto bmax = std::min<short>(3, std::max<short>(1, 40 / (to_ptr->dd * to_ptr->ds)));
    if (tr_idx == TR_BLOWS)
        to_ptr->pval = std::min<short>(to_ptr->pval, bmax);
    if (tr_idx == TR_SPEED)
        to_ptr->pval = std::min<short>(to_ptr->pval, 4);
}

static void initialize_fixed_weapon(KIND_OBJECT_IDX k_idx, object_type *o_ptr)
{
    object_kind *k_ptr;
    k_ptr = &k_info[k_idx];
    o_ptr->k_idx = k_idx;
    o_ptr->weight = k_ptr->weight;
    o_ptr->tval = k_ptr->tval;
    o_ptr->sval = k_ptr->sval;
    o_ptr->dd = k_ptr->dd;
    o_ptr->ds = k_ptr->ds;

    o_ptr->art_flags.set(k_ptr->flags);

    if (k_ptr->pval)
        o_ptr->pval = std::max<short>(o_ptr->pval, randint1(k_ptr->pval));
    if (k_ptr->flags.has(TR_ACTIVATE))
        o_ptr->activation_id = k_ptr->act_idx;

    if (k_ptr->flags.has(TR_BLOWS)) {
        auto bmax = std::min<short>(3, std::max<short>(1, 40 / (o_ptr->dd * o_ptr->ds)));
        o_ptr->pval = std::min<short>(o_ptr->pval, bmax);
    }
}

static void set_dice_bonus(object_type *o_ptr, int bonus_num, int bonus_side)
{

    int dd_bonus = o_ptr->dd - k_info[o_ptr->k_idx].dd + bonus_num;
    int ds_bonus = o_ptr->ds - k_info[o_ptr->k_idx].ds + bonus_side;

    if (dd_bonus > 0) {
        o_ptr->dd++;
        for (int i = 1; i < dd_bonus; i++) {
            if (one_in_(o_ptr->dd + i))
                o_ptr->dd++;
        }
    }

    if (ds_bonus > 0) {
        o_ptr->ds++;
        for (int i = 1; i < ds_bonus; i++) {
            if (one_in_(o_ptr->ds + i))
                o_ptr->ds++;
        }
    }

}

static void exceptional_weapon(object_type *o_ptr, std::function<void(object_type *)> grab_flag)
{

    if ((o_ptr->name1 == ART_NARSIL) || (o_ptr->is_random_artifact() && one_in_(1)) || (o_ptr->is_ego() && one_in_(7))) {
        if (o_ptr->is_ego()) {
            o_ptr->art_flags.set(TR_IGNORE_FIRE);
            o_ptr->art_flags.set(TR_IGNORE_ACID);
        }

        grab_flag(o_ptr);
        if (activation_index(o_ptr) == RandomArtActType::NONE)
            one_activation(o_ptr);

        if (o_ptr->name1 == ART_NARSIL) {
            one_high_resistance(o_ptr);
            one_ability(o_ptr);
        }

        msg_print(_("これはかなりの業物だったようだ。", "This blade seems to be exceptional."));
    }
}

static void repair_broken_with_body(KIND_OBJECT_IDX k_idx, object_type *o_ptr, object_type *mo_ptr)
{
    initialize_fixed_weapon(k_idx, o_ptr);

    monster_race *r_ptr = &r_info[mo_ptr->pval];

    std::vector<int> dice_num_list, dice_side_list;
    for (auto &d : r_ptr->blow) {
        if (d.d_dice > 0)
            dice_num_list.push_back(d.d_dice);
        if (d.d_side > 0)
            dice_side_list.push_back(d.d_side);
    }
    auto min_dice_num = std::min_element(dice_num_list.begin(), dice_num_list.end());
    auto max_dice_num = std::max_element(dice_num_list.begin(), dice_num_list.end());
    auto min_dice_side = std::min_element(dice_side_list.begin(), dice_side_list.end());
    auto max_dice_side = std::max_element(dice_side_list.begin(), dice_side_list.end());

    if (r_ptr->race_kind_flags.has(MonraceKindType::KAN_SEN)) {
        *min_dice_num = *min_dice_num * 3 / 2;
        *max_dice_num = *max_dice_num * 3 / 2;
        *min_dice_side = *min_dice_side * 3 / 2;
        *max_dice_side = *max_dice_side * 3 / 2;
    }

    set_dice_bonus(o_ptr, (std::max(*min_dice_num / 3, 1) + randint0(*max_dice_num - *min_dice_num) / 3) + 1, (std::max(*min_dice_side / 3, 1) + randint0(*max_dice_side - *min_dice_side) / 3) + 1);

    int max = r_ptr->level / 20 + 1;

    grab_flags_from_monrace(o_ptr, r_ptr, max / 2, max);

    o_ptr->to_d += std::max<short>(0, damroll(std::max(*min_dice_num / 2, 1) + randint0(*max_dice_num - *min_dice_num) / 3,
                                          std::max(*min_dice_side / 2, 1) + randint0(*max_dice_side - *min_dice_side) / 3));
    o_ptr->to_h += std::max<short>(0, damroll(std::max(*min_dice_num / 3, 1) + randint0(*max_dice_num - *min_dice_num) / 3,
                                          std::max(*min_dice_side / 2, 1) + randint0(*max_dice_side - *min_dice_side) / 3));
    o_ptr->to_a += std::max<short>(0, r_ptr->ac / 30);

    exceptional_weapon(o_ptr, [ptr = r_ptr](object_type *o_ptr) { grab_one_flag_from_monrace(o_ptr, ptr); });
}

static void repair_broken_with_weapon(KIND_OBJECT_IDX k_idx, object_type *o_ptr, object_type *mo_ptr)
{
    initialize_fixed_weapon(k_idx, o_ptr);

    set_dice_bonus(o_ptr, mo_ptr->dd - k_info[mo_ptr->k_idx].dd, mo_ptr->ds - k_info[mo_ptr->k_idx].ds);

    give_one_ability_of_object(o_ptr, mo_ptr);
    o_ptr->to_d += std::max(0, (mo_ptr->to_d / 3));
    o_ptr->to_h += std::max<short>(0, (mo_ptr->to_h / 3));
    o_ptr->to_a += std::max<short>(0, (mo_ptr->to_a));

    exceptional_weapon(o_ptr, [ptr = mo_ptr](object_type *o_ptr) { give_one_ability_of_object(o_ptr, ptr); });
}

/*!
 * @brief アイテム修復処理のメインルーチン / Repair broken weapon
 * @param player_ptr プレイヤーへの参照ポインタ
 * @param bcost 基本修復費用
 * @return 実際にかかった費用
 */
static PRICE repair_broken_weapon_aux(PlayerType *player_ptr, PRICE bcost)
{
    clear_bldg(0, 22);
    int row = 7;
    prt(_("修復には材料となるもう1つの武器や十分な量の鉱物が必要です。", "Hand one material weapon or a plenty of metal to repair a broken weapon."), row, 2);
    prt(_("材料に使用した物はなくなります！", "The material will disappear after repairing!!"), row + 1, 2);

    concptr q = _("どの折れた武器を修復しますか？", "Repair which broken weapon? ");
    concptr s = _("修復できる折れた武器がありません。", "You have no broken weapon to repair.");

    OBJECT_IDX item;
    object_type *o_ptr;
    o_ptr = choose_object(player_ptr, &item, q, s, (USE_INVEN | USE_EQUIP), FuncItemTester(&object_type::is_broken_weapon));
    if (!o_ptr)
        return 0;

    if (!o_ptr->is_ego() && !o_ptr->is_artifact()) {
        msg_format(_("それは直してもしょうがないぜ。", "It is worthless to repair."));
        return 0;
    }

    if (o_ptr->number > 1) {
        msg_format(_("一度に複数を修復することはできません！", "They are too many to repair at once!"));
        return 0;
    }

    char basenm[MAX_NLEN];
    describe_flavor(player_ptr, basenm, o_ptr, OD_NAME_ONLY);
    prt(format(_("修復する武器　： %s", "Repairing: %s"), basenm), row + 3, 2);

    q = _("材料となる物資は？", "Which weapon or metal for material? ");
    s = _("材料となる物資がありません。", "You have no material for the repair.");

    OBJECT_IDX mater;
    object_type *mo_ptr;
    mo_ptr = choose_object(player_ptr, &mater, q, s, (USE_INVEN | USE_EQUIP), FuncItemTester(&object_type::is_material));
    if (!mo_ptr)
        return 0;
    else if (mo_ptr->tval == ItemKindType::CORPSE && mo_ptr->sval == enum2i(CorpseSubType::FRAGMENT) && mo_ptr->number < 8) {
        msg_print(_("欠片を修復に使うためには八枚必要です。", "Repairing with fragments is possible if at least 8 them."));
        return 0;
    }

    if (mater == item) {
        msg_print(_("クラインの壷じゃない！", "This is not a Klein bottle!"));
        return 0;
    }

    describe_flavor(player_ptr, basenm, mo_ptr, OD_NAME_ONLY);
    prt(format(_("材料とする物資： %s", "Material : %s"), basenm), row + 4, 2);
    PRICE cost = bcost + object_value_real(o_ptr) * 2;
    if (!get_check(format(_("＄%dかかりますがよろしいですか？ ", "Costs %d gold, okay? "), cost)))
        return 0;

    if (player_ptr->au < cost) {
        describe_flavor(player_ptr, basenm, o_ptr, OD_NAME_ONLY);
        msg_format(_("%sを修復するだけのゴールドがありません！", "You do not have the gold to repair %s!"), basenm);
        msg_print(nullptr);
        return 0;
    }

    KIND_OBJECT_IDX k_idx;
    if (o_ptr->sval == SV_BROKEN_DAGGER) {
        int n = 1;
        k_idx = 0;
        for (const auto &k_ref : k_info) {
            if (k_ref.tval != ItemKindType::SWORD)
                continue;
            if ((k_ref.sval == SV_BROKEN_DAGGER) || (k_ref.sval == SV_BROKEN_SWORD) || (k_ref.sval == SV_POISON_NEEDLE))
                continue;
            if (k_ref.weight > 99)
                continue;

            if (one_in_(n)) {
                k_idx = k_ref.idx;
                n++;
            }
        }
    } else {
        auto tval = (one_in_(5) ? (mo_ptr->is_orthodox_melee_weapons() ? mo_ptr->tval : ItemKindType::SWORD) : ItemKindType::SWORD);
        while (true) {
            object_kind *ck_ptr;
            k_idx = lookup_kind(tval, SV_ANY);
            ck_ptr = &k_info[k_idx];

            if (tval == ItemKindType::SWORD) {
                if ((ck_ptr->sval == SV_BROKEN_DAGGER) || (ck_ptr->sval == SV_BROKEN_SWORD) || (ck_ptr->sval == SV_DIAMOND_EDGE) || (ck_ptr->sval == SV_POISON_NEEDLE))
                    continue;
            }
            if (tval == ItemKindType::POLEARM) {
                if ((ck_ptr->sval == SV_DEATH_SCYTHE) || (ck_ptr->sval == SV_TSURIZAO))
                    continue;
            }
            if (tval == ItemKindType::HAFTED) {
                if ((ck_ptr->sval == SV_GROND) || (ck_ptr->sval == SV_WIZSTAFF) || (ck_ptr->sval == SV_NAMAKE_HAMMER))
                    continue;
            }

            break;
        }
    }

    if (mo_ptr->is_orthodox_melee_weapons()) {
        repair_broken_with_weapon(k_idx, o_ptr, mo_ptr);
    } else if (mo_ptr->is_fragment_or_broken()) {
        repair_broken_with_body(k_idx, o_ptr, mo_ptr);
    }

    describe_flavor(player_ptr, basenm, o_ptr, OD_NAME_ONLY);
#ifdef JP
    msg_format("＄%dで%sに修復しました。", cost, basenm);
#else
    msg_format("Repaired into %s for %d gold.", basenm, cost);
#endif
    msg_print(nullptr);
    o_ptr->ident &= ~(IDENT_BROKEN);
    o_ptr->discount = 99;

    calc_android_exp(player_ptr);

    if (mo_ptr->tval == ItemKindType::CORPSE && mo_ptr->sval == enum2i(CorpseSubType::FRAGMENT))
        inven_item_increase(player_ptr, mater, -8);
    else
        inven_item_increase(player_ptr, mater, -1);

    inven_item_optimize(player_ptr, mater);

    player_ptr->update |= PU_BONUS;
    handle_stuff(player_ptr);
    return (cost);
}

/*!
 * @brief アイテム修復処理の過渡ルーチン / Repair broken weapon
 * @param player_ptr プレイヤーへの参照ポインタ
 * @param bcost 基本鑑定費用
 * @return 実際にかかった費用
 */
int repair_broken_weapon(PlayerType *player_ptr, PRICE bcost)
{
    PRICE cost;
    screen_save();
    cost = repair_broken_weapon_aux(player_ptr, bcost);
    screen_load();
    return cost;
}
