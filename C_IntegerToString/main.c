#include <stdio.h>

void convertToString(int zahl, char * buffer);

int main(){
	char numToString[3];
	int zahl = 10;
	convertToString(zahl,numToString);
	printf("Converted num: %s", numToString);
	return 0;
}

void convertToString(int zahl, char * buffer){
	sprintf(buffer, "%d", zahl);
}