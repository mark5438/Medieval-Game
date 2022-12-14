#include "camera.hpp"

int x = 0, y = 0;
float zoom = 1;

#define SPEED_FACTOR 4
#define ZOOM_FACTOR 0.04f

void check_mouse()
{
    change_camera_zoom(get_mouse_wheel_delta());
    //TODO: Move camera so that you zoom in on the mouse, instead of top left corner
}

void check_keyboard()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        move_camera_y(-SPEED_FACTOR * zoom);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        move_camera_y(SPEED_FACTOR * zoom);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        move_camera_x(-SPEED_FACTOR * zoom);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        move_camera_x(SPEED_FACTOR * zoom);
    }
}

void camera_check_hid_events()
{
    check_keyboard();
    check_mouse();
}

int get_camera_x()
{
    return x;
}

int get_camera_y()
{
    return y;
}

float get_camera_zoom()
{
    return zoom;
}

int move_camera_x(int delta)
{
    x += delta;
    return x;
}

int move_camera_y(int delta)
{
    y += delta;
    return y;
}

float change_camera_zoom(float delta)
{
    zoom += delta * ZOOM_FACTOR * zoom;
    return zoom;
}

void set_camera_x(int x_)
{
    x = x_;
}

void set_camera_y(int y_)
{
    y = y_;
}

void set_camera_zoom(float zoom_)
{
    zoom = zoom_;
}