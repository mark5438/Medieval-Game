/**
 * File in charge of keeping camera values such as position and zoom
 * 
 * When drrawing the game, these values will be used,
 * to determine what tiles should be drawn
 * How big they should be drawn, and the offset they should be drawn with
*/

#include <SFML/Graphics.hpp>

#include "mouse_wheel/mouse_wheel.hpp"

/**
 * In charge of checking keyboard and mouse events
 * that can change the cameras position or zoom factor.
*/
void camera_check_hid_events();

/**
 * Get the cameras position along the x-axis
 * 
 * @return The camras x position as integer
*/
int get_camera_x();

/**
 * Get the cameras position along the y-axis
 * 
 * @return The cameras y position as integer
*/
int get_camera_y();

/**
 * Get the cameras zoom factor
 * 
 * @return Zoom factor as floating point
*/
float get_camera_zoom();

/**
 * Move the camera along the x axis.
 * Is almost exlusively called from camera.cpp
 * 
 * @param delta Defines how much the camera is moved
*/
int move_camera_x(int);

/**
 * Move the camera along the y axis.
 * Is almost exlusively called from camera.cpp
 * 
 * @param delta Defines how much the camera is moved
*/
int move_camera_y(int);

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
float change_camera_zoom(float);

/**
 * Set the camera's x position. Useful if a new scene is loaded,
 * and the camera is set to start at a specific position.
 * 
 * @param newX The new camera x position
*/
void set_camera_x(int);

/**
 * Set the camera's y position. Useful if a new scene is loaded,
 * and the camera is set to start at a specific position.
 * 
 * @param newY the new camera y position
*/
void set_camera_y(int);

/**
 * Set the camera's x and y position. Useful if a new scene is loaded,
 * and the camera is set to start at a specific position.
 * 
 * @param newX The new camera x position
 * @param newY The new camera y position
*/
void set_camera_position(int, int);

/**
 * Set the camera zoom to a specific value
 * 
 * @param zoom New zoom factor
*/
void set_camera_zoom(float);

/**
 * Set camera zoom to default value.
 * Same as set_camera_zoom(1)
*/
void reset_camera_zoom();