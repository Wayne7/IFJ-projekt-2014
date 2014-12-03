#include "parser.h"

int result;			// globalni promenna pro kontrolu chyb



int body(tToken *token, symbolTablePtr *symbolTable){

	if (token->state != T_KEYWORD){
		return SYNTAX_ERR;
	}

	if (strcmp(token->content, "begin\0") != 0){
		return SYNTAX_ERR;
	}

	/**token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	result = precedence(token);*/
	// ZDE SE ZAVOLA FUNKCE PRO ANALYZU HLAVNIHO TELA PROGRAMU


	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}
	if (token->state != T_KEYWORD){
		return SYNTAX_ERR;
	}

	if (strcmp(token->content, "end\0") != 0){
		return SYNTAX_ERR;
	}

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}
	if (token->state != T_DOT){
		return SYNTAX_ERR;
	}

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state != T_EOF){
		return SYNTAX_ERR;
	}


	return result;
}

int funcStatement(tToken *token, symbolTablePtr *symbolTable){
	if (token->state != T_KEYWORD){
		return SYNTAX_ERR;

	}
	if (strcmp(token->content, "begin\0") != 0){
		return SYNTAX_ERR;

	}

	// ZDE SE ZAVOLA FUNKCE PRO ANALYZU TELA FUNKCE

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state != T_KEYWORD){
		return SYNTAX_ERR;
		
	}
	if (strcmp(token->content, "end\0") != 0){
		return SYNTAX_ERR;

	}

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state != T_SEMICOLON){
		return SYNTAX_ERR;
	}

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}
	if (token->state != T_KEYWORD){
		return SYNTAX_ERR;
	}

	return result;
}

int funcVarList(tToken *token, symbolTablePtr *symbolTable){
	if (token->state != T_IDENTIFICATOR){
		return SYNTAX_ERR;
	}

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state != T_COLON){
		return SYNTAX_ERR;
	}

	symbol tmp; // OPRAVIT
	tmp.key = token->content;
	tmp.isFunction = false;

	result = varType(token, symbolTable, &tmp);
	if (result != SYNTAX_OK)
		return result;

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}
	if (token->state != T_SEMICOLON){
		return SYNTAX_ERR;
	}

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state == T_IDENTIFICATOR){
		result = funcVarList(token, symbolTable);
		if (result != SYNTAX_OK)
			return result;
	}
	else{
		return result;
	}



	return result;
}

int funcVariables(tToken *token, symbolTablePtr *symbolTable){
	if (token->state == T_KEYWORD){
		if (!strcmp(token->content, "var\0")){
			*token = tGetToken();
			if (token->state == T_ERR){
				return LEX_ERR;
			}
			result = funcVarList(token, symbolTable);
			if (result != SYNTAX_OK)
				return result;
		}
		
	}

	return result;
}

int params(tToken *token, symbolTablePtr *symbolTable){
	if (token->state == T_RC){
		return result;
	}

	if (token->state != T_IDENTIFICATOR){
		return SYNTAX_ERR;
	}

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state != T_COLON){
		return SYNTAX_ERR;
	}

	symbol tmp;		///////// !!!! OPRAVIT !!!!!!!!
	tmp.key = token->content;
	tmp.isFunction = false;

	result = varType(token, symbolTable, &tmp);
	if (result != SYNTAX_OK)
		return result;

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state == T_SEMICOLON){
		*token = tGetToken();
		if (token->state == T_ERR){
			return LEX_ERR;
		}
		result = params(token, symbolTable);
		if (result != SYNTAX_OK)
			return result;
	}
	if (token->state == T_RC){
		return result;
	}
	else{
		return SYNTAX_ERR;
	}


	return result;
}

int defFunction(tToken *token, symbolTablePtr *symbolTable){
	if (token->state != T_KEYWORD){
		return result;
	}

	if (strcmp(token->content, "function\0") != 0){
		return result;
	}


	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state != T_IDENTIFICATOR){
		return LEX_ERR;
	}

	symbolTablePtr test = NULL;

	if((test = BTSearch(symbolTable, token->content)) != NULL){
		if (test->content.isDefined){
			return SEM_ERR;
		}
	}

	symbol tmp;
	tmp.key = token->content;
	tmp.isFunction = true;
	tmp.isDefined = false;
	

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state != T_LC){
		return LEX_ERR;
	}

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	result = params(token, symbolTable);
	if (result != SYNTAX_OK)
		return result;

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state != T_COLON){
		return SYNTAX_ERR;
	}

	result = varType(token, symbolTable, &tmp);
	if (result != SYNTAX_OK)
		return result;

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state != T_SEMICOLON){
		return SYNTAX_ERR;
	}


	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state == T_KEYWORD){
		if (!strcmp(token->content, "forward\0")){

			*token = tGetToken();
			if (token->state == T_ERR){
				return LEX_ERR;
			}

			if (token->state != T_SEMICOLON){
				return SYNTAX_ERR;
			}

			if (test == NULL){
				if (BTInsert(symbolTable, tmp.key, tmp) == BT_ERR){  //pokud je deklarace syntakticky spravne, vlozim prvek do tabulky symbolu a zkontroluji zda se tam jiz nenachazi
					return SEM_ERR;
				}
			}
			else{
				return SEM_ERR;										// pokud funkce byla jednou definovana, zahlasim semantickou chybu
			}

			*token = tGetToken();
			if (token->state == T_ERR){
				return LEX_ERR;
			}

			if (token->state == T_KEYWORD){
				if (!strcmp(token->content, "function\0")){
					result = defFunction(token, symbolTable);
					if (result != SYNTAX_OK)
						return result;
				}

			}

		}
		else {
			result = funcVariables(token, symbolTable);
			if (result != SYNTAX_OK)
				return result;

			result = funcStatement(token, symbolTable);
			if (result != SYNTAX_OK)
				return result;

			tmp.isDefined = true;			//funkce byla definovana

			if (test == NULL){
				if (BTInsert(symbolTable, tmp.key, tmp) == BT_ERR){  //pokud je deklarace a definice syntakticky spravne, vlozim prvek do tabulky symbolu a zkontroluji zda se tam jiz nenachazi
					return SEM_ERR;
				}
			}
			else{
				test->content.isDefined = true;						// pokud funkce byla deklarovana, v promenne test mam ulozen odkaz na funkci ktera byla definovana 
			}

			if (token->state == T_KEYWORD){
				if (!strcmp(token->content, "function\0")){
					result = defFunction(token, symbolTable);
					if (result != SYNTAX_OK)
						return result;
				}
			}
		}
	}
	else {
		return SYNTAX_ERR;
	}
	
	return result;
}

// pravidlo <var_type> -> integer
//			<var_type> -> real
//			<var_type> -> boolean
//			<var_type> -> string
int varType(tToken *token, symbolTablePtr *symbolTable, symbol *s){
	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state == T_KEYWORD){
		if (!strcmp(token->content, "integer\0")){
			s->type = tInt;
			return SYNTAX_OK;
		}
		if (!strcmp(token->content, "real\0")){
			s->type = tReal;
			return SYNTAX_OK;
		}
		if (!strcmp(token->content, "boolean\0")){
			s->type = tBool;
			return SYNTAX_OK;
		}
		if (!strcmp(token->content, "string\0")){
			s->type = tString;
			return SYNTAX_OK;
		}
	}
	return SYNTAX_ERR;
	
}

int globalListNext(tToken *token, symbolTablePtr *symbolTable){
	if (token->state != T_IDENTIFICATOR){
		return result;
	}

	symbol tmp;
	tmp.key = token->content;
	tmp.isFunction = false;

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}
	if (token->state != T_COLON){
		return SYNTAX_ERR;
	}

	if ((result = varType(token, symbolTable, &tmp)) != SYNTAX_OK){
		return result;
	}

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state != T_SEMICOLON){
		return SYNTAX_ERR;
	}
	if (BTInsert(symbolTable, tmp.key, tmp) == BT_ERR){  //pokud je deklarace syntakticky spravne, vlozim prvek do tabulky symbolu a zkontroluji zda se tam jiz nenachazi
		return SEM_ERR;
	}

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state == T_IDENTIFICATOR){	// pokud nasleduje dalsi identifikator, volam funkci znova
		result = globalListNext(token, symbolTable);
		if (result != SYNTAX_OK)
			return result;
	}

	return result;
}

// pravidlo <global_list> -> id : <var_type> ; <global_list_next>
int globalList(tToken *token, symbolTablePtr *symbolTable){
	if (token->state != T_IDENTIFICATOR){
		return SYNTAX_ERR;
	}

	symbol tmp;					
	tmp.key = token->content;
	tmp.isFunction = false;

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}
	if (token->state != T_COLON){
		return SYNTAX_ERR;
	}

	if ((result = varType(token, symbolTable, &tmp)) != SYNTAX_OK){
		return result;
	}

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}
	
	if (token->state != T_SEMICOLON){
		return SYNTAX_ERR;
	}
	if (BTInsert(symbolTable, tmp.key, tmp) == BT_ERR){  //pokud je deklarace syntakticky spravne, vlozim prvek do tabulky symbolu a zkontroluji zda se tam jiz nenachazi
		return SEM_ERR;
	}

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state == T_IDENTIFICATOR){	// pokud nasleduje dalsi identifikator, volam funkci znova
		result = globalListNext(token, symbolTable);
		if (result != SYNTAX_OK)
			return result;
	}

	return result;
}

//pravidlo <def_global> -> var <global_list>
//		   <def_global> -> eps
int defGlobal(tToken *token, symbolTablePtr *symbolTable){
	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state == T_KEYWORD){
		if (!strcmp(token->content, "var\0")){
			*token = tGetToken();
			if (token->state == T_ERR){
				return LEX_ERR;
			}
			result = globalList(token, symbolTable);
			if (result != SYNTAX_OK)
				return result;
		}
	}

	return result;
}

//pravidlo <program> -> <def_global> <def_function> <stat_list> <EOF>
int program(tToken *token, symbolTablePtr *symbolTable){
	result = defGlobal(token, symbolTable);
	if (result != SYNTAX_OK)
		return result;

	result = defFunction(token, symbolTable);
	if (result != SYNTAX_OK)
		return result;

	result = body(token, symbolTable);
	if (result != SYNTAX_OK)
		return result;

	return result;
}


int parse(symbolTablePtr *symbolTable){
	result = SYNTAX_OK;
	tToken token;
	result = program(&token, symbolTable);

	return result;
}