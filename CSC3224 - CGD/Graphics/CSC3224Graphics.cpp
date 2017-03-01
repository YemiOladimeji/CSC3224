#include "CSC3224Graphics.h"

void CSC3224Graphics::clearWindow(sf::RenderWindow w)
{
	w.clear(sf::Color::Black);
}

void CSC3224Graphics::displayWindow(sf::RenderWindow w)
{
	w.display();
}

void CSC3224Graphics::closeWindow(sf::RenderWindow w)
{
	w.close();
}
