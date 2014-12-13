#include "../../src/SSL/SSL.h"
#include "../../src/Faversham_hall/asset_manager.h"
#include <stdio.h>
#include <assert.h>


int main(int argc, char *argv[]) {
	printf("\n Starting Asset Test ...\n");

	LOG_FILE_PATH = "../../extras/log.txt";

	assert(asset_manager_create() == 0);

	int num = -10;
	asset_manager_addOther("name", &num);
	int *num2 = asset_manager_getOther("name");
	assert(*num2 == -10);

	char *str = "helP!";
	asset_manager_addOther("name", str);
	char *str2 = asset_manager_getOther("name");
	assert(strcmp(str2, "helP!") == 0);

	assert(asset_manager_reset() == 0);

	assert(asset_manager_getOther("name") == (void *)-1);

	printf(" Window Asset passed...\n");
	return 0;
}
