#include <SFML/Graphics.hpp>



int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "CSC3222 - Gaming Simulations Coursework");
	sf::Texture mapTex;
	sf::Sprite chizu;

	//Load the map and set its position/scale
	mapTex.loadFromFile("Resources\\CSC3222 Coursework.bmp");
	chizu.setTexture(mapTex);
	chizu.setOrigin(10,10);
	chizu.setPosition(window.getSize().x/2, window.getSize().y/2);
	chizu.scale(30,30);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) 
			{
			window.close();
			}
			else if (event.type = sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::K) {
					//loadSoldiers(some call to entity class);
				}
			}
		}
		window.clear();
		window.draw(chizu);
		window.display();
	}
	return 0;
}