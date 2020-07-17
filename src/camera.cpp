#include "camera.h"
#include <stdexcept>

void Camera::setVertical(float value) { vertical = value; }
void Camera::setHorizontal(float value) { horizontal = value; }
void Camera::setZoom(float value)
{
    if (value <= 0) {
        throw std::runtime_error("zoom has to be positive");
    }
    zoom = value;
}

float Camera::getVertical() const { return vertical; }
float Camera::getHorizontal() const { return horizontal; }
float Camera::getZoom() const { return zoom; }