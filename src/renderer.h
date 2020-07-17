#pragma once
#include <cstdint>

#include "camera.h"

struct Pixel {
    uint8_t r, g, b, a;
};

class Renderer {
public:
    Renderer() { }
    ~Renderer() { }

    void render(const Camera& camera, Pixel* data, int SCREEN_WIDTH,
        int SCREEN_HEIGHT);

private:
};
