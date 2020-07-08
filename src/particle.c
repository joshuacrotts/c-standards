#include "../include/particle.h"
#include "../include/stds.h"

void
particle_update( particle_t *p ) {

  if ( --p->life <= 0 ) {
    p->flags |= DEATH_MASK;
    return;
  }

  p->x += p->dx;
  p->y += p->dy;
}

void
particle_draw( particle_t *p ) {
  SDL_Rect r;
  r.x = ( int32_t ) p->x;
  r.y = ( int32_t ) p->y;
  r.w = ( int32_t ) p->w;
  r.h = ( int32_t ) p->h;

  SDL_Color c;
  c.r = 0xff;
  c.g = c.b = 0;
  c.a       = 0xff;

  draw_rect( &r, &c, true, false );
}