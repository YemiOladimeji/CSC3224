#include "GUIStyle.h"

GUIStyle::GUIStyle()
{

}

GUIStyle::GUIStyle(sf::Font * font, float borderSize, sf::Color bodyCol, sf::Color borderCol, sf::Color textCol, sf::Color bodyHighlightCol, sf::Color borderHighlightCol, sf::Color textHighlightCol)
{
	this->bodyCol = bodyCol;
	this->borderCol = borderCol;
	this->textCol = textCol;
	this->bodyHighlightCol = bodyHighlightCol;
	this->borderHighlightCol = borderHighlightCol;
	this->textHighlightCol = textHighlightCol;
	this->font = font;
	this->borderSize = borderSize;
}
