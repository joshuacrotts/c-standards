#ifndef TEXT_H
#define TEXT_H

#include "stds.h"

extern app_t app;

extern void Stds_InitFonts( void );

extern void Stds_FreeFonts( void );

extern void Stds_DrawText( float x, float y, SDL_Color *c, const char *font_directory, 
                       uint16_t font_size, const char *str, ... );

extern void Stds_GetStringSize( const char *str, const char *font_name, uint16_t font_size,
                             int32_t *stored_width, int32_t *stored_height );

#endif // TEXT_H
