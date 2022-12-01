#include <list>
#include <iostream>

#include "rapidxml-1.13/rapidxml.hpp"

#include "chunk.hpp"

class Layer
{
private:
    unsigned int id;
    unsigned int width;
    unsigned int height;

    std::list<Chunk*> chunks;

public:
    Layer(rapidxml::xml_node<>*);
    int get_texture_at(int x, int y);
};