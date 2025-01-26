#pragma once

enum TokenType {
	IDENTIFIER,
	KEYWORD,
	OPERATOR,
	LOGIC,
	DELIMITER,
	LITERAL,
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

ExecTree *makeExecTree(FILE *file, int bufferSize);
int treeGetContent(ExecTree *treeNode, char *toContentPointer);
