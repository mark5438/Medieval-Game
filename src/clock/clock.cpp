/**
 * File in charge of keeping time
*/

#include "clock.hpp"

sf::Clock clock_;

/**
 * Initialize clock object.
 * Starting at 0ms
*/
void init_clock()
{
    clock_.restart();
}

/**
 * Get elapsed time since init_clock call
 * 
 * @return Elapsed time in miliseconds as integer
*/
int get_elapsed_time()
{
    return clock_.getElapsedTime().asMilliseconds();
}