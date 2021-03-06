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
#define WORK 1
#define JOINED 2
#define MISTAKE 3

struct _unit{
    sds p1;
    vector parent;
    vector child;
    size_t len;
    int flag;
    int conf;
};

typedef struct _unit unit;

int cmp_str(void* x,void *y);
int cmp_len(void *a,void *b);

void init_unit(unit*);

void delete_unit(unit*);

void append_str(unit *src,char *str);
void append_nchar(unit *src,char *str,size_t len);

#endif /* !UNIT_H */
