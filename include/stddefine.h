#ifndef DEFS_H
#define DEFS_H

#define LEVEL_WIDTH             3000
#define LEVEL_HEIGHT            3000
#define SCREEN_WIDTH            1600
#define SCREEN_HEIGHT           900
#define EXIT_ERROR              1
#define EXIT_SUCCESS            0
#define MAX_KEYBOARD_KEYS       350
#define FPS                     60
#define MAX_SND_CHANNELS        16
#define MAX_LINE_LENGTH         1024
#define SMALL_TEXT_BUFFER       64
#define MAX_KEYBOARD_KEYS       350
#define MAX_MOUSE_BUTTONS       350
#define MAX_BUFFER_SIZE         128
#define MAX_FILE_NAME_LEN       48
#define TEXTURE_BUFFER_SIZE     4
#define WINDOW_UPDATE_TIMER     1000
#define PI                      3.14159265358979323846

#define DEATH_MASK              0x10000000
#define SPRITE_SHEET_MASK       2
#define STD_ANIMATION_MASK      1
#define ANIMATION_ACTIVE_MASK   0x01000000

enum GameState {
  RUNNING,
  PREGAME,
  INIT,
  PAUSED
};

enum CollisionSide {
  SIDE_TOP,
  SIDE_LEFT,
  SIDE_RIGHT,
  SIDE_BOTTOM,
  SIDE_NONE = -1
};

enum SoundChannel {
  CH_ANY = -1
};

enum SFX {
  SND_MAX
};

#endif
