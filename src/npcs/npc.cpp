#include "npc.hpp"

#include <iostream>

NPC::NPC(int x, int y, int initialization_tile)
{
    this->position.x = x;
    this->position.y = y;

    std::cout << initialization_tile << std::endl;
}

NPC_Animation_Generic_Animal::NPC_Animation_Generic_Animal(int w, int n, int e, int s)
{
    this->walk_west_tile = w;
    this->walk_north_tile = n;
    this->walk_east_tile = e;
    this->walk_south_tile = s;
}