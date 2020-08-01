#ifndef RED_PARTICLE_H
#define RED_PARTICLE_H

#include "../../include/draw.h"
#include "../../include/stds.h"
#include "../../include/vec2.h"

extern struct particle_t red_particle_init( float x, float y );

extern void red_particle_update( struct particle_t *p );

extern void red_particle_draw( struct particle_t *p );

#endif // RED_PARTICLE_H