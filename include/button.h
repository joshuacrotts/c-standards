#ifndef BUTTON_H
#define BUTTON_H

#include "draw.h"
#include "stds.h"
#include "text.h"

extern void Stds_UpdateButtons( void );

extern void Stds_UpdateButtons( void );

extern struct button_t *Stds_AddButton( const float x, const float y, const uint32_t w,
                                    const uint32_t h, const bool is_filled,
                                    const char *font_directory, const uint16_t font_size,
                                    const SDL_Color *font_color, const char *text );

extern struct button_t *Stds_AddButtonTexture( const float x, const float y,
                                            const char *texture_directory,
                                            const char *font_directory, const uint16_t font_size,
                                            const SDL_Color *color, const char *text );

extern void Stds_ButtonUpdate( struct button_t *button );

extern void Stds_ButtonDraw( struct button_t *button );

extern bool Stds_IsMouseOverButton( struct button_t *button );

extern bool Stds_IsButtonClicked( struct button_t *button, const int32_t mouse_code );

#endif // BUTTON_H