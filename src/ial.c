#include "ial.h"
#include "garbage_collector.h"
#include <string.h>

/*
*	Implementace binarniho stromu prevzata z druhe domaci ulohy do predmetu IAL
*/



int BTInsert(symbolTablePtr *root, char *key, symbol s){
	if (*root == NULL){
		symbolTablePtr tmp;

		if ((tmp = gMalloc(sizeof(struct BTree))) == NULL){
			return BT_ERR;
		}

		tmp->key = key;
		tmp->content = s;
		tmp->LPtr = NULL;
		tmp->RPtr = NULL;

		*root = tmp;

		return BT_OK;
	}
	else{
		int cmp = strcmp((*root)->key, key);

		if (cmp < 0){
			return BTInsert(&(*root)->LPtr, key, s);
		}
		if (cmp > 0){
			return BTInsert(&(*root)->RPtr, key, s);
		}
		if (cmp == 0){
			return BT_ERR;							// vratim error, protoze polozka jiz v tabulce je
		}


	}

	return BT_OK;
}



symbolTablePtr BTSearch(symbolTablePtr *root, char *key){
	symbolTablePtr tmp;
	tmp = *root;

	if (tmp == NULL){
		return NULL;			
	}

	int cmp;

	cmp = strcmp(tmp->key, key);

	if (cmp == 0){
		return tmp;
	}
	else if (cmp < 0){
		return BTSearch(&(*root)->LPtr, key);
	}
	else{
		return BTSearch(&(*root)->RPtr, key);
	}

	return NULL;
}

void BTInit(symbolTablePtr *root){
	*root = NULL;
}
