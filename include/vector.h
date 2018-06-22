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
void delete_vector(vector *);

void vector_push(vector *,TYPE);
void insert_vector(vector *v, TYPE key,int(*cmp)(TYPE,TYPE));
int vector_exist_key(vector *,TYPE);
void delete_key_from_vector(vector *v,TYPE k);

void shrink_vector(vector *v);
#endif