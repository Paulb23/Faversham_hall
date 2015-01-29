#include "../../src/SSL/SSL.h"
#include "../../src/Faversham_hall/objects/entity.h"
#include "../../src/Faversham_hall/objects/ai.h"
#include "../../src/Faversham_hall/objects/player.h"
#include "../../src/Faversham_hall/window_manager.h"
#include <stdio.h>
#include <assert.h>


int main(int argc, char *argv[]) {
	printf("\n Starting Entity Test ...\n");

	Entity *entity = malloc(sizeof(entity));
    Player *player = player_create();
	AI *ai = ai_create("chef");

	assert(entity != NULL);
	assert(ai != NULL);
	assert(player != NULL);

	entity_update_frame(entity);
	assert(entity->image.current_frame == 1);

	entity_update_frame(&player->entity);
	assert(player->entity.image.current_frame == 2);

	entity_update_frame(&ai->entity);
	assert(ai->entity.image.current_frame == 2);

	entity_set_pos(entity, 12 ,12);
	assert(entity->pos.x == 12 && entity->pos.y == 12);

	entity_set_pos(&player->entity, 10 ,10);
	assert(player->entity.pos.x == 10 && player->entity.pos.y == 10);

	entity_set_pos(&ai->entity, 10000 ,10000);
	assert(ai->entity.pos.x == 10000 && ai->entity.pos.y == 10000);

	printf(" Entity Tests passed...\n");
	return 0;
}
