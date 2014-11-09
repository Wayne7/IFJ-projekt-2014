#include "parser.h"

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

// pravidlo <global_list> -> id : <var_type> ; <global_list>
//			<global_list> -> eps
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
		return globalList(token);
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
		}
	}



	return result;
}


//pravidlo <program> -> <def_global> <def_function> <stat_list> <EOF>
int program(tToken *token){

	int result = SYNTAX_OK;

	result = defGlobal(token);

	return result;
}


int parse(){

	int result = SYNTAX_OK;
	tToken token;
	result = program(&token);

	return result;
}