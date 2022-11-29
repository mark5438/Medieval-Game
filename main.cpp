#include <SFML/Graphics.hpp>

#include "src/textures.hpp"
#include "src/map_loader.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Medieval Game");
    init_textures();

    Map map = Map::load_map("Tiled/starting_map.tmx");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        window.draw(get_sprite(45));

        window.display();
    }

    return 0;
}