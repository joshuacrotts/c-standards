/**
 * @file polygon.c
 * @author strah19
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
 * Defines the functions associated with the polygon struct like drawing,
 * updating, and collision detecting.
 */
#include "../include/polygon.h"

/**
 * Creates a polygon with any number of sides.
 * 
 * @param int32_t num of sides.
 * @param float size of polygon.
 * @param vec2_t position of polygon.
 * @param float angle of polygon.
 * 
 * @return polygon_t pointer to a polygon.
 */
struct polygon_t *
Stds_CreatePolygon( const int32_t sides, const float size, const struct vec2_t position,
                    const float angle ) {
  struct polygon_t *polygon;
  polygon = calloc( 1, sizeof( struct polygon_t ) );

  if ( polygon == NULL ) {
    SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION,
                  "Error: could not allocate memory for polygon_t, %s.\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  } else {
    SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Created polygon_t.\n" );
  }

  polygon->sides       = sides;
  polygon->has_overlap = false;
  polygon->model       = malloc( sizeof( struct vec2_t ) * sides );
  polygon->points      = malloc( sizeof( struct vec2_t ) * sides );

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
 * Updates the polygons position.
 *
 * @param polygon_t pointer to a polygon.
 * 
 * @return void.
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
    polygon->has_overlap = false;
  }
}

/**
 * Draws the polygon.
 *
 * @param polygon_t pointer to a polygon.
 * 
 * @return void.
 */
void
Stds_DrawPolygon( const struct polygon_t *polygon ) {
  SDL_Color white = {255, 255, 255};
  SDL_Color red   = {255, 0, 0};

  SDL_Color color = ( polygon->has_overlap ) ? white : red;
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
 * Cleans up the polygon.
 *
 * @param polygon_t pointer to a polygon.
 * 
 * @return void.
 */
void
Stds_CleanUpPolygon( struct polygon_t *polygon ) {
  free( polygon->model );
  free( polygon->points );

  free( polygon );
}

/**
 * Creates a bounding box for entities.
 *
 * @param float x position.
 * @param float y position.
 * @param float width of polygon.
 * @param float height of polygon.
 * 
 * @return polygon_t pointer to a polygon.
 */
struct polygon_t *
Stds_BoundingBox( float x, float y, float w, float h, float angle ) {
  struct polygon_t *polygon;
  polygon = calloc( 1, sizeof( struct polygon_t ) );

  if ( polygon == NULL ) {
    SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION,
                  "Error: could not allocate memory for polygon_t, %s.\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  } else {
    SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Created polygon_t.\n" );
  }

  polygon->sides   = 4;
  polygon->has_overlap = false;
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