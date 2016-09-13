#include <stdio.h>


int mul(int x, int y);

int main(){
	int (*ptr)(int,int);
	ptr = mul;
	printf("Res of mul(3,4) = %d\n", ptr(3,4));
	printf("Res of mul(4,5) = %d\n", (*ptr)(4,5));
	return 0;
}

int mul(int x, int y){
	return x*y;
}
