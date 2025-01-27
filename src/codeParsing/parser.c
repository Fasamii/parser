#include <stdlib.h>
#include <stdio.h>

#include "./interface.h"
#include "./execTree.h"
#include "./lexer.h"

ExecTree *parseSourceFile(FILE *file, int bufferSize) {
	ExecTree *execTree = (ExecTree*) malloc(sizeof(ExecTree));
	Buffer *buffer = (Buffer*) malloc(sizeof(Buffer));
	buffer->size = bufferSize;
    	buffer->index = 0;

	printf("┊\n");
	Token *token = (Token*) malloc(sizeof(Token));
	while (1) {
	if (getNextToken(file, buffer, token) != 0) { break; }
		if (token->content) {
			printf("├> %s\n", token->content);
		}
	}

	treeRemoveNodeAndChilds(execTree);
	free(buffer);
	return execTree;
}
