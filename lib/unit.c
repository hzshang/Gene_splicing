#include <unit.h>
#include <br-tree.h>
#include <stdlib.h>
#include <string.h>
#include <config.h>
#include <vector.h>

extern BR_Tree pool;

int cmp_str(void* x,void *y){
	unit *a=x;
	unit *b=y;
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

int cmp_len(void *a,void *b){
	int ret=((unit*)a)->len - ((unit*)b)->len;
	if(!ret){
		ret=a-b;
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
	init_vector(&dev->parent);
	init_vector(&dev->child);
	dev->next=NULL;
	dev->len=0;
	dev->flag=NOPASSED;
	dev->confidience=1;
}

void add_edge(unit* src,unit* dst){
	for(int i=0;i<dst->parent.size;i++){
		if(!cmp_str(src,dst->parent.list[i])){
			// don't add same unit because the possibilty equals 0 almost
			return;
		}
	}

	vector_push(&dst->parent,src);
	vector_push(&src->child,dst);

	size_t t_len=sdslen(src->p1)+dst->len-(K-2);
	if( t_len > src->len){
		delete_key(&pool,src);
		src->next=dst;
		src->len=t_len;
		insert_key(&pool,src);

		update_len(src);

	}
}

void delete_unit(unit* v){
	sdsfree(v->p1);
	sdsfree(v->p2);
	v->p1=0;
	v->p2=0;
	delete_vector(&v->parent);
	free(v);
}

void update_len(unit *v){
	for(size_t i=0;i<v->parent.size;i++){
		unit *tmp=v->parent.list[i];
		size_t t_len=sdslen(tmp->p1)+v->len-(K-2);
		if(t_len > tmp->len){
			delete_key(&pool,tmp);
			tmp->next=v;
			tmp->len=t_len;
			insert_key(&pool,tmp);

			update_len(tmp);
		}
	}
}

void set_flag_passed(unit *v){
	/* delete from pool, update len to it's parents */
    v->flag=PASSED;
    delete_key(&pool,v);
    v->len=0;
    decrease_len(v);
}

unit* find_next_child(unit *e){
    unit *dev=NULL;
    size_t max=0;
    for(size_t i=0;i<e->child.size;i++){
        unit* tmp=(unit*)e->child.list[i];
        if(tmp->flag == NOPASSED && tmp->len > max){
            dev=tmp;
            max=tmp->len;
        }
    }
    return dev;
}

void decrease_len(unit *v){
    for(size_t i=0;i<v->parent.size;i++){
    	unit *tmp=v->parent.list[i];
    	if(tmp->flag == NOPASSED && tmp->next == v){
    		delete_key(&pool,tmp);
    		tmp->next=find_next_child(tmp);
    		if(tmp->next){
    			tmp->len=sdslen(tmp->p1)+tmp->next->len-(K-2);
    		}else{
    			tmp->len=sdslen(tmp->p1);
    		}
    		insert_key(&pool,tmp);
    		decrease_len(tmp);
    	}
    }
}

void append_str(unit *src,char *str1,char *str2){
	src->p1=sdscat(src->p1,str1);
	src->p2=sdscat(src->p2,str2);
}

void append_nchar(unit *src,char *str1,char *str2,size_t len){
	src->p1=sdscatlen(src->p1,str1,len);
	src->p2=sdscatlen(src->p2,str2,len);
}

