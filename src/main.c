#include "info.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./messages/interface.h"
#include "./codeParsing/interface.h"

#define RED "\e[38;5;1m"
#define ORG "\e[38;5;9m"
#define VIO "\e[38;5;5m"
#define BLU "\e[38;5;32m"
#define CLS "\e[0m"

int main(int argc, char *argv[]) {
	printf("╮\n");
	printf(VIO"╭NAME:"CLS""NAME"\n");
	printf(VIO"╰VERSION:"CLS""VERSION"\n");

	if (argc < 2) { logMessage(13, "11", 
			"ERROR : not enough cli arguments",
			"you should provide path to source file");
		goto EXIT;
	}
	if (argc > 2) { logMessage(13, "11", 
			"ERROR : to many cli arguments", 
			"you should only provide path to source file"); 
		goto EXIT;
	}
	
	// opening file //
	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		logMessage(13, "12",
				"ERROR : cannot open file",
				"check path to file",
				"check if file even exist");
		goto EXIT;
	}

	ExecTree *execTree = (ExecTree*) malloc(sizeof(ExecTree));
	if(parseSourceFile(file, execTree, 64) != 0) {
		goto EXIT_FILE;
	}

	// end //
	EXIT_FILE:
	fclose(file);
	EXIT:
	printf("╯\n");
	return 0;
}
