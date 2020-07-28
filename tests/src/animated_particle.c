#include "../include/animated_particle.h"

#define GRAVITY 0.2f

static void add_particle_animation( struct particle_t *p );

/**
 *
 */
struct particle_t
animated_particle_init( float x, float y ) {
  struct particle_t p;
  /* Un-apply the camera offset. */
  p.x               = x;
  p.y               = y;
  p.life            = Stds_RandomInt( 100, 300 );
  p.dx              = Stds_RandomFloat( -5.f, 5.f );
  p.dy              = Stds_RandomFloat( -10.f, -7.f );
  p.particle_update = animated_particle_update;
  p.particle_draw   = animated_particle_draw;

  add_particle_animation( &p );
  SDL_QueryTexture( p.animation->current_texture, NULL, NULL, &p.w, &p.h );

  return p;
}

/**
 *
 */
void
animated_particle_update( struct particle_t *p ) {
  if ( --p->life <= 0 ) {
    p->flags |= STDS_DEATH_MASK;
    return;
  }

  p->dy += GRAVITY;

  p->x += p->dx;
  p->y += p->dy;

  p->animation->pos_x = p->x;
  p->animation->pos_y = p->y;

  Stds_AnimationUpdate( p->animation );
}

/**
 *
 */
void
animated_particle_draw( struct particle_t *p ) {
  Stds_AnimationDraw( p->animation );
}

/**
 *
 */
static void
add_particle_animation( struct particle_t *p ) {
  int8_t animation_type = Stds_RandomInt( 0, 2 );
  float  animation_time = Stds_RandomFloat( 0.05f, 0.30f );
  switch ( animation_type ) {
  case 0:
    p->animation =
        Stds_AddAnimation( "tests/res/img/particle/red/frame_", 2, animation_time, false );
    break;
  case 1:
    p->animation =
        Stds_AddAnimation( "tests/res/img/particle/green/frame_", 2, animation_time, false );
    break;
  case 2:
    p->animation =
        Stds_AddAnimation( "tests/res/img/particle/blue/frame_", 2, animation_time, false );
    break;
  default:
    break;
  }
}