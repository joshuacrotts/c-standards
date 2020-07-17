#ifndef STDS_STACK_H
#define STDS_STACK_H

#include "../../../include/stds.h"

#include "stds_data.h"

typedef struct stds_stack_t stds_stack_t;

extern void Stds_StackCreate( struct stds_stack_t *s );

extern void Stds_StackPush( struct stds_stack_t *s, void *data );

extern void *Stds_StackPop( struct stds_stack_t *s );

extern void Stds_StackClear( struct stds_stack_t *s );

extern void *Stds_StackPeek( struct stds_stack_t *s );

#endif // STDS_STACK_H