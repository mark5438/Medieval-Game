#include "map_loader.hpp"
#include "../camera/camera.hpp"

Map::Map(const char *file_path)
{
    this->file_path = file_path;
    this->load_xml_document();

    this->width = this->get_integer_attribute("width", 5);
    this->height = this->get_integer_attribute("height", 6);
    this->tile_width = this->get_integer_attribute("tilewidth", 9);
    this->tile_height = this->get_integer_attribute("tileheight", 10);

    this->initialize_tilesets();
    this->initialize_layers();

    this->doc.clear();

    // TODO: Find better way
    // For whatever reason, if I parse an xml file while another file is open,
    // The previous files data is corrupted
    for (std::list<Tileset *>::iterator it = tilesets.begin(); it != tilesets.end(); ++it)
    {
        it.operator*()->init();
    }
}

void Map::initialize_tilesets()
{
    for (rapidxml::xml_node<> *child = this->root_node->first_node("tileset"); child != NULL; child = child->next_sibling("tileset"))
    {
        char *tileset_source = child->first_attribute("source")->value();
        int firstgid = atoi(child->first_attribute("firstgid")->value());
        this->tilesets.push_back(new Tileset(tileset_source, firstgid));
    }
}

void Map::initialize_layers()
{
    rapidxml::xml_node<> *layer = this->root_node->first_node("layer");
    while (layer)
    {
        if (!strcmp(layer->first_attribute("name")->value(), "NPCS"))
            initialize_npc_layer(layer);
        else
        {
            this->layers.push_back(new Layer(layer));
        }
        layer = layer->next_sibling("layer");
    }
}

void Map::initialize_npc_layer(rapidxml::xml_node<> *npc_layer)
{
    for (rapidxml::xml_node<> *chunk = npc_layer->first_node("data")->first_node("chunk"); chunk; chunk = chunk->next_sibling("chunk"))
    {
        int start_x = atoi(chunk->first_attribute("x")->value());
        int start_y = atoi(chunk->first_attribute("y")->value());
        Chunk::add_npcs_to_list(&this->npcs, chunk, start_x, start_y);
    }
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

sf::Sprite *Map::get_sprite(int n)
{
    if (n != 0)
        for (std::list<Tileset *>::iterator it = this->tilesets.begin(); it != this->tilesets.end(); ++it)
        {
            sf::Sprite *sprite = it.operator*()->get_sprite(n);
            if (sprite)
                return sprite;
        }
    return NULL;
}

sf::Sprite *Map::get_sprite_at(Layer *l, int x, int y)
{
    return this->get_sprite(l->get_texture_at(x, y));
}

void Map::draw_sprite_at(sf::Sprite *sprite, int x, int y)
{
    sprite->setScale(get_camera_zoom(), get_camera_zoom());
    sprite->setPosition(x* get_camera_zoom() - get_camera_x(), y * get_camera_zoom() - get_camera_y());
    this->window->draw(*sprite);
}

void Map::draw_layer(Layer *l)
{
    for (int i = 0; i < this->get_height(); i++)
    {
        for (int j = 0; j < this->get_width(); j++)
        {
            sf::Sprite *sprite = this->get_sprite_at(l, j, i);
            if (sprite)
            {
                this->draw_sprite_at(sprite, j * 16, i * 16);
            }
        }
    }
}

void Map::draw_environment()
{
    for (std::list<Layer *>::iterator it = this->layers.begin(); it != this->layers.end(); ++it)
        this->draw_layer(it.operator*());
}

void Map::draw_npc(NPC *npc)
{
    sf::Sprite *sprite = this->get_sprite(npc->get_sprite_id());
    this->draw_sprite_at(sprite, npc->get_x() * 16, npc->get_y() * 16);
}

void Map::draw_npcs()
{
    for (std::list<NPC *>::iterator it = this->npcs.begin(); it != this->npcs.end(); ++it)
        this->draw_npc(it.operator*());
}

void Map::draw_map()
{
    draw_environment();
    draw_npcs();
}