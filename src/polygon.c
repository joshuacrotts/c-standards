//=============================================================================================//
// FILENAME :       polygon.c
//
// DESCRIPTION :
//        Defines the functions associated with the polygon struct like drawing,
//        updating, and collision detecting.
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
// AUTHOR :   strah19        START DATE :    31 Jul 2020
//
//=============================================================================================//

#include "../include/polygon.h"
#include "../include/draw.h"

/**
 *
 */
struct polygon_t *
Stds_CreatePolygon( const int32_t sides, const float size, const struct vec2_t position,
                    const float angle ) {
  struct polygon_t *polygon;
  polygon = malloc( sizeof( struct polygon_t ) );

  if ( polygon == NULL ) {
    SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION,
                  "Error: could not allocate memory for polygon_t, %s.\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  } else {
    SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Created polygon_t.\n" );
  }

  memset( polygon, 0, sizeof( struct polygon_t ) );
  polygon->sides   = sides;
  polygon->overlap = false;
  polygon->model   = malloc( sizeof( struct vec2_t ) * sides );
  polygon->points  = malloc( sizeof( struct vec2_t ) * sides );

  float f_theta     = ( ( float ) PI * 2.f ) / polygon->sides;
  polygon->position = position;
  polygon->angle    = angle;

  for ( int32_t i = 0; i < polygon->sides; i++ ) {
    struct vec2_t data = Stds_CreateVec2( cosf( f_theta * i ) * size, sinf( f_theta * i ) * size );
    polygon->model[i]  = data;
    polygon->points[i] = polygon->model[i];
  }

  return polygon;
}

/**
 *
 */
void
Stds_UpdatePolygon( struct polygon_t *polygon ) {
  for ( int32_t i = 0; i < polygon->sides; i++ ) {

    polygon->points[i].x = ( polygon->model[i].x * cosf( Stds_ToRadians( polygon->angle ) ) ) -
                           ( polygon->model[i].y * sinf( Stds_ToRadians( polygon->angle ) ) ) +
                           polygon->position.x;
    polygon->points[i].y = ( polygon->model[i].x * sinf( Stds_ToRadians( polygon->angle ) ) ) +
                           ( polygon->model[i].y * cosf( Stds_ToRadians( polygon->angle ) ) ) +
                           polygon->position.y;
    polygon->overlap = false;
  }
}

/**
 *
 */
void
Stds_DrawPolygon( const struct polygon_t *polygon ) {
  SDL_Color white = { 255, 255, 255 };
  SDL_Color red   = { 255, 0, 0 };

  SDL_Color color = ( polygon->overlap ) ? white : red;
  for ( int32_t i = 0; i < polygon->sides; i++ ) {
    SDL_SetRenderDrawColor( g_app.renderer, color.r, color.g, color.b, 255 );
    SDL_RenderDrawLineF( g_app.renderer, polygon->points[i].x, polygon->points[i].y,
                         polygon->points[( ( i + 1 ) % polygon->sides )].x,
                         polygon->points[( ( i + 1 ) % polygon->sides )].y );
  }
  SDL_SetRenderDrawColor( g_app.renderer, color.r, color.g, color.b, 255 );
  SDL_RenderDrawLineF( g_app.renderer, polygon->points[0].x, polygon->points[0].y,
                       polygon->position.x, polygon->position.y );
}

/**
 *
 */
void
Stds_CleanUpPolygon( struct polygon_t *polygon ) {
  free( polygon->model );
  free( polygon->points );

  free( polygon );
}

/**
 *
 */
struct polygon_t *
Stds_BoundingBox( float x, float y, float w, float h, float angle ) {
  struct polygon_t *polygon;
  polygon = malloc( sizeof( struct polygon_t ) );

  if ( polygon == NULL ) {
    SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION,
                  "Error: could not allocate memory for polygon_t, %s.\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  } else {
    SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Created polygon_t.\n" );
  }

  memset( polygon, 0, sizeof( struct polygon_t ) );
  polygon->sides   = 4;
  polygon->overlap = false;
  polygon->model   = malloc( sizeof( struct vec2_t ) * 4 );
  polygon->points  = malloc( sizeof( struct vec2_t ) * 4 );

  float f_theta     = ( ( float ) PI * 2.f ) / polygon->sides;
  polygon->position = Stds_CreateVec2( x, y );
  polygon->angle    = angle;

  polygon->model[0]  = Stds_CreateVec2( -( w / 2 ), -( h / 2 ) );
  polygon->points[0] = polygon->model[0];
  polygon->model[1]  = Stds_CreateVec2( -( w / 2 ), ( h / 2 ) );
  polygon->points[1] = polygon->model[1];
  polygon->model[2]  = Stds_CreateVec2( ( w / 2 ), ( h / 2 ) );
  polygon->points[2] = polygon->model[2];
  polygon->model[3]  = Stds_CreateVec2( ( w / 2 ), -( h / 2 ) );
  polygon->points[3] = polygon->model[3];

  for ( uint32_t i = 0; i < polygon->sides; i++ ) {
    polygon->model[i].x += w / 2;
    polygon->model[i].y += h / 2;
  }

  return polygon;
}