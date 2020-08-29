/**
 * @file text_field.c
 * @author Joshua Crotts
 * @date July 31 2020
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
 * This file defines text-input functionality. This is not to be conflated with keyboard
 * event inputs; rather, this is reserved for entering strings of text, such as typing
 * a message.
 */
#include "../include/text_field.h"

/**
 *
 */
struct text_field_t *
Stds_CreateTextFieldBlank( float x, float y, const char *font_directory, const uint16_t font_size,
                           SDL_Color *font_color ) {
  struct text_field_t *tf;
  tf = malloc( sizeof( struct text_field_t ) );

  if ( tf == NULL ) {
    fprintf( stderr, "Error: could not allocate memory for text_field_t.\n" );
    exit( EXIT_FAILURE );
  }

  memset( tf, 0, sizeof( struct text_field_t ) );

  tf->x              = x;
  tf->y              = y;
  tf->font_directory = font_directory;
  tf->font_size      = font_size;
  tf->font_color     = font_color;

  return tf;
}

/**
 *
 */
struct text_field_t *
Stds_CreateTextField( float x, float y, char *text, const char *font_directory,
                      const uint16_t font_size, SDL_Color *c ) {
  struct text_field_t *tf;
  tf = malloc( sizeof( struct text_field_t ) );

  if ( tf == NULL ) {
    fprintf( stderr, "Error: could not allocate memory for text_field_t.\n" );
    exit( EXIT_FAILURE );
  }

  memset( tf, 0, sizeof( struct text_field_t ) );

  tf->x = x;
  tf->y = y;
  strcpy( tf->text, text );

  return tf;
}

/**
 *
 */
void
Stds_AlterTextField( struct text_field_t *tf, float x, float y, char *text ) {
  tf->x = x;
  tf->y = y;
  strcpy( tf->text, text );
}

/**
 *
 */
void
Stds_ToggleTextField( struct text_field_t *tf, bool can_read_text ) {
  tf->toggle_text_input = can_read_text;
}

/**
 *
 */
void
Stds_ReadTextField( struct text_field_t *tf, const SDL_Event *event ) {
  if ( g_app.keyboard[SDL_SCANCODE_BACKSPACE] && strlen( tf->text ) > 0 ) {
    tf->text[strlen( tf->text ) - 1]   = '\0';
    g_app.keyboard[SDL_SCANCODE_BACKSPACE] = 0;
  } else
    strcat( tf->text, event->text.text);
}

/**
 *
 */
void
Stds_DrawTextField( struct text_field_t *tf ) {
  if ( strlen( tf->text ) != 0 ) {
    Stds_DrawText( tf->x, tf->y, tf->font_directory, tf->font_size, tf->font_color, tf->text );
  }
}