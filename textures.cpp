#include "textures.hpp"

sf::Sprite grass_sprite;

void load_texture(sf::Sprite *sprite, char *texture_path)
{
    // Isn't freed until program is closed
    sf::Texture * texture = (sf::Texture*) malloc(sizeof(sf::Texture));
    if (!texture->loadFromFile(texture_path, sf::IntRect(GRASS1_NORTHWEST_INNER_CORNER)))
    {
        std::cout << "Error loading texture from " << texture_path << std::endl;
    }
    sprite->setTexture(*texture);
    sprite->setScale(10, 10);
}

void init_textures()
{
    load_texture(&grass_sprite, "Assets/Terrain/grass_tileset_16x16.png");
}

sf::Sprite get_grass_sprite()
{
    return grass_sprite;
}