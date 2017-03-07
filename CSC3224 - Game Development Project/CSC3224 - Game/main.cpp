#include "SFML\Graphics.hpp"

int main() {
	sf::RenderWindow renderWindow(sf::VideoMode(720, 480), "CSC3224 - GameDev Project");
	sf::Event event;

	while (renderWindow.isOpen()){
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed) {
				renderWindow.close();
			}
			renderWindow.clear();
			renderWindow.display();
		}
	}
}