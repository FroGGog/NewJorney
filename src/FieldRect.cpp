#include "headers/FieldRect.h"



FieldRect::FieldRect(sf::RectangleShape _rect, f_type _r_type, turn_type _turn): rect(_rect), rect_type(_r_type), turn_side(_turn) {}


FieldRect::f_type FieldRect::getType() const
{
	return this->rect_type;
}

FieldRect::turn_type FieldRect::getTurn() const
{
	return this->turn_side;
}

sf::FloatRect FieldRect::getGBounds() const
{
	return this->rect.getGlobalBounds();
}

sf::RectangleShape FieldRect::getShape() const
{
	return this->rect;
}


void FieldRect::setType(f_type _type)
{
	this->rect_type = _type;
}

void FieldRect::setColor(sf::Color _color)
{
	this->rect.setFillColor(_color);
}

void FieldRect::setTurnType(turn_type _turn)
{
	this->turn_side = _turn;
}
