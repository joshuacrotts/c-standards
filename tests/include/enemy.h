#ifndef ENEMY_H
#define ENEMY_H

#include "../../include/stds.h"
#include "../../include/draw.h"
#include "../../include/trail.h"

extern entity_t*
add_enemy(float, float);


extern void
enemy_update(entity_t*);


extern void
enemy_draw(entity_t*);


#endif