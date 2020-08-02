#ifndef COLLISION_H
#define COLLISION_H

#include "stds.h"

#define SAT_VERTEX_NUMBER 4

extern enum CollisionSide Stds_CheckAABBCollision( struct entity_t *a, struct entity_t *b );

extern bool Stds_CheckCircularCollision( const struct circle_t *c1, const struct circle_t *c2 );

extern void Stds_ResolveCircularCollision( struct circle_t *c1, struct circle_t *c2 );

extern bool Stds_CheckIntersection( const float x1, const float y1, const int32_t w1,
                                    const int32_t h1, const float x2, const float y2,
                                    const int32_t w2, const int32_t h2 );

extern bool Stds_PointVsRect( const struct vec2_t *point, const SDL_FRect *rect );

extern bool Stds_RectVsRect( const SDL_FRect *r1, const SDL_FRect *r2 );

extern bool Stds_RayVsRect( const struct vec2_t *ray, const struct vec2_t *ray_direction,
                            const SDL_FRect *rect, struct vec2_t *contact_point,
                            struct vec2_t *contact_norm, float *hitNear );

extern bool Stds_AdvRectVsRect( const SDL_FRect *r1, const SDL_FRect *r2,
                                struct vec2_t *contact_point, struct vec2_t *contact_norm,
                                float *hitNear, const struct vec2_t *r1_velocity );

extern bool Stds_CheckSATOverlap( struct polygon_t *p1, struct polygon_t *p2 );

#endif // COLLISION_H