#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#include <unit.h>
#include <br-tree.h>
#include <config.h>
#include <vector.h>
#include <sds.h>
#include <graphics.h>
#include <sort.h>

typedef struct {
    char *s1;
    char *s2;
}pair;


BR_Tree tree;
vector pool;
size_t count;
// int flag;
char *str1;
char *str2;

void reverse(char *dest,const char *src,size_t len){
    for(int i=0;i<len-1;i++){
        switch(src[len-2-i]){
            case 'A':
                dest[i]='T';
                break;
            case 'T':
                dest[i]='A';
                break;
            case 'C':
                dest[i]='G';
                break;
            case 'G':
                dest[i]='C';
                break;
        }
    }
    dest[len-1]='\x00';
}

void load_file(){
    int fd1=open(FILE1,O_RDWR);
    int fd2=open(FILE2,O_RDWR);
    off_t fsize=lseek(fd1,0,SEEK_END);
    off_t fsize2=lseek(fd2,0,SEEK_END);
    assert(fsize==fsize2);
    str1=mmap(0,fsize,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd1,0);
    str2=mmap(0,fsize,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd2,0);
    close(fd1);
    close(fd2);
    if(!(str1&&str2)){
        printf("load files failed\n");
        exit(1);
    }
}

void load_fragment(pair *p,size_t frag_len,size_t k){
    for(int i=0;i<frag_len-k+1;i++){

        unit *dev1=(unit*)malloc(sizeof(unit));
        unit *dev2=(unit*)malloc(sizeof(unit));
        init_unit(dev1);
        init_unit(dev2);

        append_nchar(dev1,p->s1+i,p->s2+i,k-1);
        append_nchar(dev2,p->s1+i+1,p->s2+i+1,k-1);

        unit* tmp;
        tmp=key_exist(&tree,dev1);
        if(tmp){
            delete_unit(dev1);
            dev1=tmp;
        }else{
            insert_key(&tree,dev1);
            vector_push(&pool,dev1);
        }

        tmp=key_exist(&tree,dev2);
        if(tmp){
            delete_unit(dev2);
            dev2=tmp;
        }else{
            insert_key(&tree,dev2);
            vector_push(&pool,dev2);
        }
        add_edge(dev1,dev2);
    }
}

void combine(unit *v){
    if(v->next.size==1 && ((unit*)v->next.list[0])->in ==1){
        unit* tmp=v->next.list[0];
        delete_key(&tree,tmp);
        combine(tmp);
        delete_key(&tree,v);
        append_str(v,&tmp->p1[K-2],&tmp->p2[K-2]);
        v->next=tmp->next;
        v->best=tmp->best;
        v->len+=tmp->len-(K-2);
        insert_key(&tree,v);
    }
}

int main(int argc, char const *argv[])
{
    load_file();
    init_tree(&tree);
    init_vector(&pool);

    off_t pc=0;
    off_t npc=0;
    while(str1[pc]){
        //get first line
        while(str1[pc++]!='\n');
        npc=pc+FRAG_LEN;
        str1[npc]='\x00';
        str2[npc]='\x00';

        pair p;
        p.s1=&str1[pc];
        p.s2=(char*)malloc(FRAG_LEN+1);
        reverse(p.s2,&str2[pc],FRAG_LEN+1);
        load_fragment(&p,FRAG_LEN,K);
        free(p.s2);

        pair q;
        q.s1=(char*)malloc(FRAG_LEN+1);
        q.s2=&str2[pc];
        reverse(q.s1,&str1[pc],FRAG_LEN+1);
        load_fragment(&q,FRAG_LEN,K);
        free(q.s1);

        pc=npc+2;// the line end with "\r\n" orz
    }

    fprintf(stderr,"load edges finish\n");

    size_t sum=0;
    for(size_t i=0;i<pool.size;i++){
        if(key_exist(&tree,pool.list[i])){
            combine(pool.list[i]);
        }else{
            pool.list[i]=0;
            sum++;
        }
    }

    /* 开始遍历 */
    sort((unit**)pool.list,pool.size,compare_node);
    pool.size-=sum;
    shrink_vector(&pool);

    for(size_t i=0;i<pool.size;i++){
        unit *tmp=(unit*)pool.list[i];
        fprintf(stderr, "rand:%lu\n",i);
        if(tmp->next.size==0){
            // output signal node
            printf(">frag_%lu/0\n",count);
            puts(tmp->p1);
            printf(">frag_%lu/1\n",count++);
            puts(tmp->p2);
            pool.list[i]=0;
            delete_key(&tree,tmp);
        }else{
            //find max path
            sds str_1=sdsempty();
            sds str_2=sdsempty();
            // flag=1;
            find_path(&str_1,&str_2,tmp,MAX_DEEP);
            sdsfree(str_1);
            sdsfree(str_2);
        }
    }

    return 0;
}









