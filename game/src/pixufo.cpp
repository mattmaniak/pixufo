#include "pixufo.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "PixUfo");
    sf::Texture texture;

    if(!texture.loadFromFile("game/gfx/ufo.png"))
	{
		exit(1);
	}
	sf::Sprite ufo(texture);

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		window.draw(ufo);
		window.display();
	}
}
