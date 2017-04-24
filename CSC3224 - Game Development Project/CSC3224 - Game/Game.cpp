#include <Audio.h>
#include <Graphics.h>
#include <Texture.h>
#include <HumanInterface.h>
#include <Physics.h>

class Game {
public:
	Game(); //Default constructor
	~Game() {}; //Destructor
	void run();

private:
	Graphics player, platform, background;
	Audio audio;
	HumanInterface hI;

	sf::RenderWindow renderWindow;
	sf::CircleShape circle;
	sf::RectangleShape rect;
	sf::Sprite bg;

	void handleEvents();
	void update();
	void render();
};

Game::Game() : renderWindow(sf::VideoMode(720, 480), "CSC3224 - GameDev Project") {
	audio.loadBGM("Audio Files\\emil_theme.flac");
	bg = background.textureBG("Images\\leaf.png");
	bg.setPosition(0,0);
	circle = player.textureCircle("Images\\emil-head.png", 50);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(360, 240);
	rect = platform.textureRect("Images\\girder.png", sf::Vector2f(350, 60));
	rect.setOrigin(rect.getSize().x/2, rect.getSize().y/2);
	rect.setPosition(360, 340);
}

void Game::run() {
	sf::Clock clock;
	while (renderWindow.isOpen()) {
		sf::Time elapsed = clock.restart();
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
		movement.y -= (float)0.01;
	}
	if (hI.moveDown){
		movement.y += (float)0.01;
	}
	if (hI.moveLeft) {
		movement.x -= (float)0.01;
		circle.rotate((float)-0.05);
	}
	if (hI.moveRight) {
		movement.x += (float)0.01;
		circle.rotate((float)0.05);
	}
	circle.move(movement);
}

void Game::render() {
	renderWindow.clear();
	renderWindow.draw(bg);
	renderWindow.draw(rect);
	renderWindow.draw(circle);
	renderWindow.display();
}

int main() {
	Game game;
	game.run();

	return 0;
}