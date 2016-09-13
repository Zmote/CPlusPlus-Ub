#include <stdio.h>

void printBin(int value);

int main(){
//	printBinary(4);
//	printBinary(2);
//	printBinary(4781);
	int x = 5000;
	printf("Zahl dezimal: %d\n", x);
	printBin(x);
	x = ~x;
	printf("\nInvertierte Zahl dezimal: %d\n", x);
	printBin(x);
	x = ~x;
	printf("\nNochmals invertierte Zahl dezimal: %d\n", x);
	printBin(x);
	printf("Beispiel EXOR:\n");
	int y = 23 ^ 5;
	printf("Wert: %d", y);
	return 0;
}

void printBin(int value){
	int i;
	int resultat;
	int anz_bits = sizeof(value)*8;
	unsigned int mask = 1 << (anz_bits-1);
	printf("Value of %d in binary: ",value);
	for(i=0;i < anz_bits;i++){
		resultat = value & mask;
		if(resultat == 0){
			printf("%c",'0');
		}else{
			printf("%c",'1');
		}
		mask = mask >> 1;
	}
	printf("\n");
}
