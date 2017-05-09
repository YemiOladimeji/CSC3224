//Include the SFML Graphics module.
#include "SFML\Graphics.hpp"

int main() {

	sf::RenderWindow window(sf::VideoMode(600, 600), "CSC3222 - Gaming Simulaions"); //Initialise the window
	sf::Sprite bg; //Instantiate the Sprite object
	sf::Texture mapTexture; //Instantiate the Texture object

	mapTexture.loadFromFile("Resources\\CSC3222 Coursework.bmp"); //Load an image as a texture file
	bg.setTexture(mapTexture); //Set the Sprite's texture
	bg.setOrigin(10,10); //Set the origin of the Sprite
	bg.setPosition(window.getSize().x/2, window.getSize().y/2); //Set the position of the Sprite
	bg.scale(30,30); //Scale the Sprite up to the size of the Window

	//While the Window is open
	while (window.isOpen()) 
	{
		sf::Event event; //Instantiate an Event object

		while (window.pollEvent(event)) //While the window is listening for Events
		{
			if (event.type == event.Closed) //If the close button is pressed
			{
				window.close(); //Close the Window
			}
			else if (event.type == event.KeyPressed) //If a KeyPressed event is triggered
			{
				if (event.key.code == sf::Keyboard::K) //If the KeyPressed was the 'K' key
				{
					//loadSoldiers(); //Call the loadSoldiers function
				}
			}
		}
		window.clear(); //Clear the window of any existing items
		window.draw(bg); //Draw the background map
		window.display(); //Display what is in the current buffer
	}

}