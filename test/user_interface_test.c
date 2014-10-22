#include "tests.h"
#include "../src/game_api/graphics/sdl_window.h"
#include "../src/game_api/graphics/sdl_font.h"
#include "../src/game_api/misc/sdl_color.h"
#include "../src/game_api/misc/sdl_rect.h"
#include "../src/game_api/gui/interface.h"
#include "../src/game_api/gui/button.h"
#include <stdio.h>

void user_interface_test() {
	SDL_Init(SDL_INIT_EVERYTHING);

	Window *window = window_create("This is the Sdl user interface test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
	Interface *interface = interface_create();

	Text_Button *text_button = text_button_create(rect_create(100, 100, 150, 50), font_load("../extras/resources/debug.ttf", 50), color_create(255,255,255,255), color_create(255,0,0,255), "button?");
	Image_Button *image_button = image_button_create(rect_create(100, 200, 100, 100), image_load("../extras/resources/test_image.png", 100, 100, window), 0, 2);

	interface_add_text_button(interface, text_button);
	interface_add_image_button(interface, image_button);


		SDL_Event event;
		int running = 1;

		while(running) {
			SDL_PumpEvents();
			SDL_RenderPresent(window->renderer);
			SDL_RenderClear( window->renderer );

			interface_draw(interface, window);
			interface_update(interface, event);

			if (text_button->button_status->pressed) {
				text_button->button_text_info->background_color = color_create(0, 0, 255 ,255);
			} else if (text_button->button_status->hovered) {
				text_button->button_text_info->background_color = color_create(0, 255, 0 ,255);
			} else {
				text_button->button_text_info->background_color = color_create(255, 0, 0 ,255);
			}

			if (text_button->button_status->clicked) {
				text_button->button_text_info->text = "Clicked!";
			}
			while (SDL_PollEvent(&event))
			 {
			    if (event.type == SDL_QUIT) {
			    	running = 0;
			    	break;
			    }
			 }
		}

	    SDL_Quit();

 printf("\n Sdl user interface passed...\n");
}
