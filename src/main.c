#define _CRT_SECURE_NO_WARNINGS
#include "strings.h"
#include "scanner.h"
#include "garbage_collector.h"

	FILE *file;		// soubor globalne



int main(){

	

	/*if ((file = fopen("source.txt", "r")) == NULL){
		printf("Could not open file!\n");
		return 1;
	}


	tInitToken();
	tGetToken();

	printf("%s\n", token.content);
	printf("%d\n", token.length);

	tFreeToken();
	
	fclose(file);*/
	
	char *pole = NULL;
	pole = gMalloc(5);
	pole = gMalloc(5);
	pole = gMalloc(5);
	pole = gMalloc(5);
	pole = gMalloc(5);

	char *policko = gMalloc(50);
	pole = gReAlloc(pole, 100);

	gFree();
	
	
	return 0;
}