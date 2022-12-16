/**
 * File in charge of keeping time
*/

#include <SFML/Graphics.hpp>

/**
 * Initialize clock object.
 * Starting at 0ms
*/
void init_clock();

/**
 * Get elapsed time since init_clock call
 * 
 * @return Elapsed time in miliseconds as integer
*/
int get_elapsed_time();