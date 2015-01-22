/*-------------------------------------------------------------------------*/
/**
   @file    mission_manager.c
   @author  P. Batty
   @brief   Manages the mission and acts

   This module implements the system to manage and control the different
   scenes and missions in the game.

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "mission_manager.h"
#include "../window_manager.h"

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static const int number_of_rooms = 13;
static const char room_names[13][50] = {"kitchen", "servants_quarters", "bacement_hallway", "parlor", "dining_room", "reception", "entrance", "bathroom, duchtess_beadroom", "kids_room", "library", "study", "hallway"};
static SSL_Hashmap *rooms;

static const int number_of_npc = 11;
static const char npc_names[11][50] = {"butler", "chef", "companion", "detective", "dutchess", "maid", "nanny", "nephew", "servant", "soninlaw", "twins"};
static SSL_Hashmap *npcs;

static int act;
static int mission;


static void lock_room(char *room) {
	SSL_Hashmap_Add(rooms, room, "1");
}

static void unlock_room(char *room) {
	SSL_Hashmap_Add(rooms, room, "0");
}

static void unlock_all_rooms() {
	int i;
	for (i = 0; i < number_of_rooms; i++) {
		SSL_Hashmap_Add(rooms, room_names[i], "0");
	}
}

static void lock_npc(char *npc) {
	SSL_Hashmap_Add(npcs, npc, "1");
}

static void unlock_all_npcs() {
	int i;
	for (i = 0; i < number_of_npc; i++) {
		SSL_Hashmap_Add(rooms, npc_names[i], "0");
	}
}

static void unlock_npc(char *npc) {
	SSL_Hashmap_Add(npcs, npc, "0");
}


static void act_switch(int new_act) {
	switch (new_act) {
		case 0: {
			lock_room("parlor");
			lock_room("dining_room");
			lock_room("reception");
			lock_room("hallway");
		}
		break;
	}

	act = new_act;
	mission = 0;
}


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

void act_init() {
	act = 0;
	mission = 0;

	rooms = SSL_Hashmap_Create();
	unlock_all_rooms();

	npcs = SSL_Hashmap_Create();
	unlock_all_npcs();

	act_switch(0);
}

int is_room_locked(char *room) {
	return SSL_Hashmap_Get_Int(rooms, room);
}

int is_npc_locked(char *npc) {
	return SSL_Hashmap_Get_Int(npcs, npc);
}

void update_act() {
	switch (act) {
		case 0: {
			// update act stuff here
		}
		break;
	}
}

void draw_act() {
 // draw the mission objectvie here
}
