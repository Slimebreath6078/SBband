#pragma once

enum class MonsterResistanceType {
    HURT_ACID = 0, /* Hurt badly by acid */
    IMMUNE_ACID = 1, /* Immunity acid */
    RESIST_ACID = 2, /* Resist acid */
    HURT_ELEC = 3, /* Hurt badly by elec */
    RESIST_ELEC = 4, /* Resist elec */
    IMMUNE_ELEC = 5, /* Immunity elec */
    HURT_FIRE = 6, /* Hurt badly by fire */
    RESIST_FIRE = 7, /* Resist fire */
    IMMUNE_FIRE = 8, /* Immunity fire */
    HURT_COLD = 9, /* Hurt badly by cold */
    RESIST_COLD = 10, /* Resist cold */
    IMMUNE_COLD = 11, /* Immunity cold */
    HURT_POISON = 12, /* Hurt badly by poison */
    RESIST_POISON = 13, /* Resist poison */
    IMMUNE_POISON = 14, /* Immunity poison */
    HURT_LITE = 15, /* Hurt badly by lite */
    RESIST_LITE = 16, /* Resist lite */
    HURT_DARK = 17, /* Hurt badly by dark */
    RESIST_DARK = 18, /* Resist dark */
    HURT_NETHER = 19, /* Hurt badly by nether */
    RESIST_NETHER = 20, /* Resist nether */
    HURT_WATER = 21, /* Hurt badly by water */
    RESIST_WATER = 22, /* Resist water */
    HURT_PLASMA = 23, /* Hurt badly by plasma */
    RESIST_PLASMA = 24, /* Resist plasma */
    HURT_SHARDS = 25, /* Hurt badly by shards */
    RESIST_SHARDS = 26, /* Resist shards */
    HURT_SOUND = 27, /* Hurt badly by sound */
    RESIST_SOUND = 28, /* Resist sound */
    HURT_CHAOS = 29, /* Hurt badly by chaos */
    RESIST_CHAOS = 30, /* Resist chaos */
    HURT_NEXUS = 31, /* Hurt badly by nexus */
    RESIST_NEXUS = 32, /* Resist nexus */
    HURT_DISENCHANT = 33, /* Hurt badly by disenchantment */
    RESIST_DISENCHANT = 34, /* Resist disenchantment */
    HURT_FORCE = 35, /* Hurt badly by force */
    RESIST_FORCE = 36, /* Resist force */
    HURT_INERTIA = 37, /* Hurt badly by inertia */
    RESIST_INERTIA = 38, /* Resist inertia */
    HURT_TIME = 39, /* Hurt badly by time */
    RESIST_TIME = 40, /* Resist time */
    HURT_GRAVITY = 41, /* Hurt badly by gravity */
    RESIST_GRAVITY = 42, /* Resist gravity */
    RESIST_ALL = 43, /* Resist all */
    RESIST_TELEPORT = 44, /* Resist teleportation */
    HURT_ROCK = 45, /* Hurt by rock remover */
    RESIST_ROCK = 46, /* Resist rock remover */
    MAX, /* Max of Resistances */
};

#define RFR_EFF_IM_ACID_MASK (RFR_IM_ACID | RFR_RES_ALL)
#define RFR_EFF_IM_ELEC_MASK (RFR_IM_ELEC | RFR_RES_ALL)
#define RFR_EFF_IM_FIRE_MASK (RFR_IM_FIRE | RFR_RES_ALL)
#define RFR_EFF_IM_COLD_MASK (RFR_IM_COLD | RFR_RES_ALL)
#define RFR_EFF_IM_POIS_MASK (RFR_IM_POIS | RFR_RES_ALL)
#define RFR_EFF_RES_SHAR_MASK (RFR_RES_SHAR | RFR_RES_ALL)
#define RFR_EFF_RES_CHAO_MASK (RFR_RES_CHAO | RFR_RES_ALL)
#define RFR_EFF_RES_NEXU_MASK (RFR_RES_NEXU | RFR_RES_ALL)
