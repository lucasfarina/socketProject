#include "common.h"
#include <math.h>

clock_t start, end;
double cpu_time_used;

void storeInGC(garbageCollector_t* GC, void* store) {
	if (GC->self != NULL) {
		if (GC->next == NULL) {
			garbageCollector_t* newGC = malloc(sizeof(garbageCollector_t));
			newGC->self = store;
			newGC->next = NULL;
			GC->next = newGC;
		}
		else {
			storeInGC(GC->next, store);
		}
	}
	else {
		GC->self = store;
	}
}

void internalFreeFromGC(garbageCollector_t* GC, void* toFree) {
	if (GC->self == toFree) {
		free(GC->self);
		GC->self = NULL;
	}
	else if(GC->next != NULL) {
		internalFreeFromGC(GC->next, toFree);
		if (GC->next->self == NULL && GC->next->next == NULL) {
			free(GC->next);
			GC->next = NULL;
		}
	}
}

void freeFromGC(void* free) {
	internalFreeFromGC(&gc, free);
}

void internalfreeGC(garbageCollector_t* GC) {
	if (GC->next == NULL) {
		free(GC->self);
		GC->self = NULL;
		GC->next = NULL;
	}
	else
	{
		internalfreeGC(GC->next);
		free(GC->next);
		GC->next = NULL;
		free(GC->self);
		GC->self = NULL;
	}
}

void freeGC() {
	internalfreeGC(&gc);
}

void startTime() {
	start = clock();
}

void endTime() {
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time used: %f\n", cpu_time_used);
}

char* getDynamicSizeString(int* size) {
	int packageLength = 10;
	int currentSize = packageLength + 1;
	char* string = malloc(currentSize);
	char next = EOF;
	unsigned int i = 0;
	while ((next = (char)getchar()) != '\n' && next != EOF)
	{
		string[i] = next;
		i++;
		if (i == currentSize) {
			currentSize = i + packageLength;
			char* temp = realloc(string, currentSize);
			if (temp) {
				string = temp;
			}
			else {
				break;
			}
			free(temp);
		}
	}
	*size = i;
	string[i] = '\0';

	storeInGC(&gc, string);

	return string;
}

void getInt(int* answer) {
	scanf_s(" %d", answer);
	int i;
	while (getchar() != '\n') {
		i = 0;
	}
}

int charToInt(char character)
{
	return character - '0';
}

int stringToInt(char * charArray, int size)
{
	int sum = 0;
	for (int i = size-1; i >= 0; i--) {
		int number = charToInt(charArray[i]);
		sum += number * pow(10, (double)(size - 1 - i));
	}
	return sum;
}
