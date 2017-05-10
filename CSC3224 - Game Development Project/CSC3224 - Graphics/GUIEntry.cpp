#include "GUIEntry.h"

GUIEntry::GUIEntry()
{

}

GUIEntry::GUIEntry(const string & message, sf::RectangleShape shape, sf::Text text)
{
	this->message = message;
	this->shape = shape;
	this->text = text;
}
