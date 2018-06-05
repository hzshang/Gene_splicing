#ifndef SORT_H
#define SORT_H
#include <unit.h>
#define KEY_TYPE unit*

void sort(KEY_TYPE*,size_t t,int (*cmp)(KEY_TYPE,KEY_TYPE));
#endif