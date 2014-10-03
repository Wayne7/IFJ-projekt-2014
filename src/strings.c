#include "strings.h"

int strStringInit(string *str){
	if ((str->str = (char*) malloc(sizeof(char) * STRING_ALLOC_SIZE)) == NULL){
		return STRING_ERROR;
	}
	str->str[0] = '\0';
	str->stringLength = 0;
	str->allocatedMemory = STRING_ALLOC_SIZE;
	return STRING_SUCCESS;
}

int strAddCharToString(string *str, char c){
	if (str->stringLength >= str->allocatedMemory - 1){
		if ((str->str = (char*)realloc(str->str, str->allocatedMemory + STRING_ALLOC_SIZE)) == NULL){
			return STRING_ERROR;
		}
		str->allocatedMemory += STRING_ALLOC_SIZE;
	}
		str->str[str->stringLength] = c;
		str->stringLength++;
		str->str[str->stringLength] = '\0';
		return STRING_SUCCESS;
}

void strFreeString(string *str){
	free(str->str);
}

void strEmptyString(string *str){
	str->str[0] = '\0';
	str->stringLength = 0;
}