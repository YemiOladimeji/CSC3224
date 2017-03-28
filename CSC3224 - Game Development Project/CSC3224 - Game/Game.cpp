#include <Audio.h>
#include <Graphics.h>
#include <HumanInterface.h>

class Game {
public:
	Game(); //Default constructor
	~Game() {}; //Destructor
	void run();

private:
	sf::RenderWindow renderWindow;
	sf::CircleShape player;
	Graphics graphics;
	//HumanInterface hI;
	bool movingLeft, movingRight, movingUp, movingDown;

	void handleEvents();
	void update();
	void render();
	void handleInput(sf::Keyboard::Key key, bool isPressed);

};

Game::Game() : renderWindow(sf::VideoMode(720, 480), "CSC3224 - GameDev Project") {
	player = graphics.textureCircle("Images\\emil-head.png", 50);
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
			//hI.handleInput(event.key.code, true);
			handleInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			//hI.handleInput(event.key.code, false);
			handleInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			renderWindow.close();
			break;
		}
	}
}

void Game::handleInput(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::W) {
		movingUp = isPressed;
	}
	else if (key == sf::Keyboard::A) {
		movingLeft = isPressed;
	}
	else if (key == sf::Keyboard::S) {
		movingDown = isPressed;
	}
	else if (key == sf::Keyboard::D) {
		movingRight = isPressed;
	}
}

void Game::update() {
	sf::Vector2f movement(0, 0);
	/*if (hI.movingUp(true)) {
		movement.y -= 20;
	}
	if (hI.movingDown(true)){
		movement.y += 20;
	}
	if (hI.movingLeft(true)) {
		movement.x -= 20;
	}
	if (hI.movingRight(true)) {
		movement.x += 20;
	}*/
	if (movingUp) {
		movement.y -= 0.01;
	}
	player.move(movement);
}

void Game::render() {
	renderWindow.clear();
	renderWindow.draw(player);
	renderWindow.display();
}

int main() {
	Game game;
	game.run();

	return 0;
}