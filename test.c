
#include <stdlib.h>
#include <stdio.h>


#define MAX 10000
int cmp(const void* a,const void* b){
	return (int)a-(int)b;
}
int main(){
	srand(time(0));
	int *array=(int*)malloc(MAX*sizeof(int));
	for(int i=0;i<MAX;i++){
		array[i]=rand()%1000;
	}

	qsort(array,MAX,sizeof(int),cmp);
	for(int i=0;i<MAX-1;i++){
		if(array[i] < array[i+1]){
			printf("error\n");
			break;
		}
	}
}