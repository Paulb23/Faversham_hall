#include "../../src/SSL/SSL.h"
#include "../../src/Faversham_hall/state_controller.h"
#include "../../src/Faversham_hall/window_manager.h"
#include <stdio.h>
#include <assert.h>


int main(int argc, char *argv[]) {
	printf("\n Starting State Test ...\n");

	LOG_FILE_PATH = "../../extras/log.txt";
	create_window();

	start_game();

	switch_state(MAIN_MENU);
	assert(game_state == MAIN_MENU);

	switch_state(GAME_STATE);
	assert(game_state == GAME_STATE);

	switch_state(MAIN_MENU);
	assert(game_state == MAIN_MENU);

	switch_state(MAIN_MENU);
	assert(game_state == MAIN_MENU);

	printf(" Window State passed...\n");
	return 0;
}
