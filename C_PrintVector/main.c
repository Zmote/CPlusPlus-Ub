#include <stdio.h>
#include <stdlib.h>

#define LENGTH 9

void printArr(int * arr);
int medianOfArr(int * arr);

int main(){
	int zahlen[] = {1,2,3,4,5,6,7,11,12};
	printArr(zahlen);
	printf("\n");
	printf("Median of arr is: %d", medianOfArr(zahlen));
	return 0;
}

void printArr(int * arr){
	int * p = arr;
		while(p < &arr[LENGTH]){
			printf("%d ", *p );
			p++;
		}
}

int medianOfArr(int * arr){
	int * p = arr;
	int sum = 0;
		while(p < &arr[LENGTH]){
			sum = sum + (*p);
			p++;
		}
	return sum/LENGTH;
}
