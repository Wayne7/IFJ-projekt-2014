#define _CRT_SECURE_NO_WARNINGS
#include "precedence.h"

tableEntries entry = nula;
int varcount = 0;
symbolTablePtr ans=NULL;
name_stack s2;		// zásobník pro ukládání jmen identifikátorů
int condition;


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
	if(!ptr->top)
		return;
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

tableEntries getIndex(tToken *token,symbolTablePtr *symbolTable){


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
		if(condition){
			result = SYNTAX_ERR;
			return error;
		}
		return dolar;
	}

	case T_INTEGER:{
		symbol *item = gMalloc(sizeof(symbol));
		item->key = gMalloc(sizeof(char)*10);
		sprintf(item->key,"#_%d",varcount++);
		item->type = tInt;
		item->value.i = strtol(token->content,NULL,0);
		result = BTInsert(symbolTable,item->key, *item);
		ans = BTSearch(symbolTable, item->key);
		printf("identifikátor %d\n", ans->content.value.i);
		push_N(&s2, item->key);
		return id;
	}

	case T_REAL :{
		symbol *item = gMalloc(sizeof(symbol));
		item->key = gMalloc(sizeof(char)*10);
		sprintf(item->key,"#_%d",varcount++);
		item->type = tReal;
		item->value.r = strtod(token->content,NULL);
		result = BTInsert(symbolTable,item->key, *item);
		ans = BTSearch(symbolTable, item->key);
		push_N(&s2, item->key);
		return id;
	}

	case T_STRING:{
		symbol *item = gMalloc(sizeof(symbol));
		item->key = gMalloc(sizeof(char)*10);
		sprintf(item->key,"#_%d",varcount++);
		item->type = tString;
		item->value.s = token->content;
		result = BTInsert(symbolTable,item->key, *item);
		ans = BTSearch(symbolTable, item->key);
		push_N(&s2, item->key);
		return id;
	}

	// case T_BOOL:{
	// 	symbol *item = gMalloc(sizeof(symbol));
	// 	item->key = gMalloc(sizeof(char)*10);
	// 	sprintf(item->key,"#_%d",varcount++);
	// 	item->type = tBool;
	// 	item->value.b = strtod(token->content,NULL);				// !!!!
	// 	result = BTInsert(symbolTable,item->key, *item);
	// 	ans = BTSearch(symbolTable, item->key);
	// 	push_N(&s2, item->key);
	// 	return id;
	// }

	case T_IDENTIFICATOR : {
		symbolTablePtr item = BTSearch(symbolTable,token->content);
		if(item==NULL){
			return error;
		}
		if(!item->content.isDefined)
			return error;
		push_N(&s2,token->content);
		return id;
		
	}
	case T_KEYWORD:{
		if(condition == 1 && (strcmp(token->content,"then")==0))
			return dolar;
		if(condition == 2 && (strcmp(token->content,"do")==0))
			return dolar;
		return error;

	}


	default:{
		printf("Unexcepted symbol\n");
		return error;
	}

	}

}


tableEntries reduction(stack *stack, name_stack *n_stack, symbolTablePtr *symbolTable){
	tableEntries tmp;	//pomocná proměnná
	tableEntries item;	// návratová hodnota

	tInst inst;
	symbol *polozka = gMalloc(sizeof(symbol));
	polozka->key = gMalloc(sizeof(char)*10);
	symbolTablePtr pom1,pom2;



	tmp = top(stack);
	pop(stack);
	switch(tmp){

		case mul:{
			if(entry == nonterminal){
				entry = nula;
				if(top(stack) == nonterminal){
					pop(stack);
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
					//printf("mul\n");
					pom1 = BTSearch(symbolTable,top_N(n_stack));
					pop_N(n_stack);
					pom2 = BTSearch(symbolTable,top_N(n_stack));
					sprintf(polozka->key,"#_%d",varcount++);
					switch(pom1->content.type){
					
						case tInt:{
							if(pom2->content.type == tInt){
								polozka->type = tInt;
								result = BTInsert(symbolTable,polozka->key, *polozka);
								ans = BTSearch(symbolTable,polozka->key);
								inst = createInst(I_MUL, pom1, pom2, (void*) ans);
								break;
							}

							if(pom2->content.type == tReal){
								polozka->type = tReal;
								result = BTInsert(symbolTable,polozka->key, *polozka);
								ans = BTSearch(symbolTable,polozka->key);
								inst = createInst(I_MUL, pom1, pom2, (void*) ans);
								break;
							}
							else{
								result = SEM_ERR2;							//chyba typové kompatibility
								return error;
							}
						}

						case tReal:{
							polozka->type = tReal;
							result = BTInsert(symbolTable,polozka->key, *polozka);
						
							if(pom2->content.type == tInt){
								ans = BTSearch(symbolTable,polozka->key);
								inst = createInst(I_MUL, pom1, pom2,(void*) ans);
								break;
							}
							if(pom2->content.type == tReal){							
								ans = BTSearch(symbolTable,polozka->key);
								inst = createInst(I_MUL, pom1, pom2,(void*) ans);
								break;
							}
							else{
								result = SEM_ERR2;							//chyba typové kompatibility
								return error;
							}

						}

						case tString:
						case tBool:{
								result = SEM_ERR2;							//chyba typové kompatibility
								return error;
						}
					}
		
					pop_N(n_stack);
					push_N(&s2, polozka->key);
					instListInsert(&inst_list_global,inst);
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
			if(entry == nonterminal){
				entry = nula;
				if(top(stack) == nonterminal){
					pop(stack);
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
					//printf("divide\n");
					pom1 = BTSearch(symbolTable,top_N(n_stack));
					pop_N(n_stack);
					pom2 = BTSearch(symbolTable,top_N(n_stack));
					sprintf(polozka->key,"#_%d",varcount++);
					polozka->type = tReal;
					result = BTInsert(symbolTable,polozka->key, *polozka);
					ans = BTSearch(symbolTable,polozka->key);

					switch(pom1->content.type){
					
						case tInt:{
							if(pom2->content.type == tInt){
								inst = createInst(I_DIV, pom2, pom1,(void*) ans);
								break;
							}

							if(pom2->content.type == tReal){
								inst = createInst(I_DIV, pom2, pom1,(void*) ans);
								break;
							}
							else{
								result = SEM_ERR2;							//chyba typové kompatibility
								return error;
							}
						}

						case tReal:{
							if(pom2->content.type == tInt){
								inst = createInst(I_DIV, pom2, pom1,(void*) ans);
								break;
							}
							if(pom2->content.type == tReal){							
								inst = createInst(I_DIV, pom2, pom1,(void*) ans);
								break;
							}
							else{
								result = SEM_ERR2;							//chyba typové kompatibility
								return error;
							}

						}

						case tString:
						case tBool:{
								result = SEM_ERR2;							//chyba typové kompatibility
								return error;
						}
					}

					pop_N(n_stack);
					push_N(&s2, polozka->key);
					instListInsert(&inst_list_global,inst);
					return item;
				}
				else{
					result = SYNTAX_ERR;
					return error;
				}
			}
			else{
				result = SYNTAX_ERR;
				return error;
				}
		}

		case plus:{
			if(entry == nonterminal){
				entry = nula;
				if(top(stack) == nonterminal){
					pop(stack);
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
					//printf("plus\n");
					pom1 = BTSearch(symbolTable,top_N(n_stack));
					pop_N(n_stack);
					pom2 = BTSearch(symbolTable,top_N(n_stack));
					sprintf(polozka->key,"#_%d",varcount++);

					switch(pom1->content.type){
					
						case tInt:{
							if(pom2->content.type == tInt){
								polozka->type = tInt;
								result = BTInsert(symbolTable,polozka->key, *polozka);
								ans = BTSearch(symbolTable,polozka->key);
								inst = createInst(I_ADD, pom2, pom1,(void*) ans);
								break;
							}

							if(pom2->content.type == tReal){
								polozka->type = tReal;
								result = BTInsert(symbolTable,polozka->key, *polozka);
								ans = BTSearch(symbolTable,polozka->key);
								inst = createInst(I_ADD, pom2, pom1,(void*) ans);
								break;
							}
							else{
								result = SEM_ERR2;							//chyba typové kompatibility
								return error;
							}
						}

						case tReal:{
							polozka->type = tReal;
							result = BTInsert(symbolTable,polozka->key, *polozka);
							
							if(pom2->content.type == tReal){
								ans = BTSearch(symbolTable,polozka->key);
								inst = createInst(I_ADD, pom2, pom1,(void*) ans);
								break;
							}
								
							if(pom2->content.type == tInt){
								ans = BTSearch(symbolTable,polozka->key);
								inst = createInst(I_ADD, pom2, pom1,(void*) ans);
								break;
							}
							else{
								result = SEM_ERR2;							//chyba typové kompatibility
								return error;
							}
						}

						case tString:{
							if(pom2->content.type == tString){
								polozka->type = tString;
								result = BTInsert(symbolTable,polozka->key, *polozka);
								ans = BTSearch(symbolTable,polozka->key);
								inst = createInst(I_CONC, pom2, pom1,(void*) ans);
								break;
							}
							else{
								result = SEM_ERR2;							//chyba typové kompatibility
								return error;
							}
						}

						case tBool:{
								result = SEM_ERR2;							//chyba typové kompatibility
								return error;
						}
					}


					pop_N(n_stack);
					push_N(&s2, polozka->key);
					instListInsert(&inst_list_global,inst);
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
			if(entry == nonterminal){
				entry = nula;
				if(top(stack) == nonterminal){
					pop(stack);
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
					//printf("minus\n");
					pom1 = BTSearch(symbolTable,top_N(n_stack));
					pop_N(n_stack);
					pom2 = BTSearch(symbolTable,top_N(n_stack));
					sprintf(polozka->key,"#_%d",varcount++);
					switch(pom1->content.type){
					
						case tInt:{
							if(pom2->content.type == tInt){
								polozka->type = tInt;
								result = BTInsert(symbolTable,polozka->key, *polozka);
								ans = BTSearch(symbolTable,polozka->key);
								inst = createInst(I_SUB, pom2, pom1, (void*) ans);
								break;
							}

							if(pom2->content.type == tReal){
								polozka->type = tReal;
								result = BTInsert(symbolTable,polozka->key, *polozka);
								ans = BTSearch(symbolTable,polozka->key);
								inst = createInst(I_SUB, pom2, pom1, (void*) ans);
								break;
							}
							else{
								result = SEM_ERR2;							//chyba typové kompatibility
								return error;
							}
						}

						case tReal:{
							polozka->type = tReal;
							result = BTInsert(symbolTable,polozka->key, *polozka);
						
							if(pom2->content.type == tInt){
								ans = BTSearch(symbolTable,polozka->key);
								inst = createInst(I_SUB, pom2, pom1,(void*) ans);
								break;
							}
							if(pom2->content.type == tReal){							
								ans = BTSearch(symbolTable,polozka->key);
								inst = createInst(I_SUB, pom2, pom1,(void*) ans);
								break;
							}
							else{
								result = SEM_ERR2;							//chyba typové kompatibility
								return error;
							}

						}

						case tString:
						case tBool:{
							return error;				// sémantická chyba
						}
					}
					pop_N(n_stack);
					push_N(&s2, polozka->key);
					instListInsert(&inst_list_global,inst);
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
			if(entry == nonterminal){
					if(stack->top->data != nonterminal){
						result = SYNTAX_ERR;			// neexistuje levá strana porovnání
						return error;
					}
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
					//printf("lesser\n");
					pom1 = BTSearch(symbolTable,top_N(n_stack));
					pop_N(n_stack);
					pom2 = BTSearch(symbolTable,top_N(n_stack));
					sprintf(polozka->key,"#_%d",varcount++);
					if(pom1->content.type != pom2->content.type){
						result = SEM_ERR2;							//chyba typové kompatibility
						return error;
					}
					polozka->type = tBool;
					result = BTInsert(symbolTable,polozka->key, *polozka);
					ans = BTSearch(symbolTable,polozka->key);
					inst = createInst(I_LESSER, pom1, pom2, (void*) ans);
					pop_N(n_stack);
					push_N(&s2, polozka->key);
					instListInsert(&inst_list_global,inst);
					return item;
			}
			else
				return error;
		}
		
		case greater:{
			if(entry == nonterminal){
					if(stack->top->data != nonterminal){
						result = SYNTAX_ERR;			// neexistuje levá strana porovnání
						return error;
					}
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
					//printf("greater\n");
					pom1 = BTSearch(symbolTable,top_N(n_stack));
					pop_N(n_stack);
					pom2 = BTSearch(symbolTable,top_N(n_stack));
					sprintf(polozka->key,"#_%d",varcount++);
					if(pom1->content.type != pom2->content.type){
						result = SEM_ERR2;							//chyba typové kompatibility
						return error;
					}
					polozka->type = tBool;
					result = BTInsert(symbolTable,polozka->key, *polozka);
					ans = BTSearch(symbolTable,polozka->key);
					inst = createInst(I_GREATER, pom1, pom2, (void*) ans);
					pop_N(n_stack);
					push_N(&s2, polozka->key);
					instListInsert(&inst_list_global,inst);
					return item;
			}
			else
				return error;
		}
		
		case loe:{
			if(entry == nonterminal){
					if(stack->top->data != nonterminal){
						result = SYNTAX_ERR;			// neexistuje levá strana porovnání
						return error;
					}
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
					//printf("loe\n");
					pom1 = BTSearch(symbolTable,top_N(n_stack));
					pop_N(n_stack);
					pom2 = BTSearch(symbolTable,top_N(n_stack));
					sprintf(polozka->key,"#_%d",varcount++);
					if(pom1->content.type != pom2->content.type){
						result = SEM_ERR2;							//chyba typové kompatibility
						return error;
					}
					polozka->type = tBool;
					result = BTInsert(symbolTable,polozka->key, *polozka);
					ans = BTSearch(symbolTable,polozka->key);
					inst = createInst(I_LOE, pom1, pom2,(void*) ans);
					pop_N(n_stack);
					push_N(&s2, polozka->key);
					instListInsert(&inst_list_global,inst);
					return item;
			}
			else
				return error;
		}
		
		case goe:{
			if(entry == nonterminal){
					if(stack->top->data != nonterminal){
						result = SYNTAX_ERR;			// neexistuje levá strana porovnání
						return error;
					}
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
					//printf("goe\n");
					pom1 = BTSearch(symbolTable,top_N(n_stack));
					pop_N(n_stack);
					pom2 = BTSearch(symbolTable,top_N(n_stack));
					sprintf(polozka->key,"#_%d",varcount++);
					if(pom1->content.type != pom2->content.type){
						result = SEM_ERR2;							//chyba typové kompatibility
						return error;
					}
					polozka->type = tBool;
					result = BTInsert(symbolTable,polozka->key, *polozka);
					ans = BTSearch(symbolTable,polozka->key);
					inst = createInst(I_GOE, pom1, pom2,(void*) ans);
					pop_N(n_stack);
					push_N(&s2, polozka->key);
					instListInsert(&inst_list_global,inst);
					return item;
			}
			else
				return error;
		}
		
		case equal:{
			if(entry == nonterminal){
					if(stack->top->data != nonterminal){
						result = SYNTAX_ERR;			// neexistuje levá strana porovnání
						return error;
					}
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
					//printf("equal\n");
					pom1 = BTSearch(symbolTable,top_N(n_stack));
					pop_N(n_stack);
					pom2 = BTSearch(symbolTable,top_N(n_stack));
					sprintf(polozka->key,"#_%d",varcount++);
					if(pom1->content.type != pom2->content.type){
						result = SEM_ERR2;							//chyba typové kompatibility
						return error;
					}
					polozka->type = tBool;
					result = BTInsert(symbolTable,polozka->key, *polozka);
					ans = BTSearch(symbolTable,polozka->key);
					inst = createInst(I_EQUAL, pom1, pom2,(void*) ans);
					pop_N(n_stack);
					push_N(&s2, polozka->key);
					instListInsert(&inst_list_global,inst);
					return item;
			}
			else{
				result = SYNTAX_ERR;			// neexistuje pravá strana porovnání
				return error;
			}
		}

		case notequal:{
			if(entry == nonterminal){
					if(stack->top->data != nonterminal){
						result = SYNTAX_ERR;			// neexistuje levá strana porovnání
						return error;
					}
					pop(stack);
					item = top(stack);
					push(stack, nonterminal);
					//printf("notequal\n");
					pom1 = BTSearch(symbolTable,top_N(n_stack));
					pop_N(n_stack);
					pom2 = BTSearch(symbolTable,top_N(n_stack));
					if(pom1->content.type != pom2->content.type){
						result = SEM_ERR2;							//chyba typové kompatibility
						return error;
					}					
					sprintf(polozka->key,"#_%d",varcount++);
					polozka->type = tBool;
					result = BTInsert(symbolTable,polozka->key, *polozka);
					ans = BTSearch(symbolTable,polozka->key);
					inst = createInst(I_NOTEQUAL, pom1, pom2, (void*) ans);
					pop_N(n_stack);
					push_N(&s2, polozka->key);
					instListInsert(&inst_list_global,inst);
					return item;
			}
			else{
				result = SYNTAX_ERR;			// neexistuje pravá strana porovnání
				return error;
			}
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
					entry = nonterminal;
					return reduction(stack,n_stack,symbolTable);
				}
			}


		}

		case nonterminal:{
			entry = nonterminal;
			return reduction(stack,n_stack,symbolTable);
		}
		case lc:
		case error:
		case dolar:
		case nula:
		case slesser:{
			result = SYNTAX_ERR;			// neočekávaný znak
			return error;
		}

	
	}

	result = SYNTAX_ERR;
	return error;

}



		
int precedence(tToken *token, symbolTablePtr *symbolTable){
	stack s1;			// zasobnik pro ukladani terminalu a neterminalu
	//sValue asdf;

	tableEntries row;		// symbol na zasobniku (determinál)
	tableEntries col;		// symbol na vstupu

	stackInit(&s1);		// inicializace
	stackInit_N(&s2);

	row = dolar;
	push(&s1, row);

	//conListInit(&con_list);

	do{
		//conListSearch(&con_list,"#_2",&asdf);
		col = getIndex(token, symbolTable);
		//printf("%d",result);
		if(col == error)
			return result;

		//printf("***********************\n");


		switch (precedenceTable[row][col]){

		case B:{
				   	freeStack(&s1);			// pokud je v tabulce prazdno, jedna se o syntaktickou chybu								   	
					freeStack_N(&s2);
					return SYNTAX_ERR;
		}

		case G:{    						// Greater --> redukce
					//printf("---------redukce---------\n");
					//printf("před\t%d %d\n",row, col );
					//printStack(&s1);
					row = reduction(&s1, &s2, symbolTable);
					//printf("po:\t%d %d\n",row, col );
					//printStack(&s1);
					if(row == error){
						//printf("chyba!\n");	
						freeStack(&s1);
						freeStack_N(&s2);
						return result;
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
					   		//printf("po:\t%d %d\n",row, col );<
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
					if (token->state == T_ERR){
						freeStack(&s1);
						freeStack_N(&s2);
						return LEX_ERR;
					}
					break;

		}

		case E:{
				push(&s1,col);
				row = col;
				*token = tGetToken();
				if (token->state == T_ERR){
					freeStack(&s1);
					freeStack_N(&s2);
					return LEX_ERR;
				}
			}
		}
	//printf("\n-----\n\n" );
	//printStack_N(&s2);
	//printf("\n-----\n\n" );
	} while (row != dolar || col != dolar);
	printf("jsme venku! %d\n",result);
	//conListSearch(&con_list,"#_2",&asdf);
	//printf("%d\n",asdf.i );
	//conListPrint(&con_list);
	//instListPrint(&inst_list_global);
	//BTPrint(symbolTable);
	//printf("%p\n", ans );


	freeStack(&s1);
	freeStack_N(&s2);
	return result;
}
