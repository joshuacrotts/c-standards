#ifndef TRAIL_H
#define TRAIL_H

#include "draw.h"
#include "stds.h"

extern struct app_t app;

extern void Stds_AddTrail( struct entity_t *parent_entity, int16_t alpha_decay_rate,
                           int16_t starting_alpha, bool is_texture, SDL_RendererFlip flip );

extern void Stds_TrailUpdate( struct trail_t *t );

extern void Stds_TrailDraw( struct trail_t *t );

#endif // TRAIL_H