#include "Entity.h"
#include "Vector3D.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SFML\Graphics.hpp"

using namespace std;

//randomly generate positions for entities
//assign those positions to the entities <- vector data may possibly be getting lost, due to no proper "setPosition" function, needs checking
//push those entities onto the vector <- using two for loops may have meant that the elements in the vector only existed in the scope of that loop and not globally
//use previously written functions

int main() {

	vector<Entity> entities;
	int entNo, ab;

	sf::RenderWindow window(sf::VideoMode(400,400), "CSC3222 - Gaming Simulations Coursework");
	sf::RectangleShape frame;
	sf::Texture texture;

	texture.loadFromFile("Images\CSC3222 Coursework.bmp");
	frame.setTexture(&texture);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			window.clear();
			window.draw(frame);
			window.display();
		}
	}
	return 0;
}