#pragma once
#include "./interface.h"

typedef struct Buffer {
	char *data;
	int index;
	int size;
} Buffer;

int readFileToBuffer(FILE *file, Buffer *buffer);
int writeToToken(Token *token, int type, int size, char *content);
int getNextToken(FILE *file, Buffer *buffer, Token *token);
