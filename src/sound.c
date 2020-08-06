//=============================================================================================//
// FILENAME :       sound.c
//
// DESCRIPTION :
//        This file defines the SDL sound mixer initialization, and how to play/pause both sound
//        effects and music.
//
// NOTES :
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.
//
// AUTHOR :   Joshua Crotts        START DATE :    18 Jun 2020
//
//=============================================================================================//

#include "../include/sound.h"

/**
 * Initializes the sound context for SDL.
 *
 * @param void.
 *
 * @return void.
 */
void
Stds_InitAudio( void ) {
  g_app.sounds = malloc( sizeof( Mix_Chunk * ) * SND_MAX );
  g_app.music  = NULL;
  memset( g_app.sounds, 0, sizeof( Mix_Chunk * ) * SND_MAX );
}

/**
 * Loads a music file from the respective path.
 *
 * @param const char* path of music file.
 *
 * @return void.
 */
void
Stds_LoadMusic( const char *fileName ) {
  if ( g_app.music != NULL ) {
    Mix_HaltMusic();
    Mix_FreeMusic( g_app.music );
    g_app.music = NULL;
  }

  g_app.music = Mix_LoadMUS( fileName );
}

/**
 * Toggles the playback of the currently-loaded song.
 *
 * @param bool true to play, false otherwise.
 *
 * @return void.
 */
void
Stds_PlayMusic( const bool loop ) {
  Mix_PlayMusic( g_app.music, loop ? -1 : 0 );
}

/**
 * Loads a sound into the respective ID of the SFX.
 * For instance,
 *
 * Stds_LoadSound("res/sfx/coin.ogg", SND_COIN).
 *
 * @param const char * sound effect path.
 * @param int16_t sound effect ID.
 *
 * @return void.
 */
void
Stds_LoadSound( const char *path, const int16_t id ) {
  if ( g_app.sounds[id] != NULL ) {
    fprintf( stderr, "Error, could not add %s audio file to id %d. This id already exists!\n", path,
             id );
    exit( EXIT_FAILURE );
  }
  g_app.sounds[id] = Mix_LoadWAV( path );
}

/**
 * Plays a sound with the respective channel and ID of the SFX.
 * For instance,
 *
 * Ex: Stds_PlaySFX(SND_BRICK_BREAKER, CH_ANY).
 *
 * @param int16_t sound effect ID from enum.
 * @param int16_t channel from enum.
 *
 * @return void.
 */
void
Stds_PlaySFX( const int16_t id, const int16_t channel ) {
  Mix_PlayChannel( channel, g_app.sounds[id], 0 );
}
