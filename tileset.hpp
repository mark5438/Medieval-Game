#include <iostream>
#include <fstream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "rapidxml-1.13/rapidxml.hpp"

class Tileset
{
private:
    unsigned int tile_width;
    unsigned int tile_height;
    unsigned int tile_count;
    unsigned int columns;
    const char* file_path;
    const char* image_file_path;
    unsigned int image_width;
    unsigned int image_height;

    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> *root_node = NULL;

    void load_xml_document();
    void init();
    int get_integer_attribute(const char *, int);

    std::vector<sf::Texture> textures;
    std::vector<sf::Sprite> sprites;

public:
    static Tileset load_tileset(char* file_path);
};