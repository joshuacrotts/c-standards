#ifndef VEC2_H
#define VEC2_H

#include "stds.h"

extern struct vec2_t Stds_CreateVec2( const float x, const float y );

extern struct vec2_t Stds_CloneVec2( const struct vec2_t *v );

extern void Stds_AddVec2( struct vec2_t *u, const struct vec2_t *v );

extern void Stds_SubVec2( struct vec2_t *u, const struct vec2_t *v );

extern void Stds_RotateVec2( struct vec2_t *v, const float angle );

extern bool Stds_IsEqualVec2( const struct vec2_t *u, const struct vec2_t *v );

extern float Stds_GetMagnitudeVec2( const struct vec2_t *v );

extern float Stds_DotProduct( const struct vec2_t *u, const struct vec2_t *v );

extern void Stds_NormalizeVec2( struct vec2_t *v );

extern void Stds_AddToVec2( struct vec2_t *v, const float add );

extern void Stds_SubtractToVec2( struct vec2_t *v, const float subtract );

extern void Stds_MultiplyToVec2( struct vec2_t *v, const float multiply );

extern void Stds_DivideToVec2( struct vec2_t *v, const float divide );

#endif