#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main() {
	sf::Music music;
	sf::RenderWindow window(sf::VideoMode(400, 400), "Best Girl Simulator 2017");
	sf::Event event;

	if (!music.openFromFile("Music\\Rem Voice Remix - Re-Zero.flac")) {
		cout << "Music file could not be located.";
	}
	else {
		music.play();
	}

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