#ifndef STDS_QUEUE_H
#define STDS_QUEUE_H

#include "../../../include/stds.h"

#include "stds_data.h"

typedef struct stds_queue_t stds_queue_t;

extern void Stds_QueueCreate( struct stds_queue_t *s );

extern void Stds_QueueAdd( struct stds_queue_t *s, void *data );

extern void *Stds_QueuePoll( struct stds_queue_t *s );

extern void Stds_QueueClear( struct stds_queue_t *s );

extern void *Stds_QueuePeek( struct stds_queue_t *s );

#endif // STDS_QUEUE_H