#include "SFML\Graphics.hpp"
#include <Audio.h>

int main() {
	sf::RenderWindow renderWindow(sf::VideoMode(720, 480), "CSC3224 - GameDev Project");
	sf::Event event;
	sf::Clock clock;
	Audio audio;

	audio.loadBGM("Audio Files/MovementProposition.wav");

	while (renderWindow.isOpen()){
		while (renderWindow.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape) {
						renderWindow.close();
						break;
					}
				case sf::Event::Closed:
					renderWindow.close();
			}
			clock.restart();
			renderWindow.clear();
			renderWindow.display();
		}
	}
}