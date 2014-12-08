#include "config.h"
#include "../SSL/SSL.h"

static char *title_default = "this is the window title";
static int window_width_default = 800;
static int window_height_default = 600;

static int window_res_width_default = 800;
static int window_res_height_default = 600;

static int max_ticks_per_second_default = 60;
static int smooth_texture_scaling_default =2;
static int vsync_default = 0;
static int windowed_default = 1;
static int borderless_default = 0;

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

static void print_game_block(FILE *file) {
	fprintf(file,
	"[game]\n\n"
	"max_ticks_per_second = %i\t; number of logic updates per second\n"
	"smooth_texture_scaling = %i\t; 0 = nearest	1 = linear    2 = anisotropic\n"
	"vsync = %i\t; 0 = off    1 = on\n"
	"windowed = %i\t; 0 = full screen    1 = windowed\n"
	"borderless = %i\t; 0 = border    1 = has borders\n"
	,max_ticks_per_second_default
	,smooth_texture_scaling_default
	,vsync_default
	,windowed_default
	,borderless_default
	);
}

static int create_config() {
	FILE *file = fopen(CONFIG_PATH, "a");

	if (!file) {
		return -1;
	}

	print_display_block(file);
	print_game_block(file);

	fclose(file);
	return 0;
}

int load_config(char *path) {
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
		return -1;
	}
													// read in the information
	WINDOW_TITLE = SSL_IniFile_GetString(ini, "display", "title", NULL);

	WINDOW_WIDTH = SSL_IniFile_GetInt(ini, "display", "window_width", (int)NULL);
	WINDOW_HEIGHT = SSL_IniFile_GetInt(ini, "display", "window_height", (int)NULL);
	WINDOW_RES_WIDTH = SSL_IniFile_GetInt(ini, "display", "window_res_width", (int)NULL);
	WINDOW_RES_HEIGHT = SSL_IniFile_GetInt(ini, "display", "window_res_height", (int)NULL);

	MAX_TICKS_PER_SECOND = SSL_IniFile_GetInt(ini, "game", "max_ticks_per_second", (int)NULL);
	TEXTURE_SCALING = SSL_IniFile_GetInt(ini, "game", "smooth_texture_scaling", (int)NULL);
	VSYNC = SSL_IniFile_GetInt(ini, "game", "vsync", (int)NULL);
	WINDOWED = SSL_IniFile_GetInt(ini, "game", "windowed", (int)NULL);
	BORDERLESS = SSL_IniFile_GetInt(ini, "game", "borderless", (int)NULL);

	return 0;
}
