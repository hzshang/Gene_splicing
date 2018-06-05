#include <vector.h>

#define MIN_LENGTH 10
void init_vector(vector *v){
	v->list=(TYPE*)malloc(sizeof(TYPE*)*MIN_LENGTH);
	v->size=0;
	v->max=MIN_LENGTH;
}

void vector_push(vector *v,TYPE key){
	if(v->size == v->max){
		v->max*=2;
		v->list=(TYPE*)realloc(v->list,sizeof(TYPE*)*v->max);
	}
	v->list[v->size++]=key;
}

void delete_vector(vector *v){
	free(v->list);
}


void shrink_vector(vector *v){
	v->list=(TYPE*)realloc(v->list,sizeof(TYPE*)*v->size);
}