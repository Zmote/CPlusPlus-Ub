#include <stdio.h>
#include <stdlib.h>

int power(int num, int exp){
	int res = 1;
	for(int i = 1;i <= exp;i++){
		res = res * num;
	}
	return res;
}

int main(void){
	printf("%s","Before struct output...\n");
	typedef struct{
		char * name;
		char * surname;
		int age;
		char * description;
	}Person;

	Person zafer;
	zafer.name = "Zafer";
	zafer.surname = "Dogan";
	zafer.age = 27;
	zafer.description = "He is an awesome dude";

	printf("%s\n%s\n%i\n%s\n", zafer.name, zafer.surname,zafer.age,zafer.description);
	printf("%s", "After struct output...\n");
	printf("%s", "Testing something out...\n");

	printf("%s : %i", "Res of 3 exp 3 = ", power(3,3));

	return 0;
}