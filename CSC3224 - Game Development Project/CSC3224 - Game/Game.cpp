#include <Audio.h>
#include <Graphics.h>
#include <HumanInterface.h>


class Game {
public:
	Game(); //Default constructor
	~Game() {}; //Destructor
	void run();

private:
	void handleEvents();
	void update();
	void render();
	sf::RenderWindow renderWindow;
	Graphics graphics;
	HumanInterface hI;
};

Game::Game() : renderWindow(sf::VideoMode(720, 480), "CSC3224 - GameDev Project") {
	sf::CircleShape player = graphics.textureCircle("Images\\emil-head.png", 50);
	player.setPosition(360, 240);
}

void Game::run() {
	while (renderWindow.isOpen()) {
		handleEvents();
		update();
		render();
	}
}

void Game::handleEvents() {
	sf::Event event;
	while (renderWindow.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::KeyPressed:
			hI.handleInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			hI.handleInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			renderWindow.close();
			break;
		}
	}
}

void Game::update() {
	sf::Vector2f movement(0, 0);
	if (hI.handleInput) {

	}
}

/*int main() {

	
	sf::Clock clock;




	while (renderWindow.isOpen()){
		while (renderWindow.pollEvent(event)) {
		
			clock.restart();
			renderWindow.clear();
			renderWindow.draw(c);
			renderWindow.display();
		}
	}
}*/