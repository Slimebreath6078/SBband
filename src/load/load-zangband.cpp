#include "load/load-util.h"
#include "player/attack-defense-types.h"
#include "system/player-type-definition.h"

void set_zangband_action(player_type *player_ptr)
{
    byte tmp8u;
    rd_byte(&tmp8u);
    if (tmp8u)
        player_ptr->action = ACTION_LEARN;
}
