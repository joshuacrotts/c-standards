#include "../include/red_particle.h"

#define GRAVITY 0.2f

/**
 * 
 */
struct particle_t
red_particle_init( float x, float y ) {
  struct particle_t p;
  p.x               = x;
  p.y               = y;
  p.life            = Stds_RandomInt( 100, 300 );
  p.dx              = Stds_RandomFloat( -5.f, 5.f );
  p.dy              = Stds_RandomFloat( -10.f, -7.f );
  p.w               = Stds_RandomInt( 1, 5 );
  p.h               = p.w;
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
  p->dy += GRAVITY;

  p->x += p->dx;
  p->y += p->dy;
}

/**
 * 
 */
void
red_particle_draw( struct particle_t *p ) {
  SDL_FRect r = { p->x, p->y, p->w, p->h };
  SDL_Color c = { p->color.r, p->color.g, p->color.b, p->color.a };
  Stds_DrawRectF( &r, &c, true, false );
}