#include <SFML/Window.hpp>
#include <iostream>

using namespace std;

int main() {
	sf::Window window(sf::VideoMode(600, 600), "Best Girl Simulator 2017");
	sf::Event event;

	while (window.isOpen()) { //Open window
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}
	return 0; 
}