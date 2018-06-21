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
BR_Tree length_tree;


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
        dev1->len=k-1;
        append_nchar(dev2,p->s1+i+1,p->s2+i+1,k-1);
        dev2->len=k-1;

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



int main(int argc, char const *argv[])
{
    load_file();
    init_tree(&tree,cmp_str);
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

        pc=npc+2;//the line end with "\r\n" orz
    }

    fprintf(stderr,"load edges finish\n");

    // count = 0;
    vector tmp_pool;
    init_vector(&tmp_pool);

    for(size_t i=0;i<pool.size;i++){
        unit *e=pool.list[i];
        if(e->flag!=JOINED){
            vector_push(&tmp_pool,join(pool.list[i]));
        }else{
            //delete_key(&tree,e);
            delete_unit(e);
        }
    }

    init_tree(&length_tree,cmp_len);
    for(size_t i=0;i<tmp_pool.size;i++){
        unit *e=tmp_pool.list[i];
        if(e->flag!=JOINED){
            insert_key(&length_tree,e);
        }else{
            delete_unit(e);
        }
    }
    while(length_tree.root!=length_tree.end){
        unit *tmp=tree_max_key(&length_tree);
        find_path(tmp);
    }
    return 0;
}


