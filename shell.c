#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>								// Needed for POSIX syscalls
#include "shell.h"
#include "utils.h"

void main_loop() {
	char *line;									// Holds command string
	char **args;
	int status = 1;

	do {
		printf("pookie terminal----> ");							// Print the Prompt for this line of the terminal
		line = read_line();
		flag = 0;
		args = tokenize_line(line);
		status = dash_launch(args);
		free(line);
		free(args);
	} while (status);
}

int main() {
	main_loop();								// Driver loop for the shell
	return 0;
}