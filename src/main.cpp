#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "window.h"

constexpr int SCREEN_WIDTH = 854, SCREEN_HEIGHT = 480;

void openMandelbrotWindow()
{
    Window mandelbrot_window(SCREEN_WIDTH, SCREEN_HEIGHT);
    mandelbrot_window.task();
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "could not initialize sdl2:"
                  << SDL_GetError() << std::endl;
        return 1;
    }

    openMandelbrotWindow();

    std::cout << "exiting Mandelpan" << std::endl;
    SDL_Quit();
    return 0;
}