#ifndef COLLISION_H
#define COLLISION_H

#include "stds.h"

extern enum CollisionSide Stds_CheckAABBCollision( struct entity_t *a, struct entity_t *b );

extern bool Stds_CheckCircularCollision( struct circle_t *c1, struct circle_t *c2 );

extern void Stds_ResolveCircularCollision( struct circle_t *c1, struct circle_t *c2 );

extern bool Stds_CheckIntersection( float x1, float y1, int32_t w1, int32_t h1, float x2, float y2,
                                    int32_t w2, int32_t h2 );

#endif // COLLISION_H