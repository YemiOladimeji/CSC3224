#include <Audio.h>
#include <Graphics.h>
#include <HumanInterface.h>

int main() {
	sf::RenderWindow renderWindow(sf::VideoMode(720, 480), "CSC3224 - GameDev Project");
	sf::Event event;
	sf::Clock clock;
	//Audio audio;
	Graphics graphics;
	HumanInterface hI;

	sf::CircleShape c = graphics.textureCircle("Images\\emil-head.png", 50);

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
			hI.moveCircle(c, 5, 5);
			renderWindow.draw(c);
			renderWindow.display();
		}
	}
}