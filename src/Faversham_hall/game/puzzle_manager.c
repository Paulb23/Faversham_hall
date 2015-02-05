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
static SSL_Image *button;
static SSL_Image *paper_strip;
static SSL_List  *objects;

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
}


/*!--------------------------------------------------------------------------
  @brief    Inits the puzzle
  @param	act			act number to check on
  @param	mission		mission number to check on
  @return Void

  Inits the puzzle

\-----------------------------------------------------------------------------*/
void puzzle_init(int act, int mission) {
	objects = SSL_List_Create();

	button = SSL_Image_Load("../extras/resources/gui/game/button.png", 155, 15, game_window);

	if (act == 1 && mission == 1) {
		diary_full_page = SSL_Image_Load("../extras/resources/gui/game/diary_full_page.png", 320 / 2, WINDOW_RES_HEIGHT, game_window);
		paper_strip = SSL_Image_Load("../extras/resources/gui/game/paper_strip.png", 155, 13, game_window);

		int start_y = 15;
		int y_inc = 20;
		int i;
		for (i = 0; i < 10; i++) {
			Puzzle_Object *puzzle_object = puzzle_object_create(162, start_y, 0, paper_strip);
			SSL_List_Add(objects, puzzle_object);
			start_y += y_inc;
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
		if (SSL_Keybord_Keyname_Pressed("_2", event)) {
			return 0;
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
	if (act == 1 && mission == 1) {
		SSL_Image_Draw(diary_full_page, 0, 0, 0, 1, SDL_FLIP_NONE, game_window);
		SSL_Font_Draw(5, 15, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		SSL_Font_Draw(5, 30, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		SSL_Font_Draw(5, 45, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		SSL_Font_Draw(5, 60, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		SSL_Font_Draw(5, 75, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		SSL_Font_Draw(5, 90, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		SSL_Font_Draw(5, 105, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		SSL_Font_Draw(5, 120, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		SSL_Font_Draw(5, 135, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		SSL_Font_Draw(5, 150, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		SSL_Font_Draw(5, 165, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		SSL_Font_Draw(5, 180, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		SSL_Font_Draw(5, 195, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
		SSL_Font_Draw(5, 210, 0 ,SDL_FLIP_NONE, "1234567890123456789012", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	}

	int i;
	for(i = 0 ; i < SSL_List_Size(objects); i++) {
		Puzzle_Object *puzzle_object = SSL_List_Get(objects, i);
		SSL_Image_Draw(puzzle_object->image, puzzle_object->x, puzzle_object->y, puzzle_object->rot, 0, SDL_FLIP_NONE, game_window);
	}

	SSL_Image_Draw(button, 162, 217, 0, 1, SDL_FLIP_NONE, game_window);
	SSL_Font_Draw(167, 220, 0 ,SDL_FLIP_NONE, "1. Restart        2. Check", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,255,255,0), game_window);
}
