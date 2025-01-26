#pragma once
#include "./interface.h"

typedef struct Buffer {
	char *data;
	int index;
	int size;
} Buffer;

Token *getNextToken(Buffer *buffer);
