#include "textures.hpp"

sf::Texture grass_texture;
sf::Sprite grass_sprite;

void load_texture(sf::Texture *texture, sf::Sprite *sprite, char *texture_path)
{
    if (!texture->loadFromFile(texture_path, sf::IntRect(0, 0, 16, 16)))
    {
        std::cout << "Error loading texture from " << texture_path << std::endl;
    }
    sprite->setTexture(*texture);
}

void init_textures()
{
    load_texture(&grass_texture, &grass_sprite, "Assets/Terrain/grass_tileset_16x16.png");
}

sf::Sprite get_grass_sprite()
{
    return grass_sprite;
}