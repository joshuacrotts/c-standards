#ifndef STDS_VECTOR_H
#define STDS_VECTOR_H

#include "../../../include/stds.h"

#define STDS_VECTOR_MIN_CAP 10

typedef struct stds_vector_t stds_vector_t;

enum SHIFT_DIRECTION { LEFT, RIGHT };

extern struct stds_vector_t *Stds_VectorCreate( size_t element_size );

extern void Stds_VectorAppend( struct stds_vector_t *v, void *data );

extern void Stds_VectorInsert( struct stds_vector_t *v, ssize_t index, void *data );

extern void *Stds_VectorGet( const struct stds_vector_t *v, ssize_t index );

extern void Stds_VectorRemove( struct stds_vector_t *v, ssize_t index );

extern bool Stds_VectorIsEmpty( const struct stds_vector_t *v );

extern size_t Stds_VectorSize( const struct stds_vector_t *v );

extern void Stds_VectorDestroy( struct stds_vector_t *v );

#endif // STDS_VECTOR_H