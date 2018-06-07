#ifndef SORT_H
#define SORT_H

#define KEY_TYPE void*

void sort(KEY_TYPE*,size_t t,int (*cmp)(KEY_TYPE,KEY_TYPE));

#endif