/**
 * @file main.c
 * @author Joshua Crotts
 * @date Aug 29 2020
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
 * This file is the barebones definition of a game with C-Standards.
 */
#include "../include/main.h"

#define S_WIDTH  700
#define S_HEIGHT 700
#define L_WIDTH  3000
#define L_HEIGHT S_HEIGHT

static void init_scene( void );
static void cleanup_stage( void );
static void draw( void );
static void update( void );

/**
 * Barebones game. This is the minimum amount of code
 * necessary to run a window.
 * 
 * Example:
 *  atexit(callback_cleanup_function);
 *  Stds_InitGame(...);
 *  Stds_InitAppStructures();
 *  Stds_GameLoop();
 *  return 0;
 *
 * @param int32_targc, number of cmd arguments.
 * @param char* [] array of string arguments.
 *
 * @return status code.
 */
int
main( int argc, char *argv[] ) {
  atexit( cleanup_stage );

  Stds_InitGame( "Basic Game Test", S_WIDTH, S_HEIGHT, L_WIDTH, L_HEIGHT );
  Stds_InitAppStructures();
  Stds_ToggleDebugMode( true );
  init_scene();
  Stds_GameLoop();

  return 0;
}

/**
 * Initializes the delegation structure to use the
 * update and draw methods for rendering and updating
 * the game. These methods must be defined because the
 * delegation structure uses them in the loop function.
 *
 * Example:
 *   g_app.delegate.update = update;
 *   g_app.delegate.draw   = draw;
 *
 * Sprites and structs are also initalized here. Fonts, and 
 * audio should be initialized here.
 *
 * @param void.
 * 
 * @return void.
 */
static void
init_scene( void ) {
  g_app.delegate.update = update;
  g_app.delegate.draw   = draw;
}

/**
 * Updates all UI elements, physics, and movements, as well as the camera. Make
 * sure to update the camera before any other elements if you have one.
 *
 * @param void.
 *
 * @return void.
 */
static void
update( void ) {}

/**
 * Draws all sprites, UI elements, and anything else. Don't put any physic-logic
 * inside this function.
 *
 * @param void.
 *
 * @return void.
 */
static void
draw( void ) {

}

/**
 * Cleans up whatever elements are left via the stage and not Stds itself.
 * Be sure to assign the callback with atexit(...) BEFORE calling Stds_GameLoop()!
 *
 * @param void.
 *
 * @return void.
 */
static void
cleanup_stage( void ) {
  SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Freeing player and grid components.\n" );
}