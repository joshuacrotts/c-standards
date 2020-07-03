#include "../include/player.h"

#define DECAY_RATE    4
#define INITIAL_ALPHA 90
#define DECELERATION  0.95f
#define JUMP_VEL      12.0f;
#define VELOCITY      5.0f
#define GRAVITY       0.3f

static bool is_moving_forward = false;

static void key_input_listener( void );
static void check_bounds( void );

void
init_player() {
  player = malloc( sizeof( entity_t ) );

  if ( player == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for player_t. %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( player, 0, sizeof( entity_t ) );

  player->x          = SCREEN_WIDTH / 2.0f;
  player->y          = SCREEN_HEIGHT / 2.0f;
  player->texture[0] = load_texture( "tests/res/img/player_blue.png" );
  player->angle = 0;
  SDL_QueryTexture( player->texture[0], NULL, NULL, &player->w, &player->h );
}

void
player_update( void ) {
  key_input_listener();

  if ( is_moving_forward ) {
    player->dx += ( float ) cos( to_radians( player->angle ) ) * 0.2f;
    player->dy += ( float ) sin( to_radians( player->angle ) ) * 0.2f;
  } else {
    player->dx *= 0.99f;
    player->dy *= 0.99f;
  }

  float maxSpeed = 5.0f;
  float speed    = ( float ) sqrt( player->dx * player->dx + player->dy * player->dy );

  if ( speed > maxSpeed ) {
    player->dx *= maxSpeed / speed;
    player->dy *= maxSpeed / speed;
  }

  player->x += player->dx;
  player->y += player->dy;

  check_bounds();
  add_trail( player, DECAY_RATE, INITIAL_ALPHA );
}

void
player_draw( void ) {
  blit_texture_rotated( player->texture[0], player->x, player->y, player->angle );
}

/*
 *
 */
static void
key_input_listener( void ) {
  is_moving_forward = app.keyboard[SDL_SCANCODE_W];

  if ( app.keyboard[SDL_SCANCODE_A] ) {
    player->angle -= 3;
  }

  if ( app.keyboard[SDL_SCANCODE_D] ) {
    player->angle += 3;
  }
}

/*
 *
 */
static void
check_bounds( void ) {
  if ( player->x < 0 ) {
    player->x = 0;
  }

  if ( player->x + player->w > LEVEL_WIDTH ) {
    player->x = LEVEL_WIDTH - player->w;
  }

  if ( player->y < 0 ) {
    player->y = 0;
  }

  if ( player->y + player->h > LEVEL_HEIGHT ) {
    player->y = LEVEL_HEIGHT - player->h;
  }
}