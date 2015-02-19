/*-------------------------------------------------------------------------*/
/**
   @file    config.c
   @author  P. Batty
   @brief   Implements a the configuration system for the game

   This module implements the configuration system for the game. Loads the ini
   located at the path specified.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/
#include "config.h"
#include "../SSL/SSL.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_Mixer.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

/*----------------------------------
      Declare globals
 ----------------------------------*/


char *CONFIG_PATH;
char *WINDOW_TITLE;
int WINDOW_WIDTH;
int WINDOW_HEIGHT;
int WINDOW_RES_WIDTH;
int WINDOW_RES_HEIGHT;
int MAX_TICKS_PER_SECOND;
int TEXTURE_SCALING;
int VSYNC;
int WINDOWED;
int BORDERLESS;
char *UP_KEY;
char *DOWN_KEY;
char *LEFT_KEY;
char *RIGHT_KEY;
char *INTERACT_KEY;
char *PAUSE_KEY;
char *MUTE_KEY;
int  MUSIC_VOL;
int  SFX_VOL;

int MUTE;


/*----------------------------------
      Default values to use.
 ----------------------------------*/

static int SECTION_COUNT = 2;

static char *title_default = "Faversham Hall";
static int window_width_default = 800;
static int window_height_default = 600;

static int window_res_width_default = 320;
static int window_res_height_default = 240;

static int max_ticks_per_second_default = 60;
static int smooth_texture_scaling_default = 0;
static int vsync_default = 0;
static int windowed_default = 1;
static int borderless_default = 0;

static int music_volume_default = 50;
static int sfx_volume_default = 100;


static char *up_key_default = "_w";
static char *down_key_default = "_s";
static char *left_key_default = "_a";
static char *right_key_default = "_d";
static char *interact_key_default = "_e";
static char *pause_key_defualt = "_esc";
static char *mute_key_defualt = "_m";


/*----------------------------------
      Prints to file
 ----------------------------------*/

static void print_display_block(FILE *file) {
	fprintf(file,
		"[display]\n\n"
		"title = \"%s\"\t; title of the window\n"
		"window_width = %i\t; width of the window\n"
		"window_height = %i\t; height of the window\n"
		"window_res_width = %i\t; resolution width\n"
		"window_res_height = %i\t; resolution height\n\n"
		,title_default
		,window_width_default
		,window_height_default
		,window_res_width_default
		,window_res_height_default
	);
}


/*----------------------------------
 ----------------------------------*/

static void print_game_block(FILE *file) {
	fprintf(file,
	"[game]\n\n"
	"max_ticks_per_second = %i\t; number of logic updates per second\n"
	"smooth_texture_scaling = %i\t; 0 = nearest	1 = linear    2 = anisotropic\n"
	"vsync = %i\t; 0 = off    1 = on\n"
	"windowed = %i\t; 0 = full screen    1 = windowed\n"
	"borderless = %i\t; 0 = border    1 = no borders\n"
	"music_volume = %i\t; music volume\n"
	"sfx_volume = %i\t ; sfx volume\n"
	,max_ticks_per_second_default
	,smooth_texture_scaling_default
	,vsync_default
	,windowed_default
	,borderless_default
	,music_volume_default
	,sfx_volume_default
	);
}


/*----------------------------------
 ----------------------------------*/

static void print_key_block(FILE *file) {
	fprintf(file,
	"[keys]\n; All keys start with a _ followed by the key name e.g _1, _e ect. \n\n"
	"up_key = %s\t; movement up key\n"
	"down_key = %s\t; movement down key\n"
	"left_key = %s\t; movement left key\n"
	"right_key = %s\t; movement right key\n"
	"interact_key = %s\t; interaction key\n"
	"pause_key = %s\t; pause key\n"
	"mute_key = %s\t ; the mute key\n"
	,up_key_default
	,down_key_default
	,left_key_default
	,right_key_default
	,interact_key_default
	,pause_key_defualt
	,mute_key_defualt
	);
}


/*----------------------------------
 ----------------------------------*/

static int create_config() {
	FILE *file = fopen(CONFIG_PATH, "a");

	if (!file) {
		return -1;
	}

	print_display_block(file);
	print_game_block(file);
	print_key_block(file);

	fclose(file);
	return 0;
}


/*----------------------------------
      checks for valid sections
 ----------------------------------*/

static void check_sections_exit(SSL_IniFile *ini) {
	int i;
	for (i = 0; i <= SECTION_COUNT; i++) {
		if(!SSL_Inifile_GetSection_Name(ini, i)) {
			FILE *file = fopen(CONFIG_PATH, "a");
			fprintf(file,"\n");
			if (i == 0) {
				print_display_block(file);
			} else if (i == 1) {
				print_game_block(file);
			} else if (i == 2) {
				print_key_block(file);
			}
			fclose(file);
		}
	}
}


/*----------------------------------
      Reads the file
 ----------------------------------*/

static void read_display_section(SSL_IniFile *ini) {
	WINDOW_TITLE = SSL_IniFile_GetString(ini, "display", "title", (void *)-1);
	if (WINDOW_TITLE == (void *)-1) {
		WINDOW_TITLE = title_default;
		SSL_Log_Write("Error: ini missing window_title, reverting to default!");
	}

	WINDOW_WIDTH = SSL_IniFile_GetInt(ini, "display", "window_width", (int)-1);
	if (WINDOW_WIDTH == -1) {
		WINDOW_WIDTH = window_width_default;
		SSL_Log_Write("Error: ini missing window_width, reverting to default!");
	}

	WINDOW_HEIGHT = SSL_IniFile_GetInt(ini, "display", "window_height", (int)-1);
	if (WINDOW_HEIGHT == -1) {
		WINDOW_HEIGHT = window_height_default;
		SSL_Log_Write("Error: ini missing window_height, reverting to default!");
	}

	WINDOW_RES_WIDTH = SSL_IniFile_GetInt(ini, "display", "window_res_width", (int)-1);
	if (WINDOW_RES_WIDTH == -1) {
		WINDOW_RES_WIDTH = window_res_width_default;
		SSL_Log_Write("Error: ini missing window_res_width, reverting to default!");
	}

	WINDOW_RES_HEIGHT = SSL_IniFile_GetInt(ini, "display", "window_res_height", (int)-1);
	if (WINDOW_RES_HEIGHT == -1) {
		WINDOW_RES_HEIGHT = window_res_height_default;
		SSL_Log_Write("Error: ini missing window_res_height, reverting to default!");
	}
}


/*----------------------------------
 ----------------------------------*/

static void read_game_section(SSL_IniFile *ini) {
	MAX_TICKS_PER_SECOND = SSL_IniFile_GetInt(ini, "game", "max_ticks_per_second", (int)-1);
	if (MAX_TICKS_PER_SECOND == -1) {
		MAX_TICKS_PER_SECOND = max_ticks_per_second_default;
		SSL_Log_Write("Error: ini missing max_ticks_per_second, reverting to default!");
	}

	TEXTURE_SCALING = SSL_IniFile_GetInt(ini, "game", "smooth_texture_scaling", (int)-1);
	if (TEXTURE_SCALING == -1) {
		TEXTURE_SCALING = smooth_texture_scaling_default;
		SSL_Log_Write("Error: ini missing smooth_texture_scaling, reverting to default!");
	}

	VSYNC = SSL_IniFile_Getboolean(ini, "game", "vsync", (int)-1);
	if (VSYNC == -1) {
		VSYNC = vsync_default;
		SSL_Log_Write("Error: ini missing vsync, reverting to default!");
	}

	WINDOWED = SSL_IniFile_Getboolean(ini, "game", "windowed", (int)-1);
	if (WINDOWED == -1) {
		WINDOWED = windowed_default;
		SSL_Log_Write("Error: ini missing windowed, reverting to default!");
	}

	BORDERLESS = SSL_IniFile_Getboolean(ini, "game", "borderless", (int)-1);
	if (BORDERLESS == -1) {
		BORDERLESS = borderless_default;
		SSL_Log_Write("Error: ini missing borderless, reverting to default!");
	}

	MUSIC_VOL = SSL_IniFile_GetInt(ini, "game", "music_volume", (int)-1);
	if (MUSIC_VOL == -1) {
		MUSIC_VOL = music_volume_default;
		SSL_Log_Write("Error: ini missing music volume, reverting to default!");
	}
	Mix_VolumeMusic(MUSIC_VOL);

	SFX_VOL = SSL_IniFile_GetInt(ini, "game", "sfx_volume", (int)-1);
	if (SFX_VOL == -1) {
		SFX_VOL = sfx_volume_default;
		SSL_Log_Write("Error: ini missing sfx volume, reverting to default!");
	}
	Mix_Volume(-1, SFX_VOL);
}

/*----------------------------------
 ----------------------------------*/

static void read_key_section(SSL_IniFile *ini) {
	UP_KEY = SSL_IniFile_GetString(ini, "keys", "up_key", (char *)-1);
	if (UP_KEY == (char *)-1) {
		UP_KEY = up_key_default;
		SSL_Log_Write("Error: ini missing up_key, reverting to default!");
	}

	DOWN_KEY = SSL_IniFile_GetString(ini, "keys", "down_key", (char *)-1);
	if (DOWN_KEY == (char *)-1) {
		DOWN_KEY = down_key_default;
		SSL_Log_Write("Error: ini missing down_key, reverting to default!");
	}

	LEFT_KEY = SSL_IniFile_GetString(ini, "keys", "left_key", (char *)-1);
	if (LEFT_KEY == (char *)-1) {
		LEFT_KEY = left_key_default;
		SSL_Log_Write("Error: ini missing left_key, reverting to default!");
	}

	RIGHT_KEY = SSL_IniFile_GetString(ini, "keys", "right_key", (char *)-1);
	if (RIGHT_KEY == (char *)-1) {
		RIGHT_KEY = right_key_default;
		SSL_Log_Write("Error: ini missing left_key, reverting to default!");
	}

	INTERACT_KEY = SSL_IniFile_GetString(ini, "keys", "interact_key", (char *)-1);
	if (INTERACT_KEY == (char *)-1) {
		INTERACT_KEY = interact_key_default;
		SSL_Log_Write("Error: ini missing interact_key, reverting to default!");
	}

	PAUSE_KEY = SSL_IniFile_GetString(ini, "keys", "pause_key", (char *)-1);
	if (PAUSE_KEY == (char *)-1) {
		PAUSE_KEY = pause_key_defualt;
		SSL_Log_Write("Error: ini missing pause_key, reverting to default!");
	}

	MUTE_KEY = SSL_IniFile_GetString(ini, "keys", "mute_key", (char *)-1);
	if (MUTE_KEY == (char *)-1) {
		MUTE_KEY = mute_key_defualt;
		SSL_Log_Write("Error: ini missing mute_key, reverting to default!");
	}
}


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	Loads the config file for the program.
  @param    path		 path to the file.
  @return 	0 on success -1 on error

  Loads the config file for the program. and fill in the variables located in
  this header file. returns 0 on success -1 on error


\-----------------------------------------------------------------------------*/
int load_config(char *path) {
	CONFIG_PATH = path;								// set the path
	SSL_IniFile *ini = SSL_IniFIle_Create();		// create the ini reader

	if (ini == (void *)-1) {						// check it was created
		free(ini);
		return -1;
	}
	if (access(CONFIG_PATH, F_OK) == -1) {			// check the config file exits
		create_config();							// else make it
	}

	SSL_IniFile_Load(ini, path);					// load it

	if (ini->dictionary == NULL) {					// make sure it was loaded
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Config", "Could not create or read config file.", NULL);
		return -1;
	}

	check_sections_exit(ini);						// check all sections exist

	read_display_section(ini);						// read in the sections
	read_game_section(ini);
	read_key_section(ini);

	return 0;
}
