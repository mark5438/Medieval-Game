#include "clock.hpp"

sf::Clock clock;

void init_clock()
{
    clock.restart();
}

int get_elapsed_time()
{
    return clock.getElapsedTime().asMilliseconds();
}