#include "precedence.h"

tableEntries tramtadadaa = nula;
int condition = 0;
int varcount = 0;
conList con_list;
name_stack s2;		// zásobník pro ukládání jmen identifikátorů


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
	}
	printf("--------zasobnik-------\n");
	while(s.top != NULL){
		push(ptr,top(&s));
		printf("%d: %d\n",i,top(&s));
		pop(&s);
		i++;
	}
	printf("----------------------\n");
	
}

void stackInit_N(name_stack *ptr){
	ptr->top = NULL;
}

void push_N(name_stack *ptr, char* data){
	id_name item;

	if ((item = malloc(sizeof(struct id_item))) == NULL){
		return;
	}
	item->name = data;
	item->ptr = ptr->top;
	ptr->top = item;
}



void pop_N(name_stack *ptr){
	id_name item;

	if (ptr->top != NULL){
		item = ptr->top;
		ptr->top = item->ptr;
		free(item);
	}
}

char* top_N(name_stack *ptr){
	if (ptr->top != NULL)
		return ptr->top->name;
	return "\0";
}

bool stackEmpty_N(name_stack *ptr){
	return ptr->top == NULL;
}

void freeStack_N(name_stack *ptr){
	id_name tmp;

	while (ptr->top != NULL){
		tmp = ptr->top;
		ptr->top = tmp->ptr;
		free(tmp);
	}
}

void printStack_N(name_stack *ptr){
	int i = 0;
	name_stack s;
	stackInit_N(&s);
	while(ptr->top != NULL){
		push_N(&s,top_N(ptr));
		pop_N(ptr);
	}
	printf("--------jmena--------\n");
	while(s.top != NULL){
		push_N(ptr,top_N(&s));
		printf("%d: %s\n",i,top_N(&s));
		pop_N(&s);
		i++;
	}
	printf("---------------------\n");
	
}

void conListInit(conList *ptr){
	ptr->First = NULL;
	ptr->Last = NULL;
}

void conListInsert(conList *ptr, con item){
	conItem *tmp = malloc(sizeof(conItem));
	tmp->value = item;
	tmp->next = NULL;
	if(ptr->First == NULL){
		ptr->First = tmp;
		ptr->Last = tmp;
	}
	ptr->Last = tmp;
}

bool conListSearch(conList *ptr, char *key, sValue *val){
	if(!ptr)
		return false;
	conItem *tmp = ptr->First;
	while(tmp){
		if(!strcmp(tmp->value.key,key)){
			printf("%d\n",tmp->value.value.i );
			*val = tmp->value.value;
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

void conListDispose(conList *ptr){
	conItem *tmp = NULL;
	conItem *next;
	if(ptr)
		tmp = ptr->First;
	while(tmp){
		next = tmp->next;
		free(tmp);
		tmp = next;
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
		if(condition)
			return error;
		return dolar;
	}

	case T_INTEGER:{
		con *item = gMalloc(sizeof(con));
		item->key = gMalloc(sizeof(char)*10);
		sprintf(item->key,"#_%d",varcount++);
		item->type = tInt;
		item->value.i = atoi(token->content);
		printf("%d\n", atoi(token->content));
		printf("%d\n",item->value.i );
		conListInsert(&con_list,*item);
		push_N(&s2, item->key);
		return id;

	}
	case T_REAL :{
		con *item = malloc(sizeof(con));
		item->key = malloc(sizeof(char)*10);
		sprintf(item->key,"#_%d",varcount++);
		item->type = tReal;
		item->value.r = atoi(token->content);
		conListInsert(&con_list,*item);
		push_N(&s2, item->key);
		return id;
	}
	case T_IDENTIFICATOR : {
		return id;
		
	}
	case T_KEYWORD:{
		if(condition && strcmp(token->content,"then")!=0)
			return dolar;
		return error;
	}


	default:{
		printf("Unexcepted symbol\n");
		return error;
	}

	}

}


tableEntries reduction(stack *stack, name_stack *n_stack){
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
					// tmp = top(n_stack);
					pop_N(n_stack);
					// instListInsert(&inst_list_global,createInst(I_MUL, top_N(n_stack), tmp));
					pop_N(n_stack);
					// push_N()

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
					pop_N(n_stack);
					pop_N(n_stack);
					pop(stack);
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
					printf("div\n");
					// push_N podíl

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
					pop_N(n_stack);
					pop_N(n_stack);
					pop(stack);
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
					printf("plus\n");
					// push_N součet

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
					pop_N(n_stack);
					pop_N(n_stack);
					pop(stack);
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
					printf("minus\n");
					// push_N rozdíl

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
				pop_N(n_stack);
				pop_N(n_stack);
				printf("porovnání");
				// push_N výsledek porovnání
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
				pop_N(n_stack);
				pop_N(n_stack);
				printf("porovnání");
				// push_N výsledek porovnání
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
				pop_N(n_stack);
				pop_N(n_stack);
				printf("porovnání");
				// push_N výsledek porovnání
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
				pop_N(n_stack);
				pop_N(n_stack);
				printf("porovnání");
				// push_N výsledek porovnání
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
				pop_N(n_stack);
				pop_N(n_stack);
				printf("porovnání");
				// push_N výsledek porovnání
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
				pop_N(n_stack);
				pop_N(n_stack);
				printf("porovnání");
				// push_N výsledek porovnání
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
					return reduction(stack,n_stack);
				}
			}


		}

		case nonterminal:{
			tramtadadaa = nonterminal;
			return reduction(stack,n_stack);
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
	//sValue asdf;

	tableEntries row;		// symbol na zasobniku (determinál)
	tableEntries col;		// symbol na vstupu

	stackInit(&s1);		// inicializace
	stackInit_N(&s2);

	row = dolar;
	push(&s1, row);

	conListInit(&con_list);

	do{
		//conListSearch(&con_list,"#_2",&asdf);
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
					//printf("---------redukce---------\n");
					//printf("před\t%d %d\n",row, col );
					//printStack(&s1);
					row = reduction(&s1, &s2);
					//printf("po:\t%d %d\n",row, col );
					//printStack(&s1);
					if(row == error){
						//printf("chyba!\n");
						return SYNTAX_ERR;
					}
					break;
		}
		case L:{							// Lesser --> < push 
					//printf("před:\t%d %d\n",row, col );
					//printStack(&s1);

					if(top(&s1) == nonterminal){

						if(col >= 4 && col <= 9){
							//printf("L if %d\n",col);
							push(&s1, col);
							row = col;
							//printf("po:\t%d %d\n",row, col );
							//printStack(&s1);
						}
						else{
							//printf("L else if\n");
							pop(&s1);
					   		push(&s1, slesser);
					   		push(&s1, nonterminal);
					   		push(&s1, col);
					   		row = col;
					   		//printf("po:\t%d %d\n",row, col );
							//printStack(&s1);
				   		}
					}

					else{
						//printf("L else\n");
					 	push(&s1, slesser);
						push(&s1, col);
						row = col;
						//printf("po:\t%d %d\n",row, col );
						//printStack(&s1);
					}
					*token = tGetToken();
					if (token->state == T_ERR)
						return LEX_ERR;
					break;

		}

		case E:{
				push(&s1,col);
				row = col;
				*token = tGetToken();
				if (token->state == T_ERR)
					return LEX_ERR;
			}
		}
	//printf("\n-----\n\n" );
	//printStack_N(&s2);
	//printf("\n-----\n\n" );
	} while (row != dolar || col != dolar);//printf("jsme venku! %d\n",result);
	//conListSearch(&con_list,"#_2",&asdf);
	//printf("%d\n",asdf.i );

	

	freeStack(&s1);
	return result;
}
