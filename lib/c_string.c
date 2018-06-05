/*
#include <c_string.h>
#include <string.h>
#define MIN_SIZE 100
void init_string(string * v){
	v->size=0;
	v->max=MIN_SIZE;
	v->ptr=realloc(0,MIN_SIZE);
}

void append_str(string *v,char *p){
	size_t len=strlen(p);
	append_nstr(v,p,len);
}

void append_nstr(string *v,char *p,size_t len){
	size_t size=len+v->size+1;
	if(size>=v->max){
		v->max*=size;
		v->ptr=realloc(v->ptr,v->max);
	}
	memcpy(&v->ptr[v->size],p,len);
	v->size+=len;
	v->ptr[v->size]='\x00';
}

void append_char(string *v,char c){
	append_nstr(v,&c,1);
}

void release_str(string *v){
	free(v->ptr);
	v->ptr=0;
}
void reset_str(string *v){
	v->size=0;
}

void reseek(string *v,size_t p){
	v->size=p;
}
*/