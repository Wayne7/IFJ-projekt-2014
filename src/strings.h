#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define STRING_ERROR 91
#define STRING_SUCCESS 90
#define STRING_ALLOC_SIZE 8



typedef struct {
	int stringLength;
	int allocatedMemory;
	char * str;

}string;

int strStringInit(string * str);
void strFreeString(string * str);
int strDddCharToString(string * str, char c);
void strEmptyString(string *str);
