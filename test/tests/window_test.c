#include "../../src/SSL/SSL.h"
#include "../../src/Faversham_hall/config.h"
#include "../../src/Faversham_hall/window_manager.h"
#include <stdio.h>
#include <assert.h>


int main(int argc, char *argv[]) {
	printf("\n Starting Window Test ...\n");

	LOG_FILE_PATH = "../../extras/log.txt";

	assert(load_config("../../conf/config.ini") != -1);

	create_window();
	destory_window();

	printf(" Window Test passed...\n");
	return 0;
}
