#define _CRT_SECURE_NO_WARNINGS
#include "strings.h"
#include "scanner.h"
#include "garbage_collector.h"
#include "parser.h"

	FILE *file;		// soubor globalne
	int LEX_STATE;



int main(){

	int result = SYNTAX_OK;
	

	if ((file = fopen("source.txt", "r")) == NULL){
		printf("Could not open file!\n");
		return 1;
	}

		result = parse();
		if (result != SYNTAX_OK)
			printf("Error!\n");
		else
			printf("OK!");
	
	
	
	gFree();
	
	fclose(file);
	return 0;
}
