#include "monster-race/race-resistance-mask.h"

const EnumClassFlagGroup<MonsterResistanceType> RFR_EFF_IM_ACID_MASK = {
    MonsterResistanceType::IMMUNE_ACID,
    MonsterResistanceType::RESIST_ALL,
};

const EnumClassFlagGroup<MonsterResistanceType> RFR_EFF_IM_ELEC_MASK = {
    MonsterResistanceType::IMMUNE_ELEC,
    MonsterResistanceType::RESIST_ALL,
};

const EnumClassFlagGroup<MonsterResistanceType> RFR_EFF_IM_FIRE_MASK = {
    MonsterResistanceType::IMMUNE_FIRE,
    MonsterResistanceType::RESIST_ALL,
};

const EnumClassFlagGroup<MonsterResistanceType> RFR_EFF_IM_COLD_MASK = {
    MonsterResistanceType::IMMUNE_COLD,
    MonsterResistanceType::RESIST_ALL,
};

const EnumClassFlagGroup<MonsterResistanceType> RFR_EFF_IM_POISON_MASK = {
    MonsterResistanceType::IMMUNE_POISON,
    MonsterResistanceType::RESIST_ALL,
};

const EnumClassFlagGroup<MonsterResistanceType> RFR_EFF_RES_SHARDS_MASK = {
    MonsterResistanceType::RESIST_SHARDS,
    MonsterResistanceType::RESIST_ALL,
};

const EnumClassFlagGroup<MonsterResistanceType> RFR_EFF_RES_CHAOS_MASK = {
    MonsterResistanceType::RESIST_CHAOS,
    MonsterResistanceType::RESIST_ALL,
};

const EnumClassFlagGroup<MonsterResistanceType> RFR_EFF_RES_NEXUS_MASK = {
    MonsterResistanceType::RESIST_NEXUS,
    MonsterResistanceType::RESIST_ALL,
};
