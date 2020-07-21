//=============================================================================================//
// FILENAME :       grid.c
//
// DESCRIPTION :
//        Defines the functions associated with grids, and is able to treat
//        each 'box' as a button and deals with events like clicking.
//
// NOTES :
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.
//
// AUTHOR :   strah19        START DATE :    19 Jul 2020
//
//=============================================================================================//

#include "../include/grid.h"
#include "../include/draw.h"

static bool Stds_AssertGrid( struct grid_t* grid );

/**
 * Created grid with no texture, no collision, etc. This is useful for grids that have to change
 * colors overtime, or just don't have an accompanying texture, or other special feature.
 *
 * @param float x top-left x pos of button.
 * @param float y top-left y pos of button.
 * @param int32_t squareWidth width of each square.
 * @param int32_t squareHeight height of each square.
 * @param uint32_t cols number of columns the grid will have.
 * @param uint32_t rows number of rows the grid will have.
 * @param SDL_Color lineColor color of the lining of the grid.
 * @param SDL_Color fillColor color of the square's in the grid.
 *
 * @return grid_t pointer.
 */
struct grid_t *
Stds_CreateGrid( float x, float y, int32_t squareWidth, int32_t squareHeight, uint32_t cols,
                 uint32_t rows, SDL_Color lineColor, SDL_Color fillColor ) {
  struct grid_t *grid;
  grid = malloc( sizeof( struct grid_t ) );

  if ( grid == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Error: could not allocate memory for grid_t, %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  } else {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Created grid_t.\n" );
  }

  memset( grid, 0, sizeof( struct grid_t ) );
  grid->x         = x;
  grid->y         = y;
  grid->sx        = x;
  grid->sy        = y;
  grid->sw        = squareWidth;
  grid->sh        = squareHeight;
  grid->cols      = cols;
  grid->rows      = rows;
  grid->lineColor = lineColor;
  grid->fillColor = fillColor;

  return grid;
}

/**
 * @param grid_t* pointer to grid_t.
 *
 * @return void.
 */
void
Stds_DrawLineGrid( struct grid_t *grid ) {
  if ( Stds_AssertGrid( grid ) ) {
    grid->x = grid->sx;
    grid->y = grid->sy;

    for ( uint32_t r = 0; r < grid->rows; r++ ) {
      Stds_DrawLine( grid->x, grid->y, grid->x + ( float ) ( grid->sw * grid->cols ), grid->y,
                    &grid->lineColor );
      grid->y += ( float ) grid->sh;
    }

    grid->y = grid->sy;

    for ( uint32_t c = 0; c < grid->cols; c++ ) {
      Stds_DrawLine( grid->x, grid->y, grid->x, grid->y + ( float ) ( grid->sh * grid->rows ),
                    &grid->lineColor );
      grid->x += ( float ) grid->sw;
    }

    grid->x = grid->sx;

    Stds_DrawLine( grid->x, grid->y + ( float ) ( grid->sh * grid->rows ),
                  grid->x + ( float ) ( grid->sw * grid->cols ),
                  grid->y + ( float ) ( grid->sh * grid->rows ), &grid->lineColor );
    Stds_DrawLine( grid->x + ( float ) ( grid->sw * grid->cols ), grid->y,
                  grid->x + ( float ) ( grid->sw * grid->cols ),
                  grid->y + ( float ) ( grid->sh * grid->rows ), &grid->lineColor );
  }
}

/**
 * @param grid_t* pointer to grid_t.
 *
 * @return void.
 */
void
Stds_FillWholeGrid( struct grid_t *grid ) { 
  if ( Stds_AssertGrid( grid ) ) {
    grid->x = grid->sx;
    grid->y = grid->sy;

    SDL_FRect fillRect = { grid->x, grid->y, ( float ) grid->sw, ( float ) grid->sh };

    for( uint32_t r = 0; r < grid->rows; r++ ) {
      for( uint32_t c = 0; c < grid->cols; c++ ) {

        Stds_DrawRectF( &fillRect, &grid->fillColor, true, 0) ;

        fillRect.x += ( float ) grid->sw;
      }
      fillRect.y += ( float ) grid->sh;
      fillRect.x = grid->sx;
    }
  }
}

/**
 * @param grid_t* pointer to grid_t.
 *
 * @return void.
 */
void
Stds_FreeGrid( struct grid_t *grid ) {
  free( grid );
  SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Freed grid_t.\n" );
}

/**
 * @param grid_t* pointer to grid_t.
 *
 * @return grid_pair_t struct that holds data for what square is being hovered.
 */
struct grid_pair_t 
Stds_OnGridHover( struct grid_t* grid ) {
  struct grid_pair_t p;
  
  if ( Stds_AssertGrid( grid ) ) {
    grid->x = grid->sx;
    grid->y = grid->sy;

    SDL_Rect hoverRect = { ( int ) grid->x, ( int ) grid->y, ( int ) grid->sw, ( int ) grid->sh };

    /* Loops through each square */
    for( uint32_t r = 0; r < grid->rows; r++ ) {
      p.r = ( int32_t ) r;
      for( uint32_t c = 0; c < grid->cols; c++ ) {
        
        p.c = ( int32_t ) c;

        if ( Stds_IsMouseOverRect( ( float ) app.mouse.x, ( float ) app.mouse.y, hoverRect ) ) {
          return p;
        }

        hoverRect.x += ( int ) grid->sw;
      }
      hoverRect.y += ( int ) grid->sh;
      hoverRect.x = ( int ) grid->sx;
    }
  }

  /* -1 means that the mouse did not hover over any of the squares */
  p.c = -1;
  p.r = -1;

  return p;
}

/**
 * @param grid_t* pointer to grid_t.
 * @param int32_t the code for which mous ebutton is clicked
 *
 * @return grid_pair_t struct that holds data for what square is being clicked.
 */
struct grid_pair_t 
Stds_OnGridClicked( struct grid_t* grid, int32_t mouseCode ) {
  struct grid_pair_t p;
  
  if ( Stds_AssertGrid( grid ) ) {
    grid->x = grid->sx;
    grid->y = grid->sy;

    SDL_Rect clickRect = { ( int ) grid->x, ( int ) grid->y, ( int ) grid->sw, ( int ) grid->sh };

    /* Loops through each square */
    for( uint32_t r = 0; r < grid->rows; r++ ) {
      p.r = ( int32_t ) r;
      for( uint32_t c = 0; c < grid->cols; c++ ) {
        
        p.c = ( int32_t ) c;

        if ( Stds_IsMouseOverRect( ( float ) app.mouse.x, ( float ) app.mouse.y, clickRect ) && app.mouse.button[ mouseCode ] ) {
          app.mouse.button[ mouseCode ] = 0;
          return p;
        }

        clickRect.x += ( int ) grid->sw;
      }
      
      clickRect.y += ( int ) grid->sh;
      clickRect.x = ( int ) grid->sx;
    }
  }
  
  /* -1 means that the mouse did not hover over any of the squares */
  p.c = -1;
  p.r = -1;

  return p;
}

/**
 * Ensures that the grid is not null.
 * 
 * @param grid_t* pointer to grid_t.
 *
 * @return bool.
 */
static bool 
Stds_AssertGrid( struct grid_t* grid ) {
  return !(grid == NULL);
}