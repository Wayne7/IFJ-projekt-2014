#include "scanner.h"
#include "garbage_collector.h"

// osetrit EOF, v podmince cyklu by nemuze, protoze potrebuji nacitat dalsi znak a pokud narazim na EOF => nemuzu dokoncit algoritmus

/*
*	Hruby navrh jak by to mohlo fungovat, parser(zatim volam z mainu) vola scanner a dostava tokeny, ktere se budou ukladat do tabulky
*	Ve finale to bude stejne vypadat uplne jinak :D
*/

tToken token;			// global


void tInitToken(){
	token.content = NULL;
	token.row = 0;				// potreba zavest globalni promennou, ktera bude urcovat na kterem jsme radku!
	token.state = T_START;		// zatim stav tokenu nefunkcni
	token.length = 0;
}

void tExtendToken(int c){
	token.content = (char*) gReAlloc(token.content,(sizeof(char) * (token.length + 2)));
	token.content[token.length] = c;
	token.length++;
	token.content[token.length] = '\0';

}


void tPutCharToStream(int c){		// pokud nactu dalsi znak a jiz nevyhovuje, musim jej "vratit" zpet pro dalsi cteni
	if (!(isspace(c))){
		ungetc(c, file);
	}
}

tToken tGetToken(){

	tState state = T_START;			// stav automatu
	int c;							// promenna, do ktere nacitam znaky
	bool done = false;				// projizdim cyklem dokud neprectu cely token nebo nenarazim na konec souboru

	tInitToken(token);

	while (!(done) && (c = getc(file))){

		switch (state){

			case T_START:{

								 if (isalpha(c))
									state = T_IDENTIFICATOR;

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
								 else if (c == '{'){
									 state = T_COMMENT;
									 break;
								 }
								 else if (isspace(c)){
									 state = T_START;
									 break;
								 }


								 tExtendToken(c);
								 break;

			}

			case T_IDENTIFICATOR:{

								 if (isalpha(c) || isdigit(c) || c == '_'){
									 tExtendToken(c);
									 break;
								 }
								 else{
									 token.state = state;
									 state = T_END;
									 break;
								 }

			}
			case T_COLON:{
							 if (c == '='){
								 state = T_ASSIGN;
								 tExtendToken(c);
							 }
							 else{
								 state = T_END;
							 }
								 break;
			}
			case T_COMMENT:{
							   if (c == '}'){
								   state = T_START;
							   }
							   break;
			}


			// konecne stavy
			case T_ASSIGN:
			case T_SEMICOLON:
			case T_LC:
			case T_RC:{
								 token.state = state;
								 tPutCharToStream(c);
								 state = T_END;
								 break;
								 

			}

			case T_END:{
						   tPutCharToStream(c);
						   done = true;
						   break;
			}
			




		}
	}

	return token;
}