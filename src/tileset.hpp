#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string.h>
#include <stdio.h>

#include <SFML/Graphics.hpp>

#include "rapidxml-1.13/rapidxml.hpp"

class Tileset
{
private:
    unsigned int tile_width;
    unsigned int tile_height;
    unsigned int tile_count;
    unsigned int columns;
    char* file_path;
    char* image_file_path;
    unsigned int image_width;
    unsigned int image_height;

    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> *root_node = NULL;

    void load_xml_document();
    void init();
    int get_integer_attribute(const char *, int);

    sf::Texture texture;
    std::list<sf::Sprite*> sprites;

    void load_image();

    unsigned int firstgid;

public:
    Tileset(char*, int);
};