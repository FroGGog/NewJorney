#include "headers/Turret.h"


Turret::Turret(sf::Texture* _texture)
{
	this->sprite.setTexture(*_texture);

	this->sprite.setPosition(sf::Vector2f{ 100, 100 });

	this->attackSpeed = 1.f;
	this->rotationSpeed = 0.89f;


}

void Turret::update()
{
	this->updateRotation();

}

void Turret::render(sf::RenderTarget& target)
{	
	target.draw(this->sprite);
}

void Turret::updateRotation()
{
	this->sprite.rotate(15.f);
}
