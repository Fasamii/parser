#include <stdio.h>

#define CLS "\e[0m"
#define WHI "\e[38;5;255m"
#define NEO "\e[38;5;198m"
#define RED "\e[38;5;196m"
#define GRE "\e[38;5;77m"
#define BLU "\e[38;5;44m"

int logError(int errorType) {
	switch (errorType) {
		case 1:
			printf("┊\n");
			printf(RED"╭ERROR : not enough command arguments"CLS"\n");
			printf(RED"╰>"WHI"did you entered source file path"CLS"\n");
			return 1;
			break;
		case 2:
			printf("┊\n");
			printf(RED"╭ERROR : to many command arguments"CLS"\n");
			printf(RED"╰>"WHI"did you use spaces in file names"CLS"\n");
			return 2;  
			break;
		case 3:
			printf("┊\n");
			printf(RED"╭ERROR : cannot find source file"CLS"\n");
			printf(RED"├>"WHI"check path to source file"CLS"\n");
			printf(RED"╰>"WHI"check if your file even exist"CLS"\n");
			return 3;
			break;
		case 4:
			printf("┊\n");
			printf(RED"╭ERROR : malloc error"CLS"\n");
			printf(RED"╰>"WHI"idk is your ram full"CLS"\n");
			return 4;  
			break;
		case 5:
			printf("┊\n");
			printf(RED"╭ERROR : realloc error"CLS"\n");
			printf(RED"├>"WHI"ehh maybe some loop idk to be honest"CLS"\n");
			printf(RED"╰>"WHI"idk is your ram full"CLS"\n");
			return 5;
			break;
		case 6:
			printf("┊\n");
			printf(RED"╭ERROR : parser returns error code"CLS"\n");
			printf(RED"╰>"WHI"some inner functionality of parser broke"CLS"\n");
			return 6;
			break;
		default:
			printf("┊\n");
			printf(RED"╭ERROR : woah :o"CLS"\n");
			printf(RED"├>"NEO"how did you...\n");
			printf(RED"├>"NEO"ahhh this error doesnt even exist\n");
			printf(RED"╰>"NEO"silly you :3"CLS"\n");
			return 5851;
			break;
	}

}

void logErrorLine(int errorType, int line, char *content) {
	switch (errorType) {
		case 1:
			printf("ohmkkkjj");
			break;
	}

}
