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
  p.pos.x               = x;
  p.pos.y               = y;
  p.life            = Stds_RandomInt( 100, 300 );
  p.velocity.x              = Stds_RandomFloat( -5.f, 5.f );
  p.velocity.y              = Stds_RandomFloat( -10.f, -7.f );
  p.particle_update = animated_particle_update;
  p.particle_draw   = animated_particle_draw;

  add_particle_animation( &p );

  int32_t pw, ph;
  SDL_QueryTexture( p.animation->current_texture, NULL, NULL, &pw, &ph );
  p.w = pw;
  p.h = ph;

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

  p->velocity.y += GRAVITY;

  Stds_AddVec2(&p->pos, &p->velocity);
  p->animation->pos = Stds_CloneVec2(&p->pos);

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
    p->animation = Stds_AddAnimation( "tests/res/img/particle/red/frame_", 2, animation_time );
    break;
  case 1:
    p->animation = Stds_AddAnimation( "tests/res/img/particle/green/frame_", 2, animation_time );
    break;
  case 2:
    p->animation = Stds_AddAnimation( "tests/res/img/particle/blue/frame_", 2, animation_time );
    break;
  default:
    break;
  }
}