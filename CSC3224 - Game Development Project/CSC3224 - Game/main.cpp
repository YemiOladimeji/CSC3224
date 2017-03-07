#include "SFML\Graphics.hpp"

int main() {
	sf::RenderWindow renderWindow(sf::VideoMode(720, 480), "CSC3224 - GameDev Project");
	sf::Event event;
	sf::Clock clock;

	while (renderWindow.isOpen()){
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed) {
				renderWindow.close();
			}

			clock.restart();
			renderWindow.clear();
			renderWindow.display();
		}
	}
}