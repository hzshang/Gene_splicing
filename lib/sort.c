#include <stdlib.h>
#include <sort.h>
#define MAX 0x7FFFFFFFFFFFFF
#define MAX_SIZE 1000
// void swap(KEY_TYPE *a,KEY_TYPE *b){
//     KEY_TYPE c=*a;
//     *a=*b;
//     *b=c;
// }

// void heap_init(KEY_TYPE* root,size_t index,size_t size,int(*cmp)(KEY_TYPE,KEY_TYPE)){
//     size_t max;
//     if(2*index+1 < size && cmp(root[index],root[2*index+1])<= 0){
//         max=2*index+1;
//     }else{
//         max=index;
//     }
//     if(2*index+2 < size && cmp(root[max],root[2*index+2])<= 0){
//         max=2*index+2;
//     }
//     if(max != index){
//         swap(root+index,root+max);
//         heap_init(root,max,size,cmp);
//     }
// }

// void sort(KEY_TYPE* array,size_t size,int (*cmp)(KEY_TYPE,KEY_TYPE)){
//     for(int i=size-1;i>=0;i--){
//         heap_init(array,i,size,cmp);
//     }
// }


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