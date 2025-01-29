#include <stdlib.h>
#include <stdio.h>

#include "./interface.h"
#include "./execTree.h"
#include "./lexer.h"

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
			printf("end of file\n");
			break; 
		}
		printf("=>\e[38;5;44m%s\e[0m\n", token->content);
	}

	treeRemoveNodeAndChilds(execTree);
	free(buffer);
	return 0;
}
