#ifndef COLLISION_H
#define COLLISION_H

#include "stds.h"

extern enum CollisionSide Stds_CheckAABBCollision( entity_t *a, entity_t *b );

extern bool Stds_CheckCircularCollision( circle_t *c1, circle_t *c2 );

extern void Stds_ResolveCircularCollision( circle_t *c1, circle_t *c2 );

extern bool Stds_CheckIntersection( float x1, float y1, int32_t w1, int32_t h1, float x2, float y2,
                                int32_t w2, int32_t h2 );

#endif // COLLISION_H