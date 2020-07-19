#ifndef ANIMATED_PARTICLE_H
#define ANIMATED_PARTICLE_H

#include "../../include/animation.h"
#include "../../include/stds.h"

extern struct particle_t animated_particle_init( float x, float y );

extern void animated_particle_update( struct particle_t *p );

extern void animated_particle_draw( struct particle_t *p );

#endif // ANIMATED_PARTICLE_H