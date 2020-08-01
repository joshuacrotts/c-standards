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

  player->pos   = Stds_CreateVec2( g_app.SCREEN_WIDTH / 2.f, g_app.SCREEN_HEIGHT / 2.f );
  player->angle = 0;

  walk_animation    = Stds_AddAnimation( "tests/res/img/player/test/frame_", 16, 0.05f );
  player->animation = walk_animation;
  player->animation->is_camera_offset_enabled = true; /* Apply camera offset. */
}

/**
 *
 */
void
player_update( void ) {
  key_input_listener();

  player->w = player->animation->sprite_width;
  player->h = player->animation->sprite_height;

  player->velocity.y += GRAVITY;

  Stds_AddVec2( &player->pos, &player->velocity );
  player->animation->pos = Stds_CloneVec2( &player->pos );

  check_bounds();
  Stds_AnimationUpdate( player->animation );
  Stds_AddTextureTrail( player, DECAY_RATE, INITIAL_ALPHA, player->animation->flip, true );
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
  is_moving = g_app.keyboard[SDL_SCANCODE_A] | g_app.keyboard[SDL_SCANCODE_D];

  if ( g_app.keyboard[SDL_SCANCODE_W] ) {
    player->velocity.y            = JUMP_VEL;
    g_app.keyboard[SDL_SCANCODE_W] = 0;
  }

  if ( g_app.keyboard[SDL_SCANCODE_A] ) {
    player->velocity.x     = -VELOCITY;
    player->animation->flip = SDL_FLIP_NONE;
  }

  else if ( g_app.keyboard[SDL_SCANCODE_D] ) {
    player->velocity.x     = VELOCITY;
    player->animation->flip = SDL_FLIP_HORIZONTAL;
  }

  else {
    player->velocity.x = 0;
  }
}

/*
 *
 */
static void
check_bounds( void ) {
  Stds_ClampFloat(&player->pos.x, 0, g_app.LEVEL_WIDTH - player->w);
  Stds_ClampFloat(&player->pos.y, 0, g_app.LEVEL_HEIGHT - player->h);
}