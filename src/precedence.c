#include "precedence.h"


void stackInit(stack *ptr){
	ptr->top = NULL;
}

void push(stack *ptr, tableData data){
	stackItem item;

	if ((item = malloc(sizeof(struct sItem))) == NULL){
		return;
	}
	item->data = data;
	item->ptr = ptr->top;
	ptr->top = item;
}

void pop(stack *ptr){
	stackItem item;

	if (ptr->top != NULL){
		item = ptr->top;
		ptr->top = item->ptr;
		free(item);
	}
}

void top(stack *ptr, tableData *data){
	if (ptr->top != NULL){
		*data = ptr->top->data;
	}
}

bool stackEmpty(stack *ptr){
	return ptr->top == NULL;
}

void freeStack(stack *ptr){
	stackItem tmp;

	while (ptr->top != NULL){
		tmp = ptr->top;
		ptr->top = tmp->ptr;
		free(tmp);
	}
}


const tablePriorities precedenceTable[14][14] = {

	/*			 *	/  +  -  <  >  <= >= =  <> ID (  )  $  */
	/* * */		{G, G, G, G, G, G, G, G, G, G, L, L, G, G},
	/* / */		{G, G, G, G, G, G, G ,G, G, G, L, L, G, G},
	/* + */		{L, L, G, G, G, G, G, G, G, G, L, L, G, G},
	/* - */		{L, L, G, G, G, G, G, G, G, G, L, L, G, G},
	/* < */		{L, L, L, L, G, G, G, G, G, G, L, L, G, G},
	/* > */		{L, L, L, L, G, G, G, G, G, G, L, L, G, G},
	/* <= */	{L, L, L, L, G, G, G, G, G, G, L, L, G, G},
	/* >= */	{L, L, L, L, G, G, G, G, G, G, L, L, G, G},
	/* = */		{L, L, L, L, G, G, G, G, G, G, L, L, G, G},
	/* <> */	{L, L, L, L, G, G, G, G, G, G, L, L, G, G},
	/* ID */	{G, G, G, G, G, G, G, G, G, G, B, B, G, G},
	/* ( */		{L, L, L, L, L, L, L, L, L, L, L, L, E, B},
	/* ) */		{G, G, G, G, G, G, G, G, G, G, B, B, G, G},
	/* $ */		{L, L, L, L, L, L, L, L, L, L, L, L, B, B}
};

int getIndex(tToken *token, tableData *col){


	switch (token->state)
	{
	case T_MUL:{
		col->entry = mul;
		break;
	}

	case T_DIV:{
		col->entry = divide;
		break;
	}

	case T_PLUS:{
		col->entry = plus;
		break;
	}

	case T_MINUS:{
		col->entry = minus;
		break;
	}

	case T_LESSER:{
		col->entry = lesser;
		break;
	}

	case T_GREATER:{
		col->entry = greater;
		break;
	}

	case T_LOE:{
		col->entry = loe;
		break;
	}

	case T_GOE:{
		col->entry = goe;
		break;
	}

	case T_EQUAL:{
		col->entry = equal;
		break;
	}

	case T_NOTEQUAL:{
		col->entry = notequal;
		break;
	}

	case T_LC:{
		col->entry = lc;
		break;
	}

	case T_RC:{
		col->entry = rc;
		break;
	}

	case T_SEMICOLON:{
		col->entry = dolar;
		break;
	}

	case T_INTEGER:
	case T_REAL :
	case T_IDENTIFICATOR : {
					col->entry = id;
		   break;
	}

	default:{
		printf("Unexcepted symbol\n");
		return SYNTAX_ERR;
	}

	}

	return SYNTAX_OK;
}


int reduction(stack *stack){



}

int precedence(tToken *token){
	stack s1;			// zasobniky pro ukladani terminalu a neterminalu
	stack s2;

	tableData row;		// symbol na zasobniku
	tableData col;		// symbol na vstupu
	tableData tmp;

	stackInit(&s1);		// inicializace
	stackInit(&s2);

	row.entry = dolar;
	push(&s1, row);


	//do{
		result = getIndex(token, &col);


		switch (precedenceTable[row.entry][col.entry]){

		case B:{
				   freeStack(&s1);			// pokud je v tabulce prazdno, jedna se o syntaktickou chybu
				   freeStack(&s2);
				return SYNTAX_ERR;
		}

		case G:{
				   result = reduction(&s1);
				   break;
		}
		case L:{
				   tmp.entry = slesser;
				   push(&s1,tmp);
				   push(&s1, col);
				   row.entry = col.entry;
				   break;
		}

		default:{

			break;
			}
		}

	//} while ();

	

	printf("%d\n", col.entry);

	return result;
}