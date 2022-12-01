#include <list>
#include <iostream>
#include <string>

#include "rapidxml-1.13/rapidxml.hpp"

class Chunk
{
private:
    int x;
    int y;
    unsigned int width;
    unsigned int height;

    int values[16 * 16]; // TODO: Figure out to allocate dynamically. What if the chunk is not 16 x 16?

public:
    Chunk(rapidxml::xml_node<>*);
    int get_texture_at(int x, int y);
};