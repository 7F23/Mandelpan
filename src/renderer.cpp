#include "renderer.h"

#include <complex>

#include "camera.h"

constexpr int MAX_ITERATIONS = 60;

static std::complex<double> mandelbrot_function(std::complex<double> c,
    std::complex<double> z)
{
    return z * z + c;
}

static bool mandelbrot_convergence(std::complex<double> c, int& iterations)
{
    std::complex<double> z = { 0.0, 0.0 };
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        z = mandelbrot_function(c, z);
        if (std::abs(z) > 2) {
            iterations = i;
            return false;
        }
    }
    return true;
}

static std::complex<double> pixel_to_complex(const Camera& camera, int w, int h,
    int x, int y)
{
    double ratio = (double)w / h;

    // compute relative coordinates in range [-1, 1]^2
    double rx = (2.0 * x) / w - 1;
    double ry = 1 - (2.0 * y / h);

    return { (ratio * rx + camera.getHorizontal()) / camera.getZoom(),
        (ry + camera.getVertical()) / camera.getZoom() };
}

void Renderer::render(const Camera& camera, Pixel* data, int width,
    int height)
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int iter = 0;
            auto c = pixel_to_complex(camera, width, height, x, y);
            bool convergence = mandelbrot_convergence(c, iter);
            Pixel pixel;
            if (convergence == true) {
                pixel = Pixel { 0, 0, 0, 255 };
            } else {
                uint8_t color = 255 - iter * 4;
                pixel = Pixel { color, color, color, 255 };
            }
            data[y * width + x] = pixel;
        }
    }
}