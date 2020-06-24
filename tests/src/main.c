#include "../include/main.h"
#include "../include/player.h"

static void init_scene(void);
static void cleanup_stage(void);
static void draw(void);
static void tick(void);
static void check_enemy_collision(void);

static void update_trails(void);
static void update_parallax_backgrounds(void);

static void draw_trails(void);
static void draw_parallax_backgrounds(void);

static entity_t *enemy1;


// Barebones game. This is the minimum amount of code
// necessary to run a window.
int 
main(int argc, char *argv[]) {
  init_game("Trail, Parallax Test, and Button Test", SCREEN_WIDTH, SCREEN_HEIGHT);
  init_app_structures();
  init_scene();
  loop();

  atexit(cleanup_stage);
  return 0;
}


/*
 * Initializes the delegation structure to use the
 * tick and draw methods for rendering and updating
 * the game. These methods must be defined because the
 * delegation structure uses them in the loop function.
 *
 * Sprites and structs are also initalized here.
 */
static void 
init_scene(void) {
    app.delegate.tick = tick;
    app.delegate.draw = draw;
    
    init_player();
    enemy1 = add_enemy(200, 200);

    uint8_t parallax_frames = 5;

    float parallax_scroll[5] = {0.10f, 0.15f, 0.20f, 0.25f, 0.30f};
    init_parallax_background("tests/res/img/background_3/Layer", parallax_frames, 16.0f, parallax_scroll, true);
}


/*
 *
 */
static void 
tick(void) {
    update_parallax_backgrounds();
    update_trails();
    player_update();
    enemy_update(enemy1);
    check_enemy_collision();
}


/*
 *
 */
static void 
update_trails(void) {
    trail_t *t;
    trail_t *prev;

    prev = &app.trail_head;

    for (t = app.trail_head.next; t != NULL; t = t->next) {
        trail_update(t);

        if (t->flags & DEATH_MASK) {
            if (t == app.trail_tail) {
                app.trail_tail = prev;
            }

            prev->next = t->next;
            free(t);
            t = prev;
        }
        prev = t;
    }
}


/* 
 *
 */
static void 
update_parallax_backgrounds(void) {
    parallax_background_t *p;
    for (p = app.parallax_head.next; p != NULL; p = p->next) {
        parallax_background_update(p);
    }
}


/*
 *
 */
static void 
draw(void) {
    draw_parallax_backgrounds();
    draw_trails();
    player_draw();
    enemy_draw(enemy1);
}


/*
 *
 */
static void 
draw_trails(void) {
    trail_t *t;

    for (t = app.trail_head.next; t != NULL; t = t->next) {
        trail_draw(t);
    }
}


/*
 *
 */
static void 
draw_parallax_backgrounds(void) {
    parallax_background_t *p;

    for (p = app.parallax_head.next; p != NULL; p = p->next) {
        parallax_background_draw(p);
    }    
}


/*
 *
 */
static void 
check_enemy_collision(void) {
    enum CollisionSide s = check_aabb_collision(player, enemy1);

    if (s == SIDE_TOP || s == SIDE_BOTTOM) {
        player->dy = 0;
    }

    if (s == SIDE_LEFT || s == SIDE_RIGHT) {
        player->dx = 0;
    }
}


/*
 *
 */
static void 
cleanup_stage(void) {
    free(player);
}