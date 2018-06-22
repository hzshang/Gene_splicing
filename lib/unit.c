#include <unit.h>
#include <br-tree.h>
#include <stdlib.h>
#include <string.h>
#include <config.h>
#include <vector.h>

// int distance(unit *x,unit *y){
// 	int cnt=0;
// 	size_t len=sdslen(x->p1);
// 	for(int i=0;i<len && cnt <6 ;i++){
// 		cnt+=x->p1[i]==y->p1[i]?0:1;
// 	}
// 	return cnt;
// }
int cmp_str(void* x,void *y){
	// if(distance(x,y) < 6){
	// 	return 0;
	// }
	unit *a=x;
	unit *b=y;
	int ret=strcmp(a->p1,b->p1);

	if(ret==0){
		return 0;
	}else{
		return ret>0?1:-1;
	}
}

int cmp_len(void *a,void *b){
	int ret=((unit*)b)->len - ((unit*)a)->len;
	if(!ret){
		ret=b-a;
	}
	if(ret==0){
		return 0;
	}else{
		return ret>0?1:-1;
	}
}


void init_unit(unit* dev){
	dev->p1=sdsempty();
	init_vector(&dev->parent);
	init_vector(&dev->child);
	dev->len=0;
	dev->flag=WORK;
	dev->conf=1;
}



void delete_unit(unit* v){
	sdsfree(v->p1);
	v->p1=0;
	delete_vector(&v->parent);
	free(v);
}



void append_str(unit *src,char *str){
	src->p1=sdscat(src->p1,str);
}

void append_nchar(unit *src,char *str,size_t len){
	src->p1=sdscatlen(src->p1,str,len);
}

