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
};

extern grid_t* Stds_CreateGrid( float x, float y, int32_t squareWidth, int32_t squareHeight, 
                                uint32_t cols, uint32_t rows );

extern void Stds_DrawLineGrid( SDL_Color lineColor );

extern void Stds_FillGrid( SDL_Color fillColor );

#endif // GRID_H