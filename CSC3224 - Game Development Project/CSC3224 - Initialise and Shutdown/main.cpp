#include <SFML/Window.hpp>
#include <iostream>
#include <AudioControl.h>

using namespace std;

int main() {
	sf::Window window(sf::VideoMode(600, 600), "Best Girl Simulator 2017");
	sf::Event event;
	AudioControl aC;

	while (window.isOpen()) { //Open window
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		aC.loadBGM("Music\\Rem Voice Remix - Re-Zero.flac");
	}
	return 0; 
}