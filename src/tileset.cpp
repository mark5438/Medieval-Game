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

    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            sf::Sprite *sprite = new sf::Sprite();
            sprite->setTexture(this->texture);
            sprite->setTextureRect(sf::IntRect(j * this->tile_width, i * this->tile_height, tile_width, tile_height));
            sprites.push_back(sprite);
        }
    }
}

sf::Sprite *Tileset::get_sprite(int n)
{
    if (this->firstgid <= n < this->firstgid + this->sprites.size())
    {
        std::list<sf::Sprite *>::iterator l_front = this->sprites.begin();
        std::advance(l_front, n - this->firstgid);
        return l_front.operator*();
    }
    else
    {
        return NULL;
    }
}