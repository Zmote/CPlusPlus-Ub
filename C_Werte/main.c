#include <stdio.h>

void sub_copy(int x){
	x++;
	printf("%s\n","Copy:");
	printf("%i\n",x);
}

void sub_pointer(int * x){
	(*x)++;
	printf("%s\n","Pointer:");
	printf("%i\n",(*x));
}

int main(){
	int a = 500;
	sub_copy(a);
	sub_copy(a);
	int b = 500;
	sub_pointer(&b);
	sub_pointer(&b);
	return 0;
}