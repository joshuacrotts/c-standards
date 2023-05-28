/**
 * @file background.c
 * @author Joshua Crotts
 * @date June 18 2020
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
 * This file defines the background functionality, both regular and parallax.
 */
#include "../include/background.h"

static char input_buffer[MAX_BUFFER_SIZE];

/**
 * Loads in the parallax images specified by the directory.
 * These images should be labeled in back-to-front order.
 * For instance, if we have three layers L0, L1, and L2,
 * L0 should be the layer drawn farthest from the viewport,
 * whereas L2 should be the closest. Make sure that your
 * images all have a common suffix numbering scheme as well,
 * starting at 0.
 *
 * @param const char* string to directory of parallax background images.
 * @param size_t number of parallax frames.
 * @param float default scroll speed shared across all frames.
 * @param float[] array of modified scroll speeds. These values alter
 *        the default scroll speed of each frame. These values
 *        f1 <= f2 <= ... < fn, as implied, should be listed in
 *        back-to-front speed.
 * @param bool infinite_scroll, determining whether two copies of
 *        the image are rendered side-by-side to provide the illusion
 *        of an infinite background.
 */
void
Stds_AddParallaxBackground( const char *directory, const size_t count,
                            const float normal_scroll_speed, const float scroll_speeds[],
                            const bool infinite_scroll ) {

  struct parallax_background_t *layer;

  char        number_buffer[MAX_FILE_NUM_DIGITS];
  const char *file_extsn = ".png";

  for ( uint32_t i = 0; i < count; i++ ) {
    layer = calloc( 1, sizeof( struct parallax_background_t ) );

    if ( layer == NULL ) {
      SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                   "Could not allocate memory for parallax_background_t. %s.\n", SDL_GetError() );
      exit( EXIT_FAILURE );
    }

    snprintf( number_buffer, MAX_FILE_NUM_DIGITS, "%d", i );
    strncpy( input_buffer, directory, strlen( directory ) + 1 );
    char *file_name     = strncat( input_buffer, number_buffer, strlen( number_buffer ) + 1 );
    char *file_name_ext = strncat( input_buffer, file_extsn, strlen( file_extsn ) + 1 );
    layer->background   = Stds_AddBackground( file_name_ext );
    layer->parallax_scroll_speed = scroll_speeds[i];
    layer->normal_scroll_speed   = normal_scroll_speed;
    layer->infinite_scroll       = infinite_scroll;

    memset( input_buffer, '\0', sizeof( input_buffer ) );
    g_app.parallax_tail->next = layer;
    g_app.parallax_tail       = layer;
  }
}

/**
 * Updates the position of the parallax background element.
 * The offset is applied by multiplying the default scroll speed
 * multiplied by the scroll offset to give the illusion of
 * different scroll rates.
 *
 * @param parallax_backgorund_t pointer to struct.
 *
 * @return void.
 */
void
Stds_ParallaxBackgroundUpdate( struct parallax_background_t *p ) {
  if ( !p->infinite_scroll ) {
    p->background->pos.x =
        ( ( 0 - g_app.camera.x ) * ( p->normal_scroll_speed * p->parallax_scroll_speed ) );

    /* Repositions the background according to where it is relative to the camera. */
    p->background->pos.x = ( float ) fmodf( p->background->pos.x, p->background->w );
  } else {
    p->background->pos.x -= ( p->normal_scroll_speed * p->parallax_scroll_speed );
    if ( p->background->pos.x < -p->background->w ) {
      p->background->pos.x = 0;
    }
  }
}

/**
 * Draws the parallax background frame. Two copies of the image
 * are drawn to provide the illusion of infinite scrolling if
 * specified by the boolean in the struct.
 *
 * @param parallax_background_t pointer to struct.
 *
 * @return void.
 */
void
Stds_ParallaxBackgroundDraw( const struct parallax_background_t *p ) {
  /* Two copies of the image are drawn to give the illusion of depth and parallax. */
  Stds_DrawTexture( p->background->background_texture, p->background->pos.x, p->background->pos.y,
                    p->background->w, p->background->h, 0, SDL_FLIP_NONE, NULL, false );
  Stds_DrawTexture( p->background->background_texture, p->background->pos.x + p->background->w,
                    p->background->pos.y, p->background->w, p->background->h, 0, SDL_FLIP_NONE,
                    NULL, false );
}

/**
 * Initializes the background image specified by char*.
 * It is drawn at (0, 0), or the top-left of the window.
 *
 * @param const char *file location of background image.
 *
 * @return void.
 */
struct background_t *
Stds_AddBackground( const char *file ) {
  struct background_t *background;
  background = calloc( 1, sizeof( struct background_t ) );

  if ( background == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for background_t. %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  background->pos.x              = 0;
  background->pos.y              = 0;
  background->background_texture = Stds_LoadTexture( file );
  SDL_QueryTexture( background->background_texture, NULL, NULL, &background->w, &background->h );
  return background;
}

/**
 * Continuously updates the position of the background depending
 * on the camera's location. If no camera is used, its offset is
 * 0, thus not moving the background.
 *
 * @param background_t pointer to update.
 *
 * @return void.
 */
void
Stds_BackgroundUpdate( struct background_t *background ) {
  background->pos.x = 0 - g_app.camera.x;
  background->pos.y = 0 - g_app.camera.y;
}

/**
 * Draws the background at its appropriate location specified by the
 * update function.
 *
 * @param background_t pointer to draw.
 *
 * @return void.
 */
void
Stds_BackgroundDraw( const struct background_t *background ) {
  Stds_DrawTexture( background->background_texture, background->pos.x, background->pos.y,
                    background->w, background->h, 0, SDL_FLIP_NONE, NULL, false );
}

/**
 * Frees the context of the background struct and image.
 *
 * @param background_t pointer to free.
 *
 * @return void.
 */
void
Stds_BackgroundDie( struct background_t *background ) {
  SDL_DestroyTexture( background->background_texture );
  free( background );
}
