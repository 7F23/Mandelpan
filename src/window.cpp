#include "window.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

constexpr int screenhz = 60;

Window::Window(int SCREEN_WIDTH, int SCREEN_HEIGHT) {

	window = SDL_CreateWindow(
		"Mandelpan",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
	if (window == nullptr) {
		fprintf(stderr, "could not create window: %s\n", SDL_GetError());

	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
}

Window::~Window() {
	SDL_DestroyWindow(window);
}

void Window::userInput() {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}

		if (e.type == SDL_KEYDOWN)
		{
			//Set the proper message surface
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				camera.setVertical(camera.getVertical() + 0.1/camera.getZoom());
				break;
			case SDLK_DOWN:
				camera.setVertical(camera.getVertical() - 0.1/camera.getZoom());
				break;
			case SDLK_LEFT:
				camera.setHorizontal(camera.getHorizontal() - 0.1/camera.getZoom());
				break;
			case SDLK_RIGHT:
				camera.setHorizontal(camera.getHorizontal() + 0.1/camera.getZoom());
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


void Window::render() {
	int SCREEN_WIDTH, SCREEN_HEIGHT;
	SDL_QueryTexture(texture, NULL, NULL, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	std::vector<Pixel> pixels(SCREEN_WIDTH * SCREEN_HEIGHT);

	//render
	r.render(camera, &pixels[0], SCREEN_WIDTH, SCREEN_HEIGHT);

	//updating and blitting the texture
	SDL_UpdateTexture(texture, NULL, &pixels[0], SCREEN_WIDTH * sizeof(Pixel));
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Window::task() {
	auto time_between_two_frames = std::chrono::milliseconds(1000 / screenhz);

	frameCount = 0;
	while (quit == false) {
		auto t0 = std::chrono::system_clock::now();

		// handle user input 
		userInput();

		// give output in graphics
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
