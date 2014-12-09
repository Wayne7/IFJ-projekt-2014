#ifndef _INTERPRET
#define _INTERPRET

#include "string.h"
#include "garbage_collector.h"
#include "ilist.h"
#include "ial.h"

#define TRUE 0
#define FALSE 1

//int interpr(tInst *T, tInstList *instrlist);

typedef struct{
	char *name;
	sType type;
	sValue val;
}sVariable;


typedef struct f_item{
	sVariable data;
	struct f_item *next;
}sFrameItem;

typedef struct{
	sFrameItem* First;
	sFrameItem* Last;
}sFrame;


void frameInit(sFrame *ptr);
void frameInsert(sFrame *ptr, sVariable data);
sVariable *frameSearch(sFrame *ptr, char* name);
void frameDisposal(sFrame *ptr);
sVariable createVar(sValue val, sType type, char* name);

#endif
