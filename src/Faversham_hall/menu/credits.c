/*-------------------------------------------------------------------------*/
/**
   @file    credits.c
   @author  P. Batty
   @brief   The credits

   This module implements the credits

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "credits.h"
#include "SDL2/SDL.h"
#include "../window_manager.h"
#include "../state_controller.h"
#include "../config.h"
#include "../asset_manager.h"

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static SSL_Image *background;

/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	initialises the credits
  @return 	Void

  inits the main menu.

\-----------------------------------------------------------------------------*/
void credits_init() {
	background = SSL_Image_Load("../extras/resources/gui/menu/credits_background.png",WINDOW_RES_WIDTH, WINDOW_RES_HEIGHT, game_window);
}


/*!--------------------------------------------------------------------------
  @brief	Cleans up the credits
  @return 	Void

  Cleans up the credits

\-----------------------------------------------------------------------------*/
void credits_clean_up() {
	SSL_Image_Destroy(background);
}


/*!--------------------------------------------------------------------------
  @brief	Logic for the credits
  @return 	Void

  Credits logic

\-----------------------------------------------------------------------------*/
void credits_ticks() {

}


/*!--------------------------------------------------------------------------
  @brief	Event handler
  @param	event		the event to handle
  @return 	Void

  Event handler

\-----------------------------------------------------------------------------*/
void credits_handeler(SDL_Event event) {

	if (SSL_Keybord_Keyname_Pressed("_1", event)) {
		switch_state(MAIN_MENU);
	}
}


/*!--------------------------------------------------------------------------
  @brief	Renders the credits
  @return 	Void

  Renders the credits.

\-----------------------------------------------------------------------------*/
void credits_renderer() {
	SSL_Image_Draw(background, 0, 0, 0, 0, SDL_FLIP_NONE, game_window);

	SSL_Font_Draw(111, 5, 0 ,SDL_FLIP_NONE, "Made By:", (SSL_Font *)asset_manager_getFont("ui_title_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(123, 22, 0 ,SDL_FLIP_NONE, "Paul Batty", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(105, 37, 0 ,SDL_FLIP_NONE, "Harry Messenger", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(108, 52, 0 ,SDL_FLIP_NONE, "Naomi Chadwick", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(123, 67, 0 ,SDL_FLIP_NONE, "Zhidong Li", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(120, 82, 0 ,SDL_FLIP_NONE, "Tom Hudson", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);

	SSL_Font_Draw(103, 110, 0 ,SDL_FLIP_NONE, "Made With:", (SSL_Font *)asset_manager_getFont("ui_title_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(135, 125, 0 ,SDL_FLIP_NONE, "ANSI C", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(50, 140, 0 ,SDL_FLIP_NONE, "SDL 2, SDL_IMAGE, SDL_MIXER, SDL_TTF", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
	SSL_Font_Draw(65, 155, 0 ,SDL_FLIP_NONE, "grandchaos9000 For the font", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);

	SSL_Font_Draw(145, 225, 0 ,SDL_FLIP_NONE, "Press 1 to Continue..", (SSL_Font *)asset_manager_getFont("ui_font"), SSL_Color_Create(0,0,0,255), game_window);
}

