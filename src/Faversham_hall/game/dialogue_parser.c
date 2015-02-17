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
#include "mission_manager.h"
#include "../config.h"
#include "../../SSL/SSL.h"
#include "SDL2\SDL.h"

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static int max_chars = 41;				/**< max number of chars per line */
static int max_lines_per_page = 5;		/**< max number of lines per page */

static int max_option_chars = 11;		/**< max number of option chars per line */

static char *dialog_path = "../extras/resources/dialog/";	/**< path to the dialog files */
static SSL_IniFile *dialog;									/**< the ini file we a re currently reading */

static char *name;				/**< name of the npc currently talking */
static char *text;				/**< text that the npc is saying */
static int number_of_lines;		/**< number of lines in that text */
static int number_of_pages;		/**< number of pages in that text */
static int current_line;		/**< current line  number we a re on */
static int current_page_number;	/**< current page we are on */
static char *current_node;		/**< current dialog node we are reading */
static int option_count;		/**< number of options that we have */
static SSL_List *options;		/**< list of the options */

static SSL_Image *dialog_back;	/**< the dialog background */
static SSL_Image *portait;		/**< the portait of the character */


/*----------------------------------
     loads a dialog node
 ----------------------------------*/

static void load_node(char *node) {

	// set the current node to this one
	current_node = node;

	// read in the name and text
	name = SSL_IniFile_GetString(dialog, node, "name", "detective");
	text = SSL_IniFile_GetString(dialog, node, "text", "detective");

	// swap in case of called by different name
	if (strcmp(name, "assistant") == 0) {
		name = "companion";
	}

	// calculate the number of lines
	number_of_lines = ((strlen(text) - 1)/ max_chars);

	// calculate the number of pages
	if (number_of_lines != 0) {
		number_of_pages = (number_of_lines / max_lines_per_page);
	} else {
		number_of_pages = 0;
	}

	// set to page and line 0
	current_line = 0;
	current_page_number = 0;

	// get the numbner of options
	option_count = SSL_IniFile_GetInt(dialog, node, "option_count", 0);

	// read the options if we have some
	if (option_count != 0) {
		options = SSL_List_Create();

		int i;
		for (i = 1; i <= option_count; i++) {
			char buf[100];
			sprintf(buf, "option_%i" ,i);
			SSL_List_Add(options, SSL_IniFile_GetString(dialog, node, buf, "Error"));
		}
	}

	// free up old portrait memory
	if (portait) {
		SSL_Image_Destroy(portait);
	}

	// load in the new portrait
	char buf[100];
	if (strcmp("dutchess", name) == 0) {
		name = "duchess";
	}
	sprintf(buf, "../extras/resources/portraits/%s.png" ,name);
	portait = SSL_Image_Load(buf, 100, 140, game_window);
}

/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Inits the dialog parser
  @return 	Void

  Inits the dialog parser.

\-----------------------------------------------------------------------------*/
void dialog_init() {
	dialog_back = SSL_Image_Load("../extras/resources/gui/dialog/dialog.png", WINDOW_RES_WIDTH, WINDOW_RES_HEIGHT, game_window);
}


/*!--------------------------------------------------------------------------
  @brief	Cleans up the dialog parser
  @return 	Void

  Cleans up the dialog parser.

\-----------------------------------------------------------------------------*/
void dialog_clean_up() {
	SSL_Image_Destroy(dialog_back);
}


/*!--------------------------------------------------------------------------
  @brief	Starts the dialog
  @param	other		The npc name
  @param	act			The act number
  @return 	Void

  Cleans up the dialog parser.

\-----------------------------------------------------------------------------*/
void start_dialog(char *other, int act) {

	// if we've previous been in dialog free up memory
	if (dialog) {
		SSL_IniFile_Destroy(dialog);
	}

	// load the dialog
	dialog = SSL_IniFIle_Create();

	// exceptions to the rules
	char path[100];
	if (strcmp(other, "dutchess") == 0 && get_current_act() == 4 && get_current_mission() == 2) {
		sprintf(path, "%s%s%i_2.ini", dialog_path, other, act);
	} else if (act == 10) {
		sprintf(path, "%saccuse_%s.ini", dialog_path, other);
	} else if (act == 11) {
		sprintf(path, "%sGeneral_finale.ini", dialog_path);
	} else {
		sprintf(path, "%s%s%i.ini", dialog_path, other, act);
	}

	// if the file for the npc + act exists load that one
	if( access( path, F_OK ) != -1 ) {
		SSL_IniFile_Load(dialog, path);
		load_node("root");
	} else {

		// else check for just the npc name
		sprintf(path, "%s%s.ini", dialog_path, other);
		if( access( path, F_OK ) != -1 ) {
		} else {
			sprintf(path, "%s%s.ini", dialog_path, "test_dialogue");
		}

		// load in the fil
		SSL_IniFile_Load(dialog, path);

		// load the root node
		load_node("root");
	}
}


/*!--------------------------------------------------------------------------
  @brief	Dialog event handler
  @param	event		The event queue
  @return 	Void

  Handles events for the dialog parser.

\-----------------------------------------------------------------------------*/
int update_dialog(SDL_Event event) {

	// if we are not on the last page allow defualt to "press one for next page"
	if (current_page_number < number_of_pages && number_of_lines > 1 && current_line + max_lines_per_page < number_of_lines) {
		if (SSL_Keybord_Keyname_Pressed("_1", event)) {
			current_line += max_lines_per_page;
			current_page_number++;
		}

	// else we are on the last page
	} else {

		// if we don't have options, progress or exit convo based on action
		if (option_count == 0) {
			if (SSL_Keybord_Keyname_Pressed("_1", event)) {
				char *action = SSL_IniFile_GetString(dialog, current_node, "action", "end");
				if (strcmp(action, "end") == 0) {
					return 0;
				} else {
					load_node(action);
				}
			}

		// else we have options, load in when the 1 - 9 button is pressed and perform tehe corrosponding action
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

			// if null do nothing else perform the action
			if (strcmp(action, "null") == 0) {

			} else if (strcmp(action, "end") == 0) {
				return 0;
			} else {
				load_node(action);
			}
		}
	}

	// return 1 by default
	return 1;
}


/*!--------------------------------------------------------------------------
  @brief	Draws the dialog
  @return 	Void

  Draws the dialog

\-----------------------------------------------------------------------------*/
void render_dialog() {

	// draw the background images
	SSL_Image_Draw(portait, 1,2, 0,0, SDL_FLIP_NONE, game_window);
	SSL_Image_Draw(dialog_back, 0,0, 0,0, SDL_FLIP_NONE, game_window);

	// variables for the text drawing
	int i; // loop for lines
	int start_y = 150; // start y
	int y_inc = 15; // y incremental value

	// if we only have one line draw it
	if (number_of_lines == 0) {
		SSL_Font_Draw(10, start_y, 0 ,SDL_FLIP_NONE, text, (SSL_Font *)asset_manager_getFont("dialog_font"), SSL_Color_Create(0,0,0,255), game_window);
	} else {

		// else loop though the lines and draw them
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
			SSL_Font_Draw(10, start_y, 0 ,SDL_FLIP_NONE, final_text, (SSL_Font *)asset_manager_getFont("dialog_font"), SSL_Color_Create(0,0,0,255), game_window);
			start_y += y_inc;
		}
	}

	// if we have no options or there are more pages, draw the default "1..."
	if (option_count == 0 || current_page_number < number_of_pages) {
		SSL_Font_Draw(225, 14, 0 ,SDL_FLIP_NONE, "1. ...", (SSL_Font *)asset_manager_getFont("dialog_font"), SSL_Color_Create(0,0,0,255), game_window);

	// else draw the other options
	} else {
		int i;
		int y_inc = 14;

		// loop through the options and eaither draw one or two lines
		for (i = 0; i < option_count; i++) {
			char buf[100];
			if (strlen(SSL_List_Get_String(options, i)) < max_option_chars) {
				sprintf(buf, "%i. %s", i+1, SSL_String_Substring(SSL_List_Get_String(options, i), 0, strlen(SSL_List_Get_String(options, i))));
				SSL_Font_Draw(225, y_inc, 0 ,SDL_FLIP_NONE, buf, (SSL_Font *)asset_manager_getFont("dialog_font"), SSL_Color_Create(0,0,0,255), game_window);
			} else {
				sprintf(buf, "%i. %s", i+1, SSL_String_Substring(SSL_List_Get_String(options, i), 0, max_option_chars - 1));
				SSL_Font_Draw(225, y_inc, 0 ,SDL_FLIP_NONE, buf, (SSL_Font *)asset_manager_getFont("dialog_font"), SSL_Color_Create(0,0,0,255), game_window);
				y_inc+=18;
				sprintf(buf, "%s", SSL_String_Substring(SSL_List_Get_String(options, i), max_option_chars - 1, strlen(SSL_List_Get_String(options, i))));
				SSL_Font_Draw(225, y_inc, 0 ,SDL_FLIP_NONE, buf, (SSL_Font *)asset_manager_getFont("dialog_font"), SSL_Color_Create(0,0,0,255), game_window);
			}
		y_inc += 25;
		}
	}
}


/*!--------------------------------------------------------------------------
  @brief	Gets the current dialog node
  @return 	name of the current dialog node

  Gets the current dialog node

\-----------------------------------------------------------------------------*/
char *get_node_name() {
	return current_node;
}
