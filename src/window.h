#pragma once
#include <SDL.h>
#include "camera.h"
#include "renderer.h"

class Window {
public:
	Window(int SCREEN_WIDTH, int SCREEN_HEIGHT);
	~Window();

	void userInput();
	void render();

	void task();

	bool quit = false;
	SDL_Window* window = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;
	int frameCount = 0;

private:
	Camera camera{};
	Renderer r{};
};