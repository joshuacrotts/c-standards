#include "../include/stds_vector.h"

/**
 *
 */
struct stds_vector_t {
  size_t element_size;
  size_t logical_size;
  size_t capacity;
  void **data;
};

/**
 * Creates an ArrayList/C++ vector with the specified type. To get the
 * size, pass in sizeof(T). For instance, sizeof(int32_t).
 *
 * @param size_t size of elements in arraylist.
 *
 * @return void.
 */
stds_vector_t *
Stds_VectorCreate( size_t element_size ) {
  stds_vector_t *v;
  v = malloc( sizeof( stds_vector_t ) );

  if ( v == NULL ) {
    Stds_Print( "Error: could not allocate memory for stds_vector_t!\n" );
    exit( EXIT_FAILURE );
  }

  memset( v, 0, sizeof( stds_vector_t ) );

  v->logical_size = 0;
  v->capacity     = STDS_VECTOR_MIN_CAP;
  v->element_size = element_size;
  v->data         = malloc( sizeof( element_size ) * v->capacity );

  if ( v->data == NULL ) {
    Stds_Print( "Error: could not allocate memory for the data void** in stds_vector_t!\n" );
    exit( EXIT_FAILURE );
  }

  return v;
}

/**
 * Adds an element to the end of a vector. The data must be casted
 * to a void pointer prior to addition. Example:
 *
 * Stds_VectorAppend( v, (void *) 5 );
 *
 * @param stds_vector_t * pointer to vector.
 * @param void * pointer to data (should be casted).
 *
 * @return void.
 */
void
Stds_VectorAppend( stds_vector_t *v, void *data ) {
  if ( v->logical_size == v->capacity ) {
    v->capacity <<= 1;
    v->data = realloc( v->data, sizeof( v->element_size ) * v->capacity );
  }
  Stds_VectorInsert( v, v->logical_size++, data );
}

/**
 * Inserts an element at a specified index.
 *
 * @param stds_vector_t * pointer to vector.
 * @param size_t index of to-be-inserted element.
 * @param void * pointer to data (should be casted).
 *
 * @return void.
 */
inline void
Stds_VectorInsert( stds_vector_t *v, ssize_t index, void *data ) {
  if ( index < 0 || index >= v->logical_size ) {
    Stds_Print( "Failed to insert, index out of bounds error: %d.\n", index );
    exit( EXIT_FAILURE );
  }

  /* Up-shift the elements.*/
  v->logical_size++;
  for ( int i = v->logical_size; i >= index - 1; i-- ) {
    v->data[i] = v->data[i-1];
  }
  v->data[index] = data;
}

/**
 * Returns the data at a specified index.
 *
 * @param const stds_vector_t * pointer to vector.
 * @param size_t index of to-be-received element.
 *
 * @return void.
 */
inline void *
Stds_VectorGet( const stds_vector_t *v, ssize_t index ) {
  if ( index < 0 || index >= v->logical_size ) {
    Stds_Print( "Failed to get element, index out of bounds error: %d.\n", index );
    exit( EXIT_FAILURE );
  }
  return v->data + index;
}

/**
 * Removes an element from a vector.
 *
 * @param stds_vector_t * pointer to vector.
 * @param size_t index of to-be-removed element.
 *
 * @return void.
 */
void
Stds_VectorRemove( stds_vector_t *v, ssize_t index ) {
  if ( index < 0 || index >= v->logical_size ) {
    Stds_Print( "Failed to remove, index out of bounds error: %d.\n", index );
    exit( EXIT_FAILURE );
  }

  void *removed_data = Stds_VectorGet( v, index );

  v->logical_size--;
  /* Down-shift the elements.*/
  for ( int i = index; i < v->logical_size; i++ ) {
    v->data[i] = v->data[i + 1];
  }
}

bool
Stds_VectorIsEmpty( const stds_vector_t *v ) {
  return v->logical_size == 0;
}

size_t
Stds_VectorSize( const stds_vector_t *v ) {
  return v->logical_size;
}

void
Stds_VectorDestroy( stds_vector_t *v ) {
  free( v->data );
  free( v );
}

// static void
// Stds_VectorShift( stds_vector_t *v, size_t start, size_t end, enum SHIFT_DIRECTION direction ) {
//   for (int i = start; i < end; i++) {
//   })
// }