#include <graphics.h>
#include <stdio.h>
#include <config.h>


extern size_t count;
void find_path(sds *v1, sds *v2, unit* e,int deep){

	size_t len=sdslen(e->p1);
	*v1=sdscatlen(*v1,e->p1,len-(K-2));
	*v2=sdscatlen(*v2,e->p2,len-(K-2));
	size_t pc=sdslen(*v1);

	if(e->next.size && deep > 0 ){
		size_t max=0;
		for(size_t i=0;i<e->next.size ;i++){
			find_path(v1,v2,(unit*)e->next.list[i],deep-1);
			(*v1)[pc]='\x00';
			(*v2)[pc]='\x00';
			sdsupdatelen(*v1);
			sdsupdatelen(*v2);
		}
	}else{
		// e->flag=PASSED;
		if( deep || sdslen(*v1)>THRE_HOLD ){
			//output
			printf(">frag_%lu/0\n",count);
			puts(*v1);
			printf(">frag_%lu/1\n",count++);
			puts(*v2);
			// flag=0;
		}
	}
}


int compare_node(unit *a,unit *b){
	if(a==NULL){
		return 1;
	}else if(b==NULL){
		return -1;
	}else{
		return b->next.size-a->next.size;
	}
}






