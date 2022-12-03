#include <list>
#include <iostream>

#include <rapidxml.hpp>

#include "chunk.hpp"

class Layer
{
private:
    unsigned int id;
    unsigned int width;
    unsigned int height;

    std::list<Chunk *> chunks;

public:
    Layer(rapidxml::xml_node<> *);
    int get_texture_at(int x, int y);
    void draw_layer();

    int get_id(){return this->id;}
};