//=============================================================================================//
// FILENAME :       camera.c
//
// DESCRIPTION :
//        This file defines the function for updating a camera around a parent entity. Generally,
//        this should be the player. All offsets are pre-applied to the draw functions. To keep
//        something from being updated, just re-add the valuesx + g_app.camera.x, y +
//        g_app.camera.y.
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
// AUTHOR :   Joshua Crotts        START DATE :    18 Jun 2020
//
//=============================================================================================//

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
