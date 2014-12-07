#ifndef _PRECEDENCE
#define _PRECEDENCE

#include <stdio.h>
#include "scanner.h"
#include "parser.h"
#include "ial.h"
#include "ilist.h"


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
	error,
	nula
}tableEntries;


/* Data ulozena do prvku zasobniku */
typedef tableEntries tableData;

typedef struct id_item
{
	struct id_item *ptr;
	char* name;
}*id_name;

typedef struct{
	id_name top;
}name_stack;

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
