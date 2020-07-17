#pragma once
#include "camera.h"
#include <cstdint>

struct Pixel {
	uint8_t r, g, b, a;
};

class Renderer {
public:
	Renderer() {}
	~Renderer() {}

	void render(const Camera& camera, Pixel* data, int SCREEN_WIDTH, int SCREEN_HEIGHT);

private:
};
