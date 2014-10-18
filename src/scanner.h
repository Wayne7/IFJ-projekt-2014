#ifndef _SCANNER
#define _SCANNER

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <stdbool.h>


typedef enum{

	T_START,					// 00 - vychozi stav
	T_IDENTIFICATOR,			// 01 - identifikator
	T_COMMENT,					// 02 - komentar
	T_END,						// 03 - konec cteni

	// jeste jich sem prijde mnohem vic :)


}tState;

typedef struct{

	tState state;		// informace o druhu tokenu
	char *content;		// obsah tokenu
	int row;			// radek na kterem se token nachazi
	int length;			// delka tokenu

}tToken;

extern FILE *file;

tToken tGetToken();
void tInitToken();
void tFreeToken();
void tExtentToken(int c);

#endif
