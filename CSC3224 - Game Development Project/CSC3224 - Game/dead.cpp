#include <BGM.h>
#include <SoundFX.h>
#include <Texture.h>
#include <Circle.h>
#include <Rectangle.h>
#include <HumanInterface.h>

class Game 
{
public:
	Game(); //Default constructor
	~Game() {}; //Destructor
	void run(); //Function to run the game

private:
	sf::RenderWindow renderWindow;
	sf::CircleShape circle;
	sf::RectangleShape rect;
	sf::Sprite bg;
	sf::View view;

	BGM bgm;
	Texture txMan;
	SoundFX sfxMan;
	Circle cirMan;
	Rectangle recMan;
	HumanInterface hI;

	void handleEvents();
	void update(float deltaTime);
	void render();
	void loadTextures();
	void loadSFX();
	void createCircles();
	void createRectangles();
};

Game::Game() : renderWindow(sf::VideoMode(720, 480), "CSC3224 - GameDev Project") 
{
	this->view.setCenter(sf::Vector2f(0.0f, 0.0f));
	this->view.setSize(sf::Vector2f(720, 480));
	
	this->bgm.loadBGM("Audio Files\\emil_theme.flac");

	this->loadTextures();
	this->bg.setTexture(this->txMan.getTexRef("bgTex"));
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
	float deltaTime = 0.0f;
	sf::Clock clock;
	while (renderWindow.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		handleEvents();
		update(deltaTime);
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
			break;
		case sf::Event::Closed:
			renderWindow.close();
			break;
		}
	}
}

void Game::update(float deltaTime) 
{
	sf::Vector2f velocity(0, 0);
	float speed = 250;
	float rotation = 700;

	if (hI.moveUp) 
	{

	}
	if (hI.moveLeft) 
	{
		velocity.x -= speed * deltaTime;
		circle.rotate(-rotation * deltaTime);
	}
	if (hI.moveRight) 
	{
		velocity.x += speed * deltaTime;
		circle.rotate(rotation * deltaTime);
	}
	circle.move(velocity); 
}

void Game::render() 
{
	renderWindow.clear();
	view.setCenter(circle.getPosition());
	renderWindow.setView(view);
	renderWindow.draw(bg);
	renderWindow.draw(rect);
	renderWindow.draw(circle);
	renderWindow.display();
}

void Game::loadTextures() 
{
	txMan.loadTexture("bgTex","Images\\leaf.png");
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
	recMan.createRectangle("platform", sf::Vector2f(360, 60));
}

int main() 
{
	Game game;
	game.run();

	return 0;
}