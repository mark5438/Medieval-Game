#include "tileset.hpp"

Tileset Tileset::load_tileset(char *file_path)
{
    Tileset tileset;
    tileset.file_path = file_path;
    tileset.init();
}

void Tileset::init()
{
    this->load_xml_document();
    this->tile_width = this->get_integer_attribute("tilewidth", 9);
    this->tile_height = this->get_integer_attribute("tileheight", 10);
    this->tile_count = this->get_integer_attribute("tilecount", 9);
    this->columns = this->get_integer_attribute("columns", 7);

    rapidxml::xml_node<> *image_node = this->root_node->first_node("image");
    this->image_file_path = image_node->first_attribute("source", 6)->value();
    this->image_width = this->get_integer_attribute("width", 5);
    this->image_height = this->get_integer_attribute("height", 6);
}

void Tileset::load_xml_document()
{
    std::ifstream map_file(this->file_path);
    std::vector<char> buffer((std::istreambuf_iterator<char>(map_file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');
    this->doc.parse<0>(&buffer[0]);
    this->root_node = doc.first_node("tileset");
}

int Tileset::get_integer_attribute(const char* attribute, int size)
{
    return atoi(this->root_node->first_attribute(attribute, size)->value());
}