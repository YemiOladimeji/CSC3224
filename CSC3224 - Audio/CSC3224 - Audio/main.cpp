#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
	sf::Music music;
	sf::RenderWindow window(sf::VideoMode(400, 400), "Best Girl Simulator 2017");
	sf::Event event;

	music.openFromFile("Music\\Rem Voice Remix - Re-Zero.flac"); //Load in music file to play as BGM
	music.play(); //Play music

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