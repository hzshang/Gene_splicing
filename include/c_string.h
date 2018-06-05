/*
#ifndef STRING_H
#define STRING_H
#include <stdlib.h>

typedef struct{
	char* ptr;
	size_t size;
	size_t max;
} string;

void init_string(string *);

void append_str(string *v,char *p);
void append_nstr(string *v,char *p,size_t len);
void append_char(string *v,char c);

void release_str(string *v);
void reset_str(string *v);
void reseek(string *v,size_t p);

#endif
*/