/**
 * @file button.c
 * @author Joshua Crotts
 * @date June 22 2020
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
 * Defines the functions associated with buttons and detecting button events like clicking
 * and movement.
 */
#include "../include/button.h"

/**
 * Updates all buttons in the app struct.
 *
 * @param void.
 *
 * @return void.
 */
void
Stds_UpdateButtons( void ) {
  struct button_t *b;
  for ( b = g_app.button_head.next; b != NULL; b = b->next ) {
    Stds_ButtonUpdate( b );
  }
}

/**
 * Draws all buttons in the app struct.
 *
 * @param void.
 *
 * @return void.
 */
void
Stds_DrawButtons( void ) {
  struct button_t *b;
  for ( b = g_app.button_head.next; b != NULL; b = b->next ) {
    Stds_ButtonDraw( b );
  }
}

/**
 * Adds a button with no texture. This is useful for buttons that have to change colors overtime, or
 * just don't have an accompanying texture. Make sure to change the color with button->color = ...
 *
 * @param float x top-left x pos of button.
 * @param float y top-left y pos of button.
 * @param uint32_t w width of button.
 * @param uint32_t h height of button.
 * @param bool true if the button should be filled with color, false otherwise.
 * @param const char* string to font path used for the text.
 * @param uint16_t size of font.
 * @param SDL_Color* color to draw font.
 * @param const char* text to draw.
 *
 * @return button_t pointer.
 */
struct button_t *
Stds_AddButton( const float x, float y, const uint32_t w, const uint32_t h, const bool is_filled,
                const char *font_path, const uint16_t size, const SDL_Color *fc,
                const char *text ) {
  struct button_t *button;
  button = malloc( sizeof( struct button_t ) );

  if ( button == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                 "Error: could not allocate memory for button_t, %s.\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( button, 0, sizeof( struct button_t ) );
  SDL_Color black    = { 0, 0, 0 };
  button->rect.x     = ( int32_t ) x;
  button->rect.y     = ( int32_t ) y;
  button->rect.w     = w;
  button->rect.h     = h;
  button->font_path  = font_path;
  button->font_size  = size;
  button->color      = black;
  button->text_color = *fc;
  button->is_filled  = is_filled;

  int32_t fw, fh;
  Stds_GetStringSize( text, button->font_path, button->font_size, &fw, &fh );

  button->text_x = button->rect.x + ( ( button->rect.w - fw ) / 2 );
  button->text_y = button->rect.y + ( ( button->rect.h - fh ) / 2 );

  return button;
}

/**
 * Adds a button with a texture.
 *
 * @param float x top-left x pos of button.
 * @param float y top-left y pos of button.
 * @param const char* string to texture for button.
 * @param const char* string to font path used for the text.
 * @param uint16_t size of font.
 * @param SDL_Color* color to draw font.
 * @param const char* text to draw.
 *
 * @return button_t pointer.
 */
struct button_t *
Stds_AddButtonTexture( const float x, const float y, const char *file_path, const char *font_path,
                       const uint16_t size, const SDL_Color *fc, const char *text ) {
  struct button_t *button;
  button = calloc( 1, sizeof( struct button_t ) );

  if ( button == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                 "Error: could not allocate memory for button_t, %s.\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  button->texture_id                  = 0;
  button->texture[button->texture_id] = Stds_LoadTexture( file_path );

  button->rect.x     = ( int32_t ) x;
  button->rect.y     = ( int32_t ) y;
  button->font_path  = font_path;
  button->font_size  = size;
  button->text       = text;
  button->text_color = *fc;

  SDL_QueryTexture( button->texture[button->texture_id], NULL, NULL, &button->rect.w,
                    &button->rect.h );

  int32_t fw, fh;
  Stds_GetStringSize( text, button->font_path, button->font_size, &fw, &fh );

  button->text_x = button->rect.x + ( ( button->rect.w - fw ) / 2 );
  button->text_y = button->rect.y + ( ( button->rect.h - fh ) / 2 );

  return button;
}

/**
 * Updates the logic for the button parameter.
 *
 * @param button_t* pointer to button struct.
 *
 * @return void.
 */
void
Stds_ButtonUpdate( struct button_t *b ) {}

/**
 * Draws the button.
 *
 * @param button_t* pointer to button struct.
 *
 * @return void.
 */
void
Stds_ButtonDraw( struct button_t *b ) {
  if ( b->texture[b->texture_id] != NULL ) {
    Stds_DrawTexture( b->texture[b->texture_id], b->rect.x, b->rect.y, b->rect.w, b->rect.h, 0,
                      SDL_FLIP_NONE, NULL, true );
  } else {
    Stds_DrawRect( &b->rect, &b->color, b->is_filled, true );
  }
  Stds_DrawText( b->text_x, b->text_y, b->font_path, b->font_size, &b->text_color, b->text );
}

/**
 * Determines if the mouse cursor is over the rectangle
 * box associated with the button_t struct.
 *
 * @param button_t* pointer to button struct.
 *
 * @return bool true if mouse is over, false otherwise.
 */
inline bool
Stds_IsMouseOverButton( struct button_t *b ) {
  return Stds_IsMouseOverRect( g_app.mouse.x, g_app.mouse.y, &b->rect );
}

/**
 * Determines if the button was clicked on by the provided mouse-code.
 * This should most often be SDL_BUTTON_LEFT for the left mouse button.
 *
 * @param button_t* pointer to button struct.
 * @param int32_t mouse code to test if clicked.
 *
 * @return true if mouse code was used to click, false otherwise.
 */
bool
Stds_IsButtonClicked( struct button_t *b, int32_t mouse_code ) {
  if ( Stds_IsMouseOverButton( b ) && g_app.mouse.button[mouse_code] ) {
    g_app.mouse.button[mouse_code] = 0;
    return true;
  }
  return false;
}
