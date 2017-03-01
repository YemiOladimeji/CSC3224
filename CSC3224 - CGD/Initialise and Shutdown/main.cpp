#include <iostream>
#include <Audio.h>
#include <SFML\Window.hpp>

using namespace std;

Audio a;

int main() {
	sf::Window window(sf::VideoMode(720,480),"CSC3224 - Computer Games Development");

	while (window.isOpen) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			a.loadBGM("Music\\Rem Voice Remix - Re-Zero.flac");
		}
	}

	return 0;
}