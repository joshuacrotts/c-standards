/**
 * @file game.c
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
 * Initializes the game structures and pointers for the linked list
 * structures. The game loop is also initialized here.
 */
#include "../include/game.h"

static const char *FPS_STR = " | FPS: ";
static uint16_t    current_fps;

static void     Stds_InitWindowFPS( void );
static void     Stds_CapFramerate( long *, float * );
static uint32_t Stds_UpdateWindowTitle( uint32_t, void * );

/**
 * Initializes the app linked list data structures.
 *
 * @param void.
 *
 * @return void.
 */
void
Stds_InitAppStructures( void ) {
  g_app.text_field_tail = &g_app.text_field_head;
  g_app.parallax_tail   = &g_app.parallax_head;
  g_app.texture_tail    = &g_app.texture_head;
  g_app.button_tail     = &g_app.button_head;
  g_app.trail_tail      = &g_app.trail_head;
  g_app.font_tail       = &g_app.font_head;

  Stds_InitWindowFPS();
}

/**
 * Runs the game loop, processing input and SDL events as close
 * to the target framerate as possible.
 *
 * @param void.
 *
 * @return void.
 */
void
Stds_GameLoop( void ) {
  long  timer;
  long  then;
  float remainder;

  then = SDL_GetTicks();

  /* Main game loop. */
  while ( g_app.is_running ) {
    Stds_PrepareScene();
    Stds_ProcessInput();
    g_app.delegate.update();
    g_app.delegate.draw();
    Stds_PresentScene();
    Stds_CapFramerate( &then, &remainder );
  }
}

/**
 * Enables the SDL timer to continuously draw the current frames
 * per second to the title bar. For some reason, MacOS doesn't play
 * nicely with this setup, so if we're on a Mac, this is disabled.
 *
 * @param void.
 *
 * @return void.
 */
static void
Stds_InitWindowFPS( void ) {
#ifndef __APPLE__
  SDL_AddTimer( WINDOW_UPDATE_TIMER, Stds_UpdateWindowTitle, &current_fps );
#endif
}

/**
 * Halts the framerate to approximately sixty frames
 * per second when possible.
 *
 * @param pointers to the times from the previous iteration,
 *        and remainder.
 *
 * @return void.
 */
static void
Stds_CapFramerate( long *then, float *remainder ) {
  long wait, frame_time;

  wait = ( int32_t )( FPS_TIME + *remainder );
  *remainder -= ( int32_t ) *remainder;
  frame_time = SDL_GetTicks() - *then;
  wait -= frame_time;

  if ( wait < 1 ) {
    wait = 1;
  }

  SDL_Delay( wait );

  current_fps = 1000 / wait;
  *remainder += ( 0.667f );
  *then = SDL_GetTicks();
}

/**
 * Callback function to the SDL_AddTimer function that changes
 * the SDL_Window title to a set value with the FPS concatenated
 * onto the end.
 *
 * @param timer interval, and arguments for concatenating. This
 *        should be the frames per second (integer).
 *
 * @return interval time for callback function.
 */
static uint32_t
Stds_UpdateWindowTitle( uint32_t interval, void *args ) {
  uint16_t fps = *( uint16_t * ) args;
  /* Create text window buffer. */
  char window_buffer[SMALL_TEXT_BUFFER];

  /* Copy the title to the buffer. */
  strncpy( window_buffer, g_app.original_title, strlen( g_app.original_title ) + 1 );

  /* Move temp var to buffer. Receive ptr. */
  strncat( window_buffer, FPS_STR, strlen( FPS_STR ) + 1 );

  /* Concatenate number to title variable. */
  char *title;
  title = Stds_StrCatIntArray( window_buffer, fps );
  SDL_SetWindowTitle( g_app.window, title );

  return interval;
}
