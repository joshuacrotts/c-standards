#ifndef SQUARE_PARTICLE_H
#define SQUARE_PARTICLE_H

#include "../../../include/draw.h"
#include "../../../include/stds.h"
#include "../../../include/vec2.h"

extern struct particle_t square_particle_init( float x, float y );

extern void square_particle_update( struct particle_t *p );

extern void square_particle_draw( struct particle_t *p );

#endif // SQUARE_PARTICLE_H