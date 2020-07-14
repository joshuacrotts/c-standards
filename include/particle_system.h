#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "stds.h"

enum { PS_SUCCESS, PS_FULL, PS_INVALID_FP };

extern particle_system_t *Stds_CreateParticleSystem( int32_t max_particles );

extern int32_t Stds_InsertParticle( particle_system_t *ps, particle_t *p );

extern void Stds_ParticleSystemUpdate( particle_system_t *ps );

extern void Stds_ParticleSystemDraw( particle_system_t *ps );

#endif // PARTICLE_SYSTEM_H