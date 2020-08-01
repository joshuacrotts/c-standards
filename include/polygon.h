#ifndef POLYGON_H
#define POLYGON_H

#include "stds.h"
#include "../include/vec2.h"

extern struct app_t g_app;

extern struct polygon_t* Stds_CreatePolygon( const int32_t sides, const float size, const struct vec2_t position, const float angle );

extern void Stds_UpdatePolygon( struct polygon_t *polygon );

extern void Stds_DrawPolygon( const struct polygon_t *polygon );

extern bool Stds_CheckSATOverlap( struct polygon_t *p1, struct polygon_t *p2 );

extern void Stds_CleanUpPolygon( struct polygon_t *polygon );

extern struct polygon_t* Stds_BoundingBox( float x, float y, float w, float h, float angle );

#endif //POLYGON_H