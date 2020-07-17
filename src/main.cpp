#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "window.h"

constexpr int SCREEN_WIDTH = 854, SCREEN_HEIGHT = 480;



int main() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}

	Window mandelbrot_window(SCREEN_WIDTH, SCREEN_HEIGHT);
	mandelbrot_window.task();

	std::cout << "exiting Mandelpan" << std::endl;
	SDL_Quit();
	return 0;
}