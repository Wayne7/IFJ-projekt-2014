#include "interpret.h"
#include <string.h>

int interpr(tInstList instlist){


	while (1)
	{
		instListSucc(&instlist);
		tInst tmp = instlist.Active->instruction;


		switch (tmp.type)
		{
		case I_STOP:
			return 0;
			break;

		case I_ADD: {
						if (((((symbolTablePtr)tmp.addr1)->content.isDefined) != true) || ((((symbolTablePtr)tmp.addr2)->content.isDefined) != true))
							return SEM_ERR;
						if (((symbolTablePtr)tmp.addr1)->content.type == tInt){
							if (((symbolTablePtr)tmp.addr2)->content.type == tInt)
								((symbolTablePtr)tmp.addr3)->content.value.i = ((symbolTablePtr)tmp.addr1)->content.value.i + ((symbolTablePtr)tmp.addr2)->content.value.i;
							else
								((symbolTablePtr)tmp.addr3)->content.value.r = ((symbolTablePtr)tmp.addr1)->content.value.i + ((symbolTablePtr)tmp.addr2)->content.value.r;
						}
						else if (((symbolTablePtr)tmp.addr1)->content.type == tReal){
							if (((symbolTablePtr)tmp.addr2)->content.type == tInt)
								((symbolTablePtr)tmp.addr3)->content.value.r = ((symbolTablePtr)tmp.addr1)->content.value.r + ((symbolTablePtr)tmp.addr2)->content.value.i;
							else
								((symbolTablePtr)tmp.addr3)->content.value.r = ((symbolTablePtr)tmp.addr1)->content.value.r + ((symbolTablePtr)tmp.addr2)->content.value.r;
						}
						break;
		}

		case I_SUB: {
						if (((((symbolTablePtr)tmp.addr1)->content.isDefined) != true) || ((((symbolTablePtr)tmp.addr2)->content.isDefined) != true))
							return SEM_ERR;
						if (((symbolTablePtr)tmp.addr1)->content.type == tInt){
							if (((symbolTablePtr)tmp.addr2)->content.type == tInt)
								((symbolTablePtr)tmp.addr3)->content.value.i = ((symbolTablePtr)tmp.addr1)->content.value.i - ((symbolTablePtr)tmp.addr2)->content.value.i;
							else
								((symbolTablePtr)tmp.addr3)->content.value.r = ((symbolTablePtr)tmp.addr1)->content.value.i - ((symbolTablePtr)tmp.addr2)->content.value.r;
						}
						else if (((symbolTablePtr)tmp.addr1)->content.type == tReal){
							if (((symbolTablePtr)tmp.addr2)->content.type == tInt)
								((symbolTablePtr)tmp.addr3)->content.value.r = ((symbolTablePtr)tmp.addr1)->content.value.r - ((symbolTablePtr)tmp.addr2)->content.value.i;
							else
								((symbolTablePtr)tmp.addr3)->content.value.r = ((symbolTablePtr)tmp.addr1)->content.value.r - ((symbolTablePtr)tmp.addr2)->content.value.r;
						}
						break;
		}

		case I_MUL: {
						if (((((symbolTablePtr)tmp.addr1)->content.isDefined) != true) || ((((symbolTablePtr)tmp.addr2)->content.isDefined) != true))
							return SEM_ERR;
						if (((symbolTablePtr)tmp.addr1)->content.type == tInt){
							if (((symbolTablePtr)tmp.addr2)->content.type == tInt)
								((symbolTablePtr)tmp.addr3)->content.value.i = ((symbolTablePtr)tmp.addr1)->content.value.i * ((symbolTablePtr)tmp.addr2)->content.value.i;
							else
								((symbolTablePtr)tmp.addr3)->content.value.r = ((symbolTablePtr)tmp.addr1)->content.value.i * ((symbolTablePtr)tmp.addr2)->content.value.r;
						}
						else if (((symbolTablePtr)tmp.addr1)->content.type == tReal){
							if (((symbolTablePtr)tmp.addr2)->content.type == tInt)
								((symbolTablePtr)tmp.addr3)->content.value.r = ((symbolTablePtr)tmp.addr1)->content.value.r * ((symbolTablePtr)tmp.addr2)->content.value.i;
							else
								((symbolTablePtr)tmp.addr3)->content.value.r = ((symbolTablePtr)tmp.addr1)->content.value.r * ((symbolTablePtr)tmp.addr2)->content.value.r;
						}
						break;
		}

		case I_DIV: {
						if (((((symbolTablePtr)tmp.addr1)->content.isDefined) != true) || ((((symbolTablePtr)tmp.addr2)->content.isDefined) != true))
							return SEM_ERR;
						if (((symbolTablePtr)tmp.addr2)->content.value.i == 0)
							return RUN_ERR3;
						if (((symbolTablePtr)tmp.addr1)->content.type == tInt){
							if (((symbolTablePtr)tmp.addr2)->content.type == tInt)
								((symbolTablePtr)tmp.addr3)->content.value.r = ((symbolTablePtr)tmp.addr1)->content.value.i / ((symbolTablePtr)tmp.addr2)->content.value.i;
							else
								((symbolTablePtr)tmp.addr3)->content.value.r = ((symbolTablePtr)tmp.addr1)->content.value.i / ((symbolTablePtr)tmp.addr2)->content.value.r;
						}
						else if (((symbolTablePtr)tmp.addr1)->content.type == tReal){
							if (((symbolTablePtr)tmp.addr2)->content.type == tInt)
								((symbolTablePtr)tmp.addr3)->content.value.r = ((symbolTablePtr)tmp.addr1)->content.value.r / ((symbolTablePtr)tmp.addr2)->content.value.i;
							else
								((symbolTablePtr)tmp.addr3)->content.value.r = ((symbolTablePtr)tmp.addr1)->content.value.r / ((symbolTablePtr)tmp.addr2)->content.value.r;
						}
						break;
		}

		case I_CONC: {
						 if (((((symbolTablePtr)tmp.addr1)->content.isDefined) != true) || ((((symbolTablePtr)tmp.addr2)->content.isDefined) != true))
							 return SEM_ERR;

						 ((symbolTablePtr)tmp.addr3)->content.value.s = strcat(((symbolTablePtr)tmp.addr1)->content.value.s, ((symbolTablePtr)tmp.addr2)->content.value.s);
						 break;
		}


		case I_LESSER: {
						   if (((((symbolTablePtr)tmp.addr1)->content.isDefined) != true) || ((((symbolTablePtr)tmp.addr2)->content.isDefined) != true))
							   return SEM_ERR;
						   if ((((symbolTablePtr)tmp.addr1)->content.type == tString) && (((symbolTablePtr)tmp.addr2)->content.type == tString)){
							   if (strcmp(((symbolTablePtr)tmp.addr1)->content.value.s, ((symbolTablePtr)tmp.addr2)->content.value.s) < 0){
								   ((symbolTablePtr)tmp.addr3)->content.value.b = true;
								   printf("lesser: %d\n", ((symbolTablePtr)tmp.addr3)->content.value.b);
								   break;
							   }
							   else{
								   ((symbolTablePtr)tmp.addr3)->content.value.b = false;
								   break;
							   }
						   }

						   if ((((symbolTablePtr)tmp.addr1)->content.type == tInt) && (((symbolTablePtr)tmp.addr2)->content.type == tInt)){
							   if (((symbolTablePtr)tmp.addr1)->content.value.i < ((symbolTablePtr)tmp.addr2)->content.value.i){
								   ((symbolTablePtr)tmp.addr3)->content.value.b = true;
								   break;
							   }
							   else{
								   ((symbolTablePtr)tmp.addr3)->content.value.b = false;
								   break;
							   }
						   }

						   if ((((symbolTablePtr)tmp.addr1)->content.type == tBool) && (((symbolTablePtr)tmp.addr2)->content.type == tBool)){
							   if (((symbolTablePtr)tmp.addr1)->content.value.r < ((symbolTablePtr)tmp.addr2)->content.value.r){
								   ((symbolTablePtr)tmp.addr3)->content.value.b = true;
								   break;
							   }
							   else{
								   ((symbolTablePtr)tmp.addr3)->content.value.b = false;
								   break;
							   }
						   }

						   if ((((symbolTablePtr)tmp.addr1)->content.type == tReal) && (((symbolTablePtr)tmp.addr2)->content.type == tReal)){
							   if (((symbolTablePtr)tmp.addr1)->content.value.r < ((symbolTablePtr)tmp.addr2)->content.value.r){
								   ((symbolTablePtr)tmp.addr3)->content.value.b = true;
								   break;
							   }
							   else{
								   ((symbolTablePtr)tmp.addr3)->content.value.b = false;
								   break;
							   }
						   }
						   return SEM_ERR2;
						   break;
		}

		case I_GREATER: {
							if (((((symbolTablePtr)tmp.addr1)->content.isDefined) != true) || ((((symbolTablePtr)tmp.addr2)->content.isDefined) != true))
								return SEM_ERR;
							if ((((symbolTablePtr)tmp.addr1)->content.type == tString) && (((symbolTablePtr)tmp.addr2)->content.type == tString)){
								if (strcmp(((symbolTablePtr)tmp.addr1)->content.value.s, ((symbolTablePtr)tmp.addr2)->content.value.s) > 0){
									((symbolTablePtr)tmp.addr3)->content.value.b = true;
									break;
								}
								else{
									((symbolTablePtr)tmp.addr3)->content.value.b = false;
									break;
								}
							}

							if ((((symbolTablePtr)tmp.addr1)->content.type == tInt) && (((symbolTablePtr)tmp.addr2)->content.type == tInt)){
								if (((symbolTablePtr)tmp.addr1)->content.value.i > ((symbolTablePtr)tmp.addr2)->content.value.i){
									((symbolTablePtr)tmp.addr3)->content.value.b = true;
									break;
								}
								else{
									((symbolTablePtr)tmp.addr3)->content.value.b = false;
									break;
								}
							}

							if ((((symbolTablePtr)tmp.addr1)->content.type == tBool) && (((symbolTablePtr)tmp.addr2)->content.type == tBool)){
								if (((symbolTablePtr)tmp.addr1)->content.value.r > ((symbolTablePtr)tmp.addr2)->content.value.r){
									((symbolTablePtr)tmp.addr3)->content.value.b = true;
									break;
								}
								else{
									((symbolTablePtr)tmp.addr3)->content.value.b = false;
									break;
								}
							}

							if ((((symbolTablePtr)tmp.addr1)->content.type == tReal) && (((symbolTablePtr)tmp.addr2)->content.type == tReal)){
								if (((symbolTablePtr)tmp.addr1)->content.value.r > ((symbolTablePtr)tmp.addr2)->content.value.r){
									((symbolTablePtr)tmp.addr3)->content.value.b = true;
									break;
								}
								else{
									((symbolTablePtr)tmp.addr3)->content.value.b = false;
									break;
								}
							}
							return SEM_ERR2;

							break;
		}

		case I_LOE: {
						if (((((symbolTablePtr)tmp.addr1)->content.isDefined) != true) || ((((symbolTablePtr)tmp.addr2)->content.isDefined) != true))
							return SEM_ERR;
						if ((((symbolTablePtr)tmp.addr1)->content.type == tString) && (((symbolTablePtr)tmp.addr2)->content.type == tString)){
							if (strcmp(((symbolTablePtr)tmp.addr1)->content.value.s, ((symbolTablePtr)tmp.addr2)->content.value.s) <= 0){
								((symbolTablePtr)tmp.addr3)->content.value.b = true;
								break;
							}
							else{
								((symbolTablePtr)tmp.addr3)->content.value.b = false;
								break;
							}
						}

						if ((((symbolTablePtr)tmp.addr1)->content.type == tInt) && (((symbolTablePtr)tmp.addr2)->content.type == tInt)){
							if (((symbolTablePtr)tmp.addr1)->content.value.i <= ((symbolTablePtr)tmp.addr2)->content.value.i){
								((symbolTablePtr)tmp.addr3)->content.value.b = true;
								break;
							}
							else{
								((symbolTablePtr)tmp.addr3)->content.value.b = false;
								break;
							}
						}

						if ((((symbolTablePtr)tmp.addr1)->content.type == tBool) && (((symbolTablePtr)tmp.addr2)->content.type == tBool)){
							if (((symbolTablePtr)tmp.addr1)->content.value.r <= ((symbolTablePtr)tmp.addr2)->content.value.r){
								((symbolTablePtr)tmp.addr3)->content.value.b = true;
								break;
							}
							else{
								((symbolTablePtr)tmp.addr3)->content.value.b = false;
								break;
							}
						}

						if ((((symbolTablePtr)tmp.addr1)->content.type == tReal) && (((symbolTablePtr)tmp.addr2)->content.type == tReal)){
							if (((symbolTablePtr)tmp.addr1)->content.value.r <= ((symbolTablePtr)tmp.addr2)->content.value.r){
								((symbolTablePtr)tmp.addr3)->content.value.b = true;
								break;
							}
							else{
								((symbolTablePtr)tmp.addr3)->content.value.b = false;
								break;
							}
						}
						break;
		}

		case I_GOE:{
					   if (((((symbolTablePtr)tmp.addr1)->content.isDefined) != true) || ((((symbolTablePtr)tmp.addr2)->content.isDefined) != true))
						   return SEM_ERR;
					   if ((((symbolTablePtr)tmp.addr1)->content.type == tString) && (((symbolTablePtr)tmp.addr2)->content.type == tString)){
						   if (strcmp(((symbolTablePtr)tmp.addr1)->content.value.s, ((symbolTablePtr)tmp.addr2)->content.value.s) >= 0){
							   ((symbolTablePtr)tmp.addr3)->content.value.b = true;
							   break;
						   }
						   else{
							   ((symbolTablePtr)tmp.addr3)->content.value.b = false;
							   break;
						   }
					   }

					   if ((((symbolTablePtr)tmp.addr1)->content.type == tInt) && (((symbolTablePtr)tmp.addr2)->content.type == tInt)){
						   if (((symbolTablePtr)tmp.addr1)->content.value.i >= ((symbolTablePtr)tmp.addr2)->content.value.i){
							   ((symbolTablePtr)tmp.addr3)->content.value.b = true;
							   break;
						   }
						   else{
							   ((symbolTablePtr)tmp.addr3)->content.value.b = false;
							   break;
						   }
					   }

					   if ((((symbolTablePtr)tmp.addr1)->content.type == tBool) && (((symbolTablePtr)tmp.addr2)->content.type == tBool)){
						   if (((symbolTablePtr)tmp.addr1)->content.value.r >= ((symbolTablePtr)tmp.addr2)->content.value.r){
							   ((symbolTablePtr)tmp.addr3)->content.value.b = true;
							   break;
						   }
						   else{
							   ((symbolTablePtr)tmp.addr3)->content.value.b = false;
							   break;
						   }
					   }

					   if ((((symbolTablePtr)tmp.addr1)->content.type == tReal) && (((symbolTablePtr)tmp.addr2)->content.type == tReal)){
						   if (((symbolTablePtr)tmp.addr1)->content.value.r >= ((symbolTablePtr)tmp.addr2)->content.value.r){
							   ((symbolTablePtr)tmp.addr3)->content.value.b = true;
							   break;
						   }
						   else{
							   ((symbolTablePtr)tmp.addr3)->content.value.b = false;
							   break;
						   }
					   }
					   return SEM_ERR2;
					   break;
		}
		case I_NOTEQUAL:{
							if (((((symbolTablePtr)tmp.addr1)->content.isDefined) != true) || ((((symbolTablePtr)tmp.addr2)->content.isDefined) != true))
								return SEM_ERR;
							if ((((symbolTablePtr)tmp.addr1)->content.type == tString) && (((symbolTablePtr)tmp.addr2)->content.type == tString)){
								if (strcmp(((symbolTablePtr)tmp.addr1)->content.value.s, ((symbolTablePtr)tmp.addr2)->content.value.s) != 0){
									((symbolTablePtr)tmp.addr3)->content.value.b = true;
									break;
								}
								else{
									((symbolTablePtr)tmp.addr3)->content.value.b = false;
									break;
								}
							}

							if ((((symbolTablePtr)tmp.addr1)->content.type == tInt) && (((symbolTablePtr)tmp.addr2)->content.type == tInt)){
								if (((symbolTablePtr)tmp.addr1)->content.value.i != ((symbolTablePtr)tmp.addr2)->content.value.i){
									((symbolTablePtr)tmp.addr3)->content.value.b = true;
									printf("NOTE: %d\n", ((symbolTablePtr)tmp.addr3)->content.value.b);
									break;
								}
								else{
									((symbolTablePtr)tmp.addr3)->content.value.b = false;
									printf("NOTE: %d\n", ((symbolTablePtr)tmp.addr3)->content.value.b);
									break;
								}
							}

							if ((((symbolTablePtr)tmp.addr1)->content.type == tBool) && (((symbolTablePtr)tmp.addr2)->content.type == tBool)){
								if (((symbolTablePtr)tmp.addr1)->content.value.r != ((symbolTablePtr)tmp.addr2)->content.value.r){
									((symbolTablePtr)tmp.addr3)->content.value.b = true;
									break;
								}
								else{
									((symbolTablePtr)tmp.addr3)->content.value.b = false;
									break;
								}
							}

							if ((((symbolTablePtr)tmp.addr1)->content.type == tReal) && (((symbolTablePtr)tmp.addr2)->content.type == tReal)){
								if (((symbolTablePtr)tmp.addr1)->content.value.r != ((symbolTablePtr)tmp.addr2)->content.value.r){
									((symbolTablePtr)tmp.addr3)->content.value.b = true;
									break;
								}
								else{
									((symbolTablePtr)tmp.addr3)->content.value.b = false;
									break;
								}
							}
							return SEM_ERR2;
							break;
		}


		case I_EQUAL:{
						 if (((((symbolTablePtr)tmp.addr1)->content.isDefined) != true) || ((((symbolTablePtr)tmp.addr2)->content.isDefined) != true))
							 return SEM_ERR;
						 if ((((symbolTablePtr)tmp.addr1)->content.type == tString) && (((symbolTablePtr)tmp.addr2)->content.type == tString)){
							 if (strcmp(((symbolTablePtr)tmp.addr1)->content.value.s, ((symbolTablePtr)tmp.addr2)->content.value.s) == 0){
								 ((symbolTablePtr)tmp.addr3)->content.value.b = true;
								 printf("E: %d\n", ((symbolTablePtr)tmp.addr3)->content.value.b);
								 break;
							 }
							 else{
								 ((symbolTablePtr)tmp.addr3)->content.value.b = false;
								 printf("E: %d\n", ((symbolTablePtr)tmp.addr3)->content.value.b);
								 break;
							 }
						 }

						 if ((((symbolTablePtr)tmp.addr1)->content.type == tInt) && (((symbolTablePtr)tmp.addr2)->content.type == tInt)){
							 if (((symbolTablePtr)tmp.addr1)->content.value.i == ((symbolTablePtr)tmp.addr2)->content.value.i){
								 ((symbolTablePtr)tmp.addr3)->content.value.b = true;
								 printf("E: %d\n", ((symbolTablePtr)tmp.addr3)->content.value.b);
								 break;
							 }
							 else{
								 ((symbolTablePtr)tmp.addr3)->content.value.b = false;
								 printf("E: %d\n", ((symbolTablePtr)tmp.addr3)->content.value.b);
								 break;
							 }
						 }

						 if ((((symbolTablePtr)tmp.addr1)->content.type == tBool) && (((symbolTablePtr)tmp.addr2)->content.type == tBool)){
							 if (((symbolTablePtr)tmp.addr1)->content.value.r == ((symbolTablePtr)tmp.addr2)->content.value.r){
								 ((symbolTablePtr)tmp.addr3)->content.value.b = true;
								 break;
							 }
							 else{
								 ((symbolTablePtr)tmp.addr3)->content.value.b = false;
								 break;
							 }
						 }

						 if ((((symbolTablePtr)tmp.addr1)->content.type == tReal) && (((symbolTablePtr)tmp.addr2)->content.type == tReal)){
							 if (((symbolTablePtr)tmp.addr1)->content.value.r == ((symbolTablePtr)tmp.addr2)->content.value.r){
								 ((symbolTablePtr)tmp.addr3)->content.value.b = true;
								 break;
							 }
							 else{
								 ((symbolTablePtr)tmp.addr3)->content.value.b = false;
								 break;
							 }
						 }
						 return SEM_ERR2;
						 break;
		}

		case I_READLN: {
						   if (((symbolTablePtr)tmp.addr3)->content.type == tInt){
							   scanf("%d", &((symbolTablePtr)tmp.addr3)->content.value.i);
							   if (((symbolTablePtr)tmp.addr3)->content.value.i < 0)
								   return RUN_ERR;
							   else
								   ((symbolTablePtr)tmp.addr3)->content.isDefined = true;
							   break;
						   }
						   if (((symbolTablePtr)tmp.addr3)->content.type == tReal){
							   scanf("%lf", &((symbolTablePtr)tmp.addr3)->content.value.r);
							   if (((symbolTablePtr)tmp.addr3)->content.value.r < 0)
								   return RUN_ERR;
							   else
								   ((symbolTablePtr)tmp.addr3)->content.isDefined = true;
							   break;
						   }
						   if (((symbolTablePtr)tmp.addr3)->content.type == tString){
							   ((symbolTablePtr)tmp.addr3)->content.value.s = gMalloc(sizeof (50));
							   scanf("%s", &((symbolTablePtr)tmp.addr3)->content.value.s);
							   if (((symbolTablePtr)tmp.addr3)->content.value.s < 0)
								   return RUN_ERR;
							   else
								   ((symbolTablePtr)tmp.addr3)->content.isDefined = true;
							   break;
						   }
		break;
		}
		case I_ASSIGN: {
						   if ((((symbolTablePtr)tmp.addr1)->content.isDefined) != true) 
							   return RUN_ERR2;
						   if (((symbolTablePtr)tmp.addr1)->content.type == tInt){
							   ((symbolTablePtr)tmp.addr3)->content.value.i = ((symbolTablePtr)tmp.addr1)->content.value.i;
							   ((symbolTablePtr)tmp.addr3)->content.isDefined = true;						   
						   }
						   if (((symbolTablePtr)tmp.addr1)->content.type == tReal){
							   ((symbolTablePtr)tmp.addr3)->content.value.r = ((symbolTablePtr)tmp.addr1)->content.value.r;
							   ((symbolTablePtr)tmp.addr3)->content.isDefined = true;
						   }
						   if (((symbolTablePtr)tmp.addr1)->content.type == tString){
							   ((symbolTablePtr)tmp.addr3)->content.value.s = ((symbolTablePtr)tmp.addr1)->content.value.s;
							   ((symbolTablePtr)tmp.addr3)->content.isDefined = true;
						   }
						   if (((symbolTablePtr)tmp.addr1)->content.type == tBool){
							   ((symbolTablePtr)tmp.addr3)->content.value.b = ((symbolTablePtr)tmp.addr1)->content.value.b;
							   ((symbolTablePtr)tmp.addr3)->content.isDefined = true;
						   }
						   break;

		}
		case I_IF: {
					   if (((symbolTablePtr)tmp.addr1)->content.isDefined == false)
						   return RUN_ERR2;
					   if (((symbolTablePtr)tmp.addr1)->content.value.b == true)
						   break;
					   else{
							    instListSkip(&instlist);
								instListSucc(&instlist);
					   }
						   break;

			}

			case I_ELSE:{
							return INT_ERR;
							break;
			}

			case I_END:{
						   if (instlist.Active->ptr->instruction.type == I_ELSE)
							   instListSkip(&instlist);
						   break;
			}
		default:{
					break;
		}
/*					case I_LENGTH:
					length(char *str);
					break

					case I_SORT:
					sort(char * s);
					break;

					case I_COPY:
					copy(char* str, int position, int count);
					break;

					case I_FIND:
					find(char *s, char *search)
					break;
					*/
			
		}


	}
}
 
