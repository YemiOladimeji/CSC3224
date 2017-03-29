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
	Audio audio;
	HumanInterface hI;

	void handleEvents();
	void update();
	void render();
};

Game::Game() : renderWindow(sf::VideoMode(720, 480), "CSC3224 - GameDev Project") {
	audio.loadBGM("Audio Files\\Rem Voice Remix - Re-Zero.flac");
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
	if (hI.moveUp) {
		movement.y -= 0.01;
	}
	if (hI.moveDown){
		movement.y += 0.01;
	}
	if (hI.moveLeft) {
		movement.x -= 0.01;
	}
	if (hI.moveRight) {
		movement.x += 0.01;
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