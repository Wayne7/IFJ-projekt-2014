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
	
	gListInit();
	string test;
	strStringInit(&test);
	strAddCharToString(&test, 'a');
	strAddCharToString(&test, 'h');
	strAddCharToString(&test, 'o');
	strAddCharToString(&test, 'j');

	printf("%s\n", test.str);
	strEmptyString(&test);
	printf("%s\n", test.str);

	gFree();
	
	return 0;
}
