#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include "draw.h"
#include "stds.h"
#include "text.h"

extern struct app_t g_app;

extern struct text_field_t *Stds_CreateTextFieldBlank( float x, float y, const char *font_directory,
                                                       const uint16_t font_size, SDL_Color *c );

extern struct text_field_t *Stds_CreateTextField( float x, float y, char *text,
                                                  const char *   font_directory,
                                                  const uint16_t font_size, SDL_Color *c );

extern void Stds_AlterTextField( struct text_field_t *tf, float x, float y, char *text );

extern void Stds_ToggleTextField( struct text_field_t *tf, bool can_read_text );

extern void Stds_ReadTextField( struct text_field_t *tf, const SDL_Event *event );

extern void Stds_DrawTextField( struct text_field_t *tf );

#endif // TEXT_FIELD_H