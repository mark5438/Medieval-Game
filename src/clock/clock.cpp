#include "clock.hpp"

sf::Clock clock_;

void init_clock()
{
    clock_.restart();
}

int get_elapsed_time()
{
    return clock_.getElapsedTime().asMilliseconds();
}