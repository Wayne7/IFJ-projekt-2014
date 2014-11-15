#include "parser.h"


int body(tToken *token){
	int result = SYNTAX_OK;


	if (token->state != T_KEYWORD){
		return SYNTAX_ERR;
	}

	if (strcmp(token->content, "begin\0") != 0){
		return SYNTAX_ERR;
	}


	return result;
}


int funcStatement(tToken *token){
	int result = SYNTAX_OK;





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

	return result;
}

int funcVarNext(tToken *token){
	int result = SYNTAX_OK;

	if (token->state != T_IDENTIFICATOR){
		return result;
	}

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state != T_COLON){
		return SYNTAX_ERR;
	}

	result = varType(token);
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



	return result;
}

int funcVarList(tToken *token){
	int result = SYNTAX_OK;

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

	result = varType(token);
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
		result = funcVarNext(token);
		if (result != SYNTAX_OK)
			return result;
	}



	return result;
}

int funcVariables(tToken *token){
	int result = SYNTAX_OK;

	if (token->state == T_KEYWORD){
		if (!strcmp(token->content, "var\0")){
			*token = tGetToken();
			if (token->state == T_ERR){
				return LEX_ERR;
			}
			result = funcVarList(token);
			if (result != SYNTAX_OK)
				return result;
		}
		else{
			return SYNTAX_ERR;
		}
	}
	else{
		return SYNTAX_ERR;
	}

	return result;
}

int paramsNext(tToken *token){
	int result = SYNTAX_OK;

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state == T_RC){
		return result;
	}

	if (token->state != T_SEMICOLON){
		return SYNTAX_ERR;
	}

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	result = params(token);
	if (result != SYNTAX_OK)
		return result;

	return result;
}

int params(tToken *token){

	int result = SYNTAX_OK;

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

	result = varType(token);
	if (result != SYNTAX_OK)
		return result;
	result = paramsNext(token);
	if (result != SYNTAX_OK)
		return result;


	return result;
}


int defFunction(tToken *token){
	int result = SYNTAX_OK;


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

	result = params(token);
	if (result != SYNTAX_OK)
		return result;

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state != T_COLON){
		return SYNTAX_ERR;
	}

	result = varType(token);
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

			*token = tGetToken();
			if (token->state == T_ERR){
				return LEX_ERR;
			}

			if (token->state == T_KEYWORD){
				if (!strcmp(token->content, "function\0")){
					result = defFunction(token);
					if (result != SYNTAX_OK)
						return result;
				}
			}

		}
		else {
			result = funcVariables(token);
			if (result != SYNTAX_OK)
				return result;
		}
	}
	else {
		result = funcVariables(token);
		if (result != SYNTAX_OK)
			return result;
	}
	


	return result;
}

// pravidlo <var_type> -> integer
//			<var_type> -> real
//			<var_type> -> boolean
//			<var_type> -> string
int varType(tToken *token){
	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}

	if (token->state == T_KEYWORD){
		if (!strcmp(token->content, "integer\0")){
			return SYNTAX_OK;
		}
		if (!strcmp(token->content, "real\0")){
			return SYNTAX_OK;
		}
		if (!strcmp(token->content, "boolean\0")){
			return SYNTAX_OK;
		}
		if (!strcmp(token->content, "string\0")){
			return SYNTAX_OK;
		}
	}
	return SYNTAX_ERR;
	
}

int globalListNext(tToken *token){
	int result = SYNTAX_OK;

	if (token->state != T_IDENTIFICATOR){
		return result;
	}

	*token = tGetToken();
	if (token->state == T_ERR){
		return LEX_ERR;
	}
	if (token->state != T_COLON){
		return SYNTAX_ERR;
	}

	if ((result = varType(token)) != SYNTAX_OK){
		return result;
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

	if (token->state == T_IDENTIFICATOR){	// pokud nasleduje dalsi identifikator, volam funkci znova
		result = globalListNext(token);
		if (result != SYNTAX_OK)
			return result;
	}




	return result;
}

// pravidlo <global_list> -> id : <var_type> ; <global_list_next>
int globalList(tToken *token){
	int result = SYNTAX_OK;

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

	if ((result = varType(token)) != SYNTAX_OK){
		return result;
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

	if (token->state == T_IDENTIFICATOR){	// pokud nasleduje dalsi identifikator, volam funkci znova
		result = globalListNext(token);
		if (result != SYNTAX_OK)
			return result;
	}




	return result;
}

//pravidlo <def_global> -> var <global_list>
//		   <def_global> -> eps
int defGlobal(tToken *token){

	int result = SYNTAX_OK;

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
			result = globalList(token);
			if (result != SYNTAX_OK)
				return result;
		}
	}



	return result;
}


//pravidlo <program> -> <def_global> <def_function> <stat_list> <EOF>
int program(tToken *token){

	int result = SYNTAX_OK;

	result = defGlobal(token);
	if (result != SYNTAX_OK)
		return result;

	result = defFunction(token);
	if (result != SYNTAX_OK)
		return result;

	result = body(token);
	if (result != SYNTAX_OK)
		return result;

	return result;
}


int parse(){

	int result = SYNTAX_OK;
	tToken token;
	result = program(&token);

	return result;
}