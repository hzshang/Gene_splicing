#include <vector.h>

#define MIN_LENGTH 10
void init_vector(vector *v){
	v->list=(TYPE*)malloc(sizeof(TYPE*)*MIN_LENGTH);
	v->size=0;
	v->max=MIN_LENGTH;
}

void alloc_room(vector *v){
	if(v->size == v->max){
		v->max*=2;
		v->list=(TYPE*)realloc(v->list,sizeof(TYPE*)*v->max);
	}
}

void vector_push(vector *v,TYPE key){
	alloc_room(v);
	v->list[v->size++]=key;
}

void delete_vector(vector *v){
	free(v->list);
	v->list=0;
}


void shrink_vector(vector *v){
	v->list=(TYPE*)realloc(v->list,sizeof(TYPE*)*v->size);
}

void delete_key_from_vector(vector *v,TYPE k){
	size_t i=0;
	for(;i<v->size && v->list[i]!=k;i++);
	if(i!=v->size){
		for(;i < v->size-1;i++){
			v->list[i]=v->list[i+1];
		}
		v->size--;
	}
}

void insert_vector(vector *v, TYPE key,int(*cmp)(TYPE,TYPE)){
	alloc_room(v);
	size_t i=0;
	for(;i<v->size;i++){
		if(cmp(key,v->list[i]) < 0){
			break;
		}
	}
	for(size_t j=v->size;j>i;j--){
		v->list[j]=v->list[j-1];
	}
	v->list[i]=key;
	v->size++;
}

int vector_exist_key(vector *v,TYPE key){
	for(size_t i=0;i<v->size;i++){
		if(v->list[i]==key){
			return 1;
		}
	}
	return 0;
}
