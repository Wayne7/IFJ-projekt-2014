#include "garbage_collector.h"

// Potreba osetrit chybove stavy poradne!

gList list;						// Seznam polozek garbage collectoru

void gListInit(){
	list.first = NULL;			// Inicializace seznamu
}

void *gMalloc(int size){		// Alokace pameti a ulozeni polozky do seznamu 
	gItem tmp;

	if ((tmp = (gItem) malloc(sizeof(struct garbageItem))) == NULL){
		return NULL;
	}
	tmp->data = NULL;
	tmp->ptr = NULL;

								// Pokud je seznam prazdny, vlozim prvni prvek
	if (list.first == NULL){
		list.first = tmp;
	}
	else{						// Jinak prvku dam ukazatel na aktualne prvni prvek a posunu ukazatel 
		tmp->ptr = list.first;
		list.first = tmp;
	}

	void *allocated;

	if ((allocated = (void*)malloc(size)) == NULL){
		return NULL;
	}

	tmp->data = allocated;

	return allocated;
	
}

void gFree(){						// Uvolneni alokovane pameti
	
	gItem tmp = NULL;

	while (list.first != NULL){
		tmp = list.first;
		list.first = tmp->ptr;
		free(tmp->data);
		free(tmp);
		printf("lel\n");
	}
}

void *gReAlloc(void *memory, int size){			// Realokace pameti

	void *tmp = NULL;

	if (memory == NULL){
		memory = gMalloc(size);					// Pokud ukazatel nikam neukazuje, alokujeme novou pamet
		return memory;
	}
	else{
		tmp = realloc(memory, size);

		printf("%d\n", memory);

		if (tmp != memory){						// Pokud ukazatel na nove prirazanou pamet je ruzny od puvodniho, musime smazat starou polozku v seznamu a pridat novou
			updateList(tmp, size, memory);
		}
		printf("%d\n", tmp);
			return tmp;
	}

}

void updateList(void *memory, int size, void *memoryToFree){

	cancelPtr(memoryToFree);

	gItem tmp;

	if ((tmp = (gItem) malloc(sizeof(struct garbageItem))) == NULL){
		return; // osetrit chybovy stav
	}

	tmp->data = memory;
	tmp->ptr = NULL;

	// Pokud je seznam prazdny, vlozim prvni prvek
	if (list.first == NULL){
		list.first = tmp;
	}
	else{	// Jinak prvku dam ukazatel na aktualne prvni prvek a posunu ukazatel 
		tmp->ptr = list.first;
		list.first = tmp;
	}
	

}

void cancelPtr(void *memoryToFree){				// Uvolnim polozku v seznamu

	gItem tmp = list.first;
	gItem tmp2;

	while (tmp != NULL){
		if (tmp->ptr != NULL){
			if (tmp->ptr->data == memoryToFree){
				tmp2 = tmp->ptr;
				tmp->ptr = tmp2->ptr;
				tmp2->ptr = NULL;
				tmp2->data = NULL;
				free(tmp2);
				printf("Hello kittyyyy\n");
				return;
			}
			else if ((tmp->ptr == NULL) && (tmp != NULL)){	// pokud je to jediny prvek v seznamu, zrusim seznam a uvolnim prvek
				if (tmp->data == memoryToFree){
					list.first = NULL;
					tmp->ptr = NULL;
					tmp->data = NULL;
					free(tmp);
					printf("Hello kitty\n");
					return;
				}
			}
		tmp = tmp->ptr;
		}
	}

}
