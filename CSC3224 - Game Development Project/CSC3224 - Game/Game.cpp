#include <BGM.h>
#include <SoundFX.h>
#include <Texture.h>
#include <Circle.h>
#include <Rectangle.h>
#include <HumanInterface.h>
#include <Physics.h>

class Game {
public:
	Game(); //Default constructor
	~Game() {}; //Destructor
	void run(); //Function to run the game

private:
	BGM bgm;
	Texture txMan;
	SoundFX sfxMan;
	Circle cirMan;
	Rectangle recMan;
	HumanInterface hI;

	sf::RenderWindow renderWindow;
	sf::CircleShape circle;
	sf::RectangleShape rect;
	sf::Sprite bg;

	void handleEvents();
	void update();
	void render();
	void loadTextures();
	void loadSFX();
	void createCircles();
	void createRectangles();
};

Game::Game() : renderWindow(sf::VideoMode(720, 480), "CSC3224 - GameDev Project") 
{
	this->bgm.loadBGM("Audio Files\\emil_theme.flac");

	this->loadTextures();
	this->bg.setTexture(this->txMan.getTexRef("background"));
	this->bg.setPosition(0,0);

	this->createCircles();
	this->createRectangles();

	this->circle = this->cirMan.getCircleRef("player");
	this->circle.setTexture(&this->txMan.getTexRef("playerTex"));
	this->circle.setOrigin(circle.getRadius(), circle.getRadius());
	this->circle.setPosition(360, 240);

	this->rect = this->recMan.getRectRef("platform");
	this->rect.setTexture(&this->txMan.getTexRef("platformTex"));
	this->rect.setOrigin(rect.getSize().x/2, rect.getSize().y/2);
	this->rect.setPosition(360, 440);
}

void Game::run() 
{
	sf::Clock clock;
	while (renderWindow.isOpen()) {
		sf::Time elapsed = clock.restart();
		handleEvents();
		update();
		render();
	}
}

void Game::handleEvents() 
{
	sf::Event event;
	while (renderWindow.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::KeyPressed:
			hI.handleInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			hI.handleInput(event.key.code, false);
			hI.jumping = false;
			break;
		case sf::Event::Closed:
			renderWindow.close();
			break;
		}
	}
}

void Game::update() 
{
	const float gravity = 0.05f;
	sf::Vector2f velocity(0, 0);

	if (hI.moveUp) 
	{

	}
	if (hI.moveDown)
	{
		
	}
	if (hI.moveLeft) 
	{
		velocity.x -= (float)0.05;
		circle.rotate((float)-0.07);
	}
	if (hI.moveRight) 
	{
		velocity.x += (float)0.05;
		circle.rotate((float)0.07);
	}

	if (circle.getPosition().y + circle.getRadius() < rect.getPosition().y || velocity.y < 0)
	{
		velocity.y += gravity;
	}
	else {
		circle.setPosition(circle.getPosition().x, rect.getPosition().y - circle.getRadius());
		velocity.y = 0;
	}

	circle.move(velocity); 
}

void Game::render() 
{
	renderWindow.clear();
	renderWindow.draw(bg);
	renderWindow.draw(rect);
	renderWindow.draw(circle);
	renderWindow.display();
}

void Game::loadTextures() 
{
	txMan.loadTexture("background","Images\\leaf.png");
	txMan.loadTexture("playerTex","Images\\emil-head.png");
	txMan.loadTexture("platformTex","Images\\girder.png");
}

void Game::loadSFX() 
{

}

void Game::createCircles() 
{
	cirMan.createCircle("player", 50);
}

void Game::createRectangles() 
{
	recMan.createRectangle("platform", sf::Vector2f(350, 60));
}

int main() 
{
	Game game;
	game.run();

	return 0;
}