#ifndef ENEMY_H
#define ENEMY_H

#include "../../../include/stds.h"
#include "../../../include/draw.h"
#include "../../../include/trail.h"

extern struct entity_t*
add_enemy( float x, float y );

extern void
enemy_update( struct entity_t *e );

extern void
enemy_draw( struct entity_t *e );

#endif // ENEMY_H