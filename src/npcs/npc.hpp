#include <SFML/System/Vector2.hpp>

#define CHICKEN_NPC_NUMBER 6401
#define CHICKEN_NPC_WALK_WEST_TILE_ID 6404
#define CHICKEN_NPC_WALK_NORTH_TILE_ID 6408
#define CHICKEN_NPC_WALK_EAST_TILE_ID 64012
#define CHICKEN_NPC_WALK_SOUTH_TILE_ID 64016

#ifndef NPC_TYPE
#define NPC_TYPE

/**
 * Interface class for all NPC animations. Each NPC objects hold an object of this type,
 * That it uses to get the right animations.
 *
 * For each NPC a subclass of NPC_Animation is needed
 */
class NPC_Animation
{
public:
    virtual int get_walking_west_sprite_id() { return 0; }
    virtual int get_walking_north_sprite_id() { return 0; }
    virtual int get_walking_east_sprite_id() { return 0; }
    virtual int get_walking_south_sprite_id() { return 0; }
};

/**
 * Implementation of NPC_Animation, for animals that can only walk.
*/
class NPC_Animation_Generic_Animal : public NPC_Animation
{
private:
    int walk_west_tile;
    int walk_north_tile;
    int walk_east_tile;
    int walk_south_tile;

public:
    NPC_Animation_Generic_Animal(int, int, int, int);
    int get_walking_west_sprite_id() { return this->walk_west_tile; }
    int get_walking_north_sprite_id() { return this->walk_north_tile; }
    int get_walking_east_sprite_id() { return this->walk_east_tile; }
    int get_walking_south_sprite_id() { return this->walk_south_tile; }
};

class NPC
{
private:
    sf::Vector2<int> position;
    sf::Vector2<int> tile_offset;

    NPC_Animation * animation;

public:
    NPC(int, int, int);
    int get_sprite_id() { return animation->get_walking_north_sprite_id(); }
    int get_x() { return this->position.x; }
    int get_y() { return this->position.y; }
};

#endif // NPC_TYPE