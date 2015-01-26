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

static int max_chars = 41;
static int max_lines_per_page = 5;

static int max_option_chars = 11;

static char *dialog_path = "../extras/resources/dialog/";
static SSL_IniFile *dialog;

static char *name;
static char *text;
static int number_of_lines;
static int number_of_pages;
static int current_line;
static int current_page_number;
static char *current_node;
static int option_count;
static SSL_List *options;

static SSL_Image *dialog_back;
static SSL_Image *portait;

static void load_node(char *node) {
	max_chars = 41;
	current_node = node;
	name = SSL_IniFile_GetString(dialog, node, "name", "detective");
	text = SSL_IniFile_GetString(dialog, node, "text", "detective");

	if (strcmp(name, "assistant") == 0) {
		name = "companion";
	}

	number_of_lines = (strlen(text) / max_chars);

	if (number_of_lines != 0) {
		number_of_pages = (number_of_lines / max_lines_per_page);
	} else {
		number_of_pages = 0;
	}

	current_line = 0;
	current_page_number = 0;

	option_count = SSL_IniFile_GetInt(dialog, node, "option_count", 0);
	if (option_count != 0) {
		options = SSL_List_Create(); // memory leak todo: fix :D

		int i;
		for (i = 1; i <= option_count; i++) {
			char buf[100];
			sprintf(buf, "option_%i" ,i);
			SSL_List_Add(options, SSL_IniFile_GetString(dialog, node, buf, "Error"));
		}
	}

	if (portait) {
		SSL_Image_Destroy(portait);
	}
	char buf[100];
	sprintf(buf, "../extras/resources/portraits/%s.png" ,name);
	portait = SSL_Image_Load(buf, 100, 140, game_window);
}

/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

void dialog_init() {
	dialog_back = SSL_Image_Load("../extras/resources/gui/dialog/dialog.png", WINDOW_RES_WIDTH, WINDOW_RES_HEIGHT, game_window);
}

void start_dialog(char *other, int act) {
	if (dialog) {
		SSL_IniFile_Destroy(dialog);
	}
	dialog = SSL_IniFIle_Create();
	char path[100];
	//sprintf(path, "%s%s_%i.ini", dialog_path, other, act);
	sprintf(path, "%s%s", dialog_path, "chef1.ini");
	SSL_IniFile_Load(dialog, path);

	load_node("root");
}

int update_dialog(SDL_Event event) {

	if (current_page_number < number_of_pages && number_of_lines > 1) {
		if (SSL_Keybord_Keyname_Pressed("_1", event)) {
			current_line += max_lines_per_page;
			current_page_number++;
		}
	} else {
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
			if (SSL_Keybord_Keyname_Pressed("_5", event)) {
				action = SSL_IniFile_GetString(dialog, current_node, "option_5_action", "null");
			}
			if (SSL_Keybord_Keyname_Pressed("_6", event)) {
				action = SSL_IniFile_GetString(dialog, current_node, "option_6_action", "null");
			}
			if (SSL_Keybord_Keyname_Pressed("_7", event)) {
				action = SSL_IniFile_GetString(dialog, current_node, "option_7_action", "null");
			}
			if (SSL_Keybord_Keyname_Pressed("_8", event)) {
				action = SSL_IniFile_GetString(dialog, current_node, "option_8_action", "null");
			}
			if (SSL_Keybord_Keyname_Pressed("_9", event)) {
				action = SSL_IniFile_GetString(dialog, current_node, "option_9_action", "null");
			}

			if (strcmp(action, "null") == 0) {

			} else if (strcmp(action, "end") == 0) {
				return 0;
			} else {
				load_node(action);
			}
		}
	}

	return 1;
}

void render_dialog() {
	SSL_Image_Draw(portait, 1,2, 0,0, SDL_FLIP_NONE, game_window);
	SSL_Image_Draw(dialog_back, 0,0, 0,0, SDL_FLIP_NONE, game_window);

	int i;
	int start_y = 150;
	int y_inc = 15;
	if (number_of_lines == 0) {
		SSL_Font_Draw(10, start_y, 0 ,SDL_FLIP_NONE, text, (SSL_Font *)asset_manager_getFont("dialog_font"), SSL_Color_Create(255,255,255,0), game_window);
	} else {
		for (i = 0; i < max_lines_per_page; i++) {
			if (current_line + i > number_of_lines) {
				break;
			}
			char *final_text = SSL_String_Substring(text, (current_line + i) * max_chars, ((current_line + i) * max_chars) + max_chars);
			if (final_text == NULL) {
				final_text = SSL_String_Substring(text, (current_line + i) * max_chars, strlen(text));
			}
			if (final_text[0] == ' ') {
				final_text++;
			}
			SSL_Font_Draw(10, start_y, 0 ,SDL_FLIP_NONE, final_text, (SSL_Font *)asset_manager_getFont("dialog_font"), SSL_Color_Create(255,255,255,0), game_window);
			start_y += y_inc;
		}
	}
	if (option_count == 0 || current_page_number < number_of_pages) {
		SSL_Font_Draw(225, 10, 0 ,SDL_FLIP_NONE, "1. ...", (SSL_Font *)asset_manager_getFont("dialog_font"), SSL_Color_Create(255,255,255,0), game_window);
	} else {
		int i;
		int y_inc = 10;

		for (i = 0; i < option_count; i++) {
			int number_of_op_lines = (strlen(SSL_List_Get_String(options, i)) + 1) / max_option_chars;

			char buf[100];
			if (number_of_op_lines == 1) {
				sprintf(buf, "%i. %s", i+1, SSL_List_Get_String(options, i));
				SSL_Font_Draw(225, y_inc, 0 ,SDL_FLIP_NONE, buf, (SSL_Font *)asset_manager_getFont("dialog_font"), SSL_Color_Create(255,255,255,0), game_window);
			} else {
				int k;
				for (k = 0; k < number_of_op_lines; k++) {
					if (k == 0) {
						sprintf(buf, "%i. %s", i+1, SSL_String_Substring(SSL_List_Get_String(options, i), 0, max_option_chars - 1));
					} else {
						sprintf(buf, "%s",SSL_String_Substring(SSL_List_Get_String(options, i), (max_option_chars * k) - 1, (max_option_chars * k) + max_option_chars));
						if (buf == NULL) {
							sprintf(buf, "%s",SSL_String_Substring(SSL_List_Get_String(options, i), (max_option_chars * k) - 1, strlen(SSL_List_Get_String(options, i))));
						}
					}
					SSL_Font_Draw(225, y_inc, 0 ,SDL_FLIP_NONE, buf, (SSL_Font *)asset_manager_getFont("dialog_font"), SSL_Color_Create(255,255,255,0), game_window);

					if (k == number_of_op_lines - 2) {
						y_inc += 25;
					}
				}
			}
			y_inc += 25;
		}
	}
}

char *get_node_name() {
	return current_node;
}
