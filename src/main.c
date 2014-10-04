#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "strings.h"




int main(){

	string test;
	char testChar = 'a';
	strStringInit(&test);

	for (int x = 0; x < 10; x++){
		strAddCharToString(&test, testChar);
		testChar++;
	}

	printf("%s\n", test.str);

	strEmptyString(&test);

	printf("%s\n", test.str);
	
	strFreeString(&test);
	
	return 0;
}