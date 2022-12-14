/**
 * File in charge of keeping camera values such as position and zoom
 * 
 * When drrawing the game, these values will be used,
 * to determine what tiles should be drawn
 * How big they should be drawn, and the offset they should be drawn with
*/


#include "camera.hpp"

/**
 * Cameras default values
*/
signed int x = 0, y = 0;
float zoom = 1;

/**
 * The camera's speed factor is the number added to the camera's position
 * each frame where the camera is moving, if zoom = 1
*/
#define SPEED_FACTOR 4

/**
 * The zoom_delta is multiplied by the ZOOM_FACTOR to slow down
 * the change in zoom
*/
#define ZOOM_FACTOR 0.04f

/**
 * See if the mousewheel has moved,
 * and zoom accorcingly
*/
void check_mouse()
{
    change_camera_zoom(get_mouse_wheel_delta());
    //TODO: Move camera so that you zoom in on the mouse, instead of top left corner
}

/**
 * See if any keys that affect the camera position is pressed.
 * If so, the camera should move.
 * 
 * The camera is moved by the constant speed factor multiplied with the zoom.
 * 
 * If the camera is zoomed in, the tiles will appear bigger on the screen.
 * Therefor the camera has to move more pixels in order to feel responsive
*/
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

/**
 * In charge of checking keyboard and mouse events
 * that can change the cameras position or zoom factor.
*/
void camera_check_hid_events()
{
    check_keyboard();
    check_mouse();
}

/**
 * Get the cameras position along the x-axis
 * 
 * @return The camras x position as integer
*/
int get_camera_x()
{
    return x;
}

/**
 * Get the cameras position along the y-axis
 * 
 * @return The cameras y position as integer
*/
int get_camera_y()
{
    return y;
}

/**
 * Get the cameras zoom factor
 * 
 * @return Zoom factor as floating point
*/
float get_camera_zoom()
{
    return zoom;
}

/**
 * Move the camera along the x axis.
 * Is almost exlusively called from camera.cpp
 * 
 * @param delta Defines how much the camera is moved
*/
int move_camera_x(int delta)
{
    x += delta;
    return x;
}

/**
 * Move the camera along the y axis.
 * Is almost exlusively called from camera.cpp
 * 
 * @param delta Defines how much the camera is moved
*/
int move_camera_y(int delta)
{
    y += delta;
    return y;
}

/**
 * Change the camera zoom factor, by a floating point.
 * 
 * Note that the change is non-linear. How much the delta
 * affects the zoom depends on the zoom factor before this function call.
 * 
 * @param delta How much the zoom should be changed. The mousewheel delta
 *              can be passed directly.
 * 
 * @return The new zoom factor
*/
float change_camera_zoom(float delta)
{
    zoom += delta * ZOOM_FACTOR * zoom;
    return zoom;
}

/**
 * Set the camera's x position. Useful if a new scene is loaded,
 * and the camera is set to start at a specific position.
 * 
 * @param newX The new camera x position
*/
void set_camera_x(int x_)
{
    x = x_;
}

/**
 * Set the camera's y position. Useful if a new scene is loaded,
 * and the camera is set to start at a specific position.
 * 
 * @param newY the new camera y position
*/
void set_camera_y(int y_)
{
    y = y_;
}

/**
 * Set the camera's x and y position. Useful if a new scene is loaded,
 * and the camera is set to start at a specific position.
 * 
 * @param newX The new camera x position
 * @param newY The new camera y position
*/
void set_camera_position(int x, int y)
{
    set_camera_x(x);
    set_camera_y(y);
}

/**
 * Set the camera zoom to a specific value
 * 
 * @param zoom New zoom factor
*/
void set_camera_zoom(float zoom_)
{
    zoom = zoom_;
}

/**
 * Set camera zoom to default value.
 * Same as set_camera_zoom(1)
*/
void reset_camera_zoom()
{
    set_camera_zoom(1);
}