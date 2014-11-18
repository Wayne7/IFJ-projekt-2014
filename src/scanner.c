#include "scanner.h"
#include "garbage_collector.h"

void tInitToken(tToken *token){
	token->content = NULL;
	token->row = 0;				// potreba zavest globalni promennou, ktera bude urcovat na kterem jsme radku!
	token->state = T_START;		
	token->length = 0;
}

void tExtendToken(tToken *token, int c){
	token->content = (char*) gReAlloc(token->content,(sizeof(char) * (token->length + 2)));
	token->content[token->length] = c;
	token->content[++token->length] = '\0';

}


void tPutCharToStream(int c){		// pokud nactu dalsi znak a jiz nevyhovuje, musim jej "vratit" zpet pro dalsi cteni
	if (!(isspace(c))){
		ungetc(c, file);
	}
}

const char *KEYWORDS[20] = {		// Klicova slova
	"begin\0", "boolean\0", "do\0", "else\0", "end\0", "false\0", "find\0",
	"forward\0", "function\0", "if\0", "integer\0", "readln\0", "real\0",
	"sort\0", "string\0", "then\0", "true\0", "var\0", "while\0", "write\0"
};

tState checkKeyWord(tToken token){	
	for (int x = 0; x < 20; x++){
		if (!strcmp(KEYWORDS[x], token.content)){
		return T_KEYWORD;
		}
	}
	return T_IDENTIFICATOR;
}

tToken tGetToken(){

	tToken token;
	tState state = T_START;			// stav automatu
	int c;							// promenna, do ktere nacitam znaky
	tInitToken(&token);

	while (1){

		c = getc(file);

		if (c >= 'A' && c <= 'Z')
		c = tolower(c);				// interpret je case insensitive, vsechny znaky prevedu na male

		switch (state){

			case T_START:{

								 if (isalpha(c) || c == '_'){
									state = T_IDENTIFICATOR;
								 }
								 else if (c == ':'){
									 state = T_COLON;
								 }
								 else if (c == ';'){
									 state = T_SEMICOLON;
								 }
								 else if (c == '('){
									 state = T_LC;
								 }
								 else if (c == ')'){
									 state = T_RC;
								 }
								 else if (c == '/'){
									 state = T_DIV;
								 }
								 else if (c == '*'){
									 state = T_MUL;
								 }
								 else if (c == '-'){
									 state = T_MINUS;
								 }
								 else if (c == '+'){
									 state = T_PLUS;
								 }
								 else if (c == ','){
									 state = T_COMMA;
								 }
								 else if (c == '<'){
									 state = T_LESSER;
								 }
								 else if (c == '>'){
									 state = T_GREATER;
								 }
								 else if (c == '.'){
									 state = T_DOT;
								 }
								 else if (isdigit(c)){
									 state = T_INTEGER;
								 }
								 else if (c == '\''){
									 state = T_STRING;
									 break;
								 }
								 else if (c == '{'){
									 state = T_COMMENT;
									 break;
								 }
								 else if (isspace(c)){
									 state = T_START;
									 break;
								 }
								 else if (c == EOF){
									 token.state = T_EOF;	 
									 return token;
								 }
								 else{
									 token.state = T_ERR;
									 return token;
								
								 }


								 tExtendToken(&token, c);
								 break;

			}

			case T_IDENTIFICATOR:{

								 if (isalpha(c) || isdigit(c) || c == '_'){
									 tExtendToken(&token, c);
									 break;
								 }
								 else{
									 token.state = checkKeyWord(token);
									 tPutCharToStream(c);
									 return token;
								 }

			}
			case T_COLON:{
							 if (c == '='){
								 state = T_ASSIGN;
								 tExtendToken(&token, c);
							 }
							 else{
								 token.state = T_COLON;
								 tPutCharToStream(c);
								 return token;
							 }
								 break;
			}

			case T_STRING:{
							  if (c == EOF){
								  token.state = T_ERR;
								  return token;
							  }

							  if (c == '\''){
								  token.state = T_STRING;
								  return token;
							  }
							  else{
								  tExtendToken(&token, c);
							  }
							  break;

			}
			case T_LESSER:{
							  if (c == '='){
								  state = T_LOE;
								  tExtendToken(&token, c);
							  }
							  else if (c == '>'){
								  state = T_NOTEQUAL;
								  tExtendToken(&token, c);
							  }
							  else{
								  token.state = T_LESSER;
								  tPutCharToStream(c);
								  return token;
							  }
							  break;
			}
			case T_GREATER:{
							  if (c == '='){
								  state = T_GOE;
								  tExtendToken(&token, c);
							  }
							  else{
								  token.state = T_GREATER;
								  tPutCharToStream(c);
								  return token;
							  }
							  break;
							  
			}
			case T_INTEGER:{
							   if (isdigit(c)){
								   tExtendToken(&token, c);
								   break;
							   }
							   else if (c == '.'){
								   state = T_REAL;
								   tExtendToken(&token, c);
								   break;
							   }
							   else{
								   token.state = T_INTEGER;
								   tPutCharToStream(c);
								   return token;
							   }
			}
			case T_REAL:{
							if (isdigit(c)){
								tExtendToken(&token, c);
								break;
							}
							else{
								token.state = T_REAL;
								tPutCharToStream(c);
								return token;
							}
			}
			case T_COMMENT:{
							   if (c == '}'){
								   state = T_START;
							   }
							   if (c == EOF){
								   token.state = T_ERR;
								   return token;
							   }
							   break;
			}


			// konecne stavy
			case T_ASSIGN:
			case T_SEMICOLON:
			case T_LC:
			case T_RC:
			case T_DIV:
			case T_MUL:
			case T_MINUS:
			case T_PLUS:
			case T_COMMA:
			case T_NOTEQUAL:
			case T_LOE:
			case T_GOE:
			case T_DOT:{
						  
								 token.state = state;
								 tPutCharToStream(c);
								 return token;
								 

			}



		}
	}
}