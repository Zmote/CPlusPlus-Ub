#include <stdio.h>
#include <string.h>

int main(){
	char buffer[40];
	buffer[0] = '\0';
	char * name = "Zafer";
	char * nachname = "Dogan";
	strcat(buffer,name);
	strcat(buffer, " ");
	strcat(buffer, nachname);
	printf("%s", buffer);
}
