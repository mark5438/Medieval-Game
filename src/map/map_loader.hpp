#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include <rapidxml.hpp>

#include "../graphics/tileset.hpp"
#include "layer.hpp"
#include "../npcs/npc.hpp"

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
    void initialize_npc_layer(rapidxml::xml_node<> *);
    sf::Sprite *get_sprite_at(Layer*, int, int);
    void draw_environment();
    void draw_layer(Layer*);
    void draw_npcs();
    void draw_npc(NPC*);
    void draw_sprite_at(sf::Sprite*, int, int);

    std::list<Tileset *> tilesets;

    // TODO: Make sure all layers are sorted according to their ID
    std::list<Layer *> layers;
    std::list<NPC *> npcs;
    std::list<char *> npcs_sources;

    sf::RenderWindow * window;

public:
    /*
     *   A map is initialized with a width, height,
     *   tile_width and tile_height
     */
    Map(const char *);
    sf::Sprite *get_sprite(int);
    static Map load_map(const char *file_path);

    unsigned int get_width() { return this->width; }
    unsigned int get_height() { return this->height; }
    unsigned int get_tile_width() { return this->tile_width; }
    unsigned int get_tile_height() { return this->tile_height; }

    void set_window(sf::RenderWindow * window) { this->window = window; }

    void draw_map();
};