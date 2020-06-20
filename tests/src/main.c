#include "../include/main.h"
#include "../include/player.h"

static void init_scene(void);
static void draw(void);
static void tick(void);
static void cleanup_stage(void);

static void update_trails(void);
static void draw_trails(void);

// Barebones game. This is the minimum amount of code
// necessary to run a window.
int main(int argc, char* argv[]) {
  initGame("Trail Test", SCREEN_WIDTH, SCREEN_HEIGHT);
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
static void init_scene(void) {
  app.delegate.tick = tick;
  app.delegate.draw = draw;

  app.textureTail = &app.textureHead;
  app.fontTail = &app.fontHead;
  app.trailTail = &app.trailHead;

  init_player();
}

/*
 *
 */
static void tick(void) {
    update_trails();
    player_update();
}

/*
 *
 */
static void update_trails(void) {
    Trail* t;
    Trail* prev;

    prev = &app.trailHead;

    for (t = app.trailHead.next; t != NULL; t = t->next) {
        trail_update(t);

        if (t->flags & DEATH_MASK) {
            if (t == app.trailTail) {
                app.trailTail = prev;
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
static void draw(void) {
    draw_trails();
    player_draw();
}

/*
 *
 */
static void draw_trails(void) {
    Trail* t;

    for (t = app.trailHead.next; t != NULL; t = t->next) {
        trail_draw(t);
    }
}

/*
 *
 */
static void cleanup_stage(void) {
    free(player);
}

