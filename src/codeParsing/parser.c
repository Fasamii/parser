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

	Token *tok = getNextToken(file, buffer);
	printf("type:%i/%i\n", tok->type, _EOF);
	while (tok->type != _EOF && tok != NULL) {
		if (tok->content) {
			printf("┊ %s", tok->content);
		}
	}

	treeRemoveNodeAndChilds(execTree);
	free(buffer);
	return execTree;
}
