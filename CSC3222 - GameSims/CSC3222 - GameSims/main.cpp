//Include the SFML Graphics module.
#include "SFML\Graphics.hpp"

int main() {

	sf::RenderWindow window(sf::VideoMode(600, 600), "CSC3222 - Gaming Simulaions"); //Initialise the 
	sf::Sprite bg;
	sf::Texture mapTexture;

	mapTexture.loadFromFile("Resources\\CSC3222 Coursework.bmp");
	bg.setTexture(mapTexture);
	bg.setOrigin(10,10);
	bg.setPosition(window.getSize().x/2, window.getSize().y/2);
	bg.scale(30,30);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}
			else if (event.type == event.KeyPressed) {
				if (event.key.code == sf::Keyboard::K) {
					//loadSoldiers();
				}
			}
		}
		window.clear();
		window.draw(bg);
		window.display();
	}

}