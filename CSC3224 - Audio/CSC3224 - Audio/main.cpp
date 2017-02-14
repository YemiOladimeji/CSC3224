#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "AudioControl.h"
#include "GraphicsControl.h"

using namespace std;

int main() {
	sf::RenderWindow window(sf::VideoMode(400, 400), "Best Girl Simulator 2017");
	sf::Event event;
	AudioControl aC;
	GraphicsControl gC;

	aC.loadBGM("Music\\Rem Voice Remix - Re-Zero.flac");
	

	while(window.isOpen()){ //Open window
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
		window.draw(gC.setSpriteTexture(gC.loadTexture("Images\\dance.gif")));
		window.display();
	}
	return 0;
}