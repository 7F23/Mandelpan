#include "camera.h"

void Camera::setVertical(float value) { vertical = value; }
void Camera::setHorizontal(float value) { horizontal = value; }
void Camera::setZoom(float value) { zoom = value; }

float Camera::getVertical() const { return vertical; }
float Camera::getHorizontal() const { return horizontal; }
float Camera::getZoom() const { return zoom; }