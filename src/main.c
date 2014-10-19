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

<<<<<<< HEAD
	token = tGetToken();
	printf("%s\n", token.content);

	gFree();
	
	fclose(file);
=======
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
	
	
>>>>>>> parent of 680a14a... update
	return 0;
}
