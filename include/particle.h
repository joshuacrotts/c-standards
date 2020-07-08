#ifndef PARTICLE_H
#define PARTICLE_H

#include "draw.h"
#include "stds.h"

/**
 * Updates the particle. You need to override this function with your own implementation!
 */
extern void particle_update( particle_t *p );

/**
 * Updates the particle. You need to override this function with your own implementation!
 */
extern void particle_draw( particle_t *p );

#endif // PARTICLE_H