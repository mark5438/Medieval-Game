#include "npc.hpp"

NPC::NPC(int x, int y, int initialization_tile)
{
    this->position.x = x;
    this->position.y = y;

    switch (initialization_tile)
    {
        case CHICKEN_NPC_NUMBER:
            this->animation = new NPC_Animation_Generic_Animal(
                CHICKEN_NPC_WALK_WEST_TILE_ID,
                CHICKEN_NPC_WALK_NORTH_TILE_ID,
                CHICKEN_NPC_WALK_EAST_TILE_ID,
                CHICKEN_NPC_WALK_SOUTH_TILE_ID
            );
        break;
    }
}

NPC_Animation_Generic_Animal::NPC_Animation_Generic_Animal(int w, int n, int e, int s)
{
    this->walk_west_tile = w;
    this->walk_north_tile = n;
    this->walk_east_tile = e;
    this->walk_south_tile = s;
}