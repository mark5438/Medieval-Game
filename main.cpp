#include <SFML/Graphics.hpp>

#include "textures.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Medieval Game");
    init_textures();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        window.draw(get_grass_sprite());

        window.display();
    }

    return 0;
}