#include "../include/polygon.h"
#include "../include/draw.h"

struct polygon_t* 
Stds_CreatePolygon( const int32_t sides, const float scale, const struct vec2_t position, const float angle ) {
  struct polygon_t *polygon;
  polygon = malloc( sizeof( struct polygon_t ) );

  if ( polygon == NULL ) {
    SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION,
                  "Error: could not allocate memory for polygon_t, %s.\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  } else {
    SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Created polygon_t.\n" );
  }

  memset( polygon, 0, sizeof( struct polygon_t ) );
  polygon->sides = sides;
  polygon->overlap = false;
  polygon->model = malloc( sizeof( struct vec2_t ) * sides );
  polygon->points = malloc( sizeof( struct vec2_t ) * sides );

  float fTheta = 3.14159f * 2.0f / ( float ) polygon->sides;
  polygon->position = position;
  polygon->angle = angle;

  for ( int32_t i = 0; i < polygon->sides; i++ ) {
    struct vec2_t data = Stds_CreateVec2( 20.0f * cosf( fTheta * i ) * scale , 20.0f * sinf( fTheta * i) * scale );
    polygon->model[i] = data;
    polygon->points[i] = polygon->model[i];
  }

  return polygon;
}

void 
Stds_UpdatePolygon( struct polygon_t *polygon ) {
  for ( int32_t i = 0; i < polygon->sides; i++ ) {

    polygon->points[i].x = ( polygon->model[i].x * cosf( polygon->angle ) ) - ( polygon->model[i].y * sinf( polygon->angle ) ) + polygon->position.x;
    polygon->points[i].y = ( polygon->model[i].x * sinf( polygon->angle ) ) + ( polygon->model[i].y * cosf( polygon->angle ) ) + polygon->position.y;
    polygon->overlap = false;
  }
}

void 
Stds_DrawPolygon( struct polygon_t *polygon ) {
  SDL_Color white = {255, 255, 255};
  SDL_Color red = {255, 0, 0};

  SDL_Color color = ( polygon->overlap ) ? white : red;
  for ( int32_t i = 0; i < polygon->sides; i++ ) {
    SDL_SetRenderDrawColor( g_app.renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawLineF( g_app.renderer, polygon->points[i].x, polygon->points[i].y, 
                        polygon->points[ ( ( i + 1 ) % polygon->sides ) ].x, polygon->points[ (( i + 1 ) % polygon->sides ) ].y );
  }  
  SDL_SetRenderDrawColor( g_app.renderer, color.r, color.g, color.b, 255);
  SDL_RenderDrawLineF( g_app.renderer, polygon->points[0].x, polygon->points[0].y, polygon->position.x, polygon->position.y );
}

bool 
Stds_CheckSATOverlap( struct polygon_t *p1, struct polygon_t *p2 ) {
  struct polygon_t *poly1 = p1;
  struct polygon_t *poly2 = p2;

  for ( int32_t i = 0; i < 2; i++) {
    if ( i == 1) {  //Flips so it tests one against the other.
      poly1 = p2;
      poly2 = p1;
    }

    for (int32_t a = 0; a < poly1->sides; a++ ) {
      int32_t b = ( a + 1 ) % poly1->sides;
      struct vec2_t axis_projection = { -( poly1->points[b].y - poly1->points[a].y), poly1->points[b].x - poly1->points[a].x };  //Give normal to edge.

      float min_p1 = ( float ) INT32_MAX, max_p1 = ( float ) -INT32_MAX;
      for (int32_t points = 0; points < poly1->sides; points++ ) {
        float dot = ( poly1->points[points].x * axis_projection.x + poly1->points[points].y * axis_projection.y );

        min_p1 = ( min_p1 < dot ) ? min_p1 : dot;
        max_p1 = ( max_p1 > dot ) ? max_p1 : dot;
      }

      float min_p2 = ( float ) INT32_MAX, max_p2 = ( float ) -INT32_MAX;
      for (int32_t points = 0; points < poly2->sides; points++ ) {
        float dot = ( poly2->points[points].x * axis_projection.x + poly2->points[points].y * axis_projection.y );

        min_p2 = ( min_p2 < dot ) ? min_p2 : dot;
        max_p2 = ( max_p2 > dot ) ? max_p2 : dot;
      }

      if ( !(max_p2 >= min_p1 && max_p1 >= min_p2 ) ) {
        return false;
      }
    }
  }

  return true;
}

void 
Stds_CleanUpPolygon( struct polygon_t *polygon ) {
  free( polygon->model );
  free( polygon->points );

  free ( polygon );
}