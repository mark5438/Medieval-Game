#include "tileset.hpp"

Tileset::Tileset(char *file_path, int firstgid)
{
    strcpy(this->file_path, file_path);
    this->firstgid = firstgid;
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
    this->image_width = atoi(image_node->first_attribute("width", 5)->value());
    this->image_height = atoi(image_node->first_attribute("height", 6)->value());

    this->load_image();
    this->read_tiles();
}

void Tileset::load_xml_document()
{
    char path_buf[256];
    strcpy(path_buf, "Tiled/");
    strcat(path_buf, file_path);

    std::ifstream map_file(path_buf);
    std::vector<char> buffer((std::istreambuf_iterator<char>(map_file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');
    this->doc.parse<0>(&buffer[0]);
    this->root_node = doc.first_node("tileset");
}

int Tileset::get_integer_attribute(const char *attribute, int size)
{
    return atoi(this->root_node->first_attribute(attribute, size)->value());
}

void Tileset::load_image()
{
    int rows = this->tile_count / this->columns;

    char path_buf[256];
    strcpy(path_buf, "Assets/");
    strcat(path_buf, this->image_file_path);

    if (!this->texture.loadFromFile(path_buf))
    {
        std::cout << "Error loading texture from " << path_buf << std::endl;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            sf::Sprite *sprite = new sf::Sprite();
            sprite->setTexture(this->texture);
            sprite->setTextureRect(sf::IntRect(j * this->tile_width, i * this->tile_height, tile_width, tile_height));
            sprites.push_back(sprite);
        }
    }
}

void Tileset::read_tiles()
{
    /*
     *   For whatever reason 2 xml files can not be open at once.
     *   Therefore i must read the xml files once more
     */
    this->load_xml_document();
    rapidxml::xml_node<> *node = this->root_node->first_node("tile");
    for (rapidxml::xml_node<> *node = this->root_node->first_node("tile"); node; node = node->next_sibling("tile"))
    {
        int id = atoi(node->first_attribute("id")->value());

        // Check for animations
        // There can only be one animation per tile, so no loop is needed
        rapidxml::xml_node<> *animation_node = node->first_node("animation");
        if (animation_node)
        {
            load_animation(id, animation_node);
        }
    }
}

void Tileset::load_animation(int tileid, rapidxml::xml_node<> *node)
{
    t_animation animation;
    animation.tile_id = tileid;
    animation.duration = 0;
    for (rapidxml::xml_node<> *frame_node = node->first_node("frame"); frame_node; frame_node = frame_node->next_sibling("frame"))
    {
        t_frame frame;
        frame.tile_id = atoi(frame_node->first_attribute("tileid")->value());
        frame.duration = atoi(frame_node->first_attribute("duration")->value());
        animation.duration += frame.duration;
        animation.frames.push_back(frame);
    }
    this->animations.push_back(animation);
}

t_animation *Tileset::get_animation_tile(int tileid)
{
    for (std::list<t_animation>::iterator it = this->animations.begin(); it != this->animations.end(); ++it)
    {
        if (it.operator*().tile_id == tileid)
            return &it.operator*();
    }
    return NULL;
}

sf::Sprite *Tileset::get_sprite_at_index(int index)
{
    std::list<sf::Sprite *>::iterator l_front = this->sprites.begin();
    std::advance(l_front, index);
    return l_front.operator*();
}

sf::Sprite *Tileset::get_animation_sprite_after(t_animation *animation, int ms)
{
    int animation_time = ms % animation->duration;
    int counted_time = 0;
    for (std::list<t_frame>::iterator it = animation->frames.begin(); it != animation->frames.end(); ++it)
    {
        counted_time += it.operator*().duration;
        if (counted_time >= animation_time)
        {
            return this->get_sprite_at_index(it.operator*().tile_id);
        }
    }
    return NULL;
}

sf::Sprite *Tileset::get_sprite(int n)
{
    if (this->firstgid <= n && n < this->firstgid + this->sprites.size())
    {
        t_animation *animation_tile = get_animation_tile(n - this->firstgid);
        if (animation_tile)
            return this->get_animation_sprite_after(animation_tile, get_elapsed_time());
        else
            return this->get_sprite_at_index(n - this->firstgid);
    }
    else
    {
        return NULL;
    }
}