#pragma once

enum TokenType {
	_NULL=0,
	_IDENTIFIER=1,
	_KEYWORD=2,
	_OPERATOR=3,
	_LOGIC=4,
	_DELIMITER=5,
	_LITERAL=6,
	_EOF=7,
};

typedef struct Token {
	int type;
	int size;
	char *content;
} Token;

typedef struct ExecTree {
	struct ExecTree **nextLevel;
	int childCount;
	char *content;
} ExecTree;

ExecTree *parseSourceFile(FILE *file, int bufferSize);
int treeGetContent(ExecTree *treeNode, char *toContentPointer);
