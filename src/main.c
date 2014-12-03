#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include "strings.h"
#include "scanner.h"
#include "garbage_collector.h"
#include "parser.h"
#include "ial.h"
#include "precedence.h"
#include "ilist.h"

#include <stdlib.h>
#include <crtdbg.h>

	FILE *file;		// soubor globalne



int main(int argc, char** argv){

	int result = SYNTAX_OK;
	
	if (argc != 2){
		return 99;
	}
	

	if ((file = fopen(argv[1], "r")) == NULL){
		printf("Could not open file!\n");
		return 99;
	}

		/*symbolTablePtr symbolTable;
		BTInit(&symbolTable);

		result = parse(&symbolTable);

		if (result != SYNTAX_OK){
			printf("%d\n", result);
			printf("Error!\n");
		}
		else
			printf("OK!\n");
	
		tInstList list;
		instListInit(&list);*/

	tToken token;
	tInitToken(&token);
	token = tGetToken();

	printf("%d\n", token.state);
	printf("%s\n", token.content);

	gFree();
	printf("memory leaks: %d\n", _CrtDumpMemoryLeaks());
	
	fclose(file);

	return 0;
}
