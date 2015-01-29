#include "../../src/SSL/SSL.h"
#include "../../src/Faversham_hall/game/puzzle_manager.h"
#include "../../src/Faversham_hall/window_manager.h"
#include <stdio.h>
#include <assert.h>


int main(int argc, char *argv[]) {
	printf("\n Starting Mission Manager  Test ...\n");


	assert(valid_clue(100, 100) == 0);
	start_clue(100, 100);

	printf(" Mission Manager Tests passed...\n");
	return 0;
}
