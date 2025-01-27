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

	Token *token = (Token*) malloc(sizeof(Token));
	while (1) {
	if (getNextToken(file, buffer, token) != 0) { break; }
		if (token->content) {
			printf("├> %s\n", token->content);
		}
	}
	if (token->type == _EOF) {
		printf("├> end of file\n");
	}

	treeRemoveNodeAndChilds(execTree);
	free(buffer);
	return execTree;
}
