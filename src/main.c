#define _CRT_SECURE_NO_WARNINGS
#include "strings.h"
#include "scanner.h"
#include "garbage_collector.h"
#include "parser.h"
#include "ial.h"

	FILE *file;		// soubor globalne
	int LEX_STATE;



int main(){

	int result = SYNTAX_OK;
	

	if ((file = fopen("source.txt", "r")) == NULL){
		printf("Could not open file!\n");
		return 1;
	}

		symbolTablePtr symbolTable;
		BTInit(&symbolTable);

		result = parse(&symbolTable);

		if ((BTSearch(&symbolTable, "zaknaktel\0")) == NULL){
			printf("neni tam\n");
		}

		if (result != SYNTAX_OK){
			printf("%d\n", result);
			printf("Error!\n");
		}
		else
			printf("OK!\n");
	
	
	
	gFree();
	
	fclose(file);


	return 0;
}
