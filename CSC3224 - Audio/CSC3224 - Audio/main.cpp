#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
	sf::Music music;
	sf::RenderWindow window(sf::VideoMode(400, 400), "Best Girl Simulator 2017");
	sf::Event event;
	sf::Texture texture;
	sf::Sprite sprite;

	while(window.isOpen()){ //Open window
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (!music.openFromFile("Music\\Rem Voice Remix - Re-Zero.flac"))  //Play music
				return -1;
			else {
				music.play();
			}
			/*if (!texture.loadFromFile("Images\\dance.gif"))
				return 8;
			else {
				sprite.setTexture(texture);
			}*/
			window.clear(sf::Color::Black);
			//window.draw(sprite);
			window.display();
		}
	}
	return 0;
}