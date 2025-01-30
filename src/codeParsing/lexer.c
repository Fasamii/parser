#include <stdlib.h>
#include <stdio.h>
// local //
#include "./interface.h"
#include "./lexer.h"

int writeToToken(Token *token, int type, int size, char *content) {
	if (token == NULL) { return 1; }
	if (content == NULL) { return 4; }

	if (size == 0) { while (content[size] != '\0') { size++; }}
	token->size = size;

	token->content = (char*) malloc((size + 1) * sizeof(char));
	if (token->content == NULL) { return 21; }

	for (int i = 0; i < size; i++) { token->content[i] = content[i]; }
	token->content[size] = '\0';
	token->type = type;
	return 0;
}

int readFileToBuffer(FILE *file, Buffer *buffer) {
	if (file == NULL) { return 1; }
	if (buffer == NULL) { return 2; }
	if (buffer->size < 2) { return 11; }
	int readCount = fread(buffer->data, sizeof(char), (buffer->size - 1), file);
	buffer->data[readCount] = '\0';
	buffer->index = 0;
	if (readCount == 0) { return -10; } 
	return 0;
}

int makeTokenToDiff(FILE *file, Token *token, Buffer *buffer, char *template) {
	int i = 0;
	for (i = 0; template[i] != '\0'; i++) {
		if (buffer->index >= (buffer->size - 2)) {
			if (readFileToBuffer(file, buffer) == -10) {
				writeToToken(token, _EOF, 1, '\0');
				return -10;
			}
		}

		if (buffer->data[buffer->index] == template[i] && buffer->data[buffer->index] != '\n') {
			buffer->index++;
			continue;
		} else {
			int result = writeToToken(token, _OPERATOR, i, template);
			if (result != 0) { return result; }
			return 0;
		}
	}
	int result = writeToToken(token, _OPERATOR, i, template);
	if (result != 0) { return result; }
	return 0;
}

int makeTokenIfequal(FILE *file, Token *token, Buffer *buffer, char *template) {
	return 0;
}

int getNextToken(FILE *file, Buffer *buffer, Token *token) {
	if (file == NULL) { return 1; }
	if (buffer == NULL) { return 2; }
	if (token == NULL) { return 3; }
	if (buffer->size < 2) { return 11; }

	token->content = NULL;
	token->size = 0;
	token->type = 0;

	Buffer content;
	content.size = buffer->size;
	content.data = (char*) malloc(content.size * sizeof(char));
	content.index = 0;
	
	while (1) {
		//printf("entryindex: content-%i buffer-%i\n", content.index, buffer->index);
		
		if (buffer->data == NULL 
		|| (buffer->index - 1) >= buffer->size 
		|| buffer->data[buffer->index] == '\0') {
			if (buffer->data == NULL) {
				buffer->data = (char*) malloc(buffer->size * sizeof(char));
				if (buffer->data == NULL) { return 4; }
			}
			if (readFileToBuffer(file, buffer) == -10) {
				writeToToken(token, _EOF, 1, "\0");
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
					makeTokenToDiff(file, token, buffer, "==\n");
					return 0;
				} else {
					writeToToken(token, _IDENTIFIER, content.index, content.data);
					return 0;
				}
				break;
			case '-':
				if (content.index == 0) {
					makeTokenToDiff(file, token, buffer, "---\n");
				} else {
					writeToToken(token, _IDENTIFIER, content.index, content.data);
					return 0;
				}
				return 0;
				break;
			case '.':
				if (content.index == 0) {
					writeToToken(token, _OPERATOR, 1, ".");
					buffer->index++;
					return 0;
				} else {
					writeToToken(token, _IDENTIFIER, content.index, content.data);
					return 0;
				}
				break;
			case ',':
				if (content.index == 0) {
					writeToToken(token, _OPERATOR, 1, ",");
					buffer->index++;
					return 0;
				} else {
					writeToToken(token, _IDENTIFIER, content.index, content.data);
					return 0;
				}
			default:
				content.data[content.index] = buffer->data[buffer->index];
				content.index++;
				buffer->index++;
		}
	}
	buffer->index++;
	return 0;
}
