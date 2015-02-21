/*-------------------------------------------------------------------------*/
/**
   @file    instructions.c
   @author  P. Batty
   @brief   The instructions

   This module implements the credits

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "instructions.h"
#include "SDL2/SDL.h"
#include "../window_manager.h"
#include "../state_controller.h"
#include "../config.h"
#include "../asset_manager.h"

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static SSL_Image *background;
static Game_States state;

/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	initialises the instructions
  @return 	Void

  inits the instructions.

\-----------------------------------------------------------------------------*/
void instructions_init() {
	background = SSL_Image_Load("../extras/resources/gui/menu/instructions_background.png",WINDOW_RES_WIDTH, WINDOW_RES_HEIGHT, game_window);
	state = game_state;
}


/*!--------------------------------------------------------------------------
  @brief	Cleans up the instructions
  @return 	Void

  Cleans up the instructions

\-----------------------------------------------------------------------------*/
void instructions_clean_up() {
	SSL_Image_Destroy(background);
}


/*!--------------------------------------------------------------------------
  @brief	Logic for the instructions
  @return 	Void

  instructions logic

\-----------------------------------------------------------------------------*/
void instructions_ticks() {

}


/*!--------------------------------------------------------------------------
  @brief	Event handler
  @param	event		the event to handle
  @return 	Void

  Event handler

\-----------------------------------------------------------------------------*/
void instructions_handeler(SDL_Event event) {

	if (SSL_Keybord_Keyname_Pressed("_1", event)) {
		switch_state(state);
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
  @brief	Renders the instructions
  @return 	Void

  Renders the instructions.

\-----------------------------------------------------------------------------*/
void instructions_renderer() {
	SSL_Image_Draw(background, 0, 0, 0, 0, SDL_FLIP_NONE, game_window);
	SSL_Font_Draw(90, 20, 0 ,SDL_FLIP_NONE, "Use the W A S D keys to", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(90, 35, 0 ,SDL_FLIP_NONE, "move around the mansion", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);

	SSL_Font_Draw(90, 60, 0 ,SDL_FLIP_NONE, "Press M To Mute", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);

	SSL_Font_Draw(90, 80, 0 ,SDL_FLIP_NONE, "Use the E key to interact", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);

	SSL_Font_Draw(90, 100, 0 ,SDL_FLIP_NONE, "Use the 1 - 9 keys to make", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(90, 115, 0 ,SDL_FLIP_NONE, "selections / choices", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);

	SSL_Font_Draw(220, 135, 0 ,SDL_FLIP_NONE, "Your task", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(195, 151, 0 ,SDL_FLIP_NONE, "Status / Interaction", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);

	SSL_Font_Draw(198, 167, 0 ,SDL_FLIP_NONE, "Dialog Options", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(198, 187, 0 ,SDL_FLIP_NONE, "Who's Speaking", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(198, 205, 0 ,SDL_FLIP_NONE, "What they're saying", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);

	SSL_Font_Draw(195, 225, 0 ,SDL_FLIP_NONE, "Press 1 to Continue..", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(255,0,0,255), game_window);
}

