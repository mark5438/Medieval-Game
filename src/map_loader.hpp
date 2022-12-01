#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include "rapidxml-1.13/rapidxml.hpp"

#include "tileset.hpp"
#include "layer.hpp"

class Map
{
private:
    unsigned int width;
    unsigned int height;
    unsigned int tile_width;
    unsigned int tile_height;

    const char *file_path;
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> *root_node = NULL;

    void load_xml_document();
    int get_integer_attribute(const char *, int);
    void initialize_tilesets();
    void initialize_layers();

    std::list<Tileset*> tilesets;

    // TODO: Make sure all layers are sorted according to their ID
    std::list<Layer*> layers;

public:
    /*
     *   A map is initialized with a width, height,
     *   tile_width and tile_height
     */
    Map(const char *);
    sf::Sprite* get_sprite(int);
    sf::Sprite* get_sprite_at(int, int);
    static Map load_map(const char *file_path);

    unsigned int get_width() { return this->width; }
    unsigned int get_height() { return this->height; }
    unsigned int get_tile_width() { return this->tile_width; }
    unsigned int get_tile_height() { return this->tile_height; }
};