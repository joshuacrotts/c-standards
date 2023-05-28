/**
 * @file sound.c
 * @author Joshua Crotts
 * @date June 18 2020
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * @section DESCRIPTION
 * 
 * This file defines the SDL sound mixer initialization, and how to play/pause both sound
 * effects and music.
 */
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
  g_app.sounds = calloc( SND_MAX, sizeof( Mix_Chunk * ) );
  g_app.music  = NULL;
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
 * Stds_LoadSFX("res/sfx/coin.ogg", SND_COIN).
 *
 * @param const char * sound effect path.
 * @param int16_t sound effect ID.
 *
 * @return void.
 */
void
Stds_LoadSFX( const char *path, const int16_t id ) {
  if ( g_app.sounds[id] != NULL ) {
    SDL_Log( "Error, could not add %s audio file to id %d. This id already exists!\n", path,
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
