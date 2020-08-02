#include "../include/square_particle.h"

/**
 *
 */
struct particle_t
square_particle_init( float x, float y ) {
  struct particle_t p;
  p.pos      = Stds_CreateVec2( x, y );
  p.velocity = Stds_CreateVec2( Stds_RandomFloatBounded( -7.f, -0.5f, 0.5f, 7.f ),
                                Stds_RandomFloatBounded( -7.f, -0.5f, 0.5f, 7.f ) );
  p.life     = Stds_RandomInt( 100, 300 );

  p.dw              = Stds_RandomFloat( 1.f, 4.f );
  p.dh              = p.dw;
  p.delta_alpha     = p.dw * 2;
  p.delta_angle     = Stds_RandomInt( -3, 3 );
  p.particle_update = square_particle_update;
  p.particle_draw   = square_particle_draw;
  p.current_texture = Stds_LoadTexture( "tests/res/img/particle/beige.png" );
  p.color.a         = Stds_RandomInt( 0, 128 );

  int32_t pw, ph;
  SDL_QueryTexture( p.current_texture, NULL, NULL, &pw, &ph );
  p.w = pw;
  p.h = ph;

  return p;
}

/**
 *
 */
void
square_particle_update( struct particle_t *p ) {
  if ( p->w <= 0 || p->h <= 0 || p->color.a <= 0 ) {
    p->flags |= STDS_DEATH_MASK;
    return;
  }

  p->angle += p->delta_angle;
  --p->color.a;

  Stds_AddVec2( &p->pos, &p->velocity );
  p->w -= p->dw;
  p->h -= p->dh;
}

/**
 *
 */
void
square_particle_draw( struct particle_t *p ) {
  SDL_SetTextureBlendMode( p->current_texture, SDL_BLENDMODE_ADD );
  SDL_SetTextureAlphaMod( p->current_texture, p->color.a );
  Stds_DrawTexture( p->current_texture, p->pos.x, p->pos.y, p->w, p->h, p->angle, SDL_FLIP_NONE,
                    NULL, false );
  SDL_SetTextureBlendMode( p->current_texture, SDL_BLENDMODE_NONE );
}