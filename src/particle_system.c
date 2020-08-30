/**
 * @file particle_system.c
 * @author Joshua Crotts
 * @date July 6 2020
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * @section DESCRIPTION
 *
 * This file defines the particle system backed in static memory.
 */
#include "../include/particle_system.h"

/**
 * Initializes a particle system with a size of max particles.
 *
 * @param int32_t max number of particles that can be spawned in the system at
 *        any given time.
 *
 * @return particle_system_t * pointer to emitter.
 */
struct particle_system_t *
Stds_CreateParticleSystem( const int32_t max_particles ) {
  struct particle_system_t *ps;
  ps = malloc( sizeof( struct particle_system_t ) );

  if ( ps == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                 "Error: could not allocate memory for particle_system_t struct: %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( ps, 0, sizeof( struct particle_system_t ) );

  ps->particles     = malloc( sizeof( struct particle_t ) * max_particles );
  ps->max_particles = max_particles;
  ps->alive_count   = 0;
  ps->dead_index    = 0;

  return ps;
}

/**
 * Adds a particle to the particle system. Returns 0 (PS_SUCCESS) if a successful insertion
 * occurred, 1 (PS_FULL) if the system is full, and 2 (PS_INVALID_FP) if the particle has
 * invalid (most likely undefined) function pointers for particle_update and particle_draw.
 *
 * @param particle_system_t * pointer to particle system to insert particle into.
 * @param particle_t * pointer to particle to insert.
 *
 * @return void.
 */
int32_t
Stds_InsertParticle( struct particle_system_t *ps, const struct particle_t *p ) {
  if ( ps->alive_count >= ps->max_particles - 1 ) {
    return PS_FULL;
  }

  /* Checks to ensure the function pointers are defined as they are
     used in the update procedures. NOTE: THESE WILL NOT WORK WITHOUT A
     "CONSTRUCTOR" for the particles initializing the FP to NULL.*/
  if ( !p->particle_update || !p->particle_draw ) {
    return PS_INVALID_FP;
  }

  ps->particles[( ps->alive_count )++] = *p;
  return PS_SUCCESS;
}

/**
 * Updates the particle system. The programmer is in charge of determining
 * when a particle is dead or not. The system only updates and swaps the particles.
 * When a particle p dies, it is swapped with the last particle in the system, so it
 * won't be updated any further. In summary, dead particles are at the right-side
 * of the system, and alive particles are on the left.
 *
 * @param particle_system * pointer to system.
 *
 * @return void.
 */
void
Stds_ParticleSystemUpdate( struct particle_system_t *ps ) {
  for ( uint32_t i = 0; i < ps->alive_count; i++ ) {
    struct particle_t *p = &ps->particles[i];
    if ( p->particle_update ) {
      p->particle_update( p );
    } else {
      printf( "Error! p->particle_update function pointer is undefined.\n" );
      exit( EXIT_FAILURE );
    }

    if ( p->flags & STDS_DEATH_MASK ) {
      /*  Find the rear of the alive particles and grab it. */
      ps->dead_index                   = --( ps->alive_count );
      struct particle_t *back_particle = &ps->particles[ps->dead_index];

      /* Swap particles. */
      struct particle_t tmp = *back_particle;
      *back_particle        = *p;
      *p                    = tmp;
    }
  }
}

/**
 * Renders all particles in the system. Make sure your particles have
 * the function pointer particle_draw defined!
 *
 * @param particle_system_t * pointer to particle system.
 *
 * @return void.
 */
void
Stds_ParticleSystemDraw( const struct particle_system_t *ps ) {
  for ( uint32_t i = 0; i < ps->alive_count; i++ ) {
    struct particle_t *p = &ps->particles[i];
    if ( p->particle_draw ) {
      p->particle_draw( p );
    } else {
      printf( "Error! p->particle_draw is not defined." );
      exit( EXIT_FAILURE );
    }
  }
}