#include "GUI.h"

GUI::GUI()
{

}

GUI::GUI(sf::Vector2f dimensions, int padding, bool horizontal, GUIStyle &style, vector<pair<string, string>> entries)
{
	visible = false;
	this->horizontal = horizontal;
	this->style = style;
	this->dimensions = dimensions;
	this->padding = padding;


	sf::RectangleShape shape;
	shape.setSize(dimensions);
	shape.setFillColor(style.bodyCol);
	shape.setOutlineThickness(-style.borderSize);
	shape.setOutlineColor(style.borderCol);

	for (auto entry : entries)
	{
		sf::Text text;
		text.setString(entry.first);
		text.setFont(*style.font);
		text.setFillColor(style.textCol);
		text.setOutlineColor(style.textCol);
		text.setCharacterSize(dimensions.y - style.borderSize - padding);

		this->entries.push_back(GUIEntry(entry.second, shape, text));
	}
}

sf::Vector2f GUI::getSize()
{
	return sf::Vector2f(this->dimensions.x, this->dimensions.y*this->entries.size());
}

int GUI::getEntry(const sf::Vector2f mousePos)
{
	if (entries.size() == 0) {
		return -1;
	}
	if (!this->visible) {
		return -1;
	}
	for (int i = 0; i < this->entries.size(); ++i)
	{
		sf::Vector2f point = mousePos;
		point += this->entries[i].shape.getOrigin();
		point -= this->entries[i].shape.getPosition();

		if (point.x < 0 || point.x > this->entries[i].shape.getScale().x*this->dimensions.x) {
			continue;
		}
		if (point.y < 0 || point.y > this->entries[i].shape.getScale().y*this->dimensions.y) {
			continue;
		}
		return i;
	}

	return -1;
}

void GUI::setEntryText(int entry, string text)
{
	if (entry >= entries.size() || entry < 0) {
		return;
	}
	entries[entry].text.setString(text);

	return;
}

void GUI::setDimensions(sf::Vector2f dimensions)
{
	this->dimensions = dimensions;

	for (auto &entry : entries)
	{
		entry.shape.setSize(dimensions);
		entry.text.setCharacterSize(dimensions.y - style.borderSize - padding);
	}

	return;
}

void GUI::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (!visible) {
		return;
	}
	for (auto entry : this->entries)
	{
		target.draw(entry.shape);
		target.draw(entry.text);
	}
	return;
}

void GUI::show()
{
	sf::Vector2f offset(0.0f, 0.0f);

	this->visible = true;

	for (auto& entry : this->entries)
	{
		sf::Vector2f origin = this->getOrigin();
		origin -= offset;
		entry.shape.setOrigin(origin);
		entry.text.setOrigin(origin);

		entry.shape.setPosition(this->getPosition());
		entry.text.setPosition(this->getPosition());

		if (this->horizontal) {
			offset.x += this->dimensions.x;
		}
		else {
			offset.y += this->dimensions.y;
		}
	}
	return;
}

void GUI::hide()
{
	this->visible = false;

	return;
}

void GUI::highlight(const int entry)
{
	for (int i = 0; i < entries.size(); ++i)
	{
		if (i == entry)
		{
			entries[i].shape.setFillColor(style.bodyHighlightCol);
			entries[i].shape.setOutlineColor(style.borderHighlightCol);
			entries[i].text.setFillColor(style.textHighlightCol);
			entries[i].text.setOutlineColor(style.textHighlightCol);
		}
		else
		{
			entries[i].shape.setFillColor(style.bodyCol);
			entries[i].shape.setOutlineColor(style.borderCol);
			entries[i].text.setFillColor(style.textCol);
			entries[i].text.setOutlineColor(style.textHighlightCol);
		}
	}

	return;
}

string GUI::activate(const int entry)
{
	if (entry == -1) {
		return "null";
	}
	else 
	{
		return entries[entry].message;
	}

}

string GUI::activate(const sf::Vector2f mousePos)
{
	int entry = this->getEntry(mousePos);
	return this->activate(entry);
}
