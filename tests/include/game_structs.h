#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "../../include/stds.h"

typedef struct Stage Stage;

struct Stage {
    Trail trailHead, *trailTail;
};

#endif