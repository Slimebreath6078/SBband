﻿/*!
 * @brief 防具系のアイテムを強化して(恐らく床に)生成する処理
 * @date 2020/06/02
 * @author Hourier
 * @todo ちょっと長い。要分割
 */

#include "object-enchant/apply-magic-armor.h"
#include "artifact/random-art-generator.h"
#include "inventory/inventory-slot-types.h"
#include "object-enchant/object-boost.h"
#include "object-enchant/object-ego.h"
#include "object-enchant/tr-types.h"
#include "object-enchant/trc-types.h"
#include "object/object-kind-hook.h"
#include "object/object-kind.h"
#include "sv-definition/sv-armor-types.h"
#include "sv-definition/sv-protector-types.h"
#include "system/object-type-definition.h"
#include "util/bit-flags-calculator.h"
#include "view/display-messages.h"

/*
 * @brief コンストラクタ
 * @param owner_ptr プレーヤーへの参照ポインタ
 * @param o_ptr 強化を与えたいオブジェクトの構造体参照ポインタ
 * @param level 生成基準階
 * @param power 生成ランク
 */
ArmorEnchanter::ArmorEnchanter(player_type *owner_ptr, object_type *o_ptr, DEPTH level, int power)
    : ArmorEnchanterBase{ o_ptr, level, power }
    , owner_ptr(owner_ptr)
{
}

/*!
 * @brief 防具系オブジェクトに生成ランクごとの強化を与えるサブルーチン
 * Apply magic to an item known to be "armor"
 */
void ArmorEnchanter::apply_magic()
{
    switch (this->o_ptr->tval) {
    case TV_DRAG_ARMOR: {
        /* power > 2 is debug only */
        if (one_in_(50) || (this->power > 2))
            become_random_artifact(this->owner_ptr, this->o_ptr, false);
        break;
    }
    case TV_HARD_ARMOR:
    case TV_SOFT_ARMOR: {
        if (this->power > 1) {
            if ((this->o_ptr->tval == TV_SOFT_ARMOR) && (this->o_ptr->sval == SV_ROBE) && (randint0(100) < 15)) {
                if (one_in_(5)) {
                    this->o_ptr->name2 = EGO_YOIYAMI;
                    this->o_ptr->k_idx = lookup_kind(TV_SOFT_ARMOR, SV_YOIYAMI_ROBE);
                    this->o_ptr->sval = SV_YOIYAMI_ROBE;
                    this->o_ptr->ac = 0;
                    this->o_ptr->to_a = 0;
                } else {
                    this->o_ptr->name2 = EGO_PERMANENCE;
                }

                break;
            }

            /* power > 2 is debug only */
            if (one_in_(20) || (this->power > 2)) {
                become_random_artifact(this->owner_ptr, this->o_ptr, false);
                break;
            }

            while (true) {
                bool okay_flag = true;
                this->o_ptr->name2 = get_random_ego(INVEN_BODY, true);
                switch (this->o_ptr->name2) {
                case EGO_DWARVEN:
                    if (this->o_ptr->tval != TV_HARD_ARMOR) {
                        okay_flag = false;
                    }

                    break;
                case EGO_DRUID:
                    if (this->o_ptr->tval != TV_SOFT_ARMOR) {
                        okay_flag = false;
                    }

                    break;
                default:
                    break;
                }

                if (okay_flag)
                    break;
            }
        } else if (this->power < -1) {
            while (true) {
                bool okay_flag = true;
                this->o_ptr->name2 = get_random_ego(INVEN_BODY, false);

                switch (this->o_ptr->name2) {
                case EGO_A_DEMON:
                case EGO_A_MORGUL:
                    break;
                default:
                    msg_print(_("エラー：適した呪い鎧エゴがみつかりませんでした.", "Error:Suitable cursed armor ego not found."));
                    okay_flag = true;
                    break;
                }

                if (okay_flag)
                    break;
            }
        }

        break;
    }
    default:
        break;
    }
}

void ArmorEnchanter::enchant() {}

void ArmorEnchanter::give_ego_index() {}

void ArmorEnchanter::give_high_ego_index() {}

void ArmorEnchanter::give_cursed() {}
