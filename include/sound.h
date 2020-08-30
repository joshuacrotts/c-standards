#ifndef SOUND_H
#define SOUND_H

#include "stds.h"

extern struct app_t g_app;

extern void Stds_InitAudio( void );

extern void Stds_LoadMusic( const char *music_path );

extern void Stds_LoadSFX( const char *sfx_path, int16_t sfx_id );

extern void Stds_PlayMusic( const bool is_playing );

extern void Stds_PlaySFX( const int16_t sound_effect_id, const int16_t channel );

#endif // SOUND_H
