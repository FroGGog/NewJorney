#include "headers/Projectile.h"


void Projectile::updateCollision()
{


}

bool Projectile::updateBorderCollision()
{
	if (this->sprite.getPosition().x > 1400 || this->sprite.getPosition().x < 0) {
		this->state = projectile_state::OUT;
		return true;
	}
	else if (this->sprite.getPosition().y > 1000 || this->sprite.getPosition().y < 0) {
		this->state = projectile_state::OUT;
		return true;
	}
	else {
		return false;
	}


}

Projectile::Projectile(float r_degrees, sf::Vector2f start_pos, sf::Texture* _texture) : rotation(r_degrees)
{
	
	this->sprite.setTexture(*_texture);
	this->sprite.setPosition(start_pos);
	this->sprite.setRotation(this->rotation);

	this->speed = 15.f;
	this->state = projectile_state::NONE;

	this->velocity.x = std::cos(this->rotation * 3.14 / 180.0) * speed;
	this->velocity.y = std::sin(this->rotation * 3.14 / 180.0) * speed;

}

void Projectile::setScale(float x, float y)
{
	this->sprite.setScale(x / 5, y / 5);
}

projectile_state Projectile::getState() const
{
	return this->state;
}

void Projectile::update()
{
	this->sprite.move(this->velocity);

	this->updateBorderCollision();

}

void Projectile::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

