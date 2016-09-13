#include <stdlib.h>
#include <stdio.h>

int main(){
	union data{
		char i;
		int j;
		double z;
	};
	union data type;
	type.i  = 'c';
	type.j = 33;
	type.z = 3.3f;
	printf("%c %i %f",type.i,type.j,type.z);
	return 0;
}
