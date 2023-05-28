/**
 * @file trail.c
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
 * This file defines trail functionality with alpha-blending support.
 */
#include "../include/trail.h"

/**
 * Initializes a trail object using the supplied Entity as the parent
 * where it will stay for the duration of its life. The trail is added
 * to the App automatically, so nothing is returned.
 *
 * @param entity_t* parent entity.
 * @param int16_t rate at which the alpha decreases (should be between 0
 *        and 255, the higher it is, the faster it goes).
 * @param SDL_RendererFlip flip enum for if the trail should be flipped.
 * @param bool is_transparent if your image has a PNG background, this should be true.
 *
 * @return void.
 */
void
Stds_AddTextureTrail( struct entity_t *parent, int16_t alpha_decay, SDL_RendererFlip flip,
                      bool is_transparent ) {
  struct trail_t *t;
  t = calloc( 1, sizeof( struct trail_t ) );

  if ( t == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for trail_t. %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  t->pos  = Stds_CloneVec2( &parent->pos );
  t->w    = parent->w;
  t->h    = parent->h;
  t->flip = flip;
  t->flags |= is_transparent ? STDS_TRAIL_TRANSPARENT_TEXTURE_MASK : STDS_TRAIL_TEXTURE_MASK;

  /* If we want the trail to be the texture of the parent entity,
     we either use its animation, or static texture. */
  if ( parent->animation != NULL ) {
    if ( parent->animation->id_flags & STDS_SPRITE_SHEET_MASK ) {
      printf( "Trails are unsupported with entities that have spritesheets.\n" );
      exit( EXIT_FAILURE );
    } else {
      t->texture = parent->animation->frames[parent->animation->current_frame_id];
    }
  } else {
    t->texture = parent->texture[0];
  }

  t->alpha            = 0xff;
  t->alpha_decay_rate = alpha_decay;

  g_app.trail_tail->next = t;
  g_app.trail_tail       = t;
}

/**
 *
 */
void
Stds_AddCircleTrail( float x, float y, int32_t r, int16_t alpha_decay, SDL_Color *c ) {
  struct trail_t *t;
  t = calloc( 1, sizeof( struct trail_t ) );

  if ( t == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                 "Could not allocate memory for circular trail_t. %s.\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  t->pos.x = x;
  t->pos.y = y;
  t->r     = r;
  t->flip  = SDL_FLIP_NONE;
  t->flags |= STDS_TRAIL_CIRCLE_MASK;
  t->color = *c;

  t->alpha            = 0xff;
  t->alpha_decay_rate = alpha_decay;

  g_app.trail_tail->next = t;
  g_app.trail_tail       = t;
}

/**
 *
 */
void
Stds_AddSquareTrail( float x, float y, int32_t w, int32_t h, int16_t alpha_decay, SDL_Color *c ) {
  struct trail_t *t;
  t = calloc( 1, sizeof( struct trail_t ) );

  if ( t == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                 "Could not allocate memory for square trail_t. %s.\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  t->pos.x = x;
  t->pos.y = y;
  t->w     = w;
  t->h     = h;
  t->flip  = SDL_FLIP_NONE;
  t->flags |= STDS_TRAIL_SQUARE_MASK;
  t->color = *c;

  t->alpha            = 0xff;
  t->alpha_decay_rate = alpha_decay;

  g_app.trail_tail->next = t;
  g_app.trail_tail       = t;
}

/**
 * Updates the trail by iterating through the trail's linked lists,
 * and constantly decreasing its alpha value. Once any arbitrary
 * tail node has an alpha of 0 or less (Stds_ClampInt'd to 0), it is
 * removed.
 *
 * @param trail_t struct to update.
 *
 * @return void
 */
void
Stds_TrailUpdate( struct trail_t *t ) {
  if ( t != g_app.trail_tail ) {
    t->alpha -= t->alpha_decay_rate;
  }

  if ( t->alpha <= 0 ) {
    t->flags |= STDS_DEATH_MASK;
  }
}

/**
 * Draws the tail linked list.
 *
 * @param trail_t struct to draw.
 *
 * @return void.
 */
void
Stds_TrailDraw( struct trail_t *t ) {
  /* If texture. */
  if ( !( t->flags & STDS_TRAIL_TRANSPARENT_TEXTURE_MASK ) ) {
    SDL_SetTextureBlendMode( t->texture, SDL_BLENDMODE_BLEND );
  }

  SDL_SetTextureAlphaMod( t->texture, t->alpha );
  Stds_DrawTexture( t->texture, t->pos.x, t->pos.y, t->w, t->h, t->angle, t->flip, NULL, true );

  /* If shape. */
  if ( t->flags & STDS_TRAIL_SQUARE_MASK ) {
    SDL_FRect r = { t->pos.x, t->pos.y, t->w, t->h };
    Stds_DrawRectF( &r, &t->color, true, true );
  } else if ( t->flags & STDS_TRAIL_CIRCLE_MASK ) {
    struct circle_t circle = { t->pos.x + t->r / 2, t->pos.y + t->r / 2, t->r };
    Stds_DrawCircle( &circle, &t->color, true );
  }

  if ( !( t->flags & STDS_TRAIL_TRANSPARENT_TEXTURE_MASK ) ) {
    SDL_SetTextureBlendMode( t->texture, SDL_BLENDMODE_NONE );
  }
}