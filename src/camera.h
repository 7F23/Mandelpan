#pragma once

class Camera {
public:
    Camera(float v = 0.0f, float h = 0.0f, float z = 1.0f)
        : vertical(v)
        , horizontal(h)
        , zoom(z)
    {
    }
    ~Camera() { }

    void setVertical(float value);
    void setHorizontal(float value);
    void setZoom(float value);

    float getVertical() const;
    float getHorizontal() const;
    float getZoom() const;

private:
    float vertical;
    float horizontal;
    float zoom;
};
