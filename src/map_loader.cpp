#include "map_loader.hpp"

Map::Map(const char *file_path)
{
    this->file_path = file_path;
    this->load_xml_document();

    this->width = this->get_integer_attribute("width", 5);
    this->height = this->get_integer_attribute("height", 6);
    this->tile_width = this->get_integer_attribute("tilewidth", 9);
    this->tile_height = this->get_integer_attribute("tileheight", 10);

    this->initialize_tilesets();
}

void Map::initialize_tilesets()
{
    rapidxml::xml_node<> *tileset_node = this->root_node->first_node("tileset", 7);

    while (tileset_node)
    {
        char *tileset_source = tileset_node->first_attribute("source", 6)->value();
        unsigned int firstgid = atoi(tileset_node->first_attribute("firstgid", 8)->value());
        Tileset *tileset = new Tileset(tileset_source, firstgid);
        this->tilesets.push_back(tileset);
        tileset_node = tileset_node->next_sibling("tileset", 7);
    };
}

void Map::load_xml_document()
{
    std::ifstream map_file(this->file_path);
    std::vector<char> buffer((std::istreambuf_iterator<char>(map_file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');
    this->doc.parse<0>(&buffer[0]);
    this->root_node = doc.first_node("map");
}

int Map::get_integer_attribute(const char *attribute, int size)
{
    return atoi(this->root_node->first_attribute(attribute, size)->value());
}

Map Map::load_map(const char *file_path)
{
    return Map(file_path);
}