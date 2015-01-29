#include "../../src/SSL/SSL.h"
#include "../../src/Faversham_hall/state_controller.h"
#include "../../src/Faversham_hall/window_manager.h"
#include <stdio.h>
#include <assert.h>


int main(int argc, char *argv[]) {
	printf("\n Starting State Test ...\n");

	LOG_FILE_PATH = "../../extras/log.txt";
	create_window();

	switch_state(EXIT);
	assert(game_state == EXIT);

	start_game();

	printf(" Window State passed...\n");
	return 0;
}
