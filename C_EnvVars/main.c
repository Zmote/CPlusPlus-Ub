#include <stdio.h>
#include <stdlib.h>

int main(){
	char * envPointer;
	if(putenv("EU=Europe") != 0){
		printf("Something went wrong with putenv()");
		exit(-1);
	}

	envPointer = getenv("EU");
	if(envPointer == NULL){
		printf("Something went wrong with getenv()");
		exit(-1);
	}

	printf("Value of Env Variable EU=%s",envPointer);
	exit(0);
}
