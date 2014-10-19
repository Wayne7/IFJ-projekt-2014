#define _CRT_SECURE_NO_WARNINGS
#include "strings.h"
#include "scanner.h"
#include "garbage_collector.h"

	FILE *file;		// soubor globalne



int main(){

	

	if ((file = fopen("source.txt", "r")) == NULL){
		printf("Could not open file!\n");
		return 1;
	}


	
	
	
	tToken token;

	

	token = tGetToken();
	printf("%s\n", token.content);
	printf("%d\n", token.state);

	token = tGetToken();
	printf("%s\n", token.content);

	gFree();
	
	fclose(file);
	return 0;
}
