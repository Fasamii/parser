#include <stdlib.h>
#include <stdio.h>

#include "./interface.h"
#include "./execTree.h"
#include "./lexer.h"

void printToken(char *str) {
	printf("\e[38;5;53m├> \e[0m");
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '\t') {
			printf("\e[38;5;5m[tab]\e[0m");
			continue;
		}
		if (str[i] == '\n') {
			printf("\e[38;5;5[\\n]\e[0m");
			continue;
		}
		printf("%c", str[i]);
	}
	printf("\n");
	return;
}

int parseSourceFile(FILE *file, ExecTree *execTree, int bufferSize) {
	if (file == NULL) { return 1; }
	if (execTree == NULL) { return 2; }
	if (bufferSize < 2) { return 11; }

	Buffer *buffer = (Buffer*) malloc(sizeof(Buffer));
	if (buffer == NULL) { return 21; }

	Token *token = (Token*) malloc(sizeof(Token));
	if (token == NULL) { return 21; }

	buffer->size = bufferSize;
    	buffer->index = 0;
	buffer->data = NULL;

	while (1) {
		if (getNextToken(file, buffer, token) != 0) { break; }
		if (token->type == _EOF) {
			break; 
		}
		printToken(token->content);
	}

	treeRemoveNodeAndChilds(execTree);
	free(buffer);
	return 0;
}
