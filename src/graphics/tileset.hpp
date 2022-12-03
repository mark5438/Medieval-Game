#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string.h>
#include <stdio.h>

#include <SFML/Graphics.hpp>

#include <rapidxml.hpp>
#include <list>

#include "../clock/clock.hpp"

typedef struct frame {
    int tile_id;
    int duration;   // ms
} t_frame;

typedef struct animation {
    int tile_id;
    int duration;
    std::list<t_frame> frames;
} t_animation;

class Tileset
{
private:
    unsigned int tile_width;
    unsigned int tile_height;
    unsigned int tile_count;
    unsigned int columns;
    char file_path[512];    // TODO: Not very efficient
    char* image_file_path;
    unsigned int image_width;
    unsigned int image_height;

    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> *root_node = NULL;

    void load_xml_document();
    int get_integer_attribute(const char *, int);

    sf::Texture texture;
    std::list<sf::Sprite*> sprites;
    std::list<t_animation> animations;

    void load_image();
    void read_tiles();
    void load_animation(int, rapidxml::xml_node<>*);
    sf::Sprite * get_animation_sprite_after(t_animation * animation, int ms);
    sf::Sprite * get_sprite_at_index(int);

    t_animation * get_animation_tile(int);

    unsigned int firstgid;

public:
    Tileset(char*, int);
    Tileset();
    ~Tileset();

    void init();
    sf::Sprite* get_sprite(int n);
};