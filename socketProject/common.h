#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

extern clock_t start, end;
extern double cpu_time_used;

typedef struct garbageCollector {
	void* self;
	struct garbageCollector* next;
} garbageCollector_t;

garbageCollector_t gc;

extern void storeInGC(garbageCollector_t* GC, void* store);

void internalFreeFromGC(garbageCollector_t* GC, void* free);

extern void freeFromGC(void* free);

void internalfreeGC(garbageCollector_t* GC);

extern void freeGC();

extern void startTime();

extern void endTime();

extern char* getDynamicSizeString(int* size);

extern void getInt(int* answer);

extern int charToInt(char character);

extern int stringToInt(char* charArray, int size);
