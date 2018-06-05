#include <unit.h>
#include <br-tree.h>
#include <stdlib.h>
#include <string.h>
#include <config.h>

int cmp(unit* a,unit *b){
	int ret=strcmp(a->p1,b->p1);
	if(!ret){
		ret=strcmp(a->p2,b->p2);
	}
	if(ret==0){
		return 0;
	}else{
		return ret>0?1:-1;
	}
}

void init_unit(unit* dev){
	dev->p1=sdsempty();
	dev->p2=sdsempty();
	init_vector(&dev->next);
	dev->in=0;
	dev->flag=NOPASSED;
	dev->best=0;
	dev->len=0;
}

void add_edge(unit* src,unit* dst){
	for(int i=0;i<src->next.size;i++){
		if(!cmp(src->next.list[i],dst)){
			// don't add same unit because the possibilty equals 0 almost
			return;
		}
	}
	vector_push(&src->next,dst);
	dst->in++;
	if( dst->len+src->len-(K-2) > src->len){
		src->best=dst;
		src->len+=dst->len-(K-2);
	}

}

void delete_unit(unit* v){
	sdsfree(v->p1);
	sdsfree(v->p2);
	delete_vector(&v->next);
	free(v);
}


void append_str(unit *src,char *str1,char *str2){
	size_t len=strlen(str1);
	append_nchar(src,str1,str2,len);
}

void append_nchar(unit *src,char *str1,char*str2,size_t len){
	src->p1=sdscatlen(src->p1,str1,len);
	src->p2=sdscatlen(src->p2,str2,len);
	src->len+=len;
}

