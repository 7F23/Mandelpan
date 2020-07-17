#include "renderer.h"

#include <complex>

#include "camera.h"

constexpr int maxiterations = 60;

static std::complex<double> mandelbrotfunction(std::complex<double> c,
    std::complex<double> z)
{
    return z * z + c;
}

static bool mandelbrotconvergence(std::complex<double> c, int& iterations)
{
    std::complex<double> z = { 0.0, 0.0 };
    for (int i = 0; i < maxiterations; i++) {
        z = mandelbrotfunction(c, z);
        if (std::abs(z) > 2) {
            iterations = i;
            return false;
        }
    }
    return true;
}

static std::complex<double> pixeltocomplex(const Camera& camera, int w, int h,
    int x, int y)
{
    double ratio = (double)w / h;

    // compute relative coordinates in range [-1, 1]^2
    double rx = (2.0 * x) / w - 1;
    double ry = 1 - (2.0 * y / h);

    return { (ratio * rx + camera.getHorizontal()) / camera.getZoom(),
        (ry + camera.getVertical()) / camera.getZoom() };
}

void Renderer::render(const Camera& camera, Pixel* data, int SCREEN_WIDTH,
    int SCREEN_HEIGHT)
{
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            int iter = 0;
            auto c = pixeltocomplex(camera, SCREEN_WIDTH, SCREEN_HEIGHT, x, y);
            bool convergence = mandelbrotconvergence(c, iter);
            Pixel pixel;
            if (convergence == true) {
                pixel = Pixel { 0, 0, 0, 255 };
            } else {
                uint8_t color = 255 - iter * 4;
                pixel = Pixel { color, color, color, 255 };
            }
            data[y * SCREEN_WIDTH + x] = pixel;
        }
    }
}