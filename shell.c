#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>								// Needed for POSIX syscalls
#include "shell.h"
#include "utils.h"

int main() {
	main_loop();								// Driver loop for the shell
	return 0;
}