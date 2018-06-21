#include <graphics.h>
#include <stdio.h>
#include <config.h>
#include <br-tree.h>

extern BR_Tree length_tree;
extern size_t sum;
extern size_t s_cnt;
size_t count;

unit* join(unit *e){
    if(e->child.size!=1){
        return e;
    }
    size_t len=sdslen(e->p1);
    sds s1=sdsnewlen(e->p1,len-1);
    unit *tmp=e;
    unit *next;
    do{
        s1=sdscat(s1,&tmp->p1[K-2]);
        tmp->flag=JOINED;
        next=tmp->child.list[0];
        if(next->parent.size!=1 ||next->child.size!=1){
            break;
        }
        tmp=next;
    } while(1);

    e->p1=sdsdup(s1);
    e->flag=NOPASSED;
    e->child.list[0]=tmp->child.list[0];
    unit *d=tmp->child.list[0];
    delete_key_from_vector(&d->parent,tmp);
    vector_push(&d->parent,e);
    sdsfree(s1);
    return e;
}

void update_len(unit *v){
    v->flag=PASSED;
    for(size_t i=0;i<v->parent.size;i++){
        unit *tmp=v->parent.list[i];
        size_t t_len=sdslen(tmp->p1)+v->len-(K-2);
        // if(tmp->flag==PASSED){
        //     // delete_key_from_vector(&tmp->child,v);
        //     // delete_key_from_vector(&v->parent,tmp);
        //     tmp->len=sdslen(tmp->p1);
        // }
        if(tmp->flag!=PASSED && t_len > tmp->len){
            tmp->len=t_len;
            update_len(tmp);
        }
    }
    v->flag=NOPASSED;
}

void add_edge(unit* src,unit* dst){
    for(int i=0;i<dst->parent.size;i++){
        if(!cmp_str(src,dst->parent.list[i])){
            // don't add same unit because the possibilty equals 0 almost
            return;
        }
    }
    vector_push(&dst->parent,src);
    insert_vector(&src->child,dst,cmp_len);

    size_t t_len=sdslen(src->p1)+dst->len-(K-2);
    if( t_len > src->len){
        src->len=t_len;
        update_len(src);
    }
}

unit* find_next_child(unit *e){
    return e->child.size>0?e->child.list[0]:NULL;
}

size_t max_len(unit *p){
    size_t max=0;
    for(size_t i=0;i<p->child.size;i++){
        size_t tmp=((unit*)(p->child.list[i]))->len;
        if(max < tmp)
            max = tmp;
    }
    if(max){
        return max+sdslen(p->p1)-(K-2);
    }else{
        return sdslen(p->p1);
    }
}

void decrease_len(unit *e){
    for(size_t i=0;i<e->parent.size;i++){
        unit *p=e->parent.list[i];
        // delete_key_from_vector(&p->child,e);
        // delete_key_from_vector(&e->parent,p);
        size_t max=max_len(p);
        if(p->len > max){
            delete_key(&length_tree,p);
            p->len=max;
            insert_key(&length_tree,p);
            decrease_len(p);
        }
        // vector_push(&e->parent,p);
        // insert_vector(&p->child,e,cmp_len);
    }
}

void disable_node(unit *e){
    delete_key(&length_tree,e);
    e->len=0;
    decrease_len(e);
    for(size_t i=0;i<e->parent.size;i++){
        unit *parent=e->parent.list[i];
        delete_key_from_vector(&parent->child,e);
        delete_key_from_vector(&e->parent,parent);
    }
}

void find_path(unit* e){

    sds s_tmp=sdsdup(e->p1);
    disable_node(e);
    unit *p=e;
    unit *tmp=find_next_child(p);

    while(tmp){
        delete_key_from_vector(&p->child,tmp);
        delete_key_from_vector(&tmp->parent,p);
        disable_node(tmp);
        s_tmp=sdscat(s_tmp,&tmp->p1[K-2]);
        p=tmp;
        tmp=find_next_child(p);
    }
    size_t tmp_len=sdslen(s_tmp);
    if(tmp_len > 1500){
        sum+=sdslen(s_tmp);
        s_cnt++;
    }
    if(tmp_len > 99){
        printf(">frag_%lu\r\n",count++);
        puts(s_tmp);
    }

    sdsfree(s_tmp);
}


