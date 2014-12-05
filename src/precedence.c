#include "precedence.h"

tableEntries tramtadadaa = nula;

void stackInit(stack *ptr){
	ptr->top = NULL;
}

void push(stack *ptr, tableEntries data){
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

tableEntries top(stack *ptr){
	if (ptr->top != NULL)
		return ptr->top->data;
	return error;
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

void printStack(stack *ptr){
	int i = 0;
	stack s;
	stackInit(&s);
	while(ptr->top != NULL){
		push(&s,top(ptr));
		pop(ptr);
	}printf("----------------------\n");
	while(s.top != NULL){
		push(ptr,top(&s));
printf("%d: %d\n",i,top(&s));
		pop(&s);
		i++;
	}printf("----------------------\n");
	
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

tableEntries getIndex(tToken *token){


	switch (token->state)
	{
	case T_MUL:{
		return mul;
	}

	case T_DIV:{
		return divide;
	}

	case T_PLUS:{
		return plus;
	}

	case T_MINUS:{
		return minus;
	}

	case T_LESSER:{
		return lesser;
	}

	case T_GREATER:{
		return greater;
	}

	case T_LOE:{
		return loe;
	}

	case T_GOE:{
		return goe;
	}

	case T_EQUAL:{
		return equal;
	}

	case T_NOTEQUAL:{
		return notequal;
	}

	case T_LC:{
		return lc;
	}

	case T_RC:{
		return rc;
	}

	case T_SEMICOLON:{
		return dolar;
	}

	case T_INTEGER:
	case T_REAL :
	case T_IDENTIFICATOR : {
		return id;
		
	}

	default:{
printf("Unexcepted symbol\n");
		return error;
	}

	}

}


tableEntries reduction(stack *stack){
	tableEntries tmp;	//pomocná proměnná
	tableEntries item;	// návratová hodnota

	tmp = top(stack);
	pop(stack);
	switch(tmp){

		case mul:{
			if(tramtadadaa == nonterminal){
				tramtadadaa = nula;
				if(top(stack) == nonterminal){
					pop(stack);
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
			printf("mul\n");
					return item;
				}
				else{
					result = SYNTAX_ERR;
					return error;
				}
			}
			else
				return error;
		}

		case divide:{
			if(tramtadadaa == nonterminal){
				tramtadadaa = nula;
				if(top(stack) == nonterminal){
					pop(stack);
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
			printf("div\n");
					return item;
				}
				else{
					result = SYNTAX_ERR;
					return error;
				}
			}
			else
				return error;
		}

		case plus:{
			if(tramtadadaa == nonterminal){
				tramtadadaa = nula;
				if(top(stack) == nonterminal){
					pop(stack);
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
			printf("plus\n");
					return item;
				}
				else{
					result = SYNTAX_ERR;
					return error;
				}
			}
			else
				return error;
		}

		case minus:{
			if(tramtadadaa == nonterminal){
				tramtadadaa = nula;
				if(top(stack) == nonterminal){
					pop(stack);
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
			printf("minus\n");
					return item;
				}
				else{
					result = SYNTAX_ERR;
					return error;
				}
			}
			else
				return error;
		}

		case lesser:{
			if(tramtadadaa == nonterminal){
		printf("porovnání");
				pop(stack);
				item = top(stack);
				push(stack, nonterminal);
				return item;
			}
			else
				return error;
		}
		
		case greater:{
			if(tramtadadaa == nonterminal){
		printf("porovnání");
				pop(stack);
				item = top(stack);
				push(stack, nonterminal);
				return item;
			}
			else
				return error;
		}
		
		case loe:{
			if(tramtadadaa == nonterminal){
		printf("porovnání");
				pop(stack);
				item = top(stack);
				push(stack, nonterminal);
				return item;
			}
			else
				return error;
		}
		
		case goe:{
			if(tramtadadaa == nonterminal){
		printf("porovnání");
				pop(stack);
				item = top(stack);
				push(stack, nonterminal);
				return item;
			}
			else
				return error;
		}
		
		case equal:{
			if(tramtadadaa == nonterminal){
		printf("porovnání");
				pop(stack);
				item = top(stack);
				push(stack, nonterminal);
				return item;
			}
			else
				return error;
		}

		case notequal:{
			if(tramtadadaa == nonterminal){
		printf("porovnání");
				pop(stack);
				item = top(stack);
				push(stack, nonterminal);
				return item;
			}
			else
				return error;
		}

		case id:{
			if(top(stack) == slesser){
				pop(stack);
				item = top(stack);
				push(stack,nonterminal);
				return item;
			
			}
			else{
				result = SYNTAX_ERR;
				return error;
			}
		}

		case rc:{
			if(top(stack)==nonterminal){
				pop(stack);
				if(top(stack)==lc){
					pop(stack);
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
					return item;
				}
				else{
					tramtadadaa = nonterminal;
					return reduction(stack);
				}
			}


		}

		case nonterminal:{
			tramtadadaa = nonterminal;
			return reduction(stack);
		}
		case lc:
		case error:
		case dolar:
		case nula:
		case slesser:{
			result = SYNTAX_ERR;
			return error;
		}

	
	}

	result = SYNTAX_ERR;
	return error;

}




int precedence(tToken *token){
	stack s1;			// zasobnik pro ukladani terminalu a neterminalu

	tableEntries row;		// symbol na zasobniku (determinál)
	tableEntries col;		// symbol na vstupu

	stackInit(&s1);		// inicializace

	row = dolar;
	push(&s1, row);

	do{
		col = getIndex(token);
		if(col == error)
			return SYNTAX_ERR;
		//printf("***********************\n");


		switch (precedenceTable[row][col]){

		case B:{
				   	freeStack(&s1);			// pokud je v tabulce prazdno, jedna se o syntaktickou chybu
					return SYNTAX_ERR;
		}

		case G:{    						// Greater --> redukce
					//printf("před\t%d %d\n",row, col );
					//printStack(&s1);
					row = reduction(&s1);
					//printf("po:\t%d %d\n",row, col );
					//printStack(&s1);
					if(row == error)
						return SYNTAX_ERR;
					break;
		}
		case L:{							// Lesser --> < push 
					//printf("před:\t%d %d\n",row, col );
					//printStack(&s1);
					*token = tGetToken();
					if (token->state == T_ERR)
						return LEX_ERR;

					if(top(&s1) == nonterminal){
						if(col >= 4 && col <= 9){
							//printf("L if %d\n",col);
							push(&s1, col);
							row = col;
							//printf("po:\t%d %d\n",row, col );
							//printStack(&s1);
							break;
						}
						//printf("L else if\n");
						pop(&s1);
				   		push(&s1, slesser);
				   		push(&s1, nonterminal);
				   		push(&s1, col);
				   		row = col;
				   		//printf("po:\t%d %d\n",row, col );
						//printStack(&s1);
				   		break;
					}

					else{
						//printf("L else\n");
					 	push(&s1, slesser);
						push(&s1, col);
						row = col;
						//printf("po:\t%d %d\n",row, col );
						//printStack(&s1);
						break;
					}

		}

		case E:{
				//printf("E kur\n");
				push(&s1,col);
				row = col;
				*token = tGetToken();
				if (token->state == T_ERR)
					return LEX_ERR;
			}
		}

	} while (row != dolar || col != dolar);printf("jsme venku! %d\n",result);

	

	freeStack(&s1);
	return result;
}
