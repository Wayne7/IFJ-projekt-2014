#ifndef _PARSER
#define _PARSER

#include <stdio.h>
#include "scanner.h"
#include "ial.h"


#define SYNTAX_OK 1
#define SYNTAX_ERR -1
#define SEM_ERR -2
#define LEX_ERR -3

int parse(symbolTablePtr *symbolTable);
int varType(tToken *token, symbolTablePtr *symbolTable, symbol *s);
int params(tToken *token, symbolTablePtr *symbolTable);
int defFunction(tToken *token, symbolTablePtr *symbolTable);

#endif