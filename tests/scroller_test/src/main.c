

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

static struct text_field_t *tf;
static struct grid_t *      grid;
static struct grid_pair_t   p;
static int32_t              testTextureGridId;

static struct polygon_t *hexa;
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
static void update_polygons( void );

static void draw_trails( void );
static void draw_enemies( void );
static void draw_parallax_backgrounds( void );
static void draw_grid( void );

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

  Stds_AddFont( "tests/scroller_test/res/fonts/nes.ttf", 16 );

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

  float parallax_scroll[11] = {0.10f, 0.15f, 0.20f, 0.25f, 0.30f, 0.35f,
                               0.40f, 0.45f, 0.50f, 0.55f, 0.60f};
  Stds_AddParallaxBackground( "tests/scroller_test/res/img/background_4/layer_0", parallax_frames, 1.0f,
                              parallax_scroll, false );

  /* Create the border fade from blue to yellow. */
  SDL_Color c1 = {0xff, 0xff, 0, 0xff};
  SDL_Color c2 = {0, 0, 0xff, 0xff};

  f.c1    = c1;
  f.c2    = c2;
  f.time  = 0.0f;
  f.alpha = 0.01f;

  /* Initialize the fire animation. */
  fire_animation = Stds_AddSpritesheet( "tests/scroller_test/res/img/particle/fire_pixel/Fire04_30x40.png", 49,
                                        0.02f, 0, 0, 7, 7 );

  /* Static positions for now just to mess around with it. */
  fire_animation->pos.x       = 200;
  fire_animation->pos.y       = 400;
  fire_animation->dest_width  = 70;
  fire_animation->dest_height = 80;

  /* Generate a standard particle system. */
  ps = Stds_CreateParticleSystem( 50000 );

  /* Create the white grid for testing. */
  SDL_Color tempGridColor = {255, 255, 255, 255};
  grid                    = Stds_CreateGrid( 0, 0, 32, 32, 10, 10, &tempGridColor, &tempGridColor );

  /* Initializes textures for the grid. */
  Stds_InitializeGridTextures( grid, 1 );
  testTextureGridId = Stds_AddGridTexture( grid, "tests/scroller_test/res/img/player.png" );

  /* Initialize spriteSheet for the grid. */
  Stds_AddSpriteSheetToGrid( grid, "tests/scroller_test/res/img/Tilemap.png", 10, 10 );

  Stds_AddAnimationToGrid( grid, Stds_AddSpritesheet( "tests/scroller_test/res/img/player/spritesheet_test.png",
                                                      16, 0.05f, 0, 0, 4, 4 ) );
  grid->is_camera_offset_enabled = false;

  struct vec2_t pos = Stds_CreateVec2( 200, 100 );
  hexa              = Stds_CreatePolygon( 6, 40.0f, pos, 10.0f );
  pos               = Stds_CreateVec2( 220, 300 );
  quad              = Stds_BoundingBox( 220.0f, 300.0f, 100.0f, 20.0f, 0.0f );

  /* Init text field for testing. */
  SDL_Color c = {0xff, 0, 0, 0xff};
  tf          = Stds_CreateTextFieldBlank( 300.f, 300.f, "tests/scroller_test/res/fonts/nes.ttf", 16, &c );
  tf->toggle_text_input = true;

  g_app.text_field_tail->next = tf;
  g_app.text_field_tail = tf;
}

/**
 *
 */
static void
update( void ) {
  if ( g_app.mouse.button[SDL_BUTTON_LEFT] ) {
    add_particles( g_app.mouse.x, g_app.mouse.y, 1000 );
  }

  Stds_CameraUpdate( player );
  Stds_ParticleSystemUpdate( ps );
  update_parallax_backgrounds();
  update_trails();
  update_enemies();
  player_update();
  update_grid();
  Stds_AnimationUpdate( fire_animation );
  update_polygons();
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
      player->velocity.y = 0;
    }

    if ( s == SIDE_LEFT || s == SIDE_RIGHT ) {
      player->velocity.x = 0;
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

  Stds_DrawPolygon( quad );
  Stds_DrawPolygon( hexa );
  Stds_DrawTextField( tf );
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
  Stds_CleanUpPolygon( hexa );
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
}

/**
 *
 */
static void
update_grid( void ) {
  /* Hover code for grid */
  p = Stds_OnGridHover( grid );
}
/*
 *
 */
static void
update_polygons( void ) {

  Stds_UpdatePolygon( hexa );
  Stds_UpdatePolygon( quad );

  hexa->position.x = ( float ) g_app.mouse.x;
  hexa->position.y = ( float ) g_app.mouse.y;

  quad->angle = 90.0f;

  Stds_CheckSATOverlap( hexa, quad );
}