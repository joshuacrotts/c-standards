#ifndef PLAYER_H
#define PLAYER_H

#include "../../include/stds.h"
#include "../../include/draw.h"
#include "../../include/trail.h"

Entity* player;
extern App app;

extern void init_player(void);
extern void player_update(void);
extern void player_draw(void);

#endif