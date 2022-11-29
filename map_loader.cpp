#include "map_loader.hpp"

Map::Map(const char *file_path)
{
    this->file_path = file_path;
    this->load_xml_document();

    this->width = this->get_integer_attribute("width", 5);
    this->height = this->get_integer_attribute("height", 6);
    this->tile_width = this->get_integer_attribute("tilewidth", 9);
    this->tile_height = this->get_integer_attribute("tileheight", 10);
}

void Map::load_xml_document()
{
    std::ifstream map_file(this->file_path);
    std::vector<char> buffer((std::istreambuf_iterator<char>(map_file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');
    this->doc.parse<0>(&buffer[0]);
    this->root_node = doc.first_node("map");
}

int Map::get_integer_attribute(const char* attribute, int size)
{
    return atoi(this->root_node->first_attribute(attribute, size)->value());
}

Map Map::load_map(const char *file_path)
{
    return Map(file_path);
}