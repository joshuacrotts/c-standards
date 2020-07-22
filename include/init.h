#ifndef INIT_H
#define INIT_H

#include "background.h"
#include "sound.h"
#include "stds.h"
#include "text.h"

extern struct app_t app;

extern void Stds_InitGame( const char *title, uint32_t w, uint32_t h, uint32_t lw, uint32_t lh );

extern void Stds_Quit( void );

extern void Stds_ToggleDebugMode( bool is_debugging );

#endif // INIT_H
