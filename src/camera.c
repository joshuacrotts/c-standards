/**
 * @file camera.c
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
 * This file defines the function for updating a camera around a parent entity. Generally,
 * this should be the player. All offsets are pre-applied to the draw functions. To keep
 * something from being updated, just re-add the valuesx + g_app.camera.x, y +
 * g_app.camera.y.
 */
#include "../include/camera.h"

/**
 * Applies an offset from the supplied entity, and stores
 * the coordinates in the App struct. Typically, in an overhead
 * style game, this supplied entity will be a reference to the
 * player. If you want to remove the offset from an entity,
 * just add the coordinates of the camera to your entity
 * x + g_app.camera.x and y + g_app.camera.y. Note that if you have
 * the option to modify the placement via a method in draw.c,
 * do it there instead.
 *
 * The camera offset means, if false, the thing in question will
 * stay in the viewport of the camera. If true, the thing scrolls
 * in relation to the camera, meaning it can go off screen. In essence,
 * if you want something to stay on the screen such as a HUD element,
 * make this variable true, and false otherwise.
 *
 * @param entity_t* pointer to parent entity.
 *
 * @return void.
 */
void
Stds_CameraUpdate( const struct entity_t *focus_point ) {
  if ( focus_point != NULL ) {
    g_app.camera.x = ( focus_point->pos.x + focus_point->w / 2 ) - ( g_app.SCREEN_WIDTH >> 1 );
    g_app.camera.y = ( focus_point->pos.y + focus_point->h / 2 ) - ( g_app.SCREEN_HEIGHT >> 1 );
    g_app.camera.w = g_app.SCREEN_WIDTH;
    g_app.camera.h = g_app.SCREEN_HEIGHT;

    Stds_ClampFloat( &g_app.camera.x, 0, g_app.LEVEL_WIDTH - g_app.camera.w );
    Stds_ClampFloat( &g_app.camera.y, 0, g_app.LEVEL_HEIGHT - g_app.camera.h );
  } else {
    printf( "Error, your focus_point entity is NULL in camera.c.\n" );
    exit( EXIT_FAILURE );
  }
}
