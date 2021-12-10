#include "load/monster/monster-loader-savefile1.h"
#include "load/angband-version-comparer.h"
#include "load/load-util.h"
#include "load/monster/monster-flag-types-savefile1.h"
#include "system/monster-type-definition.h"
#include "system/player-type-definition.h"
#include "util/bit-flags-calculator.h"
#include "util/enum-converter.h"
#include "util/quarks.h"

MonsterLoader1::MonsterLoader1(PlayerType *player_ptr)
    : player_ptr(player_ptr)
{
}

/*!
 * @brief モンスターを読み込む(v3.0.0 Savefile ver10まで)
 */
void MonsterLoader1::rd_monster(monster_type *m_ptr_)
{
    this->m_ptr = m_ptr_;

    auto flags = rd_u32b();
    this->m_ptr->r_idx = rd_s16b();
    this->m_ptr->fy = rd_byte();
    this->m_ptr->fx = rd_byte();

    this->m_ptr->hp = rd_s16b();
    this->m_ptr->maxhp = rd_s16b();
    this->m_ptr->max_maxhp = rd_s16b();

    this->m_ptr->dealt_damage = rd_s32b();

    this->m_ptr->ap_r_idx = any_bits(flags, SaveDataMonsterFlagType::AP_R_IDX) ? rd_s16b() : this->m_ptr->r_idx;
    this->m_ptr->sub_align = any_bits(flags, SaveDataMonsterFlagType::SUB_ALIGN) ? rd_byte() : 0;
    this->m_ptr->mtimed[MTIMED_CSLEEP] = any_bits(flags, SaveDataMonsterFlagType::CSLEEP) ? rd_s16b() : 0;
    this->m_ptr->mspeed = rd_byte();
    this->m_ptr->energy_need = rd_s16b();
    this->m_ptr->mtimed[MTIMED_FAST] = any_bits(flags, SaveDataMonsterFlagType::FAST) ? rd_byte() : 0;
    this->m_ptr->mtimed[MTIMED_SLOW] = any_bits(flags, SaveDataMonsterFlagType::SLOW) ? rd_byte() : 0;
    this->m_ptr->mtimed[MTIMED_STUNNED] = any_bits(flags, SaveDataMonsterFlagType::STUNNED) ? rd_byte() : 0;
    this->m_ptr->mtimed[MTIMED_CONFUSED] = any_bits(flags, SaveDataMonsterFlagType::CONFUSED) ? rd_byte() : 0;
    this->m_ptr->mtimed[MTIMED_MONFEAR] = any_bits(flags, SaveDataMonsterFlagType::MONFEAR) ? rd_byte() : 0;
    this->m_ptr->target_y = any_bits(flags, SaveDataMonsterFlagType::TARGET_Y) ? rd_s16b() : 0;
    this->m_ptr->target_x = any_bits(flags, SaveDataMonsterFlagType::TARGET_X) ? rd_s16b() : 0;
    this->m_ptr->mtimed[MTIMED_INVULNER] = any_bits(flags, SaveDataMonsterFlagType::INVULNER) ? rd_byte() : 0;
    this->m_ptr->mflag.clear();
    this->m_ptr->mflag2.clear();
    if (any_bits(flags, SaveDataMonsterFlagType::SMART)) {
        rd_FlagGroup(this->m_ptr->smart, rd_byte);
    } else {
        this->m_ptr->smart.clear();
    }

    this->m_ptr->exp = any_bits(flags, SaveDataMonsterFlagType::EXP) ? rd_u32b() : 0;
    if (any_bits(flags, SaveDataMonsterFlagType::MFLAG2)) {
        rd_FlagGroup(this->m_ptr->mflag2, rd_byte);
    }

    if (any_bits(flags, SaveDataMonsterFlagType::NICKNAME)) {
        char buf[128];
        rd_string(buf, sizeof(buf));
        this->m_ptr->nickname = quark_add(buf);
    } else {
        this->m_ptr->nickname = 0;
    }

    this->m_ptr->parent_m_idx = any_bits(flags, SaveDataMonsterFlagType::PARENT) ? rd_s16b() : 0;
}
