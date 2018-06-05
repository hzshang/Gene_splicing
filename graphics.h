#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <unit.h>
#include <sds.h>
void find_path(sds *v1, sds *v2, unit* e,int deep);
int compare_node(unit *a,unit *b);
#endif