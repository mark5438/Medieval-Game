#include "mouse_wheel.hpp"

int delta = 0;

void mouse_wheel_changed(sf::Event * event)
{
    delta += event->mouseWheel.delta;
}

int get_mouse_wheel_delta()
{
    int a = delta;
    delta = 0;
    return a;
}