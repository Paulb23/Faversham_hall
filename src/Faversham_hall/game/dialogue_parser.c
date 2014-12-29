/*-------------------------------------------------------------------------*/
/**
   @file    dialogue_parser.c
   @author  P. Batty
   @brief   The dialog parser

   This module implements the dialog parser

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "dialogue_parser.h"
#include "../window_manager.h"
#include "../asset_manager.h"
#include "../config.h"
#include "../../SSL/SSL.h"
#include "SDL2\SDL.h"

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static char *dialog_path = "../extras/resources/dialog/";
static SSL_IniFile *dialog;

static char *name;
static char *text;
static char *current_node;
static int option_count;
static SSL_List *options;

static void load_node(char *node) {
	current_node = node;
	name = SSL_IniFile_GetString(dialog, node, "name", "detective");
	text = SSL_IniFile_GetString(dialog, node, "text", "detective");
	option_count = SSL_IniFile_GetInt(dialog, node, "option_count", 0);

	if (option_count != 0) {
		if (options) {
			SSL_List_Destroy(options);
		}
		options = SSL_List_Create();

		int i;
		for (i = 0; i < option_count; i++) {
			char buf[100];
			sprintf(buf, "option_%i" ,i);
			SSL_List_Add(options, SSL_IniFile_GetString(dialog, node, buf, "0"));
		}
	}
}

/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

void start_dialog(char *other, int act) {
	if (dialog) {
		SSL_IniFile_Destroy(dialog);
	}
	dialog = SSL_IniFIle_Create();
	char path[100];
	//sprintf(path, "%s%s_%i.ini", dialog_path, other, act);
	sprintf(path, "%s%s", dialog_path, "test_dialogue.ini");
	SSL_IniFile_Load(dialog, path);

	load_node("root");
}

int update_dialog(SDL_Event event) {

	if (option_count == 0) {
		if (SSL_Keybord_Keyname_Pressed("_1", event)) {
			char *action = SSL_IniFile_GetString(dialog, current_node, "action", "end");

			if (strcmp(action, "end") == 0) {
				return 0;
			} else {
				load_node(action);
			}
		}
	} else {

		char *action = "null";

		if (SSL_Keybord_Keyname_Pressed("_1", event)) {
			action = SSL_IniFile_GetString(dialog, current_node, "option_1_action", "null");
		}
		if (SSL_Keybord_Keyname_Pressed("_2", event)) {
			action = SSL_IniFile_GetString(dialog, current_node, "option_2_action", "null");
		}
		if (SSL_Keybord_Keyname_Pressed("_3", event)) {
			action = SSL_IniFile_GetString(dialog, current_node, "option_3_action", "null");
		}
		if (SSL_Keybord_Keyname_Pressed("_4", event)) {
			action = SSL_IniFile_GetString(dialog, current_node, "option_4_action", "null");
		}

		if (strcmp(action, "null") == 0) {

		} else if (strcmp(action, "end") == 0) {
			return 0;
		} else {
			load_node(action);
		}
	}

	return 1;
}

void render_dialog() {
	SSL_Font_Draw(10, 40, 0 ,SDL_FLIP_NONE, name, (SSL_Font *)asset_manager_getFont("test_font"), SSL_Color_Create(255,255,255,0), game_window);
	SSL_Font_Draw(10, 55, 0 ,SDL_FLIP_NONE, text, (SSL_Font *)asset_manager_getFont("test_font"), SSL_Color_Create(255,255,255,0), game_window);

	if (option_count == 0) {
		SSL_Font_Draw(10, 70, 0 ,SDL_FLIP_NONE, "1. ...", (SSL_Font *)asset_manager_getFont("test_font"), SSL_Color_Create(255,255,255,0), game_window);
	} else {
		int i;
		int y_inc = 55;

		for (i = 0; i < option_count; i++) {
			y_inc += 15;
			char buf[100];
			sprintf(buf, "%i. %s", i+1, SSL_List_Get_String(options, i));
			SSL_Font_Draw(10, y_inc, 0 ,SDL_FLIP_NONE, buf, (SSL_Font *)asset_manager_getFont("test_font"), SSL_Color_Create(255,255,255,0), game_window);
		}
	}
}