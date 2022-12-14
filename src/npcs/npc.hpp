#include <SFML/System/Vector2.hpp>

#define CHICKEN_NPC_NUMBER 6405

#ifndef NPC_TYPE
#define NPC_TYPE

class NPC
{
private:
    sf::Vector2<int> position;
    sf::Vector2<int> tile_offset;

public:
    NPC(int, int);
    int get_sprite_id() { return CHICKEN_NPC_NUMBER; }
    int get_x() { return this->position.x; }
    int get_y() { return this->position.y; }

};

#endif // NPC_TYPE