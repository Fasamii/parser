#pragma once
#include "./interface.h"

typedef struct Buffer {
	char *data;
	int index;
	int size;
} Buffer;

int getNextToken(FILE *file, Buffer *buffer, Token *token);
