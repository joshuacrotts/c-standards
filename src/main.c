#include "../include/main.h"

static void init_scene(void);
static void draw(void);
static void tick(void);
static void cleanup_stage(void);

// Barebones game. This is the minimum amount of code
// necessary to run a window.
int main(int argc, char* argv[]) {
  initGame("Standards C Library", SCREEN_WIDTH, SCREEN_HEIGHT);
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

  memset(&stage, 0, sizeof(Stage));
  app.textureTail = &app.textureHead;
}

/*
 *
 */
static void tick(void) {
}

/*
 *
 */
static void draw(void) {
}

static void cleanup_stage(void) {
}