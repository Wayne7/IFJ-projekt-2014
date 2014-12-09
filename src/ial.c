#include "ial.h"
#include "garbage_collector.h"
#include <string.h>

/*
*	Implementace binarniho stromu prevzata z druhe domaci ulohy do predmetu IAL
*/

int BTInsert(symbolTablePtr *root, char *key, symbol s){
	if (*root == NULL){
		symbolTablePtr tmp;

		if ((tmp = gMalloc(sizeof(struct BTree))) == NULL){
			return BT_ERR;
		}

		tmp->key = key;
		tmp->content = s;
		tmp->LPtr = NULL;
		tmp->RPtr = NULL;

		*root = tmp;

		return BT_OK;
	}
	else{
		int cmp = strcmp((*root)->key, key);

		if (cmp < 0){
			return BTInsert(&(*root)->LPtr, key, s);
		}
		if (cmp > 0){
			return BTInsert(&(*root)->RPtr, key, s);
		}
		if (cmp == 0){
			printf("nevim\n");
			return BT_ERR;							// vratim error, protoze polozka jiz v tabulce je
		}
	}

	return BT_OK;
}



symbolTablePtr BTSearch(symbolTablePtr *root, char *key){
	symbolTablePtr tmp;
	tmp = *root;

	if (tmp == NULL){
		return NULL;			
	}

	int cmp;

	cmp = strcmp(tmp->key, key);

	if (cmp == 0){
		return tmp;
	}
	else if (cmp < 0){
		return BTSearch(&(*root)->LPtr, key);
	}
	else{
		return BTSearch(&(*root)->RPtr, key);
	}

	return NULL;
}

void BTInit(symbolTablePtr *root){
	*root = NULL;
}

int length(char *str)
{
	return (strlen(str));         //funkce vraci delku zadaneho retezce
}

char *copy(char* str, int position, int count)
{
	char *copy = gMalloc(sizeof (char));
	int index = 0;
	while (count != 0)
	{
		copy[index] = str[position - 1];
		index++;
		position++;
		count--;
	}
	return copy;
}

void prefix(char* s, int search_size, int *arr){
	//int i = 0;
	int j = arr[0] = -1;
	for (int i = 0; i < search_size; i++, j++){
		while (j > -1 && s[i] != s[j]){
			j = arr[j];
		}

		if (s[i] == s[j]){
			arr[i] = arr[j];
		}
		else{
			arr[i] = j;
		}
	}
}


/*int find(char *s, char *search){        //funkce vyhleda prvni vyskyt podretezce v retezci a vrati jeho pozici
	int s_size = strlen(s);
	int search_size = strlen(search);
	if (search_size > s_size)            //pokud je hledany podretezec vetsi nez retezec vrati chybu
		return -1;
	int SizeOfArray = (search_size + 1);
	int arr[SizeOfArray];
	prefix(search, search_size, &arr[0]);

	for (int k = 0; k<search_size; k++)
	{
		printf("%d|", arr[k]);
	}
	printf("\n");


	int j = 0;
	int i = 0;
	while (j < s_size)
	{
		if (search[i] == s[j])
		{
			if (i == search_size - 1)
			{
				return (j - search_size + 2);
			}
			else
			{
				i++;
				j++;
			}
		}
		else if (arr[i] == -1)
		{
			i = 0;
			j++;
		}
		else i = arr[i];

	}
	return -1;
}


void Merge(char *array, int left, int mid, int right){

	int SizeOfArray = (right - left + 1);
	char tempArray[SizeOfArray];
	int pos = 0, lpos = left, rpos = mid + 1;

	while (lpos <= mid && rpos <= right)
	{
		if (array[lpos] <= array[rpos])
		{
			tempArray[pos++] = array[lpos++];
		}
		else
		{
			tempArray[pos++] = array[rpos++];
		}
	}
	while (lpos <= mid)
		tempArray[pos++] = array[lpos++];
	while (rpos <= right)
		tempArray[pos++] = array[rpos++];

	int iter;
	for (iter = 0; iter < pos; iter++)
	{
		array[iter + left] = tempArray[iter];
	}
	return;
}

void MergeSort(char *array, int left, int right){
	int mid = (left + right) / 2;

	if (left<right)
	{
		MergeSort(array, left, mid);
		MergeSort(array, mid + 1, right);
		Merge(array, left, mid, right);
	}
	return;
}

char* sort(char * s) {
	MergeSort(s, 0, strlen(s) - 1);
	return s;
}*/