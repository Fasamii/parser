#include <stdio.h>
#include <stdarg.h>

#define CLS "\e[0m"
#define WHI "\e[38;5;255m"
#define NEO "\e[38;5;198m"
#define RED "\e[38;5;196m"
#define GRE "\e[38;5;77m"
#define BLU "\e[38;5;44m"

void logMessage(const int type, const char *structure, ...) {
	va_list args;
	va_start (args, *structure);
	int lastLine = ((int) (structure[0] - '0')) 
		     + ((int) (structure[1] - '0'))
		     - 1;

	int line = 0;
	printf(WHI"┊"CLS"\n");
	switch (type) {
		case 13:
		#define COLOR_A RED
		#define COLOR_B WHI
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; (int) (structure[i] - '0') > j; j++) {
			if (lastLine == 0) {
				printf(WHI"├"COLOR_A);
			} 
			else if (line == 0) {
				printf(COLOR_A"╭");
			} else {
				if (line == lastLine) {
					printf(COLOR_A"╰");
				} else {
					printf(COLOR_A"├");
				}
			}
			switch (i) {
				case 0:
					printf("%s"CLS"\n", va_arg(args, char*));
					break;
				case 1:
					printf(">"COLOR_B"%s"CLS"\n", va_arg(args, char*));
					break;
			}
			line++;
		}
	}
}
