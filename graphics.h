#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <unit.h>
#include <sds.h>
unit* join(unit *e);
void update_len(unit *v);
void decrease_len(unit *v);
void disable_node(unit *e);
void add_edge(unit* src,unit* dst);
unit* find_next_child(unit *e);
void find_path(unit* e);
#endif