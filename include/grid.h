#ifndef GRID_H
#define GRID_H

#include "stds.h"

extern struct app_t app;

struct grid_t {
  float x;
  float y;
  
  float sx;
  float sy;

  int32_t sw;
  int32_t sh;

  uint32_t cols;
  uint32_t rows;

  SDL_Color lineColor;
  SDL_Color fillColor;
};

/* Will be the return type for all button related functions (what row and what col)*/
struct grid_pair_t{
    uint32_t c;
    uint32_t r;
};

extern struct grid_t* Stds_CreateGrid( float x, float y, int32_t squareWidth, int32_t squareHeight, 
                                uint32_t cols, uint32_t rows, SDL_Color lineColor, SDL_Color fillColor );

extern void Stds_DrawLineGrid( struct grid_t* grid );

extern void Stds_FillGrid( struct grid_t* grid );

extern void Stds_FreeGrid( struct grid_t* grid );

extern struct grid_pair_t Stds_OnHover( void );

extern struct grid_pair_t Stds_OnClicked( int32_t mouseCode );

#endif // GRID_H