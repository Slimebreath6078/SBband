﻿#pragma once

#include "system/angband.h"
#include "effect/attribute-types.h"

struct player_type;
bool fire_ball(player_type *player_ptr, AttributeType typ, DIRECTION dir, HIT_POINT dam, POSITION rad);
bool fire_breath(player_type *player_ptr, AttributeType typ, DIRECTION dir, HIT_POINT dam, POSITION rad);
bool fire_rocket(player_type *player_ptr, AttributeType typ, DIRECTION dir, HIT_POINT dam, POSITION rad);
bool fire_ball_hide(player_type *player_ptr, AttributeType typ, DIRECTION dir, HIT_POINT dam, POSITION rad);
bool fire_meteor(player_type *player_ptr, MONSTER_IDX who, AttributeType typ, POSITION x, POSITION y, HIT_POINT dam, POSITION rad);
bool fire_bolt(player_type *player_ptr, AttributeType typ, DIRECTION dir, HIT_POINT dam);
bool fire_blast(player_type *player_ptr, AttributeType typ, DIRECTION dir, DICE_NUMBER dd, DICE_SID ds, int num, int dev);
bool fire_beam(player_type *player_ptr, AttributeType typ, DIRECTION dir, HIT_POINT dam);
bool fire_bolt_or_beam(player_type *player_ptr, PERCENTAGE prob, AttributeType typ, DIRECTION dir, HIT_POINT dam);
bool project_hook(player_type *player_ptr, AttributeType typ, DIRECTION dir, HIT_POINT dam, BIT_FLAGS flg);
