#ifndef STDS_H
#define STDS_H

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include "stddefine.h"
#include "structs.h"

#define MAX_INT_DIGITS 11
#define DEBUG          1

#define MAX( a, b )     ( ( a ) > ( b ) ? ( a ) : ( b ) )
#define MIN( a, b )     ( ( a ) < ( b ) ? ( a ) : ( b ) )
#define MAX3( a, b, c ) ( MAX( MAX( a, b ), c ) )
#define MIN3( a, b, c ) ( MIN( MIN( a, b ), c ) )

extern int32_t Stds_RandomInt( int32_t min, int32_t max );

extern float Stds_RandomFloat( float min, float max );

extern void Stds_ClampInt( int32_t *n, int32_t min, int32_t max );

extern void Stds_CalcSlope( int32_t x1, int32_t y1, int32_t x2, int32_t y2, float *x_slope, float *y_slope );

extern float Stds_GetAngle( int32_t x1, int32_t y1, int32_t x2, int32_t y2 );

extern int32_t Stds_GetDistance( int32_t x1, int32_t y1, int32_t x2, int32_t y2 );

extern void Stds_Print( const char * s, ... );

extern float Stds_ToRadians( float degree_angle );

extern float Stds_ToDegrees( float radian_angle );

extern bool Stds_IsMouseOverRect( float x, float y, SDL_Rect rect );

extern char *Stds_Substring( const char *str, int first, int last );

extern int32_t Stds_IndexOf( const char *s, const char *search_str );

extern char * Stds_StrCatInt( const char *s, int32_t n );

#endif // STDS_H