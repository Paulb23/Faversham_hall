#include "../../src/SSL/SSL.h"
#include "../../src/Faversham_hall/game/mission_manager.h"
#include "../../src/Faversham_hall/window_manager.h"
#include <stdio.h>
#include <assert.h>


int main(int argc, char *argv[]) {
	printf("\n Starting Mission Manager  Test ...\n");


	act_init();

	assert(is_room_locked("hallway") == 0);
	assert(get_current_act() == 1);
	assert(get_current_mission() == 0);
	act_set(100);
	mission_set(100);
	assert(get_current_act() == 100);
	assert(get_current_mission() == 100);

	act_clean_up();

	printf(" Mission Manager Tests passed...\n");
	return 0;
}
