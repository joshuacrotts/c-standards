#ifndef DRAW_H
#define DRAW_H

#include "stds.h"

extern struct app_t app;

extern void Stds_PrepareScene( void );

extern void Stds_PresentScene( void );

extern void Stds_BlitTextureRect( SDL_Texture *texture, SDL_Rect *src, float x, float y,
                                  bool camera_offset );

extern void Stds_BlitTextureRectRotate( SDL_Texture *texture, SDL_Rect *src, float x, float y,
                                        uint16_t angle, SDL_RendererFlip flip,
                                        SDL_FPoint *rotate_point, bool camera_offset );

extern void Stds_BlitTexture( SDL_Texture *texture, float x, float y, bool is_center,
                              bool camera_offset );

extern void Stds_BlitTextureRotate( SDL_Texture *texture, float x, float y, uint16_t angle,
                                    SDL_RendererFlip flip, SDL_FPoint *p, bool camera_offset );

extern void Stds_BlitTextureResize( SDL_Texture *texture, float x, float y, int32_t w, int32_t h,
                                    uint16_t angle, SDL_RendererFlip flip, bool camera_offset );

extern void Stds_BlitTextureScale( SDL_Texture *texture, float x, float y, float scale_x,
                                   float scale_y, uint16_t angle, SDL_RendererFlip flip,
                                   SDL_Color *c, bool camera_offset );

extern void Stds_DrawRect( SDL_Rect *rect, SDL_Color *c, bool is_filled, bool camera_offset );

extern void Stds_DrawRectF( SDL_FRect *frect, SDL_Color *c, bool is_filled, bool camera_offset );

extern void Stds_DrawRectStroke( float x, float y, uint32_t w, uint32_t h, uint32_t thickness,
                                 SDL_Color *c, bool camera_offset );

extern void Stds_DrawCircle( struct circle_t *circle, SDL_Color *c, bool is_filled );

extern void Stds_DrawLine( float x1, float y1, float x2, float y2, SDL_Color *c );

extern SDL_Texture *Stds_LoadTexture( const char *directory );

extern SDL_Color Stds_CombineFadeColor( struct fade_color_t *fade_color );

#endif // DRAW_H
