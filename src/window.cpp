#include "window.h"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

constexpr int SCREEN_HZ = 60;

Window::Window(int width, int height)
{
    window = SDL_CreateWindow("Mandelpan", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width,
        height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "could not create sdl2 window:"
                  << SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING, width,
        height);
}

Window::~Window()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Window::userInput()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        // User requests quit
        if (e.type == SDL_QUIT) {
            quit = true;
        }

        if (e.type == SDL_KEYDOWN) {
            // Set the proper message surface
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                camera.setVertical(camera.getVertical() + 0.1 / camera.getZoom());
                break;
            case SDLK_DOWN:
                camera.setVertical(camera.getVertical() - 0.1 / camera.getZoom());
                break;
            case SDLK_LEFT:
                camera.setHorizontal(camera.getHorizontal() - 0.1 / camera.getZoom());
                break;
            case SDLK_RIGHT:
                camera.setHorizontal(camera.getHorizontal() + 0.1 / camera.getZoom());
                break;
            case SDLK_e:
                camera.setZoom(camera.getZoom() * 1.5);
                break;
            case SDLK_q:
                camera.setZoom(camera.getZoom() / 1.5);
                break;
            }
        }
    }
}

void Window::render()
{
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    std::vector<Pixel> pixels(size_t(width) * size_t(height));

    // render
    r.render(camera, &pixels[0], width, height);

    // updating and blitting the texture
    SDL_UpdateTexture(texture, nullptr, &pixels[0], width * sizeof(Pixel));
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void Window::task()
{
    auto time_between_two_frames = std::chrono::milliseconds(1000 / SCREEN_HZ);

    frameCount = 0;
    while (quit == false) {
        auto t0 = std::chrono::system_clock::now();

        // handle user input
        userInput();

        // render fractal
        render();

        auto t1 = std::chrono::system_clock::now();
        auto dt = t1 - t0;

        // sleep current thread until next interval
        if (dt < time_between_two_frames) {
            std::this_thread::sleep_for(time_between_two_frames - dt);
        }

        frameCount += 1;
    }
}
