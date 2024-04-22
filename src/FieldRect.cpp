#include "headers/FieldRect.h"



FieldRect::FieldRect(sf::RectangleShape _rect, f_type _r_type): rect(_rect), rect_type(_r_type) {}

FieldRect::f_type FieldRect::getType() const
{
	return this->rect_type;
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
