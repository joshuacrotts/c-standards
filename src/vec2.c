#include "../include/vec2.h"

/**
 *
 */
struct vec2_t
Stds_CreateVec2( float x, float y ) {
  struct vec2_t v;
  v.x = x;
  v.y = y;
  return v;
}

/**
 *
 */
struct vec2_t
Stds_CloneVec2( struct vec2_t *v ) {
  return Stds_CreateVec2( v->x, v->y );
}

/**
 * Adds two vectors together and returns the result as a part
 * of the first vector.
 *
 * @param vec2_t pointer to vector to add v to.
 * @param vec2_t pointer to vector that is added to u.
 *
 * @return void.
 */
void
Stds_AddVec2( struct vec2_t *u, struct vec2_t *v ) {
  u->x += v->x;
  u->y += v->y;
}

/**
 *
 */
void
Stds_SubVec2( struct vec2_t *u, struct vec2_t *v ) {
  u->x -= v->x;
  u->y -= v->y;
}

/**
 * Rotates a vec2_t by an angle in radians. The result is
 * stored in the vec2_t.
 *
 * @param vec2_t * pointer to vector to rotate.
 */
void
Stds_RotateVec2( struct vec2_t *v, float angle ) {
  v->x = v->x * cosf( angle ) - v->y * sinf( angle );
  v->y = v->x * sinf( angle ) + v->y * cosf( angle );
}

/**
 *
 */
bool
Stds_IsEqualVec2( struct vec2_t *u, struct vec2_t *v ) {
  return u->x == v->x && u->y == v->y;
}

/**
 *
 */
float
Stds_GetMagnitudeVec2( struct vec2_t *v ) {
  return sqrtf( v->x * v->x + v->y + v->y );
}

/**
 * Calculates the dot product of the two vectors.
 * 
 * @param
 * @param 
 * 
 * @return 
 */
float
Stds_DotProduct( struct vec2_t *u, struct vec2_t *v ) {
  float dot = u->x * v->x + u->y + v->y;
  float m1  = Stds_GetMagnitudeVec2( u );
  float m2  = Stds_GetMagnitudeVec2( v );

  return acosf( dot / ( m1 * m2 ) );
}

/**
 * Normalizes a vec2_t struct (ranges between 0 and 1.). 
 * The result is stored in the passing vector.
 *
 * @param vec2_t * pointer to vector to normalize.
 * 
 * @return void.
 */
void
Stds_NormalizeVec2( struct vec2_t *v ) {
  float mag = Stds_GetMagnitudeVec2( v );

  v->x /= mag;
  v->y /= mag;
}