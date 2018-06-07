#include <stdlib.h>
#include <sort.h>
#define MAX 0x7FFFFFFFFFFFFF
#define MAX_SIZE 1000

void merge(KEY_TYPE *array,size_t begin,size_t mid,size_t end,int(*cmp)(KEY_TYPE,KEY_TYPE)){
    KEY_TYPE* L=(KEY_TYPE*)malloc(sizeof(KEY_TYPE)*(mid-begin));
    KEY_TYPE* R=(KEY_TYPE*)malloc(sizeof(KEY_TYPE)*(end-mid));
    for(size_t i=begin;i<mid;i++)
        L[i-begin]=array[i];
    for(size_t i=mid;i<end;i++)
        R[i-mid]=array[i];
    KEY_TYPE *temp_L=L;
    KEY_TYPE *temp_R=R;
    KEY_TYPE *ptr=array;
    for(;L-temp_L < mid-begin && R-temp_R < end-mid;){
        if(cmp(*L,*R)<0){
            *ptr=*L;
            L++;
            ptr++;
        }else{
            *ptr=*R;
            R++;
            ptr++;
        }
    }
    KEY_TYPE *left;
    size_t size;
    if(L-temp_L == mid-begin){
        left=R;
        size=(end-mid)-(R-temp_R);
    }else{
        left=L;
        size=(mid-begin)-(L-temp_L);
    }
    for(size_t i=0;i<size;i++){
        ptr[i]=left[i];
    }
    free(temp_L);
    free(temp_R);
}
void sort(KEY_TYPE *array,size_t size,int(*cmp)(KEY_TYPE,KEY_TYPE)){
    size_t mid=size/2;
    if(mid){
        sort(array,mid,cmp);
        sort(array+mid,size-mid,cmp);
        merge(array,0,mid,size,cmp);
    }
}