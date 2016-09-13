#include <stdio.h>
#define MAX_FUNCTIONS 10
int counter = 0;
void * ampeln[MAX_FUNCTIONS];

void printRed();
void printBlue();
void printGreen();
void addAmpel(void (*ptr)(void));
void printAmpeln();

int main(){
	addAmpel(printRed);
	addAmpel(printBlue);
	addAmpel(printGreen);
	printAmpeln();
}

void addAmpel(void (*ptr)(void)){
	if(counter < MAX_FUNCTIONS){
		ampeln[counter] = ptr;
		counter++;
	}
}

void printAmpeln(){
	void (*ptr)(void);
	int i;
	for(i = 0; i < counter;i++){
		ptr = ampeln[i];
		ptr();
	}
}

void printRed(){
	printf("Die Ampel ist rot.\n");
}
void printBlue(){
	printf("Die Ampel ist blau.\n");
}
void printGreen(){
	printf("Die Ampel ist gr�n.\n");
}