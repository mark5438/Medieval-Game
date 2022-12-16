#include "tileset.hpp"

/**
 * Construct a tileset
 *
 * @param filepath Path to the tileset xml file
 * @param firstgid The first tile id, that corresponds to the sprite this->sprites[0]
 */
Tileset::Tileset(char *file_path, int firstgid)
{
    strcpy(this->file_path, file_path);
    this->firstgid = firstgid;
}

/**
 * The tileset is initialized after, because only one xml file
 * can be loaded at once using rapidxml, so if I load the new file
 * in the constructor, the rest of the tilesets will be ignored.
 */
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

/**
 * Loads the xml document with the give file_path[] and saves the xml data to the variable
 * doc and the variable root_node
 */
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

/**
 * Get an attribute from the rootnode as integer
 *
 * @param name The attribute name
 * @param length The attribute names length
 *
 * @return The integer value of the rootnodes first attribute with the given name
 */
int Tileset::get_integer_attribute(const char *attribute, int size)
{
    return atoi(this->root_node->first_attribute(attribute, size)->value());
}

/**
 * Loads the image
 */
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

/**
 * Loop through all tiles to check if any tiles should be animated
 */
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

/**
 * Load an animation and save it to the animations list
 */
void Tileset::load_animation(int tileid, rapidxml::xml_node<> *node)
{
    this->animations.push_back(new Animation(tileid, node));
}

/**
 *  With a given tileid, the animation is returnd
 *
 * @param tileid The tileid that the animation is bound to
 *
 * @return The anitaion object
 */
Animation *Tileset::get_animation_tile(int tileid)
{
    for (std::list<Animation*>::iterator it = this->animations.begin(); it != this->animations.end(); ++it)
    {
        if (it.operator*()->get_tile_id() == tileid)
            return it.operator*();
    }
    return NULL;
}

/**
 * Get a sprite from the sprite list at a given index,
 * the first sprite being at index 0.
 *
 * @param index The index of the sprite
 *
 * @return A pointer to the sprite at the given index
 */
sf::Sprite *Tileset::get_sprite_at_index(int index)
{
    std::list<sf::Sprite *>::iterator l_front = this->sprites.begin();
    std::advance(l_front, index);
    return l_front.operator*();
}

/**
 * Get the sprite that should be displayed one the next frame.
 *
 * @param animation A pointer to an instance of the animation struct
 *
 * @return A pointer to the sprite that should be drawn
 */
sf::Sprite *Tileset::get_animation_sprite_now(Animation *animation)
{
    return this->get_sprite_at_index(animation->get_animation_sprite_id_now());
}

/**
 * Get a sprite with a given id n
 *
 * @param n The sprite id
 *
 * @return A pointer to the sprite if the id is within this tileset. NULL otherwise
 */
sf::Sprite *Tileset::get_sprite(int n)
{
    if (this->firstgid <= n && n < this->firstgid + this->sprites.size())
    {
        Animation *animation_tile = get_animation_tile(n - this->firstgid);
        if (animation_tile)
            return this->get_animation_sprite_now(animation_tile);
        else
            return this->get_sprite_at_index(n - this->firstgid);
    }
    else
    {
        return NULL;
    }
}