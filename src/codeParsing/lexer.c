#include <stdlib.h>
#include <stdio.h>
// local //
#include "./interface.h"
#include "./lexer.h"

int printChar(Buffer *buffer) {
	if (buffer->data[buffer->index] != '\0') {
		if ((buffer->data[buffer->index]) == '\n') {
			printf("'\e[38;5;32m\e[0m'");
		} else {
			if (buffer->data[buffer->index] == '\t') {
				printf("'\e[38;5;32m➔\e[0m'");
			} else {
				printf("'\e[38;5;23m%c\e[0m'", buffer->data[buffer->index]);
			}
		}
	}
	return 0;
}

int writeToToken(Token *token, int type, int size, char *content) {
	if (token == NULL) { return 1; }
	if (content == NULL) { return 3; }
	if (size == 0) { while (content[size] != '\0') { size++; }}
	token->size = size;
	token->content = content;
	token->type = type;
	return 0;
}

int readFileToBuffer(FILE *file, Buffer *buffer) {
	if (file == NULL) { return 1; }
	if (buffer == NULL) { return 2; }
	if (buffer->size < 2) { return 3; }
	int readCount = fread(buffer->data, sizeof(char), (buffer->size - 1), file);
	buffer->data[readCount] = '\0';
	buffer->index = 0;
	if (readCount == 0) { return 10; } 
	return 0;
}

int copyBufferDataToBuffer(Buffer *bufferFrom, Buffer *bufferTo) {
	int max = 0;
	if (bufferFrom->index > bufferTo->index) {
		max = bufferFrom->index;
	} else {
		max = bufferTo->index;
	}
	for (int i = 0; i < max; i++) {
		if (i > bufferTo->size) {
			return -1;
		}
		bufferTo->data[i] = bufferFrom->data[i];
	}
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

	Buffer content;
	content.size = buffer->size;
	content.data = (char*) malloc(content.size * sizeof(char));
	content.index = 0;
	
	while (1) {
		printf("entryindex: content-%i buffer-%i\n", content.index, buffer->index);
		
		if (buffer->data == NULL 
		|| (buffer->index - 1) >= buffer->size 
		|| buffer->data[buffer->index] == '\0') {
			if (buffer->data == NULL) {
				buffer->data = (char*) malloc(buffer->size * sizeof(char));
				if (buffer->data == NULL) { return 4; }
			}
			if (readFileToBuffer(file, buffer) == 10) {
				writeToToken(token, _EOF, 0, "\0");
				return 0;
			}
		}

		if ((content.index - 1) >= content.size) {
			content.size = content.size * 2;
			content.data = (char*) realloc(content.data, content.size * sizeof(char));

		}
		if (buffer->data[buffer->index] == ' ') { 
			if (content.index == 0) {
				buffer->index++;
				continue; 
			}
			writeToToken(token, _IDENTIFIER, content.index, content.data);
			break;
		}

		if (buffer->data[buffer->index] == '\n') {
			if (content.index == 0) {
				buffer->index++;
				continue;
			} else {
				writeToToken(token, _IDENTIFIER, content.size, content.data);
				return 0;
			}
		}

		switch (buffer->data[buffer->index]) {
			case ':':
				printf("helre\n");
				if (content.index == 0) {
					writeToToken(token, _OPERATOR, 1, ":");
					buffer->index++;
					return 0;
				} else {
					writeToToken(token, _IDENTIFIER, content.index, content.data);
					return 0;
				}
				break;
			case '=':
				if (content.index == 0) {
					buffer->index++;
					if (buffer->index >= (buffer->size - 1)) {
						buffer->data = (char*) malloc(buffer->size * sizeof(char));
						if (readFileToBuffer(file, buffer) == 10) {
							writeToToken(token, _OPERATOR, 1, "=");
							return 0;
						}
					}
					if (buffer->data[buffer->index] == '=') {
						writeToToken(token, _OPERATOR, 2, "==");
						buffer->index++;
						return 0;
					} else {
						writeToToken(token, _OPERATOR, 1, "=");
						return 0;
					}
				} else {
					writeToToken(token, _IDENTIFIER, content.index, content.data);
					return 0;
				}
				break;
			default:
				content.data[content.index] = buffer->data[buffer->index];
				content.index++;
				buffer->index++;
		}

	}
	buffer->index++;
	return 0;
}
