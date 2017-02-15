#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "AudioControl.h"
#include "GraphicsControl.h"

using namespace std;

int main() {
	sf::RenderWindow window(sf::VideoMode(600, 600), "Best Girl Simulator 2017");
	sf::Event event;
	AudioControl aC;
	//GraphicsControl gC;

	aC.loadBGM("Music\\Rem Voice Remix - Re-Zero.flac");

	//Temp image loading solution
	sf::Texture img;
	if (!img.loadFromFile("Images\\PetitRemIII.png")) return 0;
	sf::Sprite sprite;
	sprite.setTexture(img);
	sprite.setOrigin(50,50);

	

	while(window.isOpen()){ //Open window
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			window.clear(sf::Color::White);
			window.draw(sprite);
			window.display();
		}
	}
	return 0;
}