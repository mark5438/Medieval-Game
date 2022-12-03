#include "camera.hpp"

int x = 0, y = 0;
float zoom = 1;

int speed_factor = 4;

void camera_check_keyboard()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        move_camera_y(-speed_factor);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        move_camera_y(speed_factor);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        move_camera_x(-speed_factor);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        move_camera_x(speed_factor);
    }
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
    zoom += delta;
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