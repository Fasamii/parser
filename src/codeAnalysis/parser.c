#include <stdlib.h>
#include <stdio.h>

#include "./interface.h"
#include "./execTree.h"
#include "./lexer.h"

ExecTree *makeExecTree(FILE *file, int bufferSize) {
	ExecTree *execTree = malloc(sizeof(ExecTree));
	Buffer *buffer = malloc(sizeof(Buffer));

	// TODO: try to use array index instea of pointer at interface return
	
	treeAppendLevel(execTree);
	treeAppendLevel(execTree->nextLevel[0]);

	treeAppendLevelWith(execTree->nextLevel[0], execTree);

	// treeRemoveNodeAndChilds(execTree);
	free(buffer);
	return execTree;
}
