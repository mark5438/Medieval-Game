/**
 * File in charge of saving mouse wheel data.
 * Whenever a new mousewheel event occurs,
 * the function mouse_wheel_changed should be called
 * with that event as a parameter. A delta variable is the modified.
 * Whenever the delta variable has been read using function int get_mouse_wheel_delta,
 * The variable will be set to 0, until new mouse wheel events occur
 * 
*/

#include <SFML/Window/Event.hpp>

/**
 * Modifies the mousewheel delta variable according to the passed event.
 * 
 * @param event The mousewheel event
*/
void mouse_wheel_changed(sf::Event* event);

/**
 * Returns the mouse wheel delta and sets it to 0
 * @return The mousewheel delta since last time this function was called
*/
int get_mouse_wheel_delta();