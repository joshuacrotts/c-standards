#include "../include/vec2.h"

/**
 *
 */
struct vec2_t
Stds_CreateVec2( const float x, const float y ) {
  struct vec2_t v;
  v.x = x;
  v.y = y;
  return v;
}

/**
 *
 */
struct vec2_t
Stds_CloneVec2( const struct vec2_t *v ) {
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
Stds_AddVec2( struct vec2_t *u, const struct vec2_t *v ) {
  u->x += v->x;
  u->y += v->y;
}

/**
 * Subtracts two vectors together. The result is stored
 * in the first vector.
 * 
 * @param vec2_t * pointer to first vector.
 * @param vec2_t * pointer to second vector.
 * 
 * @return void.
 */
void
Stds_SubVec2( struct vec2_t *u, const struct vec2_t *v ) {
  u->x -= v->x;
  u->y -= v->y;
}

/**
 * Rotates a vec2_t by an angle in radians. The result is
 * stored in the vec2_t.
 *
 * @param vec2_t * pointer to vector to rotate.
 * @param float angle in radians.
 * 
 * @return void.
 */
void
Stds_RotateVec2( struct vec2_t *v, const float angle ) {
  v->x = v->x * cosf( angle ) - v->y * sinf( angle );
  v->y = v->x * sinf( angle ) + v->y * cosf( angle );
}

/**
 * Checks to see if two vectors are equal (e.g. share the
 * same values).
 * 
 * @param vec2_t pointer to first vector.
 * @param vec2_t pointer to second vector.
 * 
 * @return true if they share the same x/y values, false otherwise.
 */
bool
Stds_IsEqualVec2( const struct vec2_t *u, const struct vec2_t *v ) {
  return u->x == v->x && u->y == v->y;
}

/**
 * Calculates the magnitude of a vector.
 * 
 * @param vec2_t pointer to vector.
 * 
 * @return magnitude scalar.
 */
float
Stds_GetMagnitudeVec2( const struct vec2_t *v ) {
  return sqrtf( v->x * v->x + v->y * v->y );
}

/**
 * Calculates the dot product of the two vectors.
 * 
 * @param vec2_t pointer to first vector.
 * @param vec2_t pointer to second vector.
 * 
 * @return scalar dot product of vectors.
 */
float
Stds_DotProduct( const struct vec2_t *u, const struct vec2_t *v ) { 
  return u->x * v->x + u->y * v->y;
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

/**
 * Adds a scalar to the vec2.
 *
 * @param vec2_t a pointer to vec2_t.
 * @param float value to add to struct.
 *
 * @return void.
 */
void 
Stds_AddToVec2( struct vec2_t *v, const float add ) {
  v->x += add;
  v->y += add;
}

/**
 * Subtracts a scalar to the vec2.
 *
 * @param vec2_t a pointer to vec2_t.
 * @param float value to subtract to struct.
 *
 * @return void.
 */
void 
Stds_SubtractToVec2( struct vec2_t *v, const float subtract ) {
  v->x -= subtract;
  v->y -= subtract;
}

/**
 * Multiplies a scalar to the vec2.
 *
 * @param vec2_t a pointer to vec2_t.
 * @param float value to multiply to struct.
 *
 * @return void.
 */
void 
Stds_MultiplyToVec2( struct vec2_t *v, const float multiply ) {
  v->x *= multiply;
  v->y *= multiply;
}

/**
 * Divides a scalar to the vec2.
 *
 * @param vec2_t a pointer to vec2_t.
 * @param float value to divides to struct.
 *
 * @return void.
 */
void 
Stds_DivideToVec2( struct vec2_t *v, const float divide ) {
  v->x /= divide;
  v->y /= divide;
}
