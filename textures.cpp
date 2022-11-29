#include "textures.hpp"

sf::Texture textures[81];
sf::Sprite sprites[81];

void load_texture(sf::Texture * texture,  sf::Sprite *sprite, char *texture_path, int x, int y, int width, int height)
{
    if (!texture->loadFromFile(texture_path, sf::IntRect(x, y, width, height)))
    {
        std::cout << "Error loading texture from " << texture_path << std::endl;
    }
    sprite->setTexture(*texture);
    sprite->setScale(10, 10);
}

void init_textures()
{
    int tilesX = GRASS_TILESET_IMAGE_WIDTH / GRASS_TILESET_TILESIZE;
    int tilesY = GRASS_TILESET_IMAGE_HEIGHT / GRASS_TILESET_TILESIZE;
    for (int i = 0, k = 0; i < tilesY; i++)
    {
        for (int j = 0; j < tilesX; j++, k++) {
            int x = j * GRASS_TILESET_TILESIZE;
            int y = i * GRASS_TILESET_TILESIZE;
            int size = GRASS_TILESET_TILESIZE;
            std::cout << "\n\n\n\n\n";
            load_texture(&textures[k], &sprites[k], GRASS_TILESET_IMAGE_SRC, x, y, size, size);
        }
    }
}

sf::Sprite get_sprite(int sprite)
{
    return sprites[sprite];
}