/*-------------------------------------------------------------------------*/
/**
   @file    main_menu.h
   @author  P. Batty
   @brief   The main menu

   This module implements the main menu

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "main_menu.h"
#include "SDL2/SDL.h"
#include "../window_manager.h"
#include "../state_controller.h"
#include "../config.h"
#include "../asset_manager.h"

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static SSL_Image *background;
static SSL_Image *title;
static Mix_Music *music;


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	initialises the main menu
  @return 	Void

  inits the main menu.

\-----------------------------------------------------------------------------*/
void main_menu_init() {
	background = SSL_Image_Load("../extras/resources/gui/menu/main_menu_background.png",WINDOW_RES_WIDTH, WINDOW_RES_HEIGHT, game_window);
	title = SSL_Image_Load("../extras/resources/gui/menu/title.png",WINDOW_RES_WIDTH, WINDOW_RES_HEIGHT, game_window);
	music = Mix_LoadMUS("../extras/resources/audio/music/menu.wav");
	Mix_PlayMusic(music, -1);
}


/*!--------------------------------------------------------------------------
  @brief	Cleans up the main menu
  @return 	Void

  Cleans up the main menu

\-----------------------------------------------------------------------------*/
void main_menu_clean_up() {
	SSL_Image_Destroy(background);
	SSL_Image_Destroy(title);
}


/*!--------------------------------------------------------------------------
  @brief	Logic for the main menu
  @return 	Void

  Main menu logic

\-----------------------------------------------------------------------------*/
void main_menu_ticks() {

}


/*!--------------------------------------------------------------------------
  @brief	Event handler
  @param	event		the event to handle
  @return 	Void

  Event handler

\-----------------------------------------------------------------------------*/
void main_menu_event_handeler(SDL_Event event) {

	if (SSL_Keybord_Keyname_Pressed("_1", event)) {
		switch_state(GAME_LOAD_STATE);
	}

	if (SSL_Keybord_Keyname_Pressed("_2", event)) {
		switch_state(GAME_STATE);
	}

	if (SSL_Keybord_Keyname_Pressed("_3", event)) {
		switch_state(INSTRUCTIONS_STATE);
	}

	if (SSL_Keybord_Keyname_Pressed("_4", event)) {
		switch_state(CREDIT_STATE);
	}

	if (SSL_Keybord_Keyname_Pressed("_5", event)) {
		switch_state(EXIT);
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
  @brief	Renders the main menu
  @return 	Void

  Renders the main menu.

\-----------------------------------------------------------------------------*/
void main_menu_renderer() {
	SSL_Image_Draw(background, 0, 0, 0, 0, SDL_FLIP_NONE, game_window);
	SSL_Image_Draw(title, 0, 0, 0, 0, SDL_FLIP_NONE, game_window);

	SSL_Font_Draw(118, 130, 0 ,SDL_FLIP_NONE, "1. Resume", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(118, 150, 0 ,SDL_FLIP_NONE, "2. New Game", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(118, 170, 0 ,SDL_FLIP_NONE, "3. Instructions", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(118, 190, 0 ,SDL_FLIP_NONE, "4. Credits", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(118, 210, 0 ,SDL_FLIP_NONE, "5. Exit", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
}

