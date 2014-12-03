#include "ilist.h"




void instListInit(tInstList *list){     //inicializace seznamu
	list->Active = NULL;
	list->First = NULL;
	list->Last = NULL;
}

void instListSucc(tInstList *list){     //posouva aktivitu na dalsi instrukci
	if (list->Active == NULL){
		return;
	}
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

