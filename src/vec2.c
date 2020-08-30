/**
 * @file vec2.c
 * @author Joshua Crotts
 * @date July 31 2020
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
 * This file defines the functions for a two-dimensional vector for (x,y) coordinates
 * such as velocity, position, acceleration/deceleration, and other miscellaneous factors.
 */
#include "../include/vec2.h"

/**
 * Creates a vec2 struct with the specified positions.
 *
 * @param float x.
 * @param float y.
 *
 * @return struct vec2_t instance.
 */
struct vec2_t
Stds_CreateVec2( const float x, const float y ) {
  struct vec2_t v;
  v.x = x;
  v.y = y;
  return v;
}

/**
 * Clones a vec2D struct. This creates a deep-copy.
 *
 * @param struct vec2_t * pointer to vec2 to copy.
 */
inline struct vec2_t
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
inline void
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
inline void
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
inline void
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
inline bool
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
inline float
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
inline float
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
inline void
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
inline void
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
inline void
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
inline void
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
inline void
Stds_DivideToVec2( struct vec2_t *v, const float divide ) {
  v->x /= divide;
  v->y /= divide;
}
