#include <string.h>
#include "interpret.h"


void frameInit(sFrame *ptr){
	ptr->First = NULL;
	ptr->Last = NULL;
}

void frameInsert(sFrame *ptr, sVariable data){
	sFrameItem *tmp;

	if ((tmp = gMalloc(sizeof(*tmp))) == NULL){
		result = INT_ERR;
		return;
	}

	tmp->data = data;
	tmp->next = NULL;

	if (ptr->First == NULL)
		ptr->First = tmp;
	else
		ptr->Last->next = tmp;

	ptr->Last = tmp;
}
sVariable *frameSearch(sFrame *ptr, char* name){
	sFrameItem *item = ptr->First;
	while(item != NULL){
		if(strcmp(item->data.name,name)==0)
			return &(item->data);
		item = item->next;
	}
	return NULL;
}
void frameDisposal(sFrame *ptr){
	sFrameItem *item = ptr->First;
	sFrameItem *tmp;
	while(item != NULL){
		tmp = item->next;
		free(item);
		item = tmp;
	}
}

sVariable createVar(sValue val, sType type, char* name){
	sVariable item;
	item.val = val;
	item.type = type;
	item.name = name;
	return item;
}






// int interpr(tInst *T, tInstList *instrlist){
// 	instrListFirst(instrlist);
// 	tInstr *L;

// 	while (1)
// 	{


// 		switch (L)
// 		{
// 		case I_STOP:
// 			return 0;
// 			break;

// 		case I_ADD:
// 			((symbol*)L->addr1)->value++;
// 			break;

// 		case I_SUB:
// 			((symbol*)L->addr1)->value--;
// 			break;

// 		case I_MUL:
// 			//kontrola typu

// 			((symbol*)L->addr3)->value = (((symbol*)L->addr1)->value) * (((symbol*)L->addr2)->value);
// 			break;

// 		case I_DIV:
// 			//kontrola typu

// 			((symbol*)L->addr3)->value = (((symbol*)L->addr1)->value) / (((symbol*)L->addr2)->value);
// 			break;

// 		case I_CONC:
// 			((symbol*)L->addr3)->value = strcat(((symbol*)L->addr1)->value, ((symbol*)L->addr2)->value);
// 			break;

// 		case I_LESSER:
// 			if ((((symbol*)L->addr1)->value) < (((symbol*)L->addr2)->value)))
// 				((symbol*)L->addr3)->value = TRUE;
// 			else
// 				((symbol*)L->addr3)->value = FALSE;
// 			break;

// 		case I_GREATER:
// 			if ((((symbol*)L->addr1)->value) > (((symbol*)L->addr2)->value)))
// 				((symbol*)L->addr3)->value = TRUE;
// 			else
// 				((symbol*)L->addr3)->value = FALSE;
// 			break;

// 		case I_LOE:
// 			if ((((symbol*)L->addr1)->value) >= (((symbol*)L->addr2)->value)))
// 				((symbol*)L->addr3)->value = TRUE;
// 			else
// 				((symbol*)L->addr3)->value = FALSE;
// 			break;

// 		case I_GOE:
// 			if ((((symbol*)L->addr1)->value) <= (((symbol*)L->addr2)->value)))
// 				((symbol*)L->addr3)->value = TRUE;
// 			else 
// 				((symbol*)L->addr3)->value = FALSE;
// 			break;

// 		case I_NOTEQUAL:
// 			if ((((symbol*)L->addr1)->value) != (((symbol*)L->addr2)->value))
// 				((symbol*)L->addr3)->value = TRUE;
// 			else
// 				((symbol*)L->addr3)->value = FALSE;
// 			break;

// 		case I_EQUAL:
// 			if ((((symbol*)L->addr1)->value) == (((symbol*)L->addr2)->value))
// 				((symbol*)L->addr3)->value = TRUE;
// 			else
// 				((symbol*)L->addr3)->value = FALSE;
// 			break;

// 		case I_LENGTH:
// 			length(instrlist);
// 			break

// 		case I_SORT:
// 			break;

// 		case I_COPY:
// 			copy(instrlist, L->addr ? , int count);
// 			break;

// 		case I_FIND:
// 			instListGoto(instrlist, L->addr3);
// 			break;
		






// 		}

// 	L = instListSucc();
// 	}
	
// }


