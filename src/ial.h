#ifndef _IAL
#define _IAL

#include <stdio.h>
#include <stdbool.h>

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


typedef struct Symbol{
	char *key;
	sType type;
	sValue value;
	bool isFunction;


}symbol, *symbolPtr;


typedef struct BTree{

	char *key;
	symbol content;
	struct BTree *LPtr;
	struct BTree *RPtr;

}*symbolTablePtr;

#endif