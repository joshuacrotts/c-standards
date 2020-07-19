#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "../../include/stds.h"

struct stage_t {
    struct trail_t trail_head, *trail_tail;
    struct entity_t enemy_head, *enemy_tail;
};

#endif // GAME_STRUCTS_H
