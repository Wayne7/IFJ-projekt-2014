#ifndef _PARSER
#define _PARSER

#include <stdio.h>
#include "scanner.h"

#define SYNTAX_OK 1
#define SYNTAX_ERR -1
#define SEM_ERR -2
#define LEX_ERR -3

int parse();
int varType(tToken *token);
int params(tToken *token);
int defFunction(tToken *token);

#endif