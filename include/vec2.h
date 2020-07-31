#ifndef VEC2_H
#define VEC2_H

#include "stds.h"

extern struct vec2_t Stds_CreateVec2( float x, float y );

extern struct vec2_t Stds_CloneVec2( struct vec2_t *v );

extern void Stds_AddVec2( struct vec2_t *u, struct vec2_t *v );

extern void Stds_SubVec2( struct vec2_t *u, struct vec2_t *v );

extern void Stds_RotateVec2( struct vec2_t *v, float angle );

extern bool Stds_IsEqualVec2( struct vec2_t *u, struct vec2_t *v );

extern float Stds_GetMagnitudeVec2( struct vec2_t *v );

extern float Stds_DotProduct( struct vec2_t *u, struct vec2_t *v );

extern void Stds_NormalizeVec2( struct vec2_t *v );

#endif