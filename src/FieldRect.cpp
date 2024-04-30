#include "headers/FieldRect.h"



FieldRect::FieldRect(f_type _r_type, turn_type _turn): rect_type(_r_type), turn_side(_turn) {}


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

std::unique_ptr<sf::Sprite> FieldRect::getShape() const
{
	return std::make_unique<sf::Sprite>(this->rect);
}


void FieldRect::setType(f_type _type)
{
	this->rect_type = _type;
}

void FieldRect::setTurnType(turn_type _turn)
{
	this->turn_side = _turn;
}

void FieldRect::setTexture(std::shared_ptr<sf::Texture> _texture, float scale_x, float scale_y)
{
	this->rect.setTexture(*_texture);
	this->rect.setScale(scale_x / _texture->getSize().x, scale_y / _texture->getSize().y);
}

void FieldRect::setPos(sf::Vector2f _newPos)
{
	this->rect.setPosition(_newPos);
}
