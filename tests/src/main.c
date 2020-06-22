#include "../include/main.h"
#include "../include/player.h"

static button_t *play_button;

static void init_play_button(void);

static void init_scene(void);
static void cleanup_stage(void);
static void draw(void);
static void tick(void);

static void update_trails(void);
static void update_parallax_backgrounds(void);

static void draw_trails(void);
static void draw_parallax_backgrounds(void);


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
    init_play_button();

    uint8_t parallax_frames = 5;

    float parallax_scroll[5] = {0.10f, 0.15f, 0.20f, 0.25f, 0.30f};
    init_parallax_background("tests/res/img/background_3/Layer", parallax_frames, 16.0f, parallax_scroll, true);
}


/*
 *
 */
static void 
init_play_button(void) {
    SDL_Color fc;
    fc.r = 0xff;
    fc.g = 0xff;
    fc.b = 0xff;
    play_button = add_button_texture(200, 200, "tests/res/img/ui/buttonStock1.png", "tests/res/fonts/nes.ttf", 24, &fc, "PLAY");
    play_button->texture[1] = load_texture("tests/res/img/ui/buttonStock1h.png");
    app.button_tail->next = play_button;
    app.button_tail = play_button;    
}


/*
 *
 */
static void 
tick(void) {
    update_parallax_backgrounds();
    update_trails();
    update_buttons();
    player_update();

    if (is_mouse_over_button(play_button)) {
        play_button->texture_id = 1;
    } else {
        play_button->texture_id = 0;
    }

    if (is_button_clicked(play_button, SDL_BUTTON_LEFT)) {
        print("CLICKED");
    }
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
    draw_buttons();
    player_draw();
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
cleanup_stage(void) {
    free(player);
}