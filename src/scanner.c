#include "scanner.h"

/*
*	Hruby navrh jak by to mohlo fungovat, parser(zatim volam z mainu) vola scanner a dostava tokeny, ktere se budou ukladat do tabulky
*	Ve finale to bude stejne vypadat uplne jinak :D
*/

tToken token;			// global


void tInitToken(){
	token.content = (char*) malloc(sizeof(char));
	token.content[0] = '\0';
	token.row = 0;				// potreba zavest globalni promennou, ktera bude urcovat na kterem jsme radku!
	token.state = T_START;		// zatim stav tokenu nefunkcni
	token.length = 0;
}

void tExtendToken(int c){
	token.content = realloc(token.content, (char*) (sizeof(char) * (token.length + 2)));
	token.content[token.length] = c;
	token.length++;
	token.content[token.length] = '\0';

}

void tFreeToken(){
	free(token.content);
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

	while (!(done) && (c = getc(file)) != EOF){

		switch (state){

			case T_START:{

									 if (isalpha(c))
										state = T_IDENTIFICATOR;

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
										 state = T_END;
										 break;
									 }

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