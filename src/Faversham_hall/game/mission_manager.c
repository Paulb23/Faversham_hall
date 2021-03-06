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
#include "dialogue_parser.h"
#include "game.h"
#include "../window_manager.h"
#include "../asset_manager.h"

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static const int number_of_rooms = 13;	// total number of room, and room names
static const char room_names[13][50] = {"kitchen", "servants_quarters", "bacement_hallway", "parlor", "dining_room", "reception", "entrance", "bathroom", "duchtess_bedroom", "kids_room", "library", "study", "hallway"};
static SSL_Hashmap *rooms;				// hashmap to store the state of the rooms

static const int number_of_npc = 11;	// total number of npc, and npc names
static const char npc_names[11][50] = {"butler", "chef", "companion", "detective", "dutchess", "maid", "nanny", "nephew", "servant", "soninlaw", "twins"};
static SSL_Hashmap *npcs;				// hashmap to store the npc states

static int act;							// current act
static int mission;						// current mission
static char *clue_found;				// last clue to be found
static Mix_Chunk *act_complete_sfx;


/*----------------------------------
     locks a room
 ----------------------------------*/

static void lock_room(char *room) {
	SSL_Hashmap_Add(rooms, room, "1");
}


/*----------------------------------
     unlocks a room
 ----------------------------------*/

static void unlock_room(char *room) {
	SSL_Hashmap_Add(rooms, room, "0");
}



/*----------------------------------
     unlocks all room
 ----------------------------------*/

static void unlock_all_rooms() {
	int i;
	for (i = 0; i < number_of_rooms; i++) {
		SSL_Hashmap_Add(rooms, room_names[i], "0");
	}
}


/*----------------------------------
     locks a npc
 ----------------------------------*/

static void lock_npc(char *npc) {
	SSL_Hashmap_Add(npcs, npc, "1");
}


/*----------------------------------
     unlocks a npc
 ----------------------------------*/

static void unlock_all_npcs() {
	int i;
	for (i = 0; i < number_of_npc; i++) {
		SSL_Hashmap_Add(npcs, npc_names[i], "0");
	}
}


/*----------------------------------
     unlocks all npc
 ----------------------------------*/

static void unlock_npc(char *npc) {
	SSL_Hashmap_Add(npcs, npc, "0");
}


/*----------------------------------
    switches act, allows for set up
 ----------------------------------*/

static void act_switch(int new_act) {
	unlock_all_rooms();	// unlock everything
	unlock_all_npcs();
	unlock_room("test_map");
	unlock_room("reception_accuse");

	switch (new_act) {	// switch and set up the act
		case 0: {
			lock_room("parlor");
			lock_room("dining_room");
			lock_room("reception");
			lock_room("hallway");
			lock_room("bacement_hallway");
			lock_room("hallway");
		}
		break;
		case 1: {
			lock_room("entrance");
		}
		break;
		case 2: {
			lock_room("entrance");
		}
		break;
		case 3: {
			lock_room("kids_room");
			lock_room("duchtess_bedroom");
		}
		break;
		case 4: {
			lock_room("kids_room");
		}
		break;
		case 5: {
			lock_room("entrance");
		}
		break;
		case 6: {
			lights_out();
		}
		break;
		case 7: {
			lights_on();
		}
		break;
		case 8: {

		}
		break;
		case 9: {
			lock_room("entrance");
		}
		break;
	}

	act = new_act;	// change to the new act
	mission = 0;	// start at mission 0
}


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	inits the mission manager
  @return 	Void

  Inits the mission manager

\-----------------------------------------------------------------------------*/
void act_init() {
	act = 1;						// start at 0, could add possibility to pass in starting act and mission for saves
	mission = 0;

	rooms = SSL_Hashmap_Create();	// create and unlock all the rooms
	unlock_all_rooms();

	npcs = SSL_Hashmap_Create();	// create and unlock all npcs
	unlock_all_npcs();

	act_complete_sfx = Mix_LoadWAV("../extras/resources/audio/sfx/new_mission.wav");

	act_switch(act);				// switch to the stating act
	clue_found = "none";
}


/*!--------------------------------------------------------------------------
  @brief	Cleans up the act
  @return 	Void

  Cleans up the act

\-----------------------------------------------------------------------------*/
void act_clean_up() {
	SSL_Hashmap_Destroy(rooms);
	SSL_Hashmap_Destroy(npcs);
	Mix_FreeChunk(act_complete_sfx);
}


/*!--------------------------------------------------------------------------
  @brief	Checks if a room is locked
  @param	room		Name of the room to check
  @return 	1 on true else 0

  Checks to see if the room is look and returns 1 if locked else 0

\-----------------------------------------------------------------------------*/
int is_room_locked(char *room) {
	return SSL_Hashmap_Get_Int(rooms, room);
}


/*!--------------------------------------------------------------------------
  @brief	Checks if a npc is locked
  @param	npc 		Name of the npc to check
  @return 	1 on true else 0

  Checks if the npc is locked and returns 1 if locked else 0

\-----------------------------------------------------------------------------*/
int is_npc_locked(char *npc) {
	return 0;
}


/*!--------------------------------------------------------------------------
  @brief	Updates the act
  @return 	Void

  Updates the act

\-----------------------------------------------------------------------------*/
void update_act() {
	int prev_mission = mission;

	switch (act) {
		case 0: {
			switch (mission) {
				case (0): {
					if (game_in_dialog()) {
						if (strcmp(game_get_talking_ai(), "butler") == 0) {
							lock_dialog();
								unlock_room("bacement_hallway");
								mission = 1;
						}
					}
				}
				break;
				case (1): {
					if (strcmp(game_get_room(),"bacement_hallway") == 0) {
						act_switch(1);
					}
				}
				break;
			}
		}
		break;
		case 1: {
			switch(mission) {
				case (0): {
					if (strcmp(game_get_room(),"servants_quarters") == 0) {
						mission = 1;
					}
				}
				break;
				case (1): {
					if (strcmp(clue_found,"diary") == 0) {
						start_dialog("assistant", 12);
						set_in_dialog();
						lock_dialog();
						mission++;
					}
				}
				break;
				case (2): {
					if (game_in_dialog() == 0) {
						act_switch(2);
					}
				}
				break;
			}
		}
		break;
		case (2): {
			switch (mission) {
				case(0): {
					if (game_in_dialog()) {
						if (strcmp(game_get_talking_ai(), "chef") == 0) {
							lock_dialog();
							if (strcmp("chef_goes_crazy5", game_get_dialog_node_name()) == 0) {
								act_switch(3);
							}
						}
					}
				}
				break;
			}
			break;
		}
		break;
		case (3): {
			switch (mission) {
				case (0): {
					if (game_in_dialog()) {
						if (strcmp(game_get_talking_ai(), "nephew") == 0 || strcmp(game_get_talking_ai(), "soninlaw") == 0) {
						lock_dialog();
						//	if (strcmp("chef_goes_crazy5", game_get_dialog_node_name()) == 0) { todo: update with real node
							lock_npc(game_get_talking_ai());
						//	}
						}
					}

					if (SSL_Hashmap_Get_Int(npcs, "nephew") && SSL_Hashmap_Get_Int(npcs, "soninlaw")) {
						act_switch(4);
					}
				}
				break;
			}
		}
		break;
		case (4): {
			switch (mission) {
				case (0) : {
					if (strcmp(game_get_room(), "hallway") == 0) {
						lock_room("entrance");
					}

					if (game_in_dialog()) {
						if (strcmp(game_get_talking_ai(), "dutchess") == 0) {
							lock_dialog();
								mission++;
						}
					}
				}
				break;
				case (1): {
					if (strcmp(clue_found,"plumber") == 0) {
						mission++;
					}
				}
				break;
				case (2): {
					if (game_in_dialog()) {
						if (strcmp(game_get_talking_ai(), "dutchess") == 0) {
							lock_dialog();
							act_switch(5);
						}
					}
				}
				break;
			}
		}
		break;
		case (5): {
			switch (mission) {
				case (0) : {
					if (game_in_dialog()) {
						if (strcmp(game_get_talking_ai(), "maid") == 0 || strcmp(game_get_talking_ai(), "twins") == 0) {
							lock_dialog();
							lock_npc(game_get_talking_ai());
						}
					}

					if (SSL_Hashmap_Get_Int(npcs, "maid") && SSL_Hashmap_Get_Int(npcs, "twins")) {
						act_switch(6);
					}
				}
				break;
			}
		}
		break;
		case (6): {
			switch(mission) {
				case (0) : {
					if (game_in_dialog()) {
						if (strcmp(game_get_talking_ai(), "servant") == 0) {
							lock_dialog();
							lights_on();
							mission++;
						}
					}
				}
				break;
				case (1): {
					if (strcmp(game_get_room(), "bacement_hallway") == 0) {
						act_switch(7);
					}
				}
				break;
			}
		}
		break;
		case (7) : {
			switch (mission) {
				case (0): {
					if (game_in_dialog()) {
						lock_dialog();
						lock_npc(game_get_talking_ai());
					}

					int valid = 1;
					int i;
					for (i = 0; i < number_of_npc; i++) {
						if (SSL_Hashmap_Get_Int(npcs, npc_names[i]) == 0) {
							if (strcmp(npc_names[i], "servant") == 0 || strcmp(npc_names[i], "twins") == 0 || strcmp(npc_names[i], "nanny") == 0 || strcmp(npc_names[i], "companion") == 0 || strcmp(npc_names[i], "detective") == 0) {
							} else {
								valid = 0;
								break;
							}
						}
					}
					if (valid) {
						act_switch(8);
					}
				}
				break;
			}
		}
		break;
		case (8) : {
			switch (mission) {
				case (0): {
					if (strcmp(game_get_room(),"reception_accuse") == 0) {
						act_switch(9);
					}
				}
				break;
			}
		}
		break;
		case (9) : {
			switch (mission) {
				case (0): {
					if (game_in_dialog()) {
						if (strcmp(game_get_dialog_node_name(), "accuse") == 0) {
							mission++;
						}
					}
				}
				break;
				case (1): {
					lock_dialog();
					if (strcmp(game_get_dialog_node_name(), "accuse") == 0) {
						start_dialog(game_get_talking_ai(), 10);
					}
					if (strcmp(game_get_dialog_node_name(), "ending2") == 0){
						mission++;
					}
					if (strcmp(game_get_dialog_node_name(), "ending9") == 0){
						mission = 3;
					}
				}
				break;
				case (2): {
					if (game_in_dialog()) {
						if (strcmp(game_get_dialog_node_name(), "ending2") == 0){
							start_dialog(game_get_talking_ai(), 11);
						}
						if (strcmp(game_get_dialog_node_name(), "ending2") == 0){
							game_end();
						}
					} else {
						game_end();
					}
				}
				break;
				case (3): {
					game_end();
				}
			}
		}
		break;
	}

	if (prev_mission != mission) {
		Mix_PlayChannel(-1, act_complete_sfx, 0);
	}
}


/*!--------------------------------------------------------------------------
  @brief	Draws the act
  @return 	Void

  Draws the act

\-----------------------------------------------------------------------------*/
void draw_act() {
	int mission_x = 13;
	int mission_y = 5;

	switch (act) {
		case 0: {
			switch (mission) {
				case (0): {
					SSL_Font_Draw(mission_x, mission_y, 0 ,SDL_FLIP_NONE, "Mission: Talk to the Butler!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
				}
				break;
				case (1): {
					SSL_Font_Draw(mission_x, mission_y, 0 ,SDL_FLIP_NONE, "Mission: Enter the Basement!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
				}
				break;
			}
		}
		break;
		case (1): {
			switch(mission) {
				case (0): {
					SSL_Font_Draw(mission_x, mission_y, 0 ,SDL_FLIP_NONE, "Mission: Enter the servants room!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
				}
				break;
				case (1): {
					SSL_Font_Draw(mission_x, mission_y, 0 ,SDL_FLIP_NONE, "Mission: Find and solve the clue!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
				}
				break;
			}
			break;
		}
		break;
		case(2): {
			switch(mission) {
				case (0): {
					SSL_Font_Draw(mission_x, mission_y, 0 ,SDL_FLIP_NONE, "Mission: Talk to the Chef!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
				}
				break;
			}
		}
		break;
		case(3): {
			switch(mission) {
				case(0): {
					SSL_Font_Draw(mission_x, mission_y, 0 ,SDL_FLIP_NONE, "Mission: Talk to the Nephew and Son in Law!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
				}
				break;
			}
		}
		break;
		case(4): {
			switch(mission) {
				case(0): {
					SSL_Font_Draw(mission_x, mission_y, 0 ,SDL_FLIP_NONE, "Mission: Talk to the Duchess!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
				}
				break;
				case(1): {
					SSL_Font_Draw(mission_x, mission_y, 0 ,SDL_FLIP_NONE, "Mission: Fix the pipes!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
				}
				break;
				case(2): {
					SSL_Font_Draw(mission_x, mission_y, 0 ,SDL_FLIP_NONE, "Mission: Talk to the Duchess!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
				}
				break;
			}
		}
		break;
		case(5): {
			switch(mission) {
				case(0): {
					SSL_Font_Draw(mission_x, mission_y, 0 ,SDL_FLIP_NONE, "Mission: Talk to the Maid and Twins!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
				}
				break;
			}
		}
		break;
		case(6): {
			switch(mission) {
				case (0) : {
					SSL_Font_Draw(mission_x, mission_y, 0 ,SDL_FLIP_NONE, "Mission: Follow the footprints!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
				}
				break;
				case (1) : {
					SSL_Font_Draw(mission_x, mission_y, 0 ,SDL_FLIP_NONE, "Mission: Talk to everyone!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
				}
				break;
			}
		}
		break;
		case(7): {
			switch(mission) {
				case (0) : {
					SSL_Font_Draw(mission_x, mission_y, 0 ,SDL_FLIP_NONE, "Mission: Talk to everyone!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
				}
				break;
			}
		}
		break;
		case(8): {
			switch(mission) {
				case (0) : {
					SSL_Font_Draw(mission_x, mission_y, 0 ,SDL_FLIP_NONE, "Mission: Enter the reception room!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
				}
				break;
			}
		}
		break;
		case (9): {
			switch (mission) {
				case  (0): {
					SSL_Font_Draw(mission_x, mission_y, 0 ,SDL_FLIP_NONE, "Mission: Accuse someone!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
				}
				break;
			}
		}
		break;
	}
}


/*!--------------------------------------------------------------------------
  @brief	Sets the current last clue found
  @return 	Void

  Sets the last clue to be found inside the mission manager

\-----------------------------------------------------------------------------*/
void found_clue(char *clue) {
	clue_found = clue;
}


/*!--------------------------------------------------------------------------
  @brief	Gets the current act
  @return 	current act number

  Gets the current act

\-----------------------------------------------------------------------------*/
int get_current_act() {
	return act;
}


/*!--------------------------------------------------------------------------
  @brief	Gets the current mission
  @return 	current mission number

  Gets the current mission

\-----------------------------------------------------------------------------*/
int get_current_mission() {
	return mission;
}


/*!--------------------------------------------------------------------------
  @brief	Sets the current act
  @param	act		Act to set to
  @return 	Void

  Sets the current act

\-----------------------------------------------------------------------------*/
void act_set(int act) {
	act_switch(act);
}


/*!--------------------------------------------------------------------------
  @brief	Sets the current mission
  @param	mission		mission to set to
  @return 	Void

  Sets the mission

\-----------------------------------------------------------------------------*/
void mission_set(int _mission) {
	mission = _mission;
}
