#include "../include/red_particle.h"

#define GRAVITY 0.2f

void
red_particle_update( struct particle_t *p ) {
  if ( --p->life <= 0 ) {
    p->flags |= DEATH_MASK;
    return;
  }
  p->dy += GRAVITY;

  p->x += p->dx;
  p->y += p->dy;
}

void
red_particle_draw( struct particle_t *p ) {
  SDL_FRect r = {p->x, p->y, p->w, p->h};
  SDL_Color c = {p->color.r, p->color.g, p->color.b, p->color.a};
  Stds_DrawRectF( &r, &c, true, false );
}