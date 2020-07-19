#ifndef ANIMATION_H
#define ANIMATION_H

#include "draw.h"
#include "stds.h"

extern struct app_t app;

extern struct animation_t *Stds_AddSpritesheet( const char *file_directory, uint8_t n, float frame_time,
                                     uint16_t start_x, uint16_t start_y );

extern struct animation_t *Stds_AddAnimation( const char *files_directory, uint8_t n, float frame_time );

extern void Stds_AnimationUpdate( struct animation_t *animation );

extern void Stds_AnimationDraw( struct animation_t *animation );

extern void Stds_AnimationDie( struct animation_t *animation );

#endif // ANIMATION_H
