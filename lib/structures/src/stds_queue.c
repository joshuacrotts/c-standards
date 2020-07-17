#include "../include/stds_queue.h"

/**
 *
 */
struct stds_queue_t {
  size_t element_size;
  size_t logical_size;
  size_t capacity;
  void **data;
};

/**
 *
 */
void
Stds_QueueCreate( struct stds_queue_t *q ) {}

/**
 *
 */
void
Stds_QueueAdd( struct stds_queue_t *q, void *data ) {}

/**
 *
 */
void *
Stds_QueuePoll( struct stds_queue_t *q ) {
  return NULL;
}

/**
 *
 */
void
Stds_QueueClear( struct stds_queue_t *q ) {}

/**
 *
 */
void *
Stds_QueuePeek( struct stds_queue_t *q ) {
  return NULL;
}
