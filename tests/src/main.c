

#include "../include/main.h"
#include "../include/player.h"

#define S_WIDTH  700
#define S_HEIGHT 700
#define L_WIDTH  3000
#define L_HEIGHT S_HEIGHT

struct entity_t *player;
struct stage_t   stage;

static SDL_Rect                  screen_edge;
static struct fade_color_t       f;
static struct particle_system_t *ps;
static struct animation_t *      fire_animation;

static struct grid_t *    grid;
static struct grid_pair_t p;
static int32_t            testTextureGridId;
static struct vec2_t cp, cn, ray = {100.0f, 100.0f}, ray_direction = { 1, 1 };
float t;
static SDL_FRect ray_rect = {300.0f, 300.0f, 200.0f, 100.0f}, other_rect = {500.0f, 500.0f, 100.0f, 100.0f};

static struct polygon_t *triangle;
static struct polygon_t *quad;

static void init_scene( void );
static void cleanup_stage( void );
static void draw( void );
static void update( void );
static void check_enemy_collision( void );
static void add_particles( int32_t, int32_t, size_t );

static void update_trails( void );
static void update_enemies( void );
static void update_parallax_backgrounds( void );
static void update_grid( void );

static void draw_trails( void );
static void draw_enemies( void );
static void draw_parallax_backgrounds( void );
static void draw_grid( void );
static void draw_collision_test( void );

/**
 * Barebones game. This is the minimum amount of code
 * necessary to run a window.
 *
 * @paramint32_targc, number of cmd arguments.
 * @param char* [] array of string arguments.
 *
 * @return status code.
 */
int
main( int argc, char *argv[] ) {
  atexit( cleanup_stage );

  Stds_InitGame( "Trail, Parallax Test, and Button Test", S_WIDTH, S_HEIGHT, L_WIDTH, L_HEIGHT );
  Stds_InitAppStructures();
  Stds_ToggleDebugMode( true );
  init_scene();
  Stds_GameLoop();

  return 0;
}

/**
 * Initializes the delegation structure to use the
 * update and draw methods for rendering and updating
 * the game. These methods must be defined because the
 * delegation structure uses them in the loop function.
 *
 * Sprites and structs are also initalized here.
 */
static void
init_scene( void ) {
  g_app.delegate.update = update;
  g_app.delegate.draw   = draw;
  stage.enemy_tail      = &stage.enemy_head;

  init_player();

  /* Create the green grass tiles for collision testing. */
  for ( uint32_t i = 0, x = 0; i < 30; i++, x += 48 ) {
    struct entity_t *e;
    e = add_enemy( x, g_app.LEVEL_HEIGHT - 20 );

    stage.enemy_tail->next = e;
    stage.enemy_tail       = e;
  }

  /* Initialize the parallax background with each frame's scroll factor. */
  uint8_t parallax_frames = 11;

  float parallax_scroll[11] = { 0.10f, 0.15f, 0.20f, 0.25f, 0.30f, 0.35f,
                                0.40f, 0.45f, 0.50f, 0.55f, 0.60f };
  Stds_AddParallaxBackground( "tests/res/img/background_4/layer_0", parallax_frames, 1.0f,
                              parallax_scroll, false );

  /* Create the border fade from blue to yellow. */
  SDL_Color c1 = { 0xff, 0xff, 0, 0xff };
  SDL_Color c2 = { 0, 0, 0xff, 0xff };

  f.c1    = c1;
  f.c2    = c2;
  f.time  = 0.0f;
  f.alpha = 0.01f;

  /* Initialize the fire animation. */
  fire_animation = Stds_AddSpritesheet( "tests/res/img/particle/fire_pixel/Fire04_30x40.png", 49,
                                        0.02f, 0, 0, 7, 7 );

  /* Static positions for now just to mess around with it. */
  fire_animation->pos_x       = 200;
  fire_animation->pos_y       = 400;
  fire_animation->dest_width  = 70;
  fire_animation->dest_height = 80;

  /* Generate a standard particle system. */
  ps = Stds_CreateParticleSystem( 1024 );

  /* Create the white grid for testing. */
  SDL_Color tempGridColor = { 255, 255, 255, 255 };
  grid                    = Stds_CreateGrid( 0, 0, 32, 32, 10, 10, &tempGridColor, &tempGridColor );

  /* Initializes textures for the grid. */
  Stds_InitializeGridTextures( grid, 1 );
  testTextureGridId = Stds_AddGridTexture( grid, "tests/res/img/player.png" );

  /* Initialize spriteSheet for the grid. */
  Stds_AddSpriteSheetToGrid( grid, "tests/res/img/Tilemap.png", 10, 10 );

  Stds_AddAnimationToGrid( grid, Stds_AddSpritesheet( "tests/res/img/player/spritesheet_test.png",
                                                      16, 0.05f, 0, 0, 4, 4 ) );
  grid->is_camera_offset_enabled = false;

  struct vec2_t pos = Stds_CreateVec2( 200, 100 );
  triangle = Stds_CreatePolygon( 3, 1, pos, 0.0f );
  pos = Stds_CreateVec2( 220, 300 );
  quad = Stds_CreatePolygon( 4, 4, pos, 90.0f );
}

/**
 *
 */
static void
update( void ) {
  if ( g_app.mouse.button[SDL_BUTTON_LEFT] ) {
    add_particles( g_app.mouse.x, g_app.mouse.y, 32 );
  }

  Stds_CameraUpdate( player );
  Stds_ParticleSystemUpdate( ps );
  update_parallax_backgrounds();
  update_trails();
  update_enemies();
  player_update();
  update_grid();
  Stds_AnimationUpdate( fire_animation );
}

/**
 *
 */
static void
update_trails( void ) {
  struct trail_t *t;
  struct trail_t *prev;

  prev = &g_app.trail_head;

  for ( t = g_app.trail_head.next; t != NULL; t = t->next ) {
    Stds_TrailUpdate( t );

    if ( t->flags & STDS_DEATH_MASK ) {
      if ( t == g_app.trail_tail ) {
        g_app.trail_tail = prev;
      }

      prev->next = t->next;
      free( t );
      t = prev;
    }
    prev = t;
  }
}

/**
 *
 */
static void
update_parallax_backgrounds( void ) {
  struct parallax_background_t *p;
  for ( p = g_app.parallax_head.next; p != NULL; p = p->next ) {
    Stds_ParallaxBackgroundUpdate( p );
  }
}

/**
 *
 */
static void
update_enemies( void ) {
  struct entity_t *e;
  for ( e = stage.enemy_head.next; e != NULL; e = e->next ) {
    enum CollisionSide s = Stds_CheckAABBCollision( player, e );

    if ( s == SIDE_TOP || s == SIDE_BOTTOM ) {
      player->dy = 0;
    }

    if ( s == SIDE_LEFT || s == SIDE_RIGHT ) {
      player->dx = 0;
    }
  }
}

/**
 *
 */
static void
draw( void ) {
  SDL_Color c = Stds_CombineFadeColor( &f );
  draw_parallax_backgrounds();
  Stds_ParticleSystemDraw( ps );
  Stds_DrawRectStroke( 0, 0, g_app.SCREEN_WIDTH, g_app.SCREEN_HEIGHT, 8, &c, 0xff );
  draw_trails();
  draw_enemies();
  player_draw();
  draw_grid();
  Stds_AnimationDraw( fire_animation );
  draw_collision_test();

  Stds_UpdatePolygon( triangle );
  Stds_UpdatePolygon( quad );

  triangle->position.x = ( float ) g_app.mouse.x;
  triangle->position.y = ( float ) g_app.mouse.y;

  triangle->overlap = Stds_CheckSATOverlap( triangle, quad );
  quad->overlap = Stds_CheckSATOverlap( quad, triangle );

  Stds_DrawPolygon( quad );
  Stds_DrawPolygon( triangle );
}

/**
 *
 */
static void
draw_trails( void ) {
  struct trail_t *t;
  for ( t = g_app.trail_head.next; t != NULL; t = t->next ) {
    Stds_TrailDraw( t );
  }
}

/**
 *
 */
static void
draw_parallax_backgrounds( void ) {
  struct parallax_background_t *p;
  for ( p = g_app.parallax_head.next; p != NULL; p = p->next ) {
    Stds_ParallaxBackgroundDraw( p );
  }
}

/**
 *
 */
static void
draw_enemies( void ) {
  struct entity_t *e;
  for ( e = stage.enemy_head.next; e != NULL; e = e->next ) {
    enemy_draw( e );
  }
}

/**
 * Cleans up whatever elements are left via the stage and not Stds itself.
 * Be sure to assign the callback with atexit(...) BEFORE calling Stds_GameLoop()!
 *
 * @param void.
 *
 * @return void.
 */
static void
cleanup_stage( void ) {
  SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Freeing player and grid components.\n" );
  free( player );
  Stds_FreeGrid( grid );
  Stds_AnimationDie( fire_animation );
  Stds_CleanUpPolygon( triangle );
  Stds_CleanUpPolygon( quad );
}

/**
 *
 */
static void
add_particles( int32_t x, int32_t y, size_t n ) {
  for ( uint32_t i = 0; i < n; i++ ) {
    struct particle_t p;

    /* Adds an animated particle. */
    p            = square_particle_init( x, y );
    int32_t code = Stds_InsertParticle( ps, &p );
    if ( code == PS_FULL ) {
      return;
    }
  }
}

/**
 *
 */
static void
draw_grid( void ) {
  Stds_DrawLineGrid( grid );
  Stds_RenderPreMadeSpriteSheet( grid );
}

/**
 *
 */
static void
update_grid( void ) {
  /* Hover code for grid */
  p = Stds_OnGridHover( grid );
}

/**
 *
 */
static void 
draw_collision_test( void ) {
  //Ray Vs Rect example.
  /*
  ray_direction.x = g_app.mouse.x - ray.x;
  ray_direction.y = g_app.mouse.y - ray.y;
  
  SDL_SetRenderDrawColor( g_app.renderer, 0, 0, 255, 255);
  SDL_RenderDrawLineF( g_app.renderer, ray.x, ray.y, g_app.mouse.x, g_app.mouse.y );

  if ( Stds_RayVsRect( &ray, &ray_direction, &ray_rect, &cp, &cn, &t ) && t < 1 ) {
    SDL_SetRenderDrawColor( g_app.renderer, 0, 255, 0, 255);
    SDL_RenderFillRectF( g_app.renderer, &ray_rect );
  } else {
    SDL_SetRenderDrawColor( g_app.renderer, 255, 0, 0, 255);
    SDL_RenderFillRectF( g_app.renderer, &ray_rect );
  }
  */

  //Rect Vs Rect example.
  /*
  if ( Stds_AdvRectVsRect( &ray_rect, &other_rect, &cp, &cn, &t, &ray_direction ) ) {
    ray_direction.x = 0;
    ray_direction.y = 0;
    SDL_SetRenderDrawColor( g_app.renderer, 0, 255, 0, 255);
    SDL_RenderFillRectF( g_app.renderer, &ray_rect );
  } else {
    SDL_SetRenderDrawColor( g_app.renderer, 255, 0, 0, 255);
    SDL_RenderFillRectF( g_app.renderer, &ray_rect );
  } 

  SDL_SetRenderDrawColor( g_app.renderer, 255, 0, 0, 255);
  SDL_RenderFillRectF( g_app.renderer, &other_rect );

  ray_rect.x += ray_direction.x;
  ray_rect.y += ray_direction.y;
  */
}