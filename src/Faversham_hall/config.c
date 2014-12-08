#include "config.h"
#include "../SSL/SSL.h"

int load_config(char *path) {
	SSL_IniFile *ini = SSL_IniFIle_Create();

	if (ini == (void *)-1) {
		free(ini);
		return -1;
	}
	SSL_IniFile_Load(ini, path);

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
