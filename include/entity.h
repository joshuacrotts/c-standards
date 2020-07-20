#ifndef ENTITY_H
#define ENTITY_H

#include "animation.h"
#include "stds.h"

/*
 *
 */
struct entity_t {
  float x;
  float y;

  /* Miscellaneous positioning variable. */
  float variability;

  /* Scales the entity in either the x or y
     direction. This should default to 1. */
  float scale_x;
  float scale_y;

  /* Directional velocity (yes, I know it's redundant). */
  float dx;
  float dy;

  /* Acceleration or deceleration factors. */
  float delta_accel_x;
  float delta_accel_y;

  /* Change rate of alpha value. */
  float delta_alpha;

  /* Size of entity if not defined by a rectangle. These
     should either be set manually, or defined by a call
     to SDL_QueryTexture(...), where you pass the addresses
     of these variables. */
  int32_t  w;
  int32_t  h;
  uint32_t flags;
  uint32_t id_flags;
  uint32_t reload;
  uint32_t identifier;

  uint16_t angle;
  uint16_t radius;

  /* Can be used interchangably for different purposes. */
  int32_t health;
  int32_t life;

  SDL_Color    color;
  SDL_Texture *texture[TEXTURE_BUFFER_SIZE];

  struct animation_t *animation;
  struct entity_t *   next;

  void ( *tick )( struct entity_t * );
  void ( *draw )( struct entity_t * );
  void ( *touch )( struct entity_t * );
  void ( *die )( struct entity_t * );
};


#endif // ENTITY_H