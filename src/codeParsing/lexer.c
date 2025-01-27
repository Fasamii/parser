#include <stdlib.h>
#include <stdio.h>
// local //
#include "./interface.h"
#include "./lexer.h"

int writeToBufferFromFile(char *data, int bufferSize, FILE *file) {
	if (data == NULL) { return 1; }
	if (bufferSize < 1) { return 2; }
	if (file == NULL) { return 3; }
	
	//TODO: change this awful thing
	for (int i = 0; i < bufferSize; i++) {
		data[i] = '\0';
	}

	if (!fgets(data, bufferSize, file)) { return 5; } 

	printf("\n");
	for (int i = 0; i < bufferSize; i++) {
		printf("\e[38;5;33m%c\e[0m", data[i]);
	}
	printf("\n");
	return 0;
}

int getNextToken(FILE *file, Buffer *buffer, Token *token) {
	if (file == NULL) { return 1; }
	if (buffer == NULL) { return 2; }
	if (token == NULL) { return 3; }
	if (buffer->size == 0) { return 5; }

	token->content = NULL;
	token->size = 0;
	token->type = 0;

	if (buffer->data == NULL) {
		buffer->data = (char*) malloc(buffer->size * sizeof(char));
		if (buffer->data == NULL) { return 4; }
		if (writeToBufferFromFile(buffer->data, buffer->size, file) != 0) {
			token->content = (char*) malloc(sizeof(char));
			token->content[0] = '\0';
			token->type = _EOF;
			token->size = 1;
			return 10;
		}
	}

	if ((buffer->index - 1) >= buffer->size || buffer->data[buffer->index] == '\n') {
		printf("<|next line please|>\n");
		if (writeToBufferFromFile(buffer->data, buffer->size, file)) {
			token->content = (char*) malloc(sizeof(char));
			token->content[0] = '\0';
			token->type = _EOF;
			token->size = 1;
			return 10;
		}
	}
	// parser lexer goes brrrr stuff below //

	
	buffer->index++;
	return 0;
}
