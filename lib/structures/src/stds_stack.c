#include "../include/stds_stack.h"

/**
 *
 */
struct stds_stack_t {
  size_t element_size;
  size_t logical_size;
  size_t capacity;
  void **data;
};

/**
 *
 */
void
Stds_StackCreate( struct stds_stack_t *s ) {}

/**
 *
 */
void
Stds_StackPush( struct stds_stack_t *s, void *data ) {}

/**
 *
 */
void *
Stds_StackPop( struct stds_stack_t *s ) {
  return NULL;
}

/**
 *
 */
void
Stds_StackClear( struct stds_stack_t *s ) {}

/**
 *
 */
void *
Stds_StackPeek( struct stds_stack_t *s ) {
  return NULL;
}