#ifndef CONFIG_H_
#define CONFIG_H_

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

int load_config(char *path);

#endif
