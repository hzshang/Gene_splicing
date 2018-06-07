/*
 * unit.h
 * Copyright (C) 2018 hzshang <hzshang15@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef UNIT_H
#define UNIT_H
#include <sys/types.h>
#include <sds.h>
#include <vector.h>
#define MIN_SIZE 4

#define PASSED 0
#define NOPASSED 1

struct _unit{
    sds p1;
    sds p2;
    vector parent;
    /* 使用优先队列保存子节点*/
    vector child;
    struct _unit *next;
    // size_t out;

    size_t len;
    int flag;
    
    int confidience;
};

typedef struct _unit unit;

int cmp_str(void* x,void *y);
int cmp_len(void *a,void *b);

void init_unit(unit*);
void add_edge(unit*,unit*);
void delete_unit(unit*);

void append_str(unit *src,char *str1,char *str2);
void append_nchar(unit *src,char *str1,char*str2,size_t len);
void update_len(unit *v);

#endif /* !UNIT_H */
