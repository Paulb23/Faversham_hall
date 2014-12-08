#include "../../src/SSL/SSL.h"
#include "../../src/Faversham_hall/config.h"
#include <stdio.h>
#include <assert.h>


int main(int argc, char *argv[]) {
	printf("\n Starting Config Test ...\n");

	LOG_FILE_PATH = "../../extras/log.txt";

	assert(load_config("../../conf/config.ini") != -1);

	assert(strcmp(WINDOW_TITLE,"this is the window title") == 0);
	assert(WINDOW_WIDTH == 800);
	assert(WINDOW_HEIGHT == 600);
	assert(WINDOWED == 1);

	printf(" Config Test passed...\n");
	return 0;
}
