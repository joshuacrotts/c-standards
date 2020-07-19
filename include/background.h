#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../include/draw.h"
#include "stds.h"

extern struct app_t app;

extern void Stds_AddParallaxBackground( const char *bg_directory, size_t n,
                                        float default_scroll_speed, float modified_scroll_speeds[],
                                        bool is_infinite );

extern void Stds_ParallaxBackgroundUpdate( struct parallax_background_t *parallax );

extern void Stds_ParallaxBackgroundDraw( struct parallax_background_t *parallax );

extern struct background_t *Stds_AddBackground( const char *bg_directory );

extern void Stds_BackgroundUpdate( struct background_t *bg );

extern void Stds_BackgroundDraw( struct background_t *bg );

extern void Stds_BackgroundDie( struct background_t *bg );

#endif // BACKGROUND_H
