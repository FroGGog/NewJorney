#include "headers/army.h"

army::army(sf::Vector2f size, sf::Vector2f start_pos, sf::Color _color) : pos(start_pos)
{

	this->shape = new sf::RectangleShape(size);

	this->shape->setFillColor(_color);

	this->shape->setPosition(this->pos);

}

army::~army()
{
	delete this->shape;
}

void army::update()
{

}

void army::updateSurrond()
{

}

void army::render(sf::RenderTarget& target)
{
	target.draw(*this->shape);
}


