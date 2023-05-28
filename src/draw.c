/**
 * @file draw.c
 * @author Joshua Crotts
 * @date June 22 2020
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
 * This file defines the various procedures for drawing primitives (lines, rectangles,
 * circles), textures, blitting rectangles, and texture caching/loading. Note that,
 * as of 7/25/2020, there IS a distinction between blitting and drawing! Blitting refers
 * to COPYING and altering a texture, whereas drawing simply means drawning with no crops
 * or cuts. Alterations may exist, but there's no splicing like a sprite sheet would have.
 */
#include "../include/draw.h"

static SDL_Texture *Stds_GetTexture( const char * );
static void         Stds_CacheTexture( const char *, SDL_Texture * );
static void         Stds_FillCircleHelper( const struct circle_t *, const SDL_Color * );
static void         Stds_DrawCircleHelper( const struct circle_t *, const SDL_Color * );

/**
 * Clears the screen with a black color.
 *
 * @param void.
 *
 * @return void.
 */
void
Stds_PrepareScene( void ) {
  SDL_SetRenderDrawColor( g_app.renderer, 0, 0, 0, 0 );
  SDL_RenderClear( g_app.renderer );
}

/**
 * Presents the current scene from the application.
 *
 * @param void.
 *
 * @return void.
 */
void
Stds_PresentScene( void ) {
  SDL_RenderPresent( g_app.renderer );
}

/**
 * Draws a rotated SDL texture at an x and y coordinate with a given
 * size.
 *
 * @param SDL_Texture* pointer to texture object.
 * @param float x coordinate.
 * @param float y coordinate.
 * @param float desired width of texture.
 * @param float desired height of texture.
 * @param uint16_t angle of rotation (0 to 360).
 * @param SDL_RendererFlip flip status (SDL_FLIP_HORIZONTAL/VERTICAL)
 * @param SDL_FPoint * pointer to rotation coordinate. NULL for rotation about the center.
 * @param bool applies camera offset or not.
 *
 * @return void.
 */
void
Stds_DrawTexture( SDL_Texture *texture, const float x, const float y, const float w, const float h,
                  const uint16_t angle, const SDL_RendererFlip flip, const SDL_FPoint *rotate_point,
                  const bool camera_offset ) {
  SDL_FRect dest_rect;

  dest_rect.x = camera_offset ? x - g_app.camera.x : x;
  dest_rect.y = camera_offset ? y - g_app.camera.y : y;
  dest_rect.w = w;
  dest_rect.h = h;

  SDL_RenderCopyExF( g_app.renderer, texture, NULL, &dest_rect, angle, rotate_point, flip );
}

/**
 * Blits (i.e. crops) a section of a texture specified by the src pointer to
 * the SDL_Rect object. This is mainly useful for sprite sheet blits.
 * If you're using an animation, make sure to set the attributes of it!
 *
 * @param SDL_Texture* pointer to texture to draw.
 * @param SDL_Rect * pointer to rect with section of texture to draw.
 * @param float x
 * @param float y
 * @param float w
 * @param float h
 * @param uint16_t angle to rotate.
 * @param SDL_RendererFlip flip or not (SDL_FLIP_NONE/VERTICAL/HORIZONTAL).
 * @param SDL_FPoint rotation point.
 * @param bool applies the camera offset or not.
 *
 * @return void.
 */
void
Stds_BlitTexture( SDL_Texture *texture, const SDL_Rect *src, const float x, const float y,
                  const float w, const float h, const uint16_t angle, const SDL_RendererFlip flip,
                  const SDL_FPoint *rotate_point, const bool camera_offset ) {
  SDL_FRect dest;
  dest.x = camera_offset ? x - g_app.camera.x : x;
  dest.y = camera_offset ? y - g_app.camera.y : y;
  dest.w = w;
  dest.h = h;

  SDL_RenderCopyExF( g_app.renderer, texture, src, &dest, angle, rotate_point, flip );
}

/**
 * Draws a rectangle with the supplied color to the screen. The
 * rectangle's properties should be filled (i.e x, y, w, and h).
 * If the last parameter is true, the shape will be filled.
 *
 * @param SDL_Rect*
 * @param SDL_Color color to fill.
 * @param bool is the rect filled or not.
 * @param bool applies the camera offset or not.
 *
 * @return void.
 */
void
Stds_DrawRect( SDL_Rect *rect, const SDL_Color *c, const bool is_filled,
               const bool camera_offset ) {
  SDL_SetRenderDrawBlendMode( g_app.renderer, SDL_BLENDMODE_BLEND );
  SDL_SetRenderDrawColor( g_app.renderer, c->r, c->g, c->b, c->a );

  if ( camera_offset ) {
    rect->x -= ( int32_t ) g_app.camera.x;
    rect->y -= ( int32_t ) g_app.camera.y;
  }

  if ( is_filled ) {
    SDL_RenderFillRect( g_app.renderer, rect );
  } else {
    SDL_RenderDrawRect( g_app.renderer, rect );
  }

  SDL_SetRenderDrawBlendMode( g_app.renderer, SDL_BLENDMODE_NONE );
}

/**
 * Draws a floating-point rectangle with the supplied color. The
 * rectangle's properties should be filled (i.e x, y, w, and h).
 * If the last parameter is true, the shape will be filled.
 *
 * @param SDL_FRect*
 * @param SDL_Color color to fill.
 * @param bool is the rect filled or not.
 * @param bool applies the camera offset or not.
 *
 * @return void.
 */
void
Stds_DrawRectF( SDL_FRect *frect, const SDL_Color *c, const bool is_filled,
                const bool camera_offset ) {
  SDL_SetRenderDrawBlendMode( g_app.renderer, SDL_BLENDMODE_BLEND );
  SDL_SetRenderDrawColor( g_app.renderer, c->r, c->g, c->b, c->a );

  if ( camera_offset ) {
    frect->x -= g_app.camera.x;
    frect->y -= g_app.camera.y;
  }

  if ( is_filled ) {
    SDL_RenderFillRectF( g_app.renderer, frect );
  } else {
    SDL_RenderDrawRectF( g_app.renderer, frect );
  }

  SDL_SetRenderDrawBlendMode( g_app.renderer, SDL_BLENDMODE_NONE );
}

/**
 * Draws a rectangle with the specified stroke (pixel width) and color.
 * First four parameters are the x, y, width, and height of rectangle.
 * The next specifies how "thick" it should be. The last four values
 * specify the RGBA values.
 *
 * @param float x
 * @param float y
 * @param uint32_t w
 * @param uint32_t h
 * @param uint32_t stroke thickness
 * @param SDL_Color *c color.
 * @param bool applies the camera offset or not.
 *
 * @return void.
 */
void
Stds_DrawRectStroke( float x, float y, uint32_t w, uint32_t h, const uint32_t stroke,
                     const SDL_Color *c, const bool camera_offset ) {
  if ( stroke <= 0 ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                 "Error: stroke %d cannot be a negative or zero value!", stroke );
    exit( EXIT_FAILURE );
  } else {
    if ( camera_offset ) {
      x += g_app.camera.x;
      y += g_app.camera.y;
    }

    /* Top-left to TR. */
    SDL_FRect r1 = { x, y, w, stroke };

    /* TL to BL. */
    SDL_FRect r2 = { x, y, stroke, h };

    /* BL to BR. */
    SDL_FRect r3 = { x, camera_offset ? h - stroke + g_app.camera.y : h - stroke, w, stroke };

    /* TR to BR. */
    SDL_FRect r4 = { camera_offset ? w - stroke + g_app.camera.x : w - stroke, y, stroke, h };

    Stds_DrawRectF( &r1, c, true, camera_offset );
    Stds_DrawRectF( &r2, c, true, camera_offset );
    Stds_DrawRectF( &r3, c, true, camera_offset );
    Stds_DrawRectF( &r4, c, true, camera_offset );
  }
}

/**
 * Draws a line with the specified color to the screen.
 *
 * @param float x1
 * @param float y1
 * @param float x2
 * @param float y2
 * @param SDL_Color * pointer to color.
 *
 * @return void.
 */
void
Stds_DrawLine( const float x1, const float y1, const float x2, const float y2,
               const SDL_Color *c ) {
  SDL_SetRenderDrawColor( g_app.renderer, c->r, c->g, c->b, c->a );
  SDL_RenderDrawLineF( g_app.renderer, x1, y1, x2, y2 );
}

/**
 * Draws a circle. Simple as that. Takes in the circle's center coordinates,
 * the radius, and RGBA.
 *
 * @param struct circle_t * pointer to circle
 * @param SDL_Color *c color to draw.
 *
 * @return void.
 */
void
Stds_DrawCircle( const struct circle_t *circle, const SDL_Color *color, const bool is_filled ) {
  if ( is_filled ) {
    Stds_FillCircleHelper( circle, color );
  } else {
    Stds_DrawCircleHelper( circle, color );
  }
}

/**
 * Completes one iteration of the color-merge procedure.
 * The speed is dependent on the fade_color_t struct passed.
 *
 * @param fade_color_t pointer to color for transition.
 *
 * @return SDL_Color copy of the new color struct.
 */
SDL_Color
Stds_CombineFadeColor( struct fade_color_t *f ) {
  if ( f->time <= 1.0f && f->is_first_color ) {
    f->time = ( float ) ( f->time + f->alpha );
  } else {
    f->is_first_color = false;
  }

  if ( f->time >= 0.0f && !f->is_first_color ) {
    f->time = ( float ) ( f->time - f->alpha );
  } else {
    f->is_first_color = true;
  }

  int32_t r = ( int32_t )( f->time * f->c2.r + ( 1.0f - f->time ) * f->c1.r );
  int32_t g = ( int32_t )( f->time * f->c2.g + ( 1.0f - f->time ) * f->c1.g );
  int32_t b = ( int32_t )( f->time * f->c2.b + ( 1.0f - f->time ) * f->c1.b );

  Stds_ClampInt( &r, 0, 0xff );
  Stds_ClampInt( &g, 0, 0xff );
  Stds_ClampInt( &b, 0, 0xff );

  SDL_Color c = { r, g, b, 0xff };

  return c;
}

/**
 * Loads an image from the specified path. An error is
 * displayed if the file cannot be found or is not
 * loadable.
 *
 * @param
 *
 * @return SDL_Texture * pointer to the texture loaded from the buffer.
 */
SDL_Texture *
Stds_LoadTexture( const char *fileName ) {
  SDL_Texture *texture;

  texture = Stds_GetTexture( fileName );

  if ( texture == NULL ) {
    texture = IMG_LoadTexture( g_app.renderer, fileName );
    if ( texture == NULL ) {
      SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Error: %s", SDL_GetError() );
      exit( EXIT_FAILURE );
    }

    Stds_CacheTexture( fileName, texture );
  }

  return texture;
}

/**
 * Searches through the SDL_Texture list to see if we have previously
 * loaded in this texture. If so, it is returned. Otherwise, NULL.
 *
 * @param file name of SDL_Texture.
 * @return SDL_Texture pointer - either NULL or object.
 */
static SDL_Texture *
Stds_GetTexture( const char *file_name ) {
  struct texture_t *t;

  for ( t = g_app.texture_head.next; t != NULL; t = t->next ) {
    if ( strcmp( t->name, file_name ) == 0 ) {
      return t->texture;
    }
  }

  return NULL;
}

/**
 * If a SDL_Texture has not been previously loaded in, we add it to
 * the cache here. The cache is a linked-list of SDL_Texture pointers
 * that store references to each texture so we do not waste resources
 * opening the input stream and loading the data back in.
 *
 * @param const char* name
 * @param SDL_Texture * pointer to the texture.
 *
 * @return void.
 */
static void
Stds_CacheTexture( const char *file_name, SDL_Texture *sdl_texture ) {
  struct texture_t *texture;
  texture = calloc( 1, sizeof( struct texture_t ) );

  if ( texture == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for texture_t. %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  g_app.texture_tail->next = texture;
  g_app.texture_tail       = texture;

  strncpy( texture->name, file_name, MAX_FILE_NAME_LEN );
  texture->texture = sdl_texture;
}

/**
 * Draws a circle outline with the specified color. This function
 * actually describes the algorithm.
 *
 * @param circle_t * pointer to circle structure.
 * @param SDL_Color * pointer to color.
 *
 * @return void.
 */
static void
Stds_DrawCircleHelper( const struct circle_t *circle, const SDL_Color *c ) {
  const float diameter = ( circle->radius * 2 );

  float x     = ( circle->radius - 1 );
  float y     = 0;
  float tx    = 1;
  float ty    = 1;
  float error = ( tx - diameter );

  SDL_SetRenderDrawColor( g_app.renderer, c->r, c->g, c->b, c->a );
  while ( x >= y ) {
    //  Each of the following renders an octant of the circle
    SDL_RenderDrawPointF( g_app.renderer, circle->center_x + x, circle->center_y - y );
    SDL_RenderDrawPointF( g_app.renderer, circle->center_x + x, circle->center_y + y );
    SDL_RenderDrawPointF( g_app.renderer, circle->center_x - x, circle->center_y - y );
    SDL_RenderDrawPointF( g_app.renderer, circle->center_x - x, circle->center_y + y );
    SDL_RenderDrawPointF( g_app.renderer, circle->center_x + y, circle->center_y - x );
    SDL_RenderDrawPointF( g_app.renderer, circle->center_x + y, circle->center_y + x );
    SDL_RenderDrawPointF( g_app.renderer, circle->center_x - y, circle->center_y - x );
    SDL_RenderDrawPointF( g_app.renderer, circle->center_x - y, circle->center_y + x );

    if ( error <= 0 ) {
      ++y;
      error += ty;
      ty += 2;
    }

    if ( error > 0 ) {
      --x;
      tx += 2;
      error += ( tx - diameter );
    }
  }
}

/**
 * Fills a circle with the specified color. This function actually
 * describes the algorithm.
 *
 * @param circle_t * pointer to circle structure.
 * @param SDL_Color * pointer to color.
 *
 * @return void.
 */
static void
Stds_FillCircleHelper( const struct circle_t *circle, const SDL_Color *c ) {
  float   offsetx, offsety, d;
  int32_t status;

  offsetx = 0;
  offsety = circle->radius;
  d       = circle->radius - 1;
  status  = 0;
  SDL_SetRenderDrawColor( g_app.renderer, c->r, c->g, c->b, c->a );

  while ( offsety >= offsetx ) {
    float x = circle->center_x;
    float y = circle->center_y;

    status +=
        SDL_RenderDrawLineF( g_app.renderer, x - offsety, y + offsetx, x + offsety, y + offsetx );
    status +=
        SDL_RenderDrawLineF( g_app.renderer, x - offsetx, y + offsety, x + offsetx, y + offsety );
    status +=
        SDL_RenderDrawLineF( g_app.renderer, x - offsetx, y - offsety, x + offsetx, y - offsety );
    status +=
        SDL_RenderDrawLineF( g_app.renderer, x - offsety, y - offsetx, x + offsety, y - offsetx );

    if ( status < 0 ) {
      status = -1;
      break;
    }

    if ( d >= 2 * offsetx ) {
      d -= 2 * offsetx + 1;
      offsetx += 1;
    } else if ( d < 2 * ( circle->radius - offsety ) ) {
      d += 2 * offsety - 1;
      offsety -= 1;
    } else {
      d += 2 * ( offsety - offsetx - 1 );
      offsety -= 1;
      offsetx += 1;
    }
  }
}