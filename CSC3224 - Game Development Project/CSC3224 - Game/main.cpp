#include "SFML\Graphics.hpp"
#include <Audio.h>
#include <Graphics.h>

int main() {
	sf::RenderWindow renderWindow(sf::VideoMode(720, 480), "CSC3224 - GameDev Project");
	sf::Event event;
	sf::Clock clock;
	Audio audio;
	Graphics graphics;

	//audio.loadBGM("Audio Files\\Rem Voice Remix - Re-Zero.flac");
	
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
			renderWindow.draw(graphics.createBGMSprite("Images\\Rem_Anime.png"));
			renderWindow.draw(graphics.clampSprite(graphics.createBGMSprite("Images\\Chaos.gif"), 0, 0, 235, 41));
			renderWindow.display();
		}
	}
}