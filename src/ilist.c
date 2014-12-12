#include "ilist.h"

void instListSkip(tInstList *list){
	instListSucc(list);
	tItem item = *(list->Active);
	while (item.instruction.type != I_END){
		instListSucc(list);
		item = *(list->Active);
		if (item.instruction.type == I_IF)
			instListSkip(list);
	}
}


void instListInit(tInstList *list){     //inicializace seznamu
	list->Active = NULL;
	list->First = NULL;
	list->Last = NULL;
}

void instListSucc(tInstList *list){     //posouva aktivitu na dalsi instrukci
	if (list->Active == NULL){
		list->Active = list->First;
	}
	else
	list->Active = list->Active->ptr;
}

void instListInsert(tInstList *list, tInst inst){   // vklada prvek a konec seznamu
	tItem *tmp;

	if ((tmp = gMalloc(sizeof(struct Item))) == NULL){
		result = INT_ERR;
		return;
	}
	tmp->instruction = inst;
	tmp->ptr = NULL;

	if (list->First == NULL){
		list->First = tmp;
	}
	else{
		list->Last->ptr = tmp;
	}
	list->Last = tmp;
}

void instListFirst (tInstList *list){       //nastavi aktivitu na prvni instrukci
    list->Active = list->First;
}

void instListGoto (tInstList *list, void *gotoInstr){ //nastavi aktivitu na instrukci podle zadaneho ukazatele
    list->Active = (tItem*) gotoInstr;
}

void *instLastPtr (tInstList *list){     //vraci ukazatel na posledni instrukci
    return (void*) list->Last;
}

tInst *instCopy (tInstList *list){        //vraci aktivni instrukci
	if (list->Active == NULL){
		return NULL;
	}
	else{
		return &(list->Active->instruction);
	}
}

void instListPrint(tInstList *list){
	tItem *tmp = list->First;
	while(tmp != NULL){
		printf("%d - %p , %p , %p\n",tmp->instruction.type,tmp->instruction.addr1,tmp->instruction.addr2,tmp->instruction.addr3 );
		tmp = tmp->ptr;}
}


tInst createInst(tInstType type, void* addr1, void* addr2, void* addr3){
	tInst item;
	item.type = type;
	item.addr1 = addr1;
	item.addr2 = addr2;
	item.addr3 = addr3;

	return item;
}
