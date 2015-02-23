/*-------------------------------------------------------------------------*/
/**
   @file    puzzle_manager.c
   @author  P. Batty
   @brief   ...

   This module implements...

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "puzzle_manager.h"
#include "mission_manager.h"
#include "../asset_manager.h"
#include "game.h"

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static SSL_Image *diary_full_page;
static SSL_Image *big_button;
static SSL_Image *button;
static SSL_Image *paper_strip;
static SSL_Image *selected_paper_strip;
static SSL_List  *objects;

static SSL_Image *horizontal;
static SSL_Image *vertical;
static SSL_Image *selected_pipe;
static SSL_Image *up_left;
static SSL_Image *up_right;
static SSL_Image *start;
static SSL_Image *end;

static Mix_Chunk *puzzle_complete_sfx;
static Mix_Chunk *puzzle_fail_sfx;

static int show_instructions;

static int selected;
static const int diary_start_y = 15;
static const int diary_y_inc = 15;
static const int diary_end_y = 165;
static const int diary_order[10] = {8,5,1,4,2,10,11,3,9,6};

static const int water_order[18] = {360,90,360,180,270,360,360,360,360,90, 180, 360, 360, 180, 360, 180, 360, 360};
static const int water_rot[4] = {90,180,270,360};

static int check_puzzle(int act, int mission) {
	if (act == 1 && mission == 1) {
		int i;
		for(i = 0 ; i < SSL_List_Size(objects); i++) {
			Puzzle_Object *puzzle_object = SSL_List_Get(objects, i);
			if (puzzle_object->y == diary_y_inc * diary_order[i]) {

			} else {
				Mix_PlayChannel(-1, puzzle_fail_sfx, 0);
				return 1;
			}

		}
	}

	if (act == 4 && mission == 1) {
		int i;
		for(i = 0 ; i < SSL_List_Size(objects); i++) {
			Puzzle_Object *puzzle_object = SSL_List_Get(objects, i);
			if (puzzle_object->rot == water_order[i]) {

			} else {
				Mix_PlayChannel(-1, puzzle_fail_sfx, 0);
				return 1;
			}

		}
	}

	Mix_PlayChannel(-1, puzzle_complete_sfx, 0);
	return 0;
}

/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Creates a new puzzle Object
  @param	x			x position
  @param	y			y position
  @param	rot			rotation of the object
  @param	image		Image of the object
  @return new Puzzle object else -1 on error

  Creates a enw puzzle object and returns it else -1 on error

\-----------------------------------------------------------------------------*/
Puzzle_Object *puzzle_object_create(int x, int y, int rot, SSL_Image *image) {
	Puzzle_Object *object = malloc(sizeof(Puzzle_Object));

		if (!object) {
			SSL_Log_Write("Failed to allocate memory for new puzzle object!");
			return (void *)-1;
		}

		object->x = x;
		object->y = y;
		object->rot = rot;
		object->image = image;

	return object;
}


/*!--------------------------------------------------------------------------
  @brief    Destroys a puzzle object
  @param	object			the object to destroy
  @return Void

  destroys a puzzle object

\-----------------------------------------------------------------------------*/
void puzzle_object_destroy(Puzzle_Object *object) {
	free(object);
}


/*!--------------------------------------------------------------------------
  @brief    Validates the clue
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return 1 if valued else 0

  Checks if the clue can be access at the current point. return1 if valid else 0

\-----------------------------------------------------------------------------*/
int valid_clue(int act, int mission) {

	if (act == 1 && mission == 1 && strcmp(game_get_room(), "servants_quarters") == 0) {
		return 1;
	}

	if (act == 4 && mission == 1 && strcmp(game_get_room(), "duchtess_bedroom") == 0) {
		return 1;
	}

	return 0;
}


/*!--------------------------------------------------------------------------
  @brief    Starts the clue
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return Void

  Starts the clue / puzzle and passes it on to the mission manager

\-----------------------------------------------------------------------------*/
void start_clue(int act, int mission) {

	if (act == 1 && mission == 1) {
		start_puzzle("diary");
	}

	if (act == 4 && mission == 1) {
		start_puzzle("plumber");
	}
}


/*!--------------------------------------------------------------------------
  @brief    Inits the puzzle
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return Void

  Inits the puzzle

\-----------------------------------------------------------------------------*/
void puzzle_init(int act, int mission) {
	if (puzzle_complete_sfx) {
		Mix_FreeChunk(puzzle_complete_sfx);
		puzzle_complete_sfx = NULL;
	}
	puzzle_complete_sfx = Mix_LoadWAV("../extras/resources/audio/sfx/puzzle_complete.wav");

	if (puzzle_fail_sfx) {
		Mix_FreeChunk(puzzle_fail_sfx);
		puzzle_fail_sfx = NULL;
	}
	puzzle_fail_sfx = Mix_LoadWAV("../extras/resources/audio/sfx/puzzle_fail.wav");

	selected = 0;
	show_instructions = 1;
	objects = SSL_List_Create();

	button = SSL_Image_Load("../extras/resources/gui/game/button.png", 155, 15, game_window);
	big_button = SSL_Image_Load("../extras/resources/gui/game/big_button.png", 155, 45, game_window);

	if (act == 1 && mission == 1) {
		diary_full_page = SSL_Image_Load("../extras/resources/gui/game/diary_full_page.png", 320 / 2, WINDOW_RES_HEIGHT, game_window);
		selected_paper_strip = SSL_Image_Load("../extras/resources/gui/game/paper/selector.png", 155, 13, game_window);

		int start_y = 15;
		int y_inc = 15;
		int i;
		for (i = 0; i < 10; i++) {
			char buffer[100];
			sprintf(buffer, "../extras/resources/gui/game/paper/%i.png", i);
			paper_strip = SSL_Image_Load(buffer, 155, 13, game_window);
			Puzzle_Object *puzzle_object = puzzle_object_create(162, start_y, 0, paper_strip);
			SSL_List_Add(objects, puzzle_object);
			start_y += y_inc;
		}
	}

	if (act == 4 && mission == 1) {
		vertical = SSL_Image_Load("../extras/resources/gui/game/water/vertical.png", 32, 32, game_window);
		horizontal = SSL_Image_Load("../extras/resources/gui/game/water/horizontal.png", 32, 32, game_window);
		up_left = SSL_Image_Load("../extras/resources/gui/game/water/up_left.png", 32, 32, game_window);
		up_right = SSL_Image_Load("../extras/resources/gui/game/water/up_right.png", 32, 32, game_window);
		start = SSL_Image_Load("../extras/resources/gui/game/water/start.png", 32, 32, game_window);
		end = SSL_Image_Load("../extras/resources/gui/game/water/end.png", 32, 32, game_window);
		selected_pipe = SSL_Image_Load("../extras/resources/gui/game/water/selected.png", 32, 32, game_window);

		int rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(50, 180, water_rot[rot], up_right));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(90, 180, water_rot[rot], up_left));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(90, 145, water_rot[rot], up_left));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(50, 145, water_rot[rot], horizontal));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(15, 145, water_rot[rot], up_right));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(15, 110, water_rot[rot], vertical));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(15, 75, water_rot[rot], vertical));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(15, 40, water_rot[rot], up_right));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(50, 40, water_rot[rot], horizontal));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(87, 40, water_rot[rot], up_right));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(87, 75, water_rot[rot], up_left));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(125, 75, water_rot[rot], horizontal));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(160, 75, water_rot[rot], horizontal));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(195, 75, water_rot[rot], up_right));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(195, 40, water_rot[rot], up_right));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(230, 40, water_rot[rot], up_right));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(230, 5, water_rot[rot], up_right));
		rot = rand() % 4;
		SSL_List_Add(objects, puzzle_object_create(265, 5, water_rot[rot], horizontal));
		rot = rand() % 4;
	}
}


/*!--------------------------------------------------------------------------
  @brief    Restarts the puzzle
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return Void

  Restarts the puzzle

\-----------------------------------------------------------------------------*/
void puzzle_restart(int act, int mission) {
	selected = 0;

	if (act == 1 && mission == 1) {
		int start_y = 15;
		int y_inc = 15;
		int i;
		for (i = 0; i < SSL_List_Size(objects); i++) {
			Puzzle_Object *puzzle_object = SSL_List_Get(objects, i);
			puzzle_object->x = 162;
			puzzle_object->y = start_y;
			start_y += y_inc;
		}
	}

	if (act == 4 && mission == 1) {
		int i;
		int rot = rand() % 4;
		for (i = 0; i < SSL_List_Size(objects); i++) {
			Puzzle_Object *puzzle_object = SSL_List_Get(objects, i);
			rot = rand() % 4;
			puzzle_object->rot = water_rot[rot];
		}
	}
}


/*!--------------------------------------------------------------------------
  @brief    Cleans up the puzzle
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return Void

  Cleans up the puzzle

\-----------------------------------------------------------------------------*/
void puzzle_clean_up(int act, int mission) {
	SSL_Image_Destroy(button);
	SSL_Image_Destroy(big_button);

	if (act == 1 && mission == 1) {
		SSL_Image_Destroy(diary_full_page);
	}
}


/*!--------------------------------------------------------------------------
  @brief    Updates the puzzle
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return Void

  Updates the puzzle
\-----------------------------------------------------------------------------*/
void puzzle_update(int act, int mission) {
	if (act == 1 && mission == 1) {

	}
}


/*!--------------------------------------------------------------------------
  @brief    Handles the puzzle events
  @param	event		the event queue
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return 1 if failed else 0 on completion

  Updates the puzzle events
\-----------------------------------------------------------------------------*/
int puzzle_update_events(SDL_Event event, int act, int mission) {
	if (act == 1 && mission == 1) {
		if (show_instructions) {
			if (SSL_Keybord_Keyname_Pressed("_1", event)) {
				show_instructions = 0;
			}
		} else {
			if (SSL_Keybord_Keyname_Pressed("_1", event)) {
				puzzle_restart(act, mission);
			}
			if (SSL_Keybord_Keyname_Pressed("_2", event)) {
				int result =  check_puzzle(act, mission);
				if (result) {
					puzzle_restart(act, mission);
				}
				return result;
			}

			if (SSL_Keybord_Keyname_Pressed("_a", event)) {
				Puzzle_Object *puzzle_object = SSL_List_Get(objects, selected);
				puzzle_object->x = 1;
			}

			if (SSL_Keybord_Keyname_Pressed("_s", event)) {
				Puzzle_Object *puzzle_object = SSL_List_Get(objects, selected);
				if (puzzle_object->y < diary_end_y && puzzle_object-> x == 1) {
					puzzle_object->y += diary_y_inc;
				}
			}

			if (SSL_Keybord_Keyname_Pressed("_w", event)) {
				Puzzle_Object *puzzle_object = SSL_List_Get(objects, selected);
				if (puzzle_object->y > diary_start_y && puzzle_object-> x == 1) {
					puzzle_object->y -= diary_y_inc;
				}
			}

			if (SSL_Keybord_Keyname_Pressed(INTERACT_KEY, event)) {
				Puzzle_Object *puzzle_object = SSL_List_Get(objects, selected);
				if (puzzle_object->x == 1) {
					if (selected < SSL_List_Size(objects) - 1) {
						selected++;
					} else {
					}
				}
			}
		}
		return 1;
	}

	if (act == 4 && mission == 1) {
		if (show_instructions) {
			if (SSL_Keybord_Keyname_Pressed("_1", event)) {
				show_instructions = 0;
			}
		} else {
			if (SSL_Keybord_Keyname_Pressed("_1", event)) {
				puzzle_restart(act, mission);
			}
			if (SSL_Keybord_Keyname_Pressed("_2", event)) {
				int result =  check_puzzle(act, mission);
				if (result) {
					puzzle_restart(act, mission);
				}
				return result;
			}
			if (SSL_Keybord_Keyname_Pressed("_w", event)) {
				if (selected < SSL_List_Size(objects) - 1) {
					selected++;
				}
			}
			if (SSL_Keybord_Keyname_Pressed("_s", event)) {
				if (selected != 0) {
					selected--;
				}
			}

			if (SSL_Keybord_Keyname_Pressed(INTERACT_KEY, event)) {
				Puzzle_Object *puzzle_object = SSL_List_Get(objects, selected);
				puzzle_object->rot += 90;
				if (puzzle_object->rot > 360) {
					puzzle_object->rot = 90;
				}
			}
		}
		return 1;
	}

	return 0;
}


/*!--------------------------------------------------------------------------
  @brief    Renders the puzzle
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return Void

  Renders the puzzle
\-----------------------------------------------------------------------------*/
void puzzle_render(int act, int mission) {
	if (show_instructions) {
		if (act == 1 && mission == 1) {
			SSL_Font_Draw(5, 15, 0 ,SDL_FLIP_NONE,  "In order to decode the diary, the correct paper", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 30, 0 ,SDL_FLIP_NONE,  "slips need to be moved over the correct lines", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 45, 0 ,SDL_FLIP_NONE,  "of the diary. Pieces will be selected in order,", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 60, 0 ,SDL_FLIP_NONE,  "use the (W,A,S) keys to control the position", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 75, 0 ,SDL_FLIP_NONE,  "of the piece. Once the selected piece is in", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 90, 0 ,SDL_FLIP_NONE,  "the correct place, press (E) to move on to the", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 105, 0 ,SDL_FLIP_NONE,  "next piece. work out the correct place, use ", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 120, 0 ,SDL_FLIP_NONE,  "the letter clue to match the gap in the slip", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 135, 0 ,SDL_FLIP_NONE,  "to the correct word. When the puzzle is complete,", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 150, 0 ,SDL_FLIP_NONE,  "take note of the message, it might be helpful.", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 165, 0 ,SDL_FLIP_NONE,  "Then Press 2 to check the puzzle and move on", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);

		}
		if (act == 4 && mission == 1) {
			SSL_Font_Draw(5, 15, 0 ,SDL_FLIP_NONE,  "In order to solve the pipes, you must control", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 30, 0 ,SDL_FLIP_NONE,  "the flow of the water. Select the piece you", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 45, 0 ,SDL_FLIP_NONE,  "want with the (W,S) keys and then rotate the", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 60, 0 ,SDL_FLIP_NONE,  "piece in order to complete the pipe lineup with", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 75, 0 ,SDL_FLIP_NONE,  "the (E) key. Once everything is lined up to your", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 90, 0 ,SDL_FLIP_NONE,  "satisfaction press (2) to flow the water. Be", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 105, 0 ,SDL_FLIP_NONE,  "careful, though - If you don't succeed the puzzle", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
			SSL_Font_Draw(5, 120, 0 ,SDL_FLIP_NONE,  "will reset and you will need to start again!", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
		}

		SSL_Font_Draw(180, 210, 0 ,SDL_FLIP_NONE,  "Press 1 to start...", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
	} else {
		if (act == 1 && mission == 1) {
			SSL_Image_Draw(diary_full_page, 0, 0, 0, 1, SDL_FLIP_NONE, game_window);
			SSL_Font_Draw(5, 15, 0 ,SDL_FLIP_NONE,  "Tuesday 15 march", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
			SSL_Font_Draw(5, 30, 0 ,SDL_FLIP_NONE,  "Tense evening. Servant", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
			SSL_Font_Draw(5, 45, 0 ,SDL_FLIP_NONE,  "Caught the butler", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
			SSL_Font_Draw(5, 60, 0 ,SDL_FLIP_NONE,  "Looking at my breasts", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
			SSL_Font_Draw(5, 75, 0 ,SDL_FLIP_NONE,  "I hate him. He is", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
			SSL_Font_Draw(5, 90, 0 ,SDL_FLIP_NONE,  "Spoiling my studying", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
			SSL_Font_Draw(5, 105, 0 ,SDL_FLIP_NONE, "and my life. I'm", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
			SSL_Font_Draw(5, 120, 0 ,SDL_FLIP_NONE, "Meeting my lawyer", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
			SSL_Font_Draw(5, 135, 0 ,SDL_FLIP_NONE, "At walnut-tree inn", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
			SSL_Font_Draw(5, 150, 0 ,SDL_FLIP_NONE, "Tomorrow at 3pm.", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
			SSL_Font_Draw(5, 165, 0 ,SDL_FLIP_NONE, "He is in trouble.", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		//	SSL_Font_Draw(5, 180, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		//	SSL_Font_Draw(5, 195, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		//	SSL_Font_Draw(5, 210, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		}

		if (act == 4 && mission == 1) {
			SSL_Image_Draw(start, 50, 210, 0, 1, SDL_FLIP_NONE, game_window);
			SSL_Image_Draw(end, 295, 5, 270, 1, SDL_FLIP_NONE, game_window);
		}

		int i;
		for(i = 0 ; i < SSL_List_Size(objects); i++) {
			Puzzle_Object *puzzle_object = SSL_List_Get(objects, i);
			SSL_Image_Draw(puzzle_object->image, puzzle_object->x, puzzle_object->y - 1, puzzle_object->rot, 0, SDL_FLIP_NONE, game_window);
		}

		if (act == 1 && mission == 1) {
			Puzzle_Object *puzzle_object = SSL_List_Get(objects, selected);
			SSL_Image_Draw(selected_paper_strip, puzzle_object->x, puzzle_object->y - 1, 0, 0, SDL_FLIP_NONE, game_window);
		}

		if (act == 4 && mission == 1) {
			Puzzle_Object *puzzle_object = SSL_List_Get(objects, selected);
			SSL_Image_Draw(selected_pipe, puzzle_object->x, puzzle_object->y - 1, 0, 0, SDL_FLIP_NONE, game_window);
		}

		SSL_Image_Draw(big_button, 162, 167, 0, 1, SDL_FLIP_NONE, game_window);

		if (act == 1 && mission == 1) {
			SSL_Font_Draw(177, 170, 0 ,SDL_FLIP_NONE, "A. Move Left", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
			SSL_Font_Draw(177, 180, 0 ,SDL_FLIP_NONE, "W. Move Up", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
			SSL_Font_Draw(177, 190, 0 ,SDL_FLIP_NONE, "S. Move Down", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
			SSL_Font_Draw(177, 200, 0 ,SDL_FLIP_NONE, "E. Place", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		}

		if (act == 4 && mission == 1) {
			SSL_Font_Draw(177, 170, 0 ,SDL_FLIP_NONE, "W. Next", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
			SSL_Font_Draw(177, 180, 0 ,SDL_FLIP_NONE, "S. Previous", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
			SSL_Font_Draw(177, 190, 0 ,SDL_FLIP_NONE, "E. Rotate", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		}

		SSL_Image_Draw(button, 162, 217, 0, 1, SDL_FLIP_NONE, game_window);
		SSL_Font_Draw(167, 220, 0 ,SDL_FLIP_NONE, "1. Restart        2. Check", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
	}
}
