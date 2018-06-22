#
# Makefile
# Copyright (C) 2018 hzshang <hzshang15@gmail.com>
#
# Distributed under terms of the MIT license.


LIB_SRC=$(wildcard lib/*.c)
CFLAGS=-Iinclude -I. -g -D DATA2#$(target)

SRC_FILES := $(wildcard lib/*.c)
OBJ_FILES := $(patsubst %.c,%.o,$(SRC_FILES))




all: graphics.c main.c libpj.o
	gcc $^ $(CFLAGS) -o main

libpj.o: $(OBJ_FILES)
	ar rcs $@ $^

lib/%.o: lib/%.c
	gcc $(CFLAGS) $^ -c -o $@

clean:
	rm -f lib/*.o *.o main