#include "../include/player.h"

#define DECAY_RATE    4
#define INITIAL_ALPHA 90
#define DECELERATION  0.95f
#define JUMP_VEL      -8.0f
#define VELOCITY      5.0f
#define GRAVITY       0.3f

static float               timer        = 0.f;
static float               frequency    = 0.1f;
static float               amplitude    = 0.2f;
static float               image_xscale = 0.f;
static float               image_yscale = 0.f;
static bool                is_moving    = false;
static bool                is_attacking = false;
static struct animation_t *walk_animation;

static void key_input_listener( void );
static void check_bounds( void );

/**
 *
 */
void
init_player() {
  player = malloc( sizeof( struct entity_t ) );

  if ( player == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for player_t. %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( player, 0, sizeof( struct entity_t ) );

  player->x     = app.SCREEN_WIDTH / 2.0f;
  player->y     = app.SCREEN_HEIGHT / 2.0f;
  player->angle = 0;

  walk_animation            = Stds_AddAnimation( "tests/res/img/player/test/frame_", 16, 0.05f );
  player->animation         = walk_animation;
  player->animation->camera = true; /* Apply camera offset. */
}

/**
 *
 */
void
player_update( void ) {
  key_input_listener();

  player->w = player->animation->sprite_width;
  player->h = player->animation->sprite_height;

  player->dy += GRAVITY;

  player->x += player->dx;
  player->y += player->dy;

  player->animation->pos_x = player->x;
  player->animation->pos_y = player->y;

  check_bounds();
  Stds_AnimationUpdate( player->animation );
  Stds_AddTextureTrail( player, DECAY_RATE, INITIAL_ALPHA, player->animation->flip );
}

/**
 *
 */
void
player_draw( void ) {
  Stds_AnimationDraw( player->animation );
}

/**
 *
 */
static void
key_input_listener( void ) {
  is_moving = app.keyboard[SDL_SCANCODE_A] | app.keyboard[SDL_SCANCODE_D];

  if ( app.keyboard[SDL_SCANCODE_W] ) {
    player->dy                   = JUMP_VEL;
    app.keyboard[SDL_SCANCODE_W] = 0;
  }

  if ( app.keyboard[SDL_SCANCODE_A] ) {
    player->dx              = -VELOCITY;
    player->animation->flip = SDL_FLIP_NONE;
  }

  else if ( app.keyboard[SDL_SCANCODE_D] ) {
    player->dx              = VELOCITY;
    player->animation->flip = SDL_FLIP_HORIZONTAL;
  }

  else {
    player->dx = 0;
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

  if ( player->x + player->w > app.LEVEL_WIDTH ) {
    player->x = app.LEVEL_WIDTH - player->w;
  }

  if ( player->y < 0 ) {
    player->y = 0;
  }

  if ( player->y + player->h > app.LEVEL_HEIGHT ) {
    player->y = app.LEVEL_HEIGHT - player->h;
  }
}