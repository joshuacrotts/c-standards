/**
 * @file stds_stack.c
 * @author Joshua Crotts
 * @date July 31 2020
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * @section DESCRIPTION
 *
 * This file defines the functions and struct for a stack data structure.
 */
#include "../include/stds_stack.h"

static void Stds_StackCheckResize( stds_stack_t *, enum SHIFT_DIRECTION );

/**
 * Stack structure. Uses the last-in-first-out property.
 */
struct stds_stack_t {
  size_t element_size;
  size_t logical_size;
  size_t capacity;

  void **data;
};

/**
 * Creates a stack with the specified type. To get the
 * size, pass in sizeof(T). For instance, sizeof(int32_t).
 *
 * @param size_t size of each individual element.
 *
 * @return void.
 */
stds_stack_t *
Stds_StackCreate( size_t element_size ) {
  stds_stack_t *s;
  s = calloc( 1, sizeof( stds_stack_t ) );

  if ( s == NULL ) {
    fprintf( stderr, "Error: could not allocate memory for stds_stack_t!\n" );
    exit( EXIT_FAILURE );
  }

  s->element_size = element_size;
  Stds_StackClear( s );
  return s;
}

/**
 * Pushes an element to the head of the stack.
 *
 * @param stds_stack_t * pointer to stack.
 * @param void * void-casted pointer to the data to push.
 *
 * @return void.
 */
void
Stds_StackPush( struct stds_stack_t *s, void *data ) {
  Stds_StackCheckResize( s, RIGHT );
  s->data[s->logical_size++] = data;
}

/**
 * Returns the head of the stack.
 *
 * @param stds_stack_t * pointer to stack.
 *
 * @return far right element of array (head of stack).
 */
void *
Stds_StackPop( struct stds_stack_t *s ) {
  if ( Stds_StackIsEmpty( s ) ) {
    fprintf( stderr, "Error! Cannot pop an empty stack.\n" );
    exit( EXIT_FAILURE );
  }

  void *removed_data           = Stds_StackPeek( s );
  s->data[s->logical_size - 1] = NULL;
  s->logical_size--;

  /* If we pop too many elements, we can downsize the stack. */
  Stds_StackCheckResize( s, LEFT );
  return removed_data;
}

/**
 * Frees the data in the backing array of the stack, resets
 * the logical size and capacity. Also reallocates the data.
 *
 * @param stds_stack_t * pointer to stack to clear.
 *
 * @return void.
 */
void
Stds_StackClear( struct stds_stack_t *s ) {
  free( s->data );
  s->capacity     = STDS_STATIC_MIN_CAP;
  s->logical_size = 0;
  s->data         = malloc( sizeof( s->element_size ) * s->capacity );
}

/**
 * Peeks at the head of the stack.
 *
 * @param stds_stack_t * pointer to stack.
 *
 * @return element at the far right of the array (head of stack).
 */
inline void *
Stds_StackPeek( struct stds_stack_t *s ) {
  if ( Stds_StackIsEmpty( s ) ) {
    fprintf( stderr, "Error! Cannot peek an empty stack.\n" );
    exit( EXIT_FAILURE );
  }

  return s->data[s->logical_size - 1];
}

/**
 * Returns the sie of the stack.
 * 
 * @param struct stds_stack_t * pointer to stack structure.
 * 
 * @return integer size (logical).
 */
inline size_t
Stds_StackSize( struct stds_stack_t *s ) {
  return s->logical_size;
}

/**
 *
 */
inline bool
Stds_StackIsEmpty( struct stds_stack_t *s ) {
  return s->logical_size == 0;
}

/**
 * Checks to see if the stack needs to be resized. Both cases are
 * handled here (upsizing and downsizing).
 *
 * @param stds_stack_t * pointer to stack.
 * @param enum SHIFT_DIRECTION refers to the last action just performed.
 *        insertions and appends are RIGHT, removals are LEFT.
 *
 * @return void.
 */
static void
Stds_StackCheckResize( stds_stack_t *s, enum SHIFT_DIRECTION direction ) {
  /* If we need to grow, then the logical size is the same as the capacity. */
  if ( s->logical_size == s->capacity && direction == RIGHT ) {
    s->capacity <<= 1;
    s->data = realloc( s->data, sizeof( s->element_size ) * s->capacity );
  }

  /* If we need to shrink, then the logical size is the same as the capacity / 2. */
  else if ( s->logical_size == ( s->capacity >> 1 ) && direction == LEFT ) {
    s->capacity >>= 1;
    s->data = realloc( s->data, sizeof( s->element_size ) * s->capacity );
  }
}