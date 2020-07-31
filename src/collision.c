//=============================================================================================//
// FILENAME :       collision.c
//
// DESCRIPTION :
//        This file defines the primary collision detectin functions. As of 7/9/2020, we have
//        an AABB collision-response function (returning an enum of the collision side), and a
//        primitive rectangle-overlap test. As of 7/15/2020, circular collision is added along with
//        a primitive response function.
//
// NOTES :
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.
//
// AUTHOR :   Joshua Crotts        START DATE :    22 Jun 2020
//
//=============================================================================================//

#include "../include/collision.h"

/**
 * Determines which side entity_t a collided onto entity_t b. This also resolves
 * the collision, and returns the side of collision.
 *
 * @param entity_t* first entity.
 * @param entity_t* second entity.
 *
 * @return enum side that a collided onto b with (the side of b).
 */
enum CollisionSide
Stds_CheckAABBCollision( struct entity_t *a, struct entity_t *b ) {
  float w  = 0.5f * ( b->w + a->w );
  float h  = 0.5f * ( b->h + a->h );
  float dx = ( b->x + b->w / 2.0f ) - ( a->x + a->w / 2.0f );
  float dy = ( b->y + b->h / 2.0f ) - ( a->y + a->h / 2.0f );

  if ( fabs( dx ) < w && fabs( dy ) < h ) {
    float wy = w * dy;
    float hx = h * dx;

    if ( wy >= hx ) {
      if ( wy > -hx ) { // top
        a->y = b->y - a->h;
        return SIDE_TOP;
      } else { // right
        a->x = b->x + b->w;
        return SIDE_RIGHT;
      }
    } else {
      if ( wy > -hx ) { // left
        a->x = b->x - a->w;
        return SIDE_LEFT;
      } else { // bottom
        a->y = b->y + b->h;
        return SIDE_BOTTOM;
      }
    }
  }
  return SIDE_NONE;
}

/**
 * Checks the center coordinates of both circles to see
 * if a collision occurs. If the distance between the foci
 * is smaller than the radii of both circles combined,
 * a collision occurred.
 *
 * @param circle_t * pointer to first circle.
 * @param circle_t * pointer to second circle.
 *
 * @return true if collision occurs, false otherwise.
 */
bool
Stds_CheckCircularCollision( const struct circle_t *c1, const struct circle_t *c2 ) {
  float distance_x = fabsf( c1->center_x - c2->center_x );
  float distance_y = fabsf( c1->center_y - c2->center_y );

  float radii_sum = c1->radius + c2->radius;
  return ( distance_x * distance_x + distance_y * distance_y <= radii_sum * radii_sum );
}

/**
 * Repositions the first circle to its correct spot if a collision occurs.
 * This function is not required; rather it is just a sample.
 *
 * @param circle_t * pointer to first circle.
 * @param circle_t * pointer to second circle.
 *
 * @return void.
 */
void
Stds_ResolveCircularCollision( struct circle_t *c1, struct circle_t *c2 ) {
  float distance_x = ( float ) c1->center_x - c2->center_x;
  float distance_y = ( float ) c1->center_y - c2->center_y;

  float radii_sum = c1->radius + c2->radius;
  float length    = sqrtf( distance_x * distance_x + distance_y * distance_y );
  float unit_x    = distance_x / length;
  float unit_y    = distance_y / length;

  float tmp_c1_x = c1->center_x;
  float tmp_c2_y = c1->center_y;

  c1->center_x = c2->center_x + ( radii_sum + 1 ) * unit_x;
  c1->center_y = c2->center_y + ( radii_sum + 1 ) * unit_y;
}

/**
 * Determines if two rectangles are collided.
 *
 * @param float x1
 * @param float y1
 * @param int32_t w1
 * @param int32_t h1
 * @param float x2
 * @param float y2
 * @param int32_t w2
 * @param int32_t h2
 *
 * @return true if overlap exists, false otherwise.
 */
inline bool
Stds_CheckIntersection( const float x1, const float y1, const int32_t w1, const int32_t h1,
                        const float x2, const float y2, const int32_t w2, const int32_t h2 ) {
  return ( fmax( x1, x2 ) < fmin( x1 + w1, x2 + w2 ) ) &&
         ( fmax( y1, y2 ) < fmin( y1 + h1, y2 + h2 ) );
}

/**
 * Checks if a point enters a rectangle.
 * 
 * @param vec2_t a pointer to a vec2_t.
 * @param SDL_FRect a pointer to a rectangle.
 * 
 * @return bool.
 */
bool 
Stds_PointVsRect( const struct vec2_t *point, const SDL_FRect *rect ) {
  return ( point->x >= rect->x && point->y >= rect->y && point->x < rect->x + rect->w && point->y < rect->y + rect->h );
}

/**
 * Checks if a rectangle enters another rectangle (AABB without entities).
 * 
 * @param SDL_FRect a pointer to a rectangle.
 * @param SDL_FRect a pointer to a rectangle.
 * 
 * @return bool.
 */
bool  
Stds_RectVsRect( const SDL_FRect *r1, const SDL_FRect *r2 ) {
  return ( r1->x < r2->x + r2->w && r1->x + r1->w > r2->x &&
			r1->y < r2->y + r2->h && r1->y + r1->h > r2->y );
}

/**
 * Checks if a ray hits a rectangle.
 * 
 * @param vec2_t the rays location.
 * @param vec2_t the rays direction.
 * @param SDL_FRect a pointer to a rectangle.
 * @param vec2_t the contact point on the rectangle.
 * @param vec2_t the normal of the contact point;
 * @param float final check for a collision.
 * 
 * @return bool.
 */
bool 
Stds_RayVsRect( const struct vec2_t *ray, const struct vec2_t *ray_direction, const SDL_FRect* rect, 
                            struct vec2_t *contact_point, struct vec2_t* contact_norm, float *hitNear) {
  struct vec2_t near;
  near.x = ( rect->x - ray->x ) / ray_direction->x;
  near.y = ( rect->y - ray->y ) / ray_direction->y;
  struct vec2_t far;
  far.x = ( rect->x + rect->w - ray->x ) / ray_direction->x;
  far.y = ( rect->y + rect->h - ray->x ) / ray_direction->y;

  if ( near.x > far.x ) {
    float temp = near.x;
    near.x = far.x;
    far.x = temp;
  }

  if ( near.y > far.y ) {
    float temp = near.y;
    near.y = far.y;
    far.y = temp;
  }

  if ( near.x > far.y || near.y > far.x ) {
    return false;
  }

  *hitNear = ( near.x > near.y ) ? near.x : near.y;
  float hitFar = ( far.x < far.y ) ? far.x : far.y;

  if ( hitFar < 0) {
    return false;
  }

  contact_point->x = ray->x + *hitNear * ray_direction->x;
  contact_point->y = ray->y + *hitNear * ray_direction->y;

  if ( near.x > near.y ) {
    if ( ray_direction->x < 0 ) {
      contact_norm->x = 1;
      contact_norm->y = 0;
    } else {
      contact_norm->x = -1;
      contact_norm->y = 0;
    }
  }
  else if ( near.x < near.y ) {
    if ( ray_direction->y < 0 ) {
      contact_norm->x = 0;
      contact_norm->y = 1;
    } else {
      contact_norm->x = 0;
      contact_norm->y = -1;
    }
  }

  return true;
}

/**
 * Checks if a rectangle collides with rectangle
 * 
 * @param SDL_FRect first rectangle.
 * @param SDL_FRect second rectangle.
 * @param vec2_t the contact point on the rectangle.
 * @param vec2_t the normal of the contact point;
 * @param float final check for a collision.
 * 
 * @return bool.
 */
bool 
Stds_AdvRectVsRect( const SDL_FRect *r1, const SDL_FRect *r2, 
                                struct vec2_t *contact_point, struct vec2_t* contact_norm, 
                                float *hitNear, const struct vec2_t *r1_velocity ) {
  if ( r1_velocity->x == 0.0f && r1_velocity->y == 0 ) {
    return false;
  }

  SDL_FRect expand_rectangle;
  expand_rectangle.x = r2->x - r1->w / 2 + ( r1->w / 2 + 1 );
  expand_rectangle.y = r2->y - r1->h / 2 + ( r1->h / 2 + 1 );

  expand_rectangle.w = r2->w + r1->w - 2;
  expand_rectangle.h = r2->h + r1->h - 2;

  struct vec2_t ray = {r1->x + r1->w, r1->y + r1->h};

  if (Stds_RayVsRect(&ray,  r1_velocity, &expand_rectangle, contact_point, contact_norm, hitNear ) ) {
    if ( *hitNear <= 1.0f ) {
      return true;
    }
  }

  return false;
}
