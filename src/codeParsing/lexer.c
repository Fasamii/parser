#include <stdlib.h>
#include <stdio.h>
// local //
#include "./interface.h"
#include "./lexer.h"

int writeToBufferFromFile(char *data, int bufferSize, FILE *file) {
	if (bufferSize < 1) { return 2; }
	if (file == NULL) { return 3; }
	if (data == NULL) {
		data = (char*) malloc(bufferSize * sizeof(char));
		if (data == NULL) { return 4; }
	}
	if (!fgets(data, bufferSize, file)) {
		return 5;
	}
	return 0;
}

Token *getNextToken(FILE *file, Buffer *buffer) {
	if (file == NULL) { return NULL; }
	if (buffer == NULL) { return NULL; }
	if (buffer->size == 0) { return NULL; }

	Token *token = (Token*) malloc(sizeof(Token));
	if (token == NULL) { return NULL; }
	token->content = NULL;
	token->size = 0;
	token->type = 0;

	if (buffer->data == NULL) {
		buffer->data = (char*) malloc(buffer->size * sizeof(char));
		if (buffer->data == NULL) { return NULL; }
		if (!writeToBufferFromFile(buffer->data, buffer->size, file)) {
			token->content = (char*) malloc(sizeof(char));
			token->content[0] = '\0';
			token->type = _EOF;
			token->size = 1;
			return token;
		}
	}

	if ((buffer->index - 1) >= buffer->size) {
		if (!writeToBufferFromFile(buffer->data, buffer->size, file)) {
			token->content = (char*) malloc(sizeof(char));
			token->content[0] = '\0';
			token->type = _EOF;
			token->size = 1;
			return token;
		}
	}
	
	return NULL;
}
