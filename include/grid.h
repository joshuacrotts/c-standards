#ifndef GRID_H
#define GRID_H

#include "stds.h"

extern struct app_t app;

/* Will be the return type for all button related functions (what row and what col). */
struct grid_pair_t {
  int32_t c;
  int32_t r;

  float x;
  float y;
};

extern struct grid_t *Stds_CreateGrid( float x, float y, int32_t squareWidth, int32_t squareHeight,
                                       uint32_t cols, uint32_t rows, SDL_Color lineColor,
                                       SDL_Color fillColor );

extern struct grid_pair_t Stds_OnGridHover( struct grid_t *grid );

extern struct grid_pair_t Stds_OnGridClicked( struct grid_t *grid, int32_t mouseCode );

extern int32_t Stds_AddAnimationToGrid( struct grid_t *grid, struct animation_t *animate );

extern int32_t Stds_AddGridTexture( struct grid_t *grid, const char *filePath );

extern void Stds_DrawLineGrid( struct grid_t *grid );

extern void Stds_FillWholeGrid( struct grid_t *grid );

extern void Stds_FreeGrid( struct grid_t *grid );

extern void Stds_InitializeGridTextures( struct grid_t *grid, int32_t textureBuffer );

extern void Stds_PutGridTexture( struct grid_t *grid, uint32_t col, uint32_t row, int32_t index, 
                                 SDL_RendererFlip flip, uint16_t angle );

extern void Stds_AddSpriteSheetToGrid( struct grid_t *grid, const char *filePath, uint32_t cols,
                                       uint32_t rows );

extern void Stds_SelectSpriteForGrid( struct grid_t *grid, uint32_t sheetCol, uint32_t sheetRow );

extern void Stds_DrawSelectedSpriteOnGrid( struct grid_t *grid, uint32_t gridCol,
                                           uint32_t gridRow, SDL_RendererFlip flip, uint16_t angle );

extern void Stds_RenderAnimationToGrid( struct grid_t *grid, uint32_t col, uint32_t row,
                                        int32_t index, SDL_RendererFlip flip, uint16_t angle );

extern void Stds_AddCollisionToGrid( struct grid_t *grid, uint32_t col, uint32_t row );

#endif // GRID_H