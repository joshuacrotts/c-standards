#include "../include/enemy.h"

/**
 * 
 */
struct entity_t *
add_enemy( float x, float y ) {
  struct entity_t *e;

  e = malloc( sizeof( struct entity_t ) );
  memset( e, 0, sizeof( struct entity_t ) );

  e->x          = x;
  e->y          = y;
  e->texture[0] = Stds_LoadTexture( "tests/res/img/grass.png" );
  SDL_QueryTexture( e->texture[0], NULL, NULL, &e->w, &e->h );

  return e;
}

/**
 * 
 */
void
enemy_update( struct entity_t *e ) {}

/**
 * 
 */
void
enemy_draw( struct entity_t *e ) {
  Stds_BlitTexture( e->texture[0], e->x, e->y, false, true );
}
