#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "AudioControl.h"

using namespace std;

int main() {
	sf::RenderWindow window(sf::VideoMode(400, 400), "Best Girl Simulator 2017");
	sf::Event event;
	AudioControl aC;

	aC.loadBGM("Music\\Rem Voice Remix - Re-Zero.flac");

	while(window.isOpen()){ //Open window
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear(sf::Color::White);
		window.display();
	}
	return 0;
}