#include "headers/Turret.h"


Turret::Turret(sf::Texture* _texture)
{

	this->sprite.setTexture(*_texture);

	this->sprite.setOrigin(_texture->getSize().x / 2, _texture->getSize().y / 2);

	this->attackSpeed = 1.f;
	this->rotationSpeed = 0.89f;


}


sf::Sprite Turret::getSprite() const
{
	return this->sprite;
}

void Turret::setPos(sf::Vector2f _newPos)
{
	this->sprite.setPosition(_newPos);
}

void Turret::setScale(float x, float y)
{
	this->sprite.setScale(x, y);
}

void Turret::update(sf::Vector2f _enemyPos)
{
	sf::Vector2f distance = _enemyPos - this->sprite.getPosition();

	distance /= sqrtf(distance.x * distance.x + distance.y * distance.y);

	float angle = atan2(distance.y, distance.x);

	auto angle_degrees = angle * 180 / 3.14159f;

	this->sprite.setRotation(angle_degrees);


}

void Turret::render(sf::RenderTarget& target)
{	
	target.draw(this->sprite);
}


void Turret::updateRotation()
{

	this->sprite.rotate(2.f);
}
