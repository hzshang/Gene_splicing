#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#define TYPE void*
typedef struct{
	TYPE* list;
	size_t size;
	size_t max;
} vector;

void init_vector(vector *);
void vector_push(vector *,TYPE);
void delete_vector(vector *);
void shrink_vector(vector *v);
#endif