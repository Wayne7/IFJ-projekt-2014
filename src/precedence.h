#ifndef _PRECEDENCE
#define _PRECEDENCE

#include <stdio.h>
#include "scanner.h"
#include "parser.h"
#include "ial.h"


/* Priority precedencni tabulky */
typedef enum {
	G,		// Greater
	L,		// Lesser
	E,		// Equal
	B		// Blank
}tablePriorities;

/* Reprezentace terminalu a neterminalu */
typedef enum{
	mul,
	divide,
	plus,
	minus,
	lesser,
	greater,
	loe,
	goe,
	equal,
	notequal,
	id,
	lc,
	rc,
	dolar,
	slesser,
	nonterminal,
	error
}tableEntries;


/* Data ulozena do prvku zasobniku */
typedef struct{

	tableEntries entry;
}tableData;


/* Prvek zasobniku */
typedef struct sItem{
	struct sItem *ptr;
	tableData data;
}*stackItem;


/* Zasobnik */
typedef struct{
	stackItem top;
}stack;

extern int result;

int precedence(tToken *token);

#endif