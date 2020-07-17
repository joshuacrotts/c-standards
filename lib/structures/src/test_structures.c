#include "../include/stds_vector.h"

int
main( int argc, char *argv[] ) {

  /* Specify the type of the arraylist as a parameter. */
  stds_vector_t *v = Stds_VectorCreate( sizeof( int32_t ) );

  /* Append void pointer-casted values.*/
  Stds_VectorAppend( v, ( void * ) 1 );
  Stds_VectorAppend( v, ( void * ) 2 );
  Stds_VectorAppend( v, ( void * ) 3 );
  Stds_VectorAppend( v, ( void * ) 4 );
  Stds_VectorAppend( v, ( void * ) 5 );
  Stds_VectorAppend( v, ( void * ) 6 );
  Stds_VectorAppend( v, ( void * ) 7 );
  Stds_VectorAppend( v, ( void * ) 8 );
  Stds_VectorAppend( v, ( void * ) 9 );

  for ( int i = 0; i < Stds_VectorSize( v ); i++ ) {
    Stds_Print( "%d\n", *( int32_t * ) Stds_VectorGet( v, i ) );
  }

  Stds_Print( "Removing index 4 which should be element 5.\n\n\n" );
  Stds_VectorRemove( v, 4 );
  Stds_VectorInsert( v, 4, ( void * ) 10000 );

  for ( int i = 0; i < Stds_VectorSize( v ); i++ ) {
    Stds_Print( "%d\n", *( int32_t * ) Stds_VectorGet( v, i ) );
  }

  Stds_VectorDestroy( v );
}