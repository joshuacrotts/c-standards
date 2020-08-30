#include "../include/red_particle.h"

#define GRAVITY 0.2f

/**
 *
 */
struct particle_t
red_particle_init( float x, float y ) {
  struct particle_t p;
  p.pos      = Stds_CreateVec2( x, y );
  p.velocity = Stds_CreateVec2( Stds_RandomFloat( -5.f, 5.f ), Stds_RandomFloat( -10.f, -7.f ) );
  p.life     = Stds_RandomInt( 100, 300 );
  p.w        = Stds_RandomInt( 1, 5 );
  p.h        = p.w;

  p.particle_update = red_particle_update;
  p.particle_draw   = red_particle_draw;
  p.color.r         = 0xff;
  p.color.a         = 0xff;
  p.color.g         = 0;
  p.color.b         = 0;

  return p;
}

/**
 *
 */
void
red_particle_update( struct particle_t *p ) {
  if ( --p->life <= 0 ) {
    p->flags |= STDS_DEATH_MASK;
    return;
  }
  p->velocity.y += GRAVITY;

  Stds_AddVec2( &p->pos, &p->velocity );
}

/**
 *
 */
void
red_particle_draw( struct particle_t *p ) {
  SDL_FRect r = { p->pos.x, p->pos.y, p->w, p->h };
  SDL_Color c = { p->color.r, p->color.g, p->color.b, p->color.a };
  Stds_DrawRectF( &r, &c, true, false );
}