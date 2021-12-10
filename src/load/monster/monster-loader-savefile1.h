#pragma once

#include "load/monster/monster-loader-base.h"

struct monster_type;
class PlayerType;
class MonsterLoader1 : public MonsterLoaderBase {
public:
    MonsterLoader1() = default;
    void rd_monster(monster_type *m_ptr) override;

private:
    monster_type *m_ptr = nullptr;
};
