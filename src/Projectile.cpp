#include "headers/Projectile.h"


Projectile::Projectile(float r_degrees, sf::Vector2f start_pos, sf::Texture* _texture) : rotation(r_degrees)
{
	
	this->sprite.setTexture(*_texture);
	this->sprite.setPosition(start_pos);
	this->sprite.setRotation(this->rotation);

	this->speed = 15.f;
	

	this->velocity.x = std::cos(this->rotation * 3.14 / 180.0) * speed;
	this->velocity.y = std::sin(this->rotation * 3.14 / 180.0) * speed;

}

void Projectile::setScale(float x, float y)
{
	this->sprite.setScale(x / 5, y / 5);
}

void Projectile::update()
{
	this->sprite.move(this->velocity);

}

void Projectile::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

