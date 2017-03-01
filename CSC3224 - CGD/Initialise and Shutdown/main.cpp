#include <SFML/Window.hpp>
#include <iostream>

using namespace std;

int main() {
	sf::Window window(sf::VideoMode(720, 480), "CSC3224 - Game Development Project");
	sf::Event event;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		//Game loop will go here
	}
	return 0;
}