#ifndef PLAYER_H
#define PLAYER_H

#include "../../include/animation.h"
#include "../../include/draw.h"
#include "../../include/stds.h"
#include "../../include/trail.h"

extern struct entity_t *player;
extern struct app_t app;

extern void init_player( void );

extern void player_update( void );

extern void player_draw( void );

#endif // PLAYER_H