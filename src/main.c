#include "info.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./error/interface.h"
#include "./codeAnalysis/interface.h"

#define RED "\e[38;5;1m"
#define ORG "\e[38;5;9m"
#define VIO "\e[38;5;5m"
#define BLU "\e[38;5;32m"
#define CLS "\e[0m"

int main(int argc, char *argv[]) {
	printf("╮\n");
	printf(VIO"╭NAME:"CLS""NAME"\n");
	printf(VIO"╰VERSION:"CLS""VERSION"\n");

	int exitMsg = 0;
	// checking cli arguments //
	if (argc < 2) { exitMsg = logError(1); goto EXIT; }
	if (argc > 2) { exitMsg = logError(2); goto EXIT; }
	
	// opening file //
	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		exitMsg = logError(3);
		goto EXIT;
	}

	ExecTree *execTree = makeExecTree(file, 64);
	if (execTree == NULL) {
		exitMsg = logError(6);
		goto EXIT_FILE;
	}

	// end //
	EXIT_FILE:
	fclose(file);
	EXIT:
	printf("╯\n");
	return exitMsg;
}
