#include <stdlib.h>
#include <stdio.h>
// local //
#include "../codeAnalysis/interface.h"

int treeAddLevels(ExecTree *parent, int size) {
	if (parent == NULL) { return 1; }
	if (size < 1) { return 3; }
	if (parent->childCount > 0) { return 6; }
	if (parent->nextLevel != NULL) { return 6; }
	parent->nextLevel = (ExecTree**) malloc(size * sizeof(ExecTree*));
	if (parent->nextLevel == NULL) { return 4; }
	for (int i = 0; i < size; i++) {
		ExecTree *child = malloc(sizeof(ExecTree));
		if (child == NULL) { i--; continue; }
		child->nextLevel = NULL;
		child->childCount = 0;
		parent->nextLevel[i] = child;
		parent->childCount++;
	}
	return 0;
}

int treeAppendLevel(ExecTree *parent) {
	if (parent == NULL) { return 1; }
	ExecTree **tempPointer = (ExecTree**) realloc(parent->nextLevel, (parent->childCount + 1) * sizeof(ExecTree*));
	if (tempPointer == NULL) { return 7; }
	parent->nextLevel = tempPointer;
	parent->nextLevel[parent->childCount] = (ExecTree*) malloc(sizeof(ExecTree*));
	ExecTree *child = malloc(sizeof(ExecTree));
	if (child == NULL) { return 4; }
	child->childCount = 0;
	child->content = NULL;
	child->nextLevel = NULL;
	parent->nextLevel[parent->childCount] = child;
	parent->childCount++;
	return 0;
}	

int treePrependLevel(ExecTree *parent) {
	if (parent == NULL) { return 1; }
	ExecTree **tempPointer = (ExecTree**) realloc(parent->nextLevel, (parent->childCount + 1) * sizeof(ExecTree*));
	if (tempPointer == NULL) { return 7; }
	parent->nextLevel = tempPointer;
	for (int i = parent->childCount; i > 0; i--) {
		parent->nextLevel[i] = parent->nextLevel[i - 1];
	}
	ExecTree *child = malloc(sizeof(ExecTree));
	if (child == NULL) { 
		for (int i = (parent->childCount + 1); i > 0; i--) {
			parent->nextLevel[i - 1] = parent->nextLevel[i];
		}
		return 4;
	}
	child->childCount = 0;
	child->content = NULL;
	child->nextLevel = NULL;
	parent->nextLevel[0] = child;
	parent->childCount++;
	return 0;
}

int treeAppendLevelWith(ExecTree *parent, ExecTree *child) {
	if (parent == NULL) { return 1; }
	if (child == NULL) { return 2; }
	if (parent->nextLevel == NULL) {
		parent->nextLevel = (ExecTree**) malloc(sizeof(ExecTree*));
		if (parent->nextLevel == NULL) { return 4; }
	} else {
		ExecTree **tempPointer = (ExecTree**) realloc(parent->nextLevel, (parent->childCount + 1) * sizeof(ExecTree*));
		if (tempPointer == NULL) { return 7; }
		parent->nextLevel = tempPointer;
	}
	parent->nextLevel[parent->childCount] = child;
	parent->childCount++;
	return 0;
}

int treePrependLevelWith(ExecTree *parent, ExecTree *child) {
	if (parent == NULL) { return 1; }
	if (child == NULL) { return 2; }
	if (parent->nextLevel == NULL) {
		parent->nextLevel = (ExecTree**) malloc(sizeof(ExecTree*));
		if (parent->nextLevel == NULL) { return 4; }
	} else {
		ExecTree **tempPointer = (ExecTree**) realloc(parent->nextLevel, (parent->childCount + 1) * sizeof(ExecTree*));
		if (tempPointer == NULL) { return 7; }
		parent->nextLevel = tempPointer;

	}
	for (int i = parent->childCount + 1; i > 0; i--) {
		parent->nextLevel[i] = parent->nextLevel[i - 1];
	}
	parent->nextLevel[0] = child;
	parent->childCount++;
	return 0;
}

int treeCopyToContent(ExecTree *treeNode, char *content) {
	if (treeNode == NULL) { return 1; }
	if (content == NULL) { return 2; }
	int size = 0;
	for (int i = 0; content[i] != '\0'; i++) {
		size++;
	}
	size++;
	if (treeNode->content == NULL) {
		treeNode->content = (char*) malloc(size * sizeof(char));
		if (treeNode->content == NULL) { return 4; }
	} else {
		char *tempPointer = (char*) realloc(treeNode->content, size * sizeof(char));
		if (tempPointer == NULL) { return 7; }
		treeNode->content = tempPointer;

	}
	for (int i = 0; i < size; i++) {
		treeNode->content[i] = content[i];
	}
	return 0;
}

int treeNodeRemoveContent(ExecTree *treeNode) {
	if (treeNode == NULL) { return 1; }
	if (treeNode->content == NULL) { return 5; }
	free(treeNode->content);
	treeNode->content = NULL;
	return 0;
}

int treeRemoveNodeAndChilds(ExecTree *treeNode) {
	if (treeNode == NULL) { return 1; }
	int exitCode = 0;
	if (treeNode->childCount > 0) {
		for (int i = 0; i < treeNode->childCount; i++) {
			// TODO: add logic for ignoring if deeper in tree root is passed
			if (treeNode->nextLevel[i] != NULL) {
				exitCode = treeRemoveNodeAndChilds(treeNode->nextLevel[i]);
				if (exitCode != 0) {
					return exitCode;
				}
			}
			if (treeNode->content != NULL) {
				free(treeNode->content);
				treeNode->content = NULL;
			}
		}
	}
	free(treeNode->nextLevel);
	treeNode->nextLevel = NULL;
	free(treeNode);
	treeNode = NULL;
	printf("\t\e[38;5;3msegAfter\e[0m\n");
	return exitCode;
}

char *treeGetContentPointer(ExecTree *treeNode) {
	if (treeNode == NULL) { return NULL; }
	if (treeNode->content == NULL) { return NULL; }
	return treeNode->content;
}

char *treeCopyContentToPointer(ExecTree *treeNode) {
	if (treeNode == NULL) { return NULL; }
	if (treeNode->content == NULL) { return NULL; }
	int size = 0;
	for (int i = 0; treeNode->content[i] != '\0'; i++) {
		size++;
	}
	char *content = (char*) malloc(size * sizeof(char));
	if (content == NULL) { return NULL; }
	for (int i = 0; i < size; i++) {
		content[i] = treeNode->content[i];
	}
	return content;
}
