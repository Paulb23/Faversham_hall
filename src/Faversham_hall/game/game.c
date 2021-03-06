/*-------------------------------------------------------------------------*/
/**
   @file    game.c
   @author  P. Batty
   @brief   Implements a the game loop

   This module implements the game loop
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "game.h"
#include "../config.h"
#include "../state_controller.h"
#include "../window_manager.h"
#include "../objects/entity.h"
#include "../objects/player.h"
#include "../objects/ai.h"
#include "map_manager.h"
#include "mission_manager.h"
#include "puzzle_manager.h"
#include "../asset_manager.h"
#include "dialogue_parser.h"
#include "SDL2/SDL.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static char *current_map_name = "";	/**< Name of the current map we are on*/
static int current_floor;			/**< keeps track of what floor we are on */

static SSL_Tiled_Map *current_map;	/**< Current tmx map we are on */
static SSL_IniFile *map_ini;		/**< Current ini file for the map */

static int world_offset_x;			/**< X offset of the world */
static int world_offset_y;			/**< Y offset of the world */

static Player *player;				/**< The player */
static SSL_List *ai;				/**< The Ai list */

static int in_dialog;				/**< Are we in dialogue */
static int locked_room;				/**< is the room we are tying to load locked */
static int locked_dialog;			/**< can we leave the dialog */
static int in_puzzle;				/**< are we in a puzzle */
static char *puzzle;				/**< name of the puzzle currently solving */

static int end_game = 0;

static SSL_Image *ui_background;	/**< the ui background */
static SSL_Image *pause_background;	/**< the pause background */
static SSL_Image *end_background;	/**< the end background */

static int paused;					/**< are we paused */
static Mix_Music *music;
static Mix_Chunk *load_sfx;


/*----------------------------------
     Saves the game
 ----------------------------------*/

void save_game() {
	SSL_IniFile *save = load_ini("start_map");	// open the ini

	char buf[100];	// buffer for ints

												// set the data
	SSL_IniFile_Set(save, "11", "load", current_map_name);

	itoa(player->entity.pos.x / SSL_Tiled_Get_Tile_Width(current_map), buf, 10);
	SSL_IniFile_Set(save, "11", "startX", buf);

	itoa(player->entity.pos.y / SSL_Tiled_Get_Tile_Height(current_map), buf, 10);
	SSL_IniFile_Set(save, "11", "startY", buf);

	itoa(get_current_act(), buf, 10);
	SSL_IniFile_Set(save, "11", "start_act", buf);

	itoa(get_current_mission(), buf, 10);
	SSL_IniFile_Set(save, "11", "start_mission", buf);

											// save the data
	FILE *file = fopen("../extras/resources/maps/loading/start_map.ini", "wb");
	fprintf(file, ";DO NOT DELETE THIS CONTAINS THE FISRT MAP TO LOAD AND AND THE PLAYERS POSITION \n"
				  ";COULD BE USED FOR SAVES! \n\n"
				  "[00]\n"
				  "load = \"%s\" \n"
				  "floor = %i \n"
				  "startX = %i \n"
				  "startY = %i \n"
				  "start_act = %i \n"
				  "start_mission = %i \n\n\n"
				  "[11]\n"
				  "load = \"%s\" \n"
				  "floor = %i \n"
				  "startX = %i \n"
				  "startY = %i \n"
				  "start_act = %i \n"
				  "start_mission = %i \n\n\n"
				   , SSL_IniFile_GetString(save, "00", "load", "bacement_hallway")
				   , SSL_IniFile_GetInt(save, "00", "floor", 0)
				   , SSL_IniFile_GetInt(save, "00", "startX", 2)
				   , SSL_IniFile_GetInt(save, "00", "startY", 11)
				   , SSL_IniFile_GetInt(save, "00", "start_act", 0)
				   , SSL_IniFile_GetInt(save, "00", "start_mission", 0)
				   , SSL_IniFile_GetString(save, "11", "load", "bacement_hallway")
				   , SSL_IniFile_GetInt(save, "11", "floor", 0)
				   , SSL_IniFile_GetInt(save, "11", "startX", 2)
				   , SSL_IniFile_GetInt(save, "11", "startY", 11)
				   , SSL_IniFile_GetInt(save, "11", "start_act", 0)
				   , SSL_IniFile_GetInt(save, "11", "start_mission", 0)
				   );
    fclose(file);
	SSL_IniFile_Destroy(save);	// free the memory
}


/*----------------------------------
     Loads the level
 ----------------------------------*/

static void load_level(char *map_name) {

	// load music
	if (music) {
		Mix_FreeMusic(music);
	}
	char path[100] = "";
	sprintf(path, "../extras/resources/audio/music/%s.wav", map_name);
	music = Mix_LoadMUS(path);
	Mix_PlayMusic(music, -1);

	if (strcmp(map_name,"reception") == 0 && get_current_act() == 8) {
		map_name = "reception_accuse";
	}

	if (current_map) {
		SSL_Tiled_Map_Destroy(current_map);
	}
	current_map = load_map(map_name); // load the map and ini files
	map_ini = load_ini(map_name);
	current_map_name = map_name;	  // update the map name

	// destory the old list
	if (ai) {
		SSL_List_Destroy(ai);
		ai = NULL;
	}
	ai = SSL_List_Create();			// set up ai
	printf(" ");
	load_ai(current_map, ai);

	if (get_current_act() != 5 && get_current_act() != 6 && get_current_act() != 8) {
		load_servant(current_map, ai);
	}

	if (get_current_act() == 6 && get_current_mission() == 0) {
		SSL_Tiled_Set_Lighting(current_map, SSL_Color_Create(0, 0, 0, 255));
		show_layer(current_map, SSL_Tiled_Get_LayerIndex(current_map, "puzzle"));
	} else {
		load_lights(current_map);		  // set up lighting
		SSL_Tiled_Set_Lighting(current_map, SSL_Color_Create(0, 0, 0, 150));
	}

	if (strcmp(map_name, "bacement_hallway") == 0) {
		current_floor = 0;
	}
	if (strcmp(map_name, "entrance") == 0) {
		current_floor = 1;
	}
	if (strcmp(map_name, "hallway") == 0) {
		current_floor = 2;
	}
}


/*----------------------------------
     Loads the next level
 ----------------------------------*/

static void load_next_level() {
	char pos[50] = "";																		// combine the xy coordinates of the player
	sprintf(pos, "%i%i", player->entity.pos.x / SSL_Tiled_Get_Tile_Width(current_map), player->entity.pos.y / SSL_Tiled_Get_Tile_Height(current_map));
	int start_x = SSL_IniFile_GetInt(map_ini, pos , "startX", 1);							// read the current map ini, for the next map name,
	int start_y = SSL_IniFile_GetInt(map_ini, pos, "startY", 1);							// and starting x, y coordinates

	if (is_room_locked(SSL_IniFile_GetString(map_ini, pos, "load", "test_map"))) {
		locked_room = 1;
		return;
	}
	save_game();
	// play door sound
	if (load_sfx) {
		Mix_FreeChunk(load_sfx);
	}
	char buf[100] = "";
	sprintf(buf, "../extras/resources/audio/sfx/load_room_%i.wav", (rand() % 5) + 1);
	load_sfx = Mix_LoadWAV(buf);
	Mix_PlayChannel(-1, load_sfx, 0);

	load_level(SSL_IniFile_GetString(map_ini, pos, "load", "test_map"));					// load the level

																							// set up the player for the new map
	entity_set_pos((Entity *)&player->entity, start_x * SSL_Tiled_Get_Tile_Width(current_map), start_y * SSL_Tiled_Get_Tile_Height(current_map));
	player->destination_x = start_x * SSL_Tiled_Get_Tile_Width(current_map);
	player->destination_y = start_y * SSL_Tiled_Get_Tile_Height(current_map);
	if (get_current_act() == 6 && get_current_mission() == 0) {
		player->entity.light->range = 4;
	} else {
		player->entity.light->range = 6;
	}
	SSL_Tiled_Add_Light(current_map, player->entity.light);
	in_dialog = 0;
	locked_dialog = 0;
}


/*----------------------------------
     loads the game
 ----------------------------------*/

static void load_game() {

	SSL_IniFile *save = load_ini("start_map");	// open the ini
	current_floor = SSL_IniFile_GetInt(save, "11", "floor", 0);
	int start_x = SSL_IniFile_GetInt(save, "11", "startX", 1);
	int start_y = SSL_IniFile_GetInt(save, "11", "startY", 1);
	int start_act = SSL_IniFile_GetInt(save, "11", "start_act", 1);
	int start_mission = SSL_IniFile_GetInt(save, "11", "start_mission", 1);
										// load the map stored in the start_map ini
	load_level(SSL_IniFile_GetString(save, "11", "load", "test_map"));

	SSL_Tiled_Add_Light(current_map, player->entity.light);
	entity_set_pos((Entity *)&player->entity, start_x * SSL_Tiled_Get_Tile_Width(current_map), start_y * SSL_Tiled_Get_Tile_Height(current_map));

	act_set(start_act);
	mission_set(start_mission);
	paused = 0;
}


/*----------------------------------
     updates animations
 ----------------------------------*/

static void update_animation() {
	entity_update_frame((Entity *)&player->entity);
	int i;
	for (i = 0; i < SSL_List_Size(ai); i++) {
		AI *character = (AI *)SSL_List_Get(ai, i);
		entity_update_frame((Entity *)&character->entity);
	}
}


/*----------------------------------
     updates camrea
 ----------------------------------*/
static void update_camrea() {
	world_offset_x = -((player->entity.pos.x) - (WINDOW_RES_WIDTH / 2));
	world_offset_y = -((player->entity.pos.y) - (WINDOW_RES_HEIGHT / 2));
}


/*----------------------------------
     updates player
 ----------------------------------*/
static void update_player() {
	if (locked_dialog == 0) {
		player_move(player,current_map);
	}
}


/*----------------------------------
     updates player status
 ----------------------------------*/
static void update_player_status() {
	if (player->moving) {
		if (locked_dialog == 0) {
			in_dialog = 0;
		}
		locked_room = 0;
	}
}

/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	initialises the game
  @param	load	1 to load 0 to not load.
  @return 	Voids

  Starts the game.

\-----------------------------------------------------------------------------*/
void game_init(int load) {
	dialog_init();	// set up the dialog
	current_floor = 0;
	end_game = 0;

	map_ini = load_ini("start_map");	// get the start_map ini and read it
	current_floor = SSL_IniFile_GetInt(map_ini, "00", "floor", 0);
	int start_x = SSL_IniFile_GetInt(map_ini, "00", "startX", 1);
	int start_y = SSL_IniFile_GetInt(map_ini, "00", "startY", 1);
	int start_act = SSL_IniFile_GetInt(map_ini, "00", "start_act", 1);
	int start_mission = SSL_IniFile_GetInt(map_ini, "00", "start_mission", 1);
											// load the map stored in the start_map ini
	load_level(SSL_IniFile_GetString(map_ini, "00", "load", "test_map"));

	player = player_create();			// create and load the player
	SSL_Tiled_Add_Light(current_map, player->entity.light);
	entity_set_pos((Entity *)&player->entity, start_x * SSL_Tiled_Get_Tile_Width(current_map), start_y * SSL_Tiled_Get_Tile_Height(current_map));

	// set up initial variable states
	world_offset_x = 0;
	world_offset_y = 0;
	locked_room = 0;
	locked_dialog = 0;
	paused = 0;
	in_puzzle = 0;

	// load the ui
	ui_background = SSL_Image_Load("../extras/resources/gui/game/ui.png", WINDOW_RES_WIDTH, WINDOW_RES_HEIGHT, game_window);
	pause_background = SSL_Image_Load("../extras/resources/gui/game/pause.png", WINDOW_RES_WIDTH, WINDOW_RES_HEIGHT, game_window);
	end_background = SSL_Image_Load("../extras/resources/gui/game/end.png", WINDOW_RES_WIDTH, WINDOW_RES_HEIGHT, game_window);

	// set up the mission counter
	act_init();
	act_set(start_act);
	mission_set(start_mission);

	if (load) {
		load_game();
	}
}


/*!--------------------------------------------------------------------------
  @brief	Cleans up the game
  @param	new_state		The state to change to
  @return 	Void

  Cleans up the game

\-----------------------------------------------------------------------------*/
void game_clean_up(Game_States new_state) {
	SSL_IniFile_Destroy(map_ini);
	player_destroy(player);

	int i;
	for (i = 0; i < SSL_List_Size(ai); i++) {
		AI *character = (AI *)SSL_List_Get(ai, i);
		ai_destroy(character);
	}

	SSL_Image_Destroy(ui_background);
	SSL_Image_Destroy(pause_background);

	dialog_clean_up();
	act_clean_up();
}


/*!--------------------------------------------------------------------------
  @brief	Logic for the game
  @param	delta		Delta time
  @param	uptime		Uptime
  @return 	Void

  Game logic

\-----------------------------------------------------------------------------*/
void game_ticks(double delta, int uptime) {

	// update animations
	update_animation();

	if (end_game == 0) {
		// if we are not paused
		if (!paused) {
			if (!in_puzzle) {
				update_player();
				update_player_status();

				update_camrea();
				update_act();
			} else {
				puzzle_update(get_current_act(), get_current_mission());
			}
		} else {
			// psued code here
		}
	} else {

	}

	// set background draw color
	SDL_SetRenderDrawColor(game_window->renderer, 0, 0, 0, 255);
}


/*!--------------------------------------------------------------------------
  @brief	Event handler
  @param	event		the event to handle
  @param	uptime		Uptime
  @return 	Void

  Event handler

\-----------------------------------------------------------------------------*/
void game_event_handle(SDL_Event event, int uptime) {

	if (end_game == 0) {
		// if we are not paused
		if (!paused) {

			if (in_dialog) {
				in_dialog = update_dialog(event);
			} else if (in_puzzle) {
				in_puzzle = puzzle_update_events(event, get_current_act(), get_current_mission());
				if (in_puzzle == 0) {
					puzzle_clean_up(get_current_act(), get_current_mission());
					found_clue(puzzle);
				}
			} else {

				/* check for loading and if so
				 * load the map and set up the player
				 */
				if(player_check_load(event, player, current_map) && !player->moving) {
					load_next_level();
				}

				/* check for character interaction and if so
				 * start the conversation
				 */
				if(player_character_interaction_check(event, player, current_map)) {
					if (get_current_act() != 6 && get_current_act() != 8 && strcmp("servants_quarters", current_map_name) == 0) {
					} else {
						start_dialog(get_closest_ai_name(player, ai), get_current_act());
						in_dialog = 1;
					}
				}

				/* check for clue interaction and if so
				 * start the puzzle
				 */
				if (player_clue_interaction_check(event, player, current_map) && valid_clue(get_current_act(), get_current_mission())) {
					start_clue(get_current_act(), get_current_mission());
				}

				/* check if the player want to pause
				 * and if so pause
				 */
				if (SSL_Keybord_Keyname_Pressed(PAUSE_KEY, event)) {
					paused = 1;
				}

				// unlock the dialog when it has ended
				unlock_dialog();
			}
		} else {
			// paused code heere

			/* check if the player want to unpause
			 * and if so unpause
			 */
			if (SSL_Keybord_Keyname_Pressed(PAUSE_KEY, event) || SSL_Keybord_Keyname_Pressed("_1", event)) {
				paused = 0;
			}

			/* check if the player want to save
			 * and if so save
			 */
			if (SSL_Keybord_Keyname_Pressed("_2", event)) {
				save_game();
			}

			/* check if the player want to load
			 * and if so load
			 */
			if (SSL_Keybord_Keyname_Pressed("_3", event)) {
				load_game();
			}

			/* check if the player wants instructions
			 * and if so show them
			 */
			if (SSL_Keybord_Keyname_Pressed("_4", event)) {
				switch_state(INSTRUCTIONS_STATE);
			}

			/* check if the player want to go to the main menu
			 * and if so go to the main menu
			 */
			if (SSL_Keybord_Keyname_Pressed("_5", event)) {
				switch_state(MAIN_MENU);
			}

			/** if the user want to exit
			 * exit the game
			 */
			if (SSL_Keybord_Keyname_Pressed("_6", event)) {
				switch_state(EXIT);
			}
		}
	} else {

		if (SSL_Keybord_Keyname_Pressed("_1", event)) {
			switch_state(CREDIT_STATE);
		}
	}


	if (SSL_Keybord_Keyname_Pressed(MUTE_KEY, event)) {
		if (MUTE == 0) {
			Mix_VolumeMusic(0);
			Mix_Volume(-1, 0);
			MUTE = 1;
		} else {
			Mix_VolumeMusic(MUSIC_VOL);
			Mix_Volume(-1, SFX_VOL);
			MUTE = 0;
		}
	}

}


/*!--------------------------------------------------------------------------
  @brief	Renders the game
  @return 	Void

  Renders the game.

\-----------------------------------------------------------------------------*/
void game_render() {
	// set background draw color
	SDL_SetRenderDrawColor(game_window->renderer, 0, 0, 0, 255);

	if (!in_puzzle) {
		// draw the world
		SSL_Tiled_Draw_Map(current_map, world_offset_x, world_offset_y, game_window);
		SSL_Tiled_Draw_Lights(current_map, world_offset_x, world_offset_y, game_window, raytrace);

		// draw the player
		SSL_Image_Draw(player->entity.image.image, player->entity.pos.x + world_offset_x, player->entity.pos.y + world_offset_y, 0, player->entity.image.current_frame + (player->entity.image.max_frames * player->entity.image.current_row), 0, game_window);

		// draw the ai
		int i;
		for (i = 0; i < SSL_List_Size(ai); i++) {
			AI *character = (AI *)SSL_List_Get(ai, i);
			SSL_Image_Draw(character->entity.image.image, character->entity.pos.x + world_offset_x, character->entity.pos.y + world_offset_y, 0, character->entity.image.current_frame + (character->entity.image.max_frames * character->entity.image.current_row), 0, game_window);
		}
	}
	//if we are in dialog draw it
	if (in_dialog) {
		if (end_game == 0) {
			render_dialog();
		}
	} else if (in_puzzle) {
		puzzle_render(get_current_act(), get_current_mission());
	} else {

		// draw the ui
		SSL_Image_Draw(ui_background, 0, 0, 0, 1, SDL_FLIP_NONE, game_window);

		// else check and draw info about available interactions
		int layer = SSL_Tiled_Get_LayerIndex(current_map, "other");					// get the loading tile layer

		int info_x = 10;
		int info_y = 20;

		if (SSL_Tiled_Get_TileId(current_map, entity_get_tile_x((Entity *)&player->entity, current_map), entity_get_tile_y((Entity *)&player->entity, current_map), layer) == 1 && !locked_room) {
			SSL_Font_Draw(info_x, info_y, 0 ,SDL_FLIP_NONE, "Press E to load", (SSL_Font *)asset_manager_getFont("test_font"), SSL_Color_Create(255,255,255,0), game_window);
		}
		if (SSL_Tiled_Get_TileId(current_map, entity_get_tile_x((Entity *)&player->entity, current_map), entity_get_tile_y((Entity *)&player->entity, current_map), layer) == 4) {
			if (get_current_act() != 6 && get_current_act() != 8 && strcmp("servants_quarters", current_map_name) == 0) {
			} else {
				SSL_Font_Draw(info_x, info_y, 0 ,SDL_FLIP_NONE, "Press E to Talk", (SSL_Font *)asset_manager_getFont("test_font"), SSL_Color_Create(255,255,255,0), game_window);
			}
		}
		if (valid_clue(get_current_act(), get_current_mission()) && SSL_Tiled_Get_TileId(current_map, entity_get_tile_x((Entity *)&player->entity, current_map), entity_get_tile_y((Entity *)&player->entity, current_map), layer) == 3) {
			SSL_Font_Draw(info_x, info_y, 0 ,SDL_FLIP_NONE, "Press E to collect", (SSL_Font *)asset_manager_getFont("test_font"), SSL_Color_Create(255,255,255,0), game_window);
		}

		// let them know the room is locked
		if (locked_room) {
			SSL_Font_Draw(info_x, info_y, 0 ,SDL_FLIP_NONE, "Room Locked!", (SSL_Font *)asset_manager_getFont("test_font"), SSL_Color_Create(255,255,255,0), game_window);
		}

		// draw the mission info
		draw_act();
	}

	if (paused) {
		SSL_Image_Draw(pause_background, 0, 0, 0, 1, SDL_FLIP_NONE, game_window);
		SSL_Font_Draw(118, 20, 0 ,SDL_FLIP_NONE, "PAUSED!", (SSL_Font *)asset_manager_getFont("ui_title_font"), SSL_Color_Create(255,255,255,0), game_window);

		SSL_Font_Draw(118, 50, 0 ,SDL_FLIP_NONE, "1. Continue", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
		SSL_Font_Draw(118, 70, 0 ,SDL_FLIP_NONE, "2. Save", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
		SSL_Font_Draw(118, 90, 0 ,SDL_FLIP_NONE, "3. Load", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
		SSL_Font_Draw(118, 110, 0 ,SDL_FLIP_NONE, "4. Instructions", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
		SSL_Font_Draw(118, 130, 0 ,SDL_FLIP_NONE, "5. Main Menu", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
		SSL_Font_Draw(118, 150, 0 ,SDL_FLIP_NONE, "6. Exit", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
	}

	if (end_game > 0) {
		SSL_Image_Draw(end_background, 0, 0, 0, 1, SDL_FLIP_NONE, game_window);
		if (end_game == 2) {
			SSL_Font_Draw(118, 70, 0 ,SDL_FLIP_NONE, "You Lose!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
		} else {
			SSL_Font_Draw(118, 70, 0 ,SDL_FLIP_NONE, "You Win!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
		}
		SSL_Font_Draw(155, 145, 0 ,SDL_FLIP_NONE, "1. Continue", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
	}
}


/*!--------------------------------------------------------------------------
  @brief	Ends the game
  @return 	Void

  Ends the game

\-----------------------------------------------------------------------------*/
void game_end() {
	in_dialog = 0;
	if (strcmp(get_closest_ai_name(player, ai), "dutchess") == 0) {
		end_game = 1;
	} else {
		end_game = 2;
	}
}


/*!--------------------------------------------------------------------------
  @brief	Sets the player in the dialog
  @return 	Void

  Sets the player in the dialog

\-----------------------------------------------------------------------------*/
void set_in_dialog() {
	in_dialog = 1;
}


/*!--------------------------------------------------------------------------
  @brief	Gets weatherer are in dialog
  @return 	1 on true else 0

  Gets weatherer are in dialog, returns 1 on true else 0

\-----------------------------------------------------------------------------*/
int game_in_dialog() {
	return in_dialog;
}


/*!--------------------------------------------------------------------------
  @brief	Gets ai name
  @return 	name of the ai, else null

  Gets the name of the ai we are talking to

\-----------------------------------------------------------------------------*/
char *game_get_talking_ai() {
	if (in_dialog) {
		return get_closest_ai_name(player, ai);
	} else {
		return NULL;
	}
}


/*!--------------------------------------------------------------------------
  @brief	Gets dialog node name
  @return 	name of the dialog node else  null

  Gets the name of the current dialog node in conversation else null

\-----------------------------------------------------------------------------*/
char *game_get_dialog_node_name() {
	if (in_dialog) {
		return get_node_name();
	} else {
		return NULL;
	}
}


/*!--------------------------------------------------------------------------
  @brief	Gets room currently in
  @return 	name of the room the player is in

  Gets the name of the room the player is currently in

\-----------------------------------------------------------------------------*/
char *game_get_room() {
	return current_map_name;
}


/*!--------------------------------------------------------------------------
  @brief	Locks the dialog
  @return 	Void

  Stops the player from the leaving the dialog

\-----------------------------------------------------------------------------*/
void lock_dialog() {
	locked_dialog = 1;
}


/*!--------------------------------------------------------------------------
  @brief	Unlocks the dialog
  @return 	Void

  Allows the player from the leaving the dialog

\-----------------------------------------------------------------------------*/
void unlock_dialog() {
	locked_dialog = 0;
}


/*!--------------------------------------------------------------------------
  @brief	Starts a puzzle sequence
  @param	puzzle_name		name of the puzzle to pass to the mission manager
  @return 	Void

  Starts a puzzle sequence.

\-----------------------------------------------------------------------------*/
void start_puzzle(char *puzzle_name) {
	in_puzzle = 1;
	puzzle = puzzle_name;
	puzzle_init(get_current_act(), get_current_mission());
}


/*!--------------------------------------------------------------------------
  @brief	Reloads the map for lights out
  @return 	Void

  Reloads the map for lights out

\-----------------------------------------------------------------------------*/
void lights_out() {
	player->entity.light->range = 4;
	SSL_Tiled_Set_Lighting(current_map, SSL_Color_Create(0, 0, 0, 255));
	show_layer(current_map, SSL_Tiled_Get_LayerIndex(current_map, "puzzle"));

	int i;
	for (i = 0; i < SSL_List_Size(ai); i++) {
		AI *character = (AI *)SSL_List_Get(ai, i);
		character->entity.light->range = 2;
	}
}


/*!--------------------------------------------------------------------------
  @brief	Reloads the map for lights out
  @return 	Void

  Reloads the map for lights out

\-----------------------------------------------------------------------------*/
void lights_on() {
	player->entity.light->range = 4;
	SSL_Tiled_Set_Lighting(current_map, SSL_Color_Create(0, 0, 0, 150));
	hide_layer(current_map, SSL_Tiled_Get_LayerIndex(current_map, "puzzle"));

	int i;
	for (i = 0; i < SSL_List_Size(ai); i++) {
		AI *character = (AI *)SSL_List_Get(ai, i);
		character->entity.light->range = 6;
	}

	player->entity.light->range = 6;

	load_lights(current_map);
}
