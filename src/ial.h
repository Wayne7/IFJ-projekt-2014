#ifndef _IAL
#define _IAL

#include <stdio.h>
#include <stdbool.h>

#define BT_OK 0
#define BT_ERR 1

typedef union {
	int i;
	double r;
	char *s;
	bool b;

}sValue;

typedef enum{
	tInt,
	tString,
	tBool,
	tReal
}sType;

typedef struct{
	char *name;
	sType type;
}sParam;

typedef struct params{
	sParam param;
	struct params *ptr;
}sParams;

typedef struct Symbol{
	char *key;
	sType type;
	sParams params;
	bool isFunction;
	bool isDefined;
	//symbolTablePtr symbolTable;		// lokalni tabulka symbolu pro funkce

}symbol, *symbolPtr;


typedef struct BTree{
	char *key;
	symbol content;
	struct BTree *LPtr;
	struct BTree *RPtr;

}*symbolTablePtr;


void STInit(symbolTablePtr *root);
void BTInit(symbolTablePtr *root);
int BTInsert(symbolTablePtr *root, char *key, symbol s);
symbolTablePtr BTSearch(symbolTablePtr *root, char *key);

#endif